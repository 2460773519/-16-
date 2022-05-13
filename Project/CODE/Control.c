#include "Control.h"
#include "MENU.h"

#define PB 5
#define PM 4
#define PS 3
#define ZO 0
#define NS 3
#define NM 4
#define NB 5



//方向环变量
int duty=0;             
int k_mid=0;
int P1=21,d1=0;
int LOW1=0;
int uwb_flag=0;
int kp_g=25,kd_g=5;    // 25 5
float turn_on_out=0;
float err_on=0;
float fuzz_p=0;
float fuzz_kp=10;
int stop_cuan=0;


//速度环变量
int val,var;
int las_v=0,v=0;
int pwm_speed=0,expd_speed=265,kp_speed=7,speed,kp_low=5,expd_speed_low=250; 
float Left_OutPWM = 0.f;
float Right_OutPWM = 0.f;
float speed_P = 0.01f; 
float speed_I = 0.08f;
int d_speed=0;
int pwm_tai=0;
int kp_tai=30;
int ca_su=1240;
int left_duty,right_duty;
int VP=0,VI=0;
int L_error[2]={0},R_error[2]={0};
int las_speed=0;
char abs_stop=0;
int i5=0,s_p_copy=0;
int s_p_1=0;
int speed_Angle=0;



//直立变量
int err,Angle,expd=73;   //73
int pwm_station,last_icm;
double fGyroscopeAngleIntegral=0;  //融合角度
double g_fGyroscopeAngleSpeed;    //归一陀螺仪值
double g_fGravityAngle;           //归一加速度
int GYROSCOPE_ANGLE_SIGMA_FREQUENCY=167;  //陀螺仪调整频率   小会超调(大跟随时间变长)  //2.1 140// 1.3 167 // 1.0  62  
float GYROSCOPE_ANGLE_RATIO=1.3;     
int kp=20,kd=40;    // 9  51   31   30   +41  -0.8
int kp_ping,kd_ping;
float g_x=0;
int s_p=0,sp_yaun_su=0;
int use_time=0;
int s_p_Angel=-0;
int s_p_speed=15;
int kai=0;
int s_p_mc=2200;
int wan_point=28;



//uwb通信
int mc_dis=7800;
int stop_time=50; //发送次数  35
int gogogo_dis=1000;
char fon='B',las_fon=0;
int yaokong=0,ZUOYOU=0;
int jianjianjian=0;

//编码器
int stop_js=0;
int mc_quan=0;
int temp1=1;
int banma_mc=0;

//蓝牙
unsigned short int send_data[6];  


/*---------------------------------------------------------------
---------------------------------------------------------
-----------------------------------------------------------------*/

