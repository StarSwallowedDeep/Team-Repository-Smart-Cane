<p align="center">
  <img src="https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/9aede7af-bee4-41e9-b2ef-5f8270797d7b" alt="이미지 설명">
</p>  

# **Smart Cane**
## **🔶 개요**
<br>

+ **소개**
    + ### **"안전 보행을 위한, AI기반 사용자 맞춤형 스마트 지팡이 "**
      <br>지팡이는 **전방 물체를 확인하기 위한 도구**이지만, **거리와 위치**가 명확하지 않아서 **주변 상황**만을 인지하게 됩니다.  
      이로 인해 **지팡이를 사용하는 사람들은** 물체에 직접 부딪혀가며 감각으로 거리나 위치를 측정해야 하므로 **위험을 감수**해야만 합니다.  
      <br>IoT 기술과 결합하여 지팡이가 가지고 있는 **문제점을 보안**하고 **보행의 자유**를 제공하는 장비를 구현하기 위해 **다양한 센서**를 장착하여 물체를 확인하는 과정을 개선하였습니다.  
      <br>이를 위해 **딥 러닝**(인공지능)을 활용하여 사용자 개개인의 안전 거리를 조정하고, **어플리케이션과 연동**을 통해 현 위치 및 **보행에 도움이 되는 장치**를 구현하였습니다.
<br>

+ **목적**
  
    + **안전 보행** : 지팡이가 주변을 감지하고, **위험 요소를 경고해** 안전한 보행을 도와 줌
    + **편의성** : 앱과 연동하여 다양한 기능을 제어하고 정보를 송수신하여 **최적화된 서비스**를 제공
<br>

## **📌 주요기능 및 기술**
<br>

+ **시스템**
   + ###### Smart Cane 구성
  <p>
  <img src="https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/f97e7add-7a5f-4c19-881b-05744588daca" alt="이미지 설명" style="width: 70%;">
  <img src="https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/e997e9e5-576e-4a18-a892-8cc94733d3af" alt="이미지 설명" style="width: 70%;">
  <img src="https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/10a057e4-38a3-48a9-bf36-50a0196f0ad1" alt="이미지 설명" style="width: 70%;">
  </p>
  
  + ###### Application
  <p>
  <img src="https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/af13d4ac-a99f-4139-80e0-e5f303d20251" alt="이미지 설명" style="width: 70%;">
  </p>
<br>

+ **메커니즘**
  + ###### 원리
  <p>
  <img src="https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/f0c45083-ac3d-4985-81e0-60978ee4ce6b" alt="이미지 설명" style="width: 70%;">
  <img src="https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/f58f9cc6-8c32-40e7-9684-56c211f69e50" alt="이미지 설명" style="width: 70%;">
  <img src="https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/d3054a47-5125-42c1-82ac-05fb04bcef9f" alt="이미지 설명" style="width: 70%;">
  </p>
  
  ![image-10](https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/0df56c38-0fec-40cc-9ca0-9c08f458530a)
  ![image-8](https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/e6fc308d-ac3e-4e68-839e-cab90229e361)
  ![image-9](https://github.com/StarSwallowedDeep/Team-Repository-Smart-Cane/assets/139122242/7eb01845-b7a3-4257-848a-0ccb37482ec4)
<br>

## **📑 개발 과정**
<br>

1. **Arduino**
    + 각각의 센서는 구분되는 역할을 갖고, 이에 맞는 함수를 사용하여 감지하도록 설계 함
    + 블루투스를 활용하여 센서의 안전 거리 값을 조정하는 기능을 하도록 수행

<br>

2. **Application**
    + 어플리케이션을 블루투스와 연동하여 데이터를 송수신하도록 구현
    + 어플리케이션내에 보행에 도움이 되는 다양한 기능 추가

<br>

3. **BackEnd**
    + 사용자별 데이터를 수집하기 위해 Firebase를 사용
    + 데이터를 관리 및 저장
    + 개인화된 서비스 제공하여 사용자의 편의성 제공

<br>

4. **DeepRunning**
    + Firebase에서 개인별 데이터를 불러오기 위해 파싱 작업 수행
    + 수집된 데이터를 기반으로 Python의 TensorFlow를 활용하여 데이터를 분석하고 예측 하도록 구현
