# 3Phase_Inverter_Modeling
DLL code for running 3Phase Inverter with carrier based PWM

## Intro

본격적인 3상 시스템을 다루기 전 시뮬레이션을 통해 인버터의 입출력을 확인해본다.

프로젝트의 전체 구성은 

1. 일반 3상 AC전압과 RL부하를 활용한 모델
2. 3상 인버터와 6스텝 제어
3. DLL을 사용하지 않는 PWM 제어
4. DLL을 사용한 PWM 제어

의 4가지이다.

본 리포지토리에서는 4번의 코드를 리뷰하고 업데이트한다.

## 3Phase output

주파수가 가변될 수 있는 평형 3상의 출력 전압을 인버터로 제어하는 것이 목표이므로,

각 상에 공통인 반송파와(Carrier) 위상이 120도씩 차이나는 3개의 기준파가 필요하다.

반송파의 경우 미리 설정해둔 Sampling Time을 신호로 입력받을 수 있다.

기준파는 주파수와 진폭을 특정할 수 있는 매개변수를 통해 구현한다.

* 주파수
* Vdc
* 진폭 변조지수

2번과 3번이 합쳐져서 진폭을 구현해야 나중에 선형변조 영역과 과변조 영역을 확인 할 수 있겠다.

결론적으로, 코드의 전체적인 틀은 위에서 언급한 입력값 4개, 출력은 3개의 각 파형으로 구상하였다. 

## Code review (Partial)
```
if (INV_on) {
		Theta += 2 * PI * Fre * Tsamp;                   // Discrete angle output for Sin wave which has input Fre
		if (Theta > 2 * PI) { // 2PI BOUND
			Theta = 0;
		}
		V_sin_A = (Vdc*ma*0.5)*sin(Theta);               //amplitude modified by modulation ratio
		V_sin_B = (Vdc * ma * 0.5) * sin(Theta-2*PIOF3); //120 phase delay
		V_sin_C = (Vdc * ma * 0.5) * sin(Theta-4*PIOF3); //240 phase delay
		
		//0~1 Duty output
		A_Signal = (V_sin_A + 0.5 * Vdc) * INV_Vdc; 
		B_Signal = (V_sin_B + 0.5 * Vdc) * INV_Vdc;
		C_Signal = (V_sin_C + 0.5 * Vdc) * INV_Vdc;

	}
	else {
		A_Signal = 0.5;
		B_Signal = 0.5;
		C_Signal = 0.5;
	}
```
## Plecs Circuit
![3PINV](https://user-images.githubusercontent.com/125186303/222340012-c02789a9-75d5-4069-a074-c92be99d5a15.jpg)

3Phase Inverter with RL loads

![CBPWM](https://user-images.githubusercontent.com/125186303/222340084-4165c1c0-e514-41ab-840c-bd0e644defbd.jpg)

Carrier Based PWM (Triangular wave)

## Result
![plot1](https://user-images.githubusercontent.com/125186303/222340804-8b2fd479-e1c2-44bc-8fe4-0d9a34f01d61.jpg)

Output Voltage sin wave, Voltage modulation ratio (0.8)

![plot2](https://user-images.githubusercontent.com/125186303/222340820-b5d376da-139e-4a96-8b76-2cfd20e34f96.jpg)

a-b line to line voltage, a Phase voltage, a Pole voltage

![plot3](https://user-images.githubusercontent.com/125186303/222340826-07035f78-6771-4332-aaab-20d1a888affd.jpg)

Common mode current


---
## Feedback
* Sampling time의 경우 MCU에서는 클락을 분주하여 사용한다, 분주비 레지스터 설정에 따라서 기본파 주파수가 변형되지 않도록 조치가 필요

* 고조파 성분을 확인하고 싶을때 필요한 주파수 변조비도 입력으로 받으면 좋을 것 같음

* 이번 프로젝트의 이해를 바탕으로 다음에는 공간벡터 PWM를 구현