void TIM6_zhoduan()
{
  static int i1=0,i2=0,sum_m=0;
  int n1=0;
  static int i4=0;
  i1++;
  i2++;
  get_icm20602_accdata();
  get_icm20602_gyro();
  AngleCalculate();
  
  var = tim_encoder_get_count(TIM_3)*50;
  val = -tim_encoder_get_count(TIM_4)*50; 
  
  if(abs(var)<=abs(val))   val=var+(val-var)/(wan_point/10.0);
  else var=val+(var-val)/(wan_point/10.0);
     
  las_speed = speed;
  speed=(-((var+val)*50))/1024;
  speed = (speed*7+las_speed*3)/10;   //算出车模速度
                       
     if(i2==25)   //50ms到 执行速度控制
     {
        i2=0;
        if(s_p==0&&s_p_1==0)   //动态p 和姿态控制 速度环
        {
          if(abs(var)<=abs(val))   val=var+(val-var)/3.5;
          else var=val+(var-val)/3.5;
          
          v=expd_speed_low-(-((var+val)*50))/1024; //期望速度p
          if(v<0) low_mov=2*kp_low*v/100;
          else low_mov=kp_low*v/100;  //动态转向外环P
          if(low_mov<=-30) low_mov=-30;
          if(low_mov>=0) low_mov=0;
   
          v=expd_speed-(-((var+val)*50))/1024;//期望速度Angel
          speed_Angle=-2*kp_speed*v/100;
          if(speed_Angle<=-15) speed_Angle=-15;
          if(speed_Angle>=30) speed_Angle=30;
        }
        else  //坡道不要动态
        {
          low_mov=0;
          speed_Angle=0;
        }
           
        if(banma!=0) //斑马线动态p为0
        {
          low_mov=0;
        }
           
        if(yuan_4==2&&yuan_6==0) //环里面压低姿态
        {
           speed_Angle=speed_Angle+5;
        }       
     }
     
  if(kai==1)  //起步跑接球标志位
  {
     speed_Angle=-25; //压低姿态
     if((Angle>=160&&kaishi==0))  //接到球了
     {
       jianjianjian=1;
       beepds=5;
       kai=2;
     }    
  }
 // if(kai!=0)speed_Angle=-25;
  
  if(jianjianjian>=1)
  {
    if(beepds==0) beepds=5;
      uart_putchar(UART_4,'A');
      jianjianjian++;
      if(jianjianjian>=stop_time) jianjianjian=0;
  }
  
  if(kai==100) kai=3;
  
  
  
  if(kai>=3)  //正常接球发信息三轮停
  {
    //if(beepds==0) beepds=5;
     uart_putchar(UART_4,'S');
     kai++;       
  }
  if(kai>=stop_time) kai=0;//发多少次stop_time(35)
     

  if(stop==0&&fash_lanya==0&&mc_js==1)//mc_js==1  计脉冲
  { 
     sum_m = sum_m-((var+val)/200);
  }
  if(sum_m>=mc_dis) //距离mc_dis后停车发
  {         
     beepds=5;
     stop_js=1;
     mc_js=0;
     sum_m=0;
  }
  
    if(i1==3)   //6ms到角度控制
    {
      i1=0;  
      err = Angle- 14-expd-pwm_speed+speed_Angle;   //-20 = 往前倒                                    
    }


  if(gpio_get(bo_4))  //开启检测上坡
  {
    s_p_con();
    if(stop==0&&kaishi==0&&s_p==0&&stop_cuan==0)
    {
     if(Angle<=50||Angle>=180)
     {
       beepds=10;
       STOP();
     }
    }
  }

//  pwm_station=(-g_fGyroscopeAngleSpeed/200-(err-pwm_speed)*kp/10)*kd; // 2ms 一次角速度控制 
   pwm_station=(err)*kp+g_fGyroscopeAngleSpeed*kd/200; // 2ms 一次角速度控制 
   if(pwm_station>=700) pwm_station=700;
   if(pwm_station<=-700) pwm_station=-700;

   
   turn();             //究极转向环控制
   
  // if(banma>=1) banma++;
   if(kaishi>0&&stop==0) kaishi--;//接球屏蔽识别元素
   if(kaishi==1)
   {
//     GYROSCOPE_ANGLE_SIGMA_FREQUENCY=GYROSCOPE_ANGLE_SIGMA_FREQUENCY-27;
//     GYROSCOPE_ANGLE_RATIO=GYROSCOPE_ANGLE_RATIO+0.8;
   }
   
   if(stop==0) pwm_sum(); //电机输出
  
   if(stop_js>=1)
   {
     stop_js++;
     uart_putchar(UART_4,'Y');
   }
 
   if(stop_js>=stop_time)   //减速100个程序周期后停车
   {
     sancha_fx=0;
     stop_js=0;
     STOP();
   }
   
   if(banma>=1&&yuan==0) banma_mc=banma_mc-(var+val)/200; //斑马计数脉冲
   if(yuan!=0&&yuan_3==0) banma_mc=banma_mc-(var+val)/200; //圆环没进关
}


