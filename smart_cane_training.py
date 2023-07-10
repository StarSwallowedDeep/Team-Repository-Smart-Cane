import tensorflow as tf
import pandas as pd
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import csv

# Firebase 초기화
cred = credentials.Certificate("smartcane.json")
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://smart-23-f9ebe-default-rtdb.firebaseio.com/'
})

# 파이어베이스에서 "_User_Data"로 끝나는 모든 항목 가져오기
ref = db.reference('/')
user_data_refs = ref.order_by_key().end_at('_User_Data')

# 사용자 데이터 이름 추출
user_data_names = []
for user_data_ref in user_data_refs.get():
    user_data_name = user_data_ref.rsplit('_', 1)[1]
    user_data_names.append(user_data_name)

# 데이터 불러오기, 모델 훈련 및 예측 결과 Firebase에 저장
for user_data_name in user_data_names:
    # CSV 파일 이름
    csv_file_name = f'{user_data_name}_data.csv'

    # 데이터를 CSV 파일로 작성
    with open(csv_file_name, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)

        # CSV 파일 헤더 작성
        headers = ['초음파A', '초음파B', '적외선'] 
        writer.writerow(headers)

        # 사용자 데이터 가져오기
        user_data_ref = ref.child(user_data_name)
        user_data = user_data_ref.get()

        # 사용자 데이터를 CSV 파일에 작성
        if user_data is not None:
            for data_point in user_data:
                # 데이터 포인트에서 적절한 값을 추출하여 리스트로 작성
                row = [data_point['value1'], data_point['value2'], data_point['value3']]
                writer.writerow(row)

        # 데이터 불러오기
        data = pd.read_csv(csv_file_name)
    
        # 센서 이름 리스트
        sensor_names = ['초음파A', '초음파B', '적외선']

        # 모델 정의
        model = tf.keras.models.Sequential([
            tf.keras.layers.Dense(64, activation='relu', input_shape=(3,)),
            tf.keras.layers.Dense(64, activation='relu'),
            tf.keras.layers.Dense(1)
        ])

        # 모델 컴파일
        model.compile(optimizer='adam', loss='mean_squared_error')

        # 모델 훈련
        # 입력과 출력이 동일한 값을 가지도록 훈련
        model.fit(data[['초음파A', '초음파B', '적외선']], data[['초음파A', '초음파B', '적외선']], epochs=10, batch_size=32)

        # 모델 저장
        model.save(f'{user_data_name}_distance_deeprunning_model.h5')

        # 저장된 모델 불러오기
        loaded_model = tf.keras.models.load_model(f'{user_data_name}_distance_deeprunning_model.h5')

        # 입력 데이터로 예측
        new_data = pd.DataFrame({
            '초음파A': [50, 70, 400],
            '초음파B': [50, 70, 400],
            '적외선': [50, 70, 400]
        })
        # []안의 첫번째 값이 초음파A, 두번째 값이 초음파B, 세번째 값이 적외선
        predictions = loaded_model.predict(new_data)

        # 예측 결과 출력 및 Firebase에 저장
        ref = db.reference(f'/{user_data_name}_User_Data')
        data_dict = {}
        for i, prediction in enumerate(predictions):
            predicted_distance = int(prediction[0])
            sensor_name = sensor_names[i]
            print(f"{sensor_name}: {predicted_distance}")
            data_dict[sensor_name] = predicted_distance

        ref.set(data_dict)
