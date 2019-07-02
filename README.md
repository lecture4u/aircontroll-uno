# aircontroll-uno
source code for air controlling arduino uno board

Author: @yoseplee

System Airconditioner contoller hack with hardware!

* Arduino Uno
* Servo Mortor
  * pin: ~9
  * 5v
  * GND
* Light sensor(cds)
  * pin: A0
  * 3.2v
  * GND
  
## Description

이 아두이노 보드는 에어컨 컨트롤러의 전원 표시등을 추적합니다. 조도 센서는 이를 감시하고 있으며 작동 상태를 확인합니다.

센서 값이 튀는 현상을 최소화 하기 위해, 조도센서를 2.5초간 5회 측정한 후 그 평균으로 판단합니다.

만약 전원 표시등이 꺼진다면 아두이노 보드의 서보모터를 작동시켜 버튼을 누르게 합니다.

현재 전원 표시등의 상태는 휴리스틱하게 결정된 값이 입력되어 있습니다. 조도센서를 가져다 대고 그 값을 측정하여 해당 환경에 적정한 값을 설정하여야 합니다.