void turn() 
{
  int i=0;
  int sum=0;   
  float las_err_ft=0;
  int fkp=0,fkd=0;  
  float las_err_on=0;
  static int i3=0,a1=0;
  int lows;
  i3++;
  k_mid= regression(mid,30,59);

  las_err_on = err_on;

 
  if(i3==3)
  { 
     i3=0;
     a1++;
     if(a1==3) las_err_ft=err_ft;
     
     if(gui_low>LOW) lows=gui_low;
     else lows=LOW;
     
     if(lows>=35) lows=35;
     
     if(banma==0)
     {
     if(sp_yaun_su==1)  //上坡时 误差用 底下下10行
     {
         for(i=55;i<=58;i++)
         {
             if(abs(mid[i]-mid[i+1])>=3) mid[i] = (mid[i+1]*5+mid[i]*5)/10;
             sum=sum+(mid[i]-79);
         }
           err_ft=sum/7; 
     }
     if(sp_yaun_su==0)
     {
        for(i=lows;i<=lows+HIGHT;i++)
        {
           sum=sum+(mid[i]-79);  
        }
        
        err_ft=sum/HIGHT;
        
        sum=0;
        
        for(i=39;i<=59;i++)
        {
           sum=sum+(mid[i]-79);  
        }
        
        err_ft=(err_ft*8+(sum/20)*2)/10; 
     }
     }
    else
     {
       if(banma==1)
       {
           for(i=55;i<=58;i++)
           {
              if(abs(mid[i]-mid[i+1])>=3) mid[i] = (mid[i+1]*5+mid[i]*5)/10;
               sum=sum+(mid[i]-79);
               
           }
             err_ft=sum/3; 
       }
       else
       {
           for(i=22;i<=27;i++)
           {
              if(abs(mid[i]-mid[i+1])>=3) mid[i] = (mid[i+1]*5+mid[i]*5)/10;
               sum=sum+(mid[i]-79);
           }
             err_ft=sum/7;
         
       }
     }
     
     if(banma!=0)
     {
       
        err_ft=(err_ft+las_err_ft)/2;
     }
     else          err_ft = (err_ft*8+k_mid*2)/10;
     
   //  if(yaokong==1) err_ft=0; //遥控车不要误差
       
       //err_ft=(err_ft*9+las_err_ft*1)/10;
          // 上坡误差缩小
       if(stop_js>=1) err_ft=err_ft;    // 停车靠左
       //if(banma>=1 &&banma<=135&&err_ft_chan==0) err_ft=0;  //斑马线屏蔽误差
       if(err_ft_chan==1) err_ft=err_ft*1.2; //三叉放大误差  
       if(a1==3)
       {
         dt_err_ft = err_ft - las_err_ft;
       //  fuzz_p=fuzz_kp*Fuzzy_DirP(err_ft,dt_err_ft);
         a1=0;
       }  
//       if(dt_err_ft<=20)
//       {
//         if(fabs(fuzz_p)<fabs(dt_err_ft))
//         //yidong = (int)dt_err_ft;
//         fuzz_p=dt_err_ft;
//       }  
      // if(err_ft>=0)
     turn_on_out=(P1-low_mov)*err_ft+2*d1*(dt_err_ft);//6毫秒更新一次转向外环
       
       
       //  fkp=(P1-low_mov) + err_ft*err_ft/(kp_tai); //动态p
         
       //  turn_on_out=fkp*err_ft+d1*(dt_err_ft)*2;//6毫秒更新一次转向外环
  }
    
     err_on = (turn_on_out*speed/2000.0-(icm_gyro_x+41)/100.0);
     if(yaokong==0) duty  = -(err_on*(kp_g))+(err_on-las_err_on)*kd_g;

     if(duty>=600) duty=600;
     if(duty<=-600) duty=-600;
     
     
     //if(yaokong==1) duty=ZUOYOU;
  
}

 
void  s_p_con()
{
  int b1=0,b2=0;
  if(s_p==1000)
  {
    s_p=0;      
      sp_yaun_su=0;
      s_p_1=0;
    sp_yaun_su=0;
       kp=kp+15;
       kd=kd-10;
    mc_quan=0;
     pwm_speed = 0;
   // beepds=0;
  }
  
  if(s_p==0&&s_p_1==0)
  if(regression(L_side,35,45)<=11&&regression(L_side,35,45)>=4
      &&-regression(R_side,35,45)<=11&&-regression(R_side,35,45)>=4&&err_ft<=3&&abs(val-var)<=200
      &&kaishi==0&&yuan==0&&stop==0&&banma==0&&err_ft_chan==0)
    {
         for(b1=50;b1>25;b1=b1-1)  //判断右边界是否跳变很多 连续
         {
           if((L_side[b1-2] - L_side[b1])>8 || (L_side[b1-2] - L_side[b1])<-1)
           {
             break;
           }
         }
         
         for(b2=50;b2>25;b2=b2-1)  //判断右边界是否跳变很多 连续
         {
           if((R_side[b2] - R_side[b2-2])>8 || (R_side[b2] - R_side[b2-3])<-1)
           {
             break;
           }
         }
       if(b1==25&&b2==25)
       {
       //  if(beepds==0) beepds=5;

         s_p_1=1; 
         pwm_speed = s_p_Angel;
       }
    }
  
   if(s_p_1>=1)
   {
    s_p_1++;
    if(yuan==0&&stop==0&&s_p==0&&sp_yaun_su==0
       &&icm_acc_x<-7000&&-icm_acc_z<-12500&&regression(L_side,35,45)!=0&&regression(R_side,35,45)!=0)
    {
      yuan_7=3;
      kp=kp-15;
      kd=kd+10;
      s_p=1;
      sp_yaun_su=1;
      beepds=5; 
      s_p_1=0;    
    }
   }
  
  if(s_p_1==70)
  {
    pwm_speed=0;
    s_p_1=0;
  }
  
  
 if(s_p==1&&mc_quan!=8000&&sp_yaun_su==1) pwm_speed = s_p_Angel;  //上坡时往后仰
 if(s_p==1&&mc_quan!=8000&&sp_yaun_su==1)
 {
   if(speed<=300)
   {  
    mc_quan=mc_quan-(var+val)/200;
   }

 }
 if(mc_quan>s_p_mc&& mc_quan <7500&&s_p==1&&sp_yaun_su==1)     //检测到坡顶
 {   
   beepds=5;
   mc_quan = 8000;
  // kp=kp+15;
  // kd=kd-5;
   
 }
 if(mc_quan==8000&&sp_yaun_su==1) 
 {
   pwm_speed=s_p_speed;//坡顶时 往前倒
   if(icm_acc_x<-6000&&-icm_acc_z<-11500&&sp_yaun_su==1) //检测下坡
   {
      s_p_copy=0;
      s_p=2;
      sp_yaun_su=0;
      beepds=5; 
      mc_quan=0;
      kp=kp+15;
      kd=kd-10;
   }  
 }

 
 if(s_p>=2)
 {
   pwm_speed=s_p_speed;   //下坡后姿态不稳定 先400ms固定姿态走
   s_p++;
 }
 if(s_p==30)
 {
   pwm_speed=s_p_speed;
//  kp=kp+18;
////  kd=kd-8;
 }
 if(s_p>=300)
 {
  // beepds=5;
    //kd=kd-5;
   pwm_speed=0;
   sp_yaun_su=0;
   s_p=0;
 }
}




