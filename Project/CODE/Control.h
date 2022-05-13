#ifndef _Control_h
#define _Control_h





#include "headfile.h"
#include "FUZZ.h"

#define youp    TIM_5_CH3_A02
#define youn    TIM_5_CH4_A03
#define zuop    TIM_5_CH2_A01
#define zuon    TIM_5_CH1_A00


//#define youp    TIM_5_CH4_A03
//#define youn    TIM_5_CH1_A00
//#define zuop    TIM_5_CH2_A01
//#define zuon    TIM_5_CH3_A02

//#define zuop    TIM_5_CH1_A00
//#define zuon    TIM_5_CH2_A01

extern int val,var;
extern int pwm_speed,expd_speed,kp_speed,speed,kp_low,expd_speed_low;
extern int err,Angle,expd;
extern int GYROSCOPE_ANGLE_SIGMA_FREQUENCY;  //陀螺仪调整频率   小会超调(大跟随时间变长)  //2.3 156 0.9  60
extern float GYROSCOPE_ANGLE_RATIO;
extern double g_fGyroscopeAngleSpeed;
extern double fGyroscopeAngleIntegral;
extern double g_fGyroscopeAngleSpeed;
extern unsigned short int send_data[6];
extern int pwm_station,last_icm;
extern int kp,kd;
extern int d1,P1;
extern int duty;
extern int k_mid;
extern int stop_js;
extern int s_p,sp_yaun_su;
//extern uint8   ;
extern int flas;
extern int las_v,v;
extern int LOW1;
extern int a,b,c,d;
extern int uwb_flag;
extern int kp_g,kd_g;
extern int mc_dis;
extern int stop_time,yaokong,ZUOYOU;
extern int kp_ping,kd_ping;
extern float Left_OutPWM;
extern float Right_OutPWM;
extern char abs_stop,fon,las_fon;
extern int s_p_Angel;
extern int mc_quan;
extern int kai;
extern int s_p_mc;
extern float fuzz_p,fuzz_kp;
extern int d_speed,ca_su,kp_tai;
extern int VP,VI,i5;
extern int temp1,banma_mc;
extern int speed_Angle;
extern int use_time,gogogo_dis;
extern int stop_cuan,jianjianjian,s_p_speed;
//函数声明

//extern void turn();
extern void laya_send();
extern void pwm_sum();
extern void AngleCalculate();
extern void turn();
extern void STOP();
extern int regression(int *LINE,int startline,int endline); 
extern float Fuzzy_Z(float P,float D);
extern void uwb();
extern void Data_Send(UARTN_enum uartn,unsigned short int *pst);
extern void TIM6_zhoduan();
extern void v_speed_set2pwm(int16 leftSpeed,int16 rightSpeed);
extern void ABS();
extern void s_p_con();
extern void Speed_loop();
extern void KalmanFilter(float ACC_Angle);
#endif