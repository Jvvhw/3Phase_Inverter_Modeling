#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#define f2          ((float)(1./2.))
#define f3          ((float)(f2/3.))
#define f4          ((float)(f3/4.))
#define f5          ((float)(f4/5.))
#define f6          ((float)(f5/6.))
#define f7          ((float)(f6/7.))
#define f8          ((float)(f7/8.))
#define f9          ((float)(f8/9.))
#define f10         ((float)(f9/10.))
#define f11         ((float)(f10/11.))
#define f12         ((float)(f11/12.))
#define f13         ((float)(f12/13.))
#define f14         ((float)(f13/14.))
#define f15         ((float)(f14/15.))

// Floating-point Constants
#define PI          ((float)3.141592653589793)
#define PI2         ((float)6.283185307179586)
#define PIOF6       ((PI*INV_6))
#define PIOF3       ((PI*INV_3))
#define PIOF2       ((PI*0.5))
#define PI5OF6      ((PIOF6*5))
#define INV_2PI     ((float)0.159154943091895)
#define INV_PI      ((float)0.318309886183791)
#define SQRT2       ((float)1.414213562373095)
#define SQRT3       ((float)1.732050807568877)
#define SQRT3HALF   ((float)0.866025403784438)
#define INV_SQRT2   ((float)0.707106781186547)
#define INV_SQRT3   ((float)0.577350269189626)
#define INV_3       ((float)0.333333333333333)
#define INV_6       ((float)0.166666666666667)
#define Rm2Rpm      ((float)9.549296585513720)
#define Rpm2Rm      ((float)0.104719755119659)
#define RAD2DEG     ((float)57.29577951308232)


// Macro Functions
#define LIMIT(x,s,l)            (((x)>(l))?(l):((x)<(s))?((s)):(x))
#define MAX(a, b)               ((a)>(b) ? (a) : (b))
#define MAX_3(a, b, c)          ((a)>MAX(b, c) ? (a) : MAX(b, c))

#define MIN(a, b)               ((a)>(b) ? (b) : (a))
#define MIN_3(a, b, c)             ((a)>MIN(b,c) ? MIN(b,c) : (a))

#define BOUND_PI(x)             ((x>0)?((x)-2.*PI*(int)((x+PI)/(2.*PI))):((x)-2.*PI*(int)((x-PI)/(2.*PI))))
#define ABS(x)                  ((x>0)?(x):(-x))
#define SIGN(x)                 ((x<0)? -1. : 1. )
#define SIN(x,x2)       ((x)*((float)1.-(x2)*(f3-(x2)*(f5-(x2)*(f7-(x2)*(f9-(x2)*(f11-(x2)*(f13-(x2)*f15))))))))
#define COS(x2)         ((float)1.-(x2)*(f2-(x2)*(f4-(x2)*(f6-(x2)*(f8-(x2)*(f10-(x2)*(f12-(x2)*f14)))))))
#define SIN_INV_X(x2)   (((float)1.-(x2)*(f3-(x2)*(f5-(x2)*(f7-(x2)*(f9-(x2)*(f11-(x2)*(f13-(x2)*f15))))))))
#define EXP(x)          ((float)1.+(x)*((float)1.+(x)*(f2+(x)*(f3+(x)*(f4+(x)*(f5+(x)*(f6+(x)*f7)))))))


//General Purpose Define
#define OFF                 0
#define ON                  1

//Gw_fcn
#define CUTRPM_L 100
#define CUTRPM_H 200

//General Purpose Define

#define TRUE                1
#define FALSE               0

//FW operation Mode
#define NONE            0
#define TABLEBASE       1
#define VOLTAGEFB       2

#define DO_NOTHING 0
#define UP_SEQUENCE 1
#define DOWN_SEQUENCE 2

#define     SECTOR1(x)              ((x) > (0) && (x) < (PIOF3))
#define     SECTOR2(x)              ((x) > (PIOF3) && (x) < (PIOF3*2))
#define     SECTOR3(x)              ((x) > (PIOF3*2) && (x) < (PI))
#define     SECTOR4(x)              ((x) > (-PI) && (x) < (-PIOF3*2))
#define     SECTOR5(x)              ((x) > (-PIOF3*2) && (x) < (-PIOF3))
#define     SECTOR6(x)              ((x) > (-PIOF3) && (x) < (0))


#define	K_ALLPASS	0
#define	K_LPF		1
#define	K_HPF		2
#define	K_BPF		3
#define	K_NOTCH		4




#define MOT_ROTEM 0
#define MOT_IPM 1

//////// Edit this to use corresponding parameters /////////
#define MOT_TYPE MOT_ROTEM
////////////////////////////////////////////////////////////

//Parameters

float Tsamp;
float Temp;

int Seq_mode = 0;
int init = 0;

float a, W_LPF;
float INV_a;
int loop_chk = 1;

// Signal Generator
float Theta;
float V_sin_A;
float V_sin_B;
float V_sin_C;
float Fre = 0;
float ma = 1;

float A_Signal;
float B_Signal;
float C_Signal;

//Inverter
float Is_rated = 10.;
int PWM_mode_set = 0;

float Vdc;
int INV_on;
float INV_Vdc;


#endif	//__CONTROLLER_H__