void Speed_loop()
{   
  
   uart_putchar(UART_4,'Y');
    var= tim_encoder_get_count(TIM_4)*200/170;								// 采集对应编码器数据
    val=-tim_encoder_get_count(TIM_3)*200/170;// 采集对应编码器数据
    
    L_error[0]=-var;
    R_error[0]=-val;
    left_duty=left_duty+33/10.0*(L_error[0]-L_error[1])+5/10.0*L_error[0];
    
    L_error[1]=L_error[0];
    
    right_duty=right_duty+33/10.0*(R_error[0]-R_error[1])+5/10.0*R_error[0];

    R_error[1]=R_error[0];
  
  

    if(left_duty>=0)
    {
      if(left_duty>999) left_duty=999;
      pwm_duty_updata(TIM_5, zuon, 0);
      pwm_duty_updata(TIM_5, zuop, left_duty); 
    }
    else
    {
      if(left_duty<-999) left_duty=-999;
      pwm_duty_updata (TIM_5, zuon, -left_duty);
      pwm_duty_updata (TIM_5, zuop, 0);
    }
    if(right_duty>=0)
    {
      if(right_duty>999) right_duty=999;
      pwm_duty_updata (TIM_5, youn, 0);
      pwm_duty_updata (TIM_5, youp, right_duty);
    }
    else
    {
      if(right_duty<-999) right_duty=-999;
      pwm_duty_updata (TIM_5, youn,-right_duty);
      pwm_duty_updata (TIM_5, youp, 0);
    }
    
  if(i5>0) i5--;
  if(i5==1) 
  {
    i5=0;
    beepds=10;
    pwm_duty_updata(TIM_5, zuon, 0);
     pwm_duty_updata(TIM_5, zuop, 0);
     pwm_duty_updata(TIM_5, youn, 0);
     pwm_duty_updata(TIM_5, youp, 0); 
    tim_interrupt_disable(TIM_7);
    tim_interrupt_enable(TIM_6);
  }
}

int16 Filter(int16 a)
{
    static float Filter_win[4]={0,0,0,0};//
	uint8  mid_weight[4]={0,1,2,7};
	float b;
	uint8 i;
	uint8 mid_coe=0;
    float sumErr=0;
	int16 c;
	b = (float)a;
	
	
		  //加权滑动平均滤波
  Filter_win[3]=b; //Servo_Control0ut
  for(i=0;i<4;i++)
  {
    sumErr+=Filter_win[i]*mid_weight[i];
    mid_coe+=mid_weight[i];
  }
  b = sumErr/mid_coe;
  for(i=0;i<3;i++) //先进先出原则
  {
    Filter_win[i]=Filter_win[i+1];
  }
  c = (int16)b;
	return c;
}

void AngleCalculate(void)
{   
       double   fDeltaValue=0;//中间变量为补偿量 
       icm_acc_z = 0.8*icm_acc_z+0.2*last_icm;
       icm_acc_z = Filter(icm_acc_z);
        //    加速度    =       （Z轴加速度-加速度零偏值）  * 加速度角度比例
	g_fGravityAngle =       (icm_acc_z-240) * 1;// accle_z/185; //加速度    
        //            陀螺仪值    =  （陀螺仪Z轴值-陀螺仪零偏值）  * 陀螺仪角度比例
        g_fGyroscopeAngleSpeed = -(icm_gyro_y+9) * GYROSCOPE_ANGLE_RATIO;          //gyro 角速度	 
	
      //中间补偿量  =（加速度           -融合角度      ）/ 加速度常量
        fDeltaValue =(g_fGravityAngle - fGyroscopeAngleIntegral) / 2;      //补偿量

      //融合角度                +=（陀螺仪值               + 中间补偿量 ）/ 陀螺仪调整频率
	fGyroscopeAngleIntegral +=(g_fGyroscopeAngleSpeed + fDeltaValue) / GYROSCOPE_ANGLE_SIGMA_FREQUENCY;
        
        Angle = fGyroscopeAngleIntegral/19;
       // err = Angle +52+75-expd;
       // pwm_station =(-g_fGyroscopeAngleSpeed+(err)*kp*5)*kd/100; // 2ms 一次角速度控制
        last_icm = icm_acc_z;     
}


void Data_Send(UARTN_enum uartn,unsigned short int *pst)
{
        unsigned char _cnt=0;	unsigned char sum = 0;
	unsigned char data_to_send[23];         //发送缓存
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=(unsigned char)(pst[0]>>8);  //高8位
	data_to_send[_cnt++]=(unsigned char)pst[0];  //低8位
	data_to_send[_cnt++]=(unsigned char)(pst[1]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[1];
	data_to_send[_cnt++]=(unsigned char)(pst[2]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[2];
	data_to_send[_cnt++]=(unsigned char)(pst[3]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[3];
	data_to_send[_cnt++]=(unsigned char)(pst[4]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[4];
	data_to_send[_cnt++]=(unsigned char)(pst[5]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[5];
	data_to_send[_cnt++]=(unsigned char)(pst[6]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[6];
	data_to_send[_cnt++]=(unsigned char)(pst[7]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[7];
	data_to_send[_cnt++]=(unsigned char)(pst[8]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[8];
	data_to_send[3] = _cnt-4;
	sum = 0;
	for(unsigned char i=0;i<_cnt;i++)
		sum += data_to_send[i];
        
	data_to_send[_cnt++] = sum;
        for(unsigned char i=0;i<_cnt;i++)
        uart_putchar(uartn,data_to_send[i]);
}

void laya_send()              //蓝牙发送函数
{
//    send_data[0]=low_mov;    
//    send_data[1]=speed;
//    send_data[2]=err_ft;
//    send_data[3]=icm_gyro_x+44;
//   send_data[4]=-icm_gyro_y;
//  send_data[5]=icm_gyro_z;
   // send_data[6]=fGyroscopeAngleIntegral;
   // send_data[2]=icm_acc_z-300;
    send_data[0]=S2_L;    
    send_data[1]=S2_R;
//    send_data[2]=Angle;
//    send_data[3]=icm_gyro_x+44;
    Data_Send(UART_4,send_data);   
    uart_putchar(UART_4,0x33);
}


void STOP()
{
   stop = 1;
   
   
   //abs_stop=1;
//   pwm_duty_updata(TIM_5, zuon, 480);
//   pwm_duty_updata(TIM_5, zuop, 0);
//   pwm_duty_updata(TIM_5, youn, 480);
//   pwm_duty_updata(TIM_5, youp, 0);  
//   
  //systick_delay_ms(300);
   //while(1)
//   {
//     if(i4<=4000)  i4++;
//     if(i4==3999)  i4=5000;
//      if(abs(icm_acc_x)>=1000&&i4==5000) break;
//      if((ok)) break;
//      ABS();
//      uart_putchar(UART_4,'Y');
//  }
  // beepds=5;
   if(gpio_get(bo_1))
   {
   pwm_duty_updata(TIM_5, zuon, 0);
   pwm_duty_updata(TIM_5, zuop, 0);
   pwm_duty_updata(TIM_5, youn, 0);
   pwm_duty_updata(TIM_5, youp, 0); 
   }
   else
   {
   pwm_duty_updata(TIM_5, zuon, 600);
   pwm_duty_updata(TIM_5, zuop, 0);
   pwm_duty_updata(TIM_5, youn, 600);
   pwm_duty_updata(TIM_5, youp, 0);  
   
   systick_delay_ms(250);
     
   pwm_duty_updata(TIM_5, zuon, 0);
   pwm_duty_updata(TIM_5, zuop, 0);
   pwm_duty_updata(TIM_5, youn, 0);
   pwm_duty_updata(TIM_5, youp, 0);
     
   i5=500;
   tim_interrupt_disable(TIM_6);
   tim_interrupt_enable(TIM_7);
   }
//   GYROSCOPE_ANGLE_SIGMA_FREQUENCY=GYROSCOPE_ANGLE_SIGMA_FREQUENCY+27;
//   GYROSCOPE_ANGLE_RATIO=GYROSCOPE_ANGLE_RATIO-0.8;
  
  if(s_p!=0) s_p=1000;  
  if(kai==1||kai==2) 
  {
    kai=3; //强制跑
    kp=kp-10;
    kd=kd-5;
  }
}

void pwm_sum()
{
   int pwm_sum;
   //  pwm_tai=0;
   if(pwm_station>=0)
   {
     if(pwm_station>=999) pwm_station=999;
      if(duty>=0)  //左转
        {
//          if(d_speed<=-ca_su) 
//          {
//             pwm_tai =kp_tai*(val-var)/10;        
//          } 
//          else pwm_tai=0;
          
            pwm_sum=duty+pwm_station;
            if(duty>=999) duty=999;
            if(pwm_sum>=999) pwm_sum=999;
            
        pwm_duty_updata(TIM_5, zuon, duty);
        pwm_duty_updata(TIM_5, zuop, pwm_station);//左轮正       
        pwm_duty_updata(TIM_5, youn, 0); 
        pwm_duty_updata(TIM_5, youp, pwm_sum); //右你吧 
        }
      else
      {
//          if(d_speed>=ca_su) 
//          {
//             pwm_tai =-kp_tai*(val-var)/10;        
//          } 
//          
//           else pwm_tai=0;
        pwm_sum=pwm_station-duty;
        if(duty<=-999) duty=-999;
        if(pwm_sum>=999) pwm_sum=999;
         pwm_duty_updata(TIM_5, zuon, 0);
         pwm_duty_updata(TIM_5, zuop, pwm_sum);
         pwm_duty_updata(TIM_5, youn, -duty);
         pwm_duty_updata(TIM_5, youp, pwm_station);   
        
         
      }  
   }
   
   else
   {
        pwm_station=-pwm_station;
        if(pwm_station>=999) pwm_station=999;
        if(duty>=0)
        {
            pwm_sum=duty+pwm_station;
            if(duty>=999) duty=999;
            if(pwm_sum>=999) pwm_sum=999;
            
     
        pwm_duty_updata(TIM_5, zuon, pwm_sum);
        pwm_duty_updata(TIM_5, zuop, 0);
        pwm_duty_updata(TIM_5, youn, pwm_station);
        pwm_duty_updata(TIM_5, youp, duty);
           
        }
   
      else
      {
        pwm_sum=pwm_station-duty;
        if(duty<=-999) duty=-999;
        if(pwm_sum>=999) pwm_sum=999;
        
   
        pwm_duty_updata(TIM_5, zuon, pwm_station);
        pwm_duty_updata(TIM_5, zuop, -duty);
        pwm_duty_updata(TIM_5, youn, pwm_sum);
        pwm_duty_updata(TIM_5, youp, 0);   
        
            
      }  
   }
}

//void pwm_sum()
//{
//   int pwm_sum;
//     
//   if(pwm_station>=0)
//   {
//     if(pwm_station>=999) pwm_station=999;
//      if(duty>=0)
//        {
//            pwm_sum=duty+pwm_station;
//            if(duty>=999) duty=999;
//            if(pwm_sum>=999) pwm_sum=999;
//        pwm_duty_updata(TIM_5, zuon, duty);
//        pwm_duty_updata(TIM_5, zuop, pwm_station);//左轮正       
//        pwm_duty_updata(TIM_5, youn, 0); 
//        pwm_duty_updata(TIM_5, youp, pwm_sum); //右你吧 
//        }
//      else
//      { 
//        pwm_sum=pwm_station-duty;
//        if(duty<=-999) duty=-999;
//        if(pwm_sum>=999) pwm_sum=999;
//         pwm_duty_updata(TIM_5, zuon, 0);
//         pwm_duty_updata(TIM_5, zuop, pwm_sum);
//         pwm_duty_updata(TIM_5, youn, -duty);
//         pwm_duty_updata(TIM_5, youp, pwm_station);   
//      }  
//   }
//   
//   else
//   {
//        pwm_station=-pwm_station;
//        if(pwm_station>=999) pwm_station=999;
//        if(duty>=0)
//        {
//            pwm_sum=duty+pwm_station;
//            if(duty>=999) duty=999;
//            if(pwm_sum>=999) pwm_sum=999;
//            
//     
//        pwm_duty_updata(TIM_5, zuon, pwm_sum);
//        pwm_duty_updata(TIM_5, zuop, 0);
//        pwm_duty_updata(TIM_5, youn, pwm_station);
//        pwm_duty_updata(TIM_5, youp, duty);
//           
//        }
//   
//      else
//      {
//        pwm_sum=pwm_station-duty;
//        if(duty<=-999) duty=-999;
//        if(pwm_sum>=999) pwm_sum=999;
//        
//   
//        pwm_duty_updata(TIM_5, zuon, pwm_station);
//        pwm_duty_updata(TIM_5, zuop, -duty);
//        pwm_duty_updata(TIM_5, youn, pwm_sum);
//        pwm_duty_updata(TIM_5, youp, 0);   
//        
//            
//      }  
//   }
//}




int regression(int *LINE,int startline,int endline)        
{    
    int B;
    int i;
    int sumX=0,sumY=0,avrX=0,avrY=0 ;    
    int num=0,B_up1=0,B_up2=0,B_up,B_down;
    for(i=startline;i<=endline;i++)
    {
        num++;  //总的行数
        sumX+=i;    
        sumY+= (int)LINE[i];
    }
    avrX=sumX/num;//中间行
    avrY=sumY/num;//中间列
    B_up=0;
    B_down=0;
    for(i=startline;i<=endline;i++)
    {        
        B_up1=(int)((int)LINE[i]-avrY);
        B_up2=i-avrX;//有正负值
        B_up+=(int)((B_up1*B_up2));
//        B_up=B_up/100*100;
        B_down+=(int)(((i-avrX)*(i-avrX)));
    }
    if(B_down==0) 
        B=0;
    else 
        B=B_up*16/B_down;//16为放大系数
    return -B;
}



  

void v_speed_set2pwm(int16 leftSpeed,int16 rightSpeed)//ABS停车
{
    
    int16 v_e_L = leftSpeed + val;//S.CL S.CR是左右轮编码器的值，不需要经过处理，直接用真实值
    int16 v_e_R = rightSpeed + (var);
    static int32 v_e_Counter_L = 0;
    static int32 v_e_Counter_R = 0;
    
//    if( meet.turn_C&&meet.turn_C!=2)
//          v_e_L=0;
    int32 v_e_Counter_MayBeNotChange = (v_e_Counter_L + v_e_L + v_e_Counter_R + v_e_R)/2;
            
    int16 v_e = (v_e_L + v_e_R)/2;
    
    float I_endless = (float)v_e_Counter_MayBeNotChange * speed_I;
    if((I_endless > 480)&&(v_e > 0))
	{
		v_e_Counter_MayBeNotChange = (v_e_Counter_L  + v_e_Counter_R)/2;
	}else 
          if((I_endless < -480)&&(v_e <0))
	{
		v_e_Counter_MayBeNotChange = (v_e_Counter_L + v_e_Counter_R)/2;
	}else
	{
                //累加积分
		v_e_Counter_L = v_e_Counter_L + v_e_L;
		v_e_Counter_R = v_e_Counter_R + v_e_R;
	}
    
    int32 v_e_counter = (v_e_Counter_L + v_e_Counter_R)/2;
            
    float OutPWM = v_e * speed_P + v_e_counter * speed_I;
    Left_OutPWM  = OutPWM;
    Right_OutPWM = OutPWM;
    
    if(Left_OutPWM > 950.f)  {Left_OutPWM = 950.f;}
    if(Left_OutPWM < -950.f) {Left_OutPWM = -950.f;}
    
    if(Right_OutPWM > 950.f){Right_OutPWM = 950.f;}
    if(Right_OutPWM < -950.f){Right_OutPWM = -950.f;}
    
}

void ABS()
{
   v_speed_set2pwm(0,0);
          
   if(Right_OutPWM>=0)
   {
      pwm_duty_updata(TIM_5, zuon, 0);
      pwm_duty_updata(TIM_5, zuop, Right_OutPWM);//右轮正    
   }
   else
   {
      pwm_duty_updata(TIM_5, zuon, -Right_OutPWM);
      pwm_duty_updata(TIM_5, zuop, 0);//右轮正    
     
   }
   if(Left_OutPWM>=0)
   {
      pwm_duty_updata(TIM_5, youn, 0); 
      pwm_duty_updata(TIM_5, youp, Left_OutPWM);
   }
   else
   {
     pwm_duty_updata(TIM_5, youn, -Left_OutPWM); 
     pwm_duty_updata(TIM_5, youp, 0); //
   }
}


//float Q_bias, Angle_err;
//float PCt_0, PCt_1, E;
//float K_0, K_1, t_0, t_1;
//float Pdot[4] ={0,0,0,0};
//float PP[2][2] = { { 1, 0 },{ 0, 1 } };
//
//void KalmanFilter(int16 Accel,int16 Gyro)		
//{
//    static float  Gyro_y = 0;
//	fGyroscopeAngleIntegral+=(Gyro - Q_bias)/GYROSCOPE_ANGLE_SIGMA_FREQUENCY; //先验估计
// 
//	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分
// 
//	Pdot[1] = -PP[1][1];
//	Pdot[2] = -PP[1][1];
//	Pdot[3]= Q_gyro;
//	
//	PP[0][0] += Pdot[0]/GYROSCOPE_ANGLE_SIGMA_FREQUENCY;   // Pk-先验估计误差协方差微分的积分
//	PP[0][1] += Pdot[1]/GYROSCOPE_ANGLE_SIGMA_FREQUENCY;   // =先验估计误差协方差
//	PP[1][0] += Pdot[2]/GYROSCOPE_ANGLE_SIGMA_FREQUENCY;
//	PP[1][1] += Pdot[3]/GYROSCOPE_ANGLE_SIGMA_FREQUENCY;
//		
//	Angle_err = Accel - fGyroscopeAngleIntegral;	//-先验估计
//	
//	PCt_0 = GYROSCOPE_ANGLE_RATIO * PP[0][0];
//	PCt_1 = GYROSCOPE_ANGLE_RATIO * PP[1][0];
//	
//	E = R_angle + GYROSCOPE_ANGLE_RATIO * PCt_0;
//	
//	K_0 = PCt_0 / E;
//	K_1 = PCt_1 / E;
//	
//	t_0 = PCt_0;
//	t_1 = GYROSCOPE_ANGLE_RATIO * PP[0][1];
// 
//	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
//	PP[0][1] -= K_0 * t_1;
//	PP[1][0] -= K_1 * t_0;
//	PP[1][1] -= K_1 * t_1;
//		
//	fGyroscopeAngleIntegral	+= K_0 * Angle_err;	 //后验估计
//	Q_bias	+= K_1 * Angle_err;	 //后验估计
//	Gyro_y   = Gyro - Q_bias;	 //输出值(后验估计)的微分=角速度
//         Angle = fGyroscopeAngleIntegral/18;
//	
//}

#define Peried 1/100.0f		//卡尔曼积分周期
#define Q GYROSCOPE_ANGLE_RATIO				//过程噪声2.0		越小积分越慢，跟踪加速度计越慢越平滑
#define R GYROSCOPE_ANGLE_SIGMA_FREQUENCY			//测量噪声5000.0	越小跟踪加速度计越快
float KalmanGain = 1.0f;	//卡尔曼增益

void KalmanFilter(float ACC_Angle)
{
	//卡尔曼滤波局部参量
    static float Priori_Estimation = 0;//先验估计
    static float Posterior_Estimation = 0;//后验估计
    static float Priori_Convariance = 0;//先验方差
    static float Posterior_Convariance = 0;//后验方差
    static float las=0;
    ACC_Angle = (ACC_Angle*8+las*2)/10;
     ACC_Angle = Filter(ACC_Angle);
    las = ACC_Angle;
    g_fGyroscopeAngleSpeed = -(icm_gyro_y-12) * GYROSCOPE_ANGLE_RATIO;
	//卡尔曼滤波
    //1.时间更新(预测) : X(k|k-1) = A(k,k-1)*X(k-1|k-1) + B(k)*u(k) 
    Priori_Estimation = Posterior_Estimation - (-icm_gyro_y-12)*Peried;		//先验估计，积分获得角度
	if (Priori_Estimation != Priori_Estimation)
	{
		Priori_Estimation = 0;
	}
	
    //2.更新先验协方差  : P(k|k-1) = A(k,k-1)*P(k-1|k-1)*A(k,k-1)'+Q(k) 
    Priori_Convariance = (float)sqrt( Posterior_Convariance * Posterior_Convariance + Q * Q );
	if (Priori_Convariance != Priori_Convariance)
	{
		Priori_Convariance = 0;
	}
	
    //  卡尔曼后验估计：测量更新  
    // 1.计算卡尔曼增益  : K(k) = P(k|k-1)*H(k)' / (H(k)*P(k|k-1)*H(k)' + R(k)) /
    KalmanGain = (float)sqrt( Priori_Convariance * Priori_Convariance / ( Priori_Convariance * Priori_Convariance + R * R ) );
	if (KalmanGain != KalmanGain)
	{
		KalmanGain = 1;
	}
	
    //2.测量更新(校正): X(k|k) = X(k|k-1)+K(k)*(Z(k)-H(k)*X(k|k-1)) 
    Posterior_Estimation  = Priori_Estimation + KalmanGain * (ACC_Angle - Priori_Estimation );
	if (Posterior_Estimation != Posterior_Estimation)
	{
		Posterior_Estimation = 0;
	}
	
    // 3.更新后验协方差  : P(k|k) =（I-K(k)*H(k)）*P(k|k-1) 
    Posterior_Convariance = (float)sqrt(( 1 - KalmanGain ) * Priori_Convariance * Priori_Convariance );
	if (Posterior_Convariance != Posterior_Convariance)
	{
		Posterior_Convariance = 0;
	}
	
    //得到最终角度 
        
     
    fGyroscopeAngleIntegral=Posterior_Estimation;
    Angle = -fGyroscopeAngleIntegral/19;
	
//	if (Attitude_Angle.Y != Attitude_Angle.Y)
//	{
//		Attitude_Angle.Y = 1;
//	}
}




    