#include "MENU.h"
//
//菜单相关变量
int t=0;
uint8 se=0;
int stop=1;
int kaishi=0;
int beepds=0;
int ok_data=0;



///*--------------------------------------------------
//-------------------初始化函数-----------------------
//----------------------------------------------------*/
void csh()
{ 
//   gpio_init(B13, GPO, GPIO_HIGH, GPO_PUSH_PULL);        // 单片机LED灯
//   gpio_init(H2 , GPO, GPIO_HIGH, GPO_PUSH_PULL);        // 单片机LED灯
   gpio_init(beepd, GPO, GPIO_LOW, GPO_PUSH_PULL);        // 蜂鸣器
   
   gpio_init(up, GPI, GPIO_HIGH, GPI_FLOATING_IN);      //按键：上
   gpio_init(down, GPI, GPIO_HIGH, GPI_FLOATING_IN);	//按键：下
   gpio_init(ok, GPI, GPIO_HIGH, GPI_FLOATING_IN);	//按键：确定
   gpio_init(returnd, GPI, GPIO_HIGH, GPI_FLOATING_IN);	//按键：返回
   gpio_init(jia, GPI, GPIO_HIGH, GPI_FLOATING_IN);	//按键：加
   gpio_init(jian, GPI, GPIO_HIGH, GPI_FLOATING_IN);	//按键：减
   
   gpio_init(bo_1, GPI, GPIO_HIGH, GPI_FLOATING_IN);      
   gpio_init(bo_2, GPI, GPIO_HIGH, GPI_FLOATING_IN);
   gpio_init(bo_3, GPI, GPIO_HIGH, GPI_FLOATING_IN);
   gpio_init(bo_4, GPI, GPIO_HIGH, GPI_FLOATING_IN);
   
   //编码器初始化
   tim_encoder_init(TIM_3, TIM_3_ENC1_B04, TIM_3_ENC2_B05);				// 初始化 TIM_1 B005/06 正交编码器采集
   tim_encoder_init(TIM_4, TIM_4_ENC1_B06, TIM_4_ENC2_B07);				// 初始化 TIM_8 C00/C01 正交编码器采集
   
  //电机初始化
   pwm_init(TIM_5, TIM_5_CH1_A00, 16000, 0);                              // 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
   pwm_init(TIM_5, TIM_5_CH2_A01, 16000, 0);                              // 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
   pwm_init(TIM_5, TIM_5_CH3_A02, 16000, 0);                              // 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
   pwm_init(TIM_5, TIM_5_CH4_A03, 16000, 0);                              // 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
   
   //外设初始化
    lcd_init(); 
    icm20602_init();
    mt9v03x_init();
//   


   //中断初始化
    uart_init(UART_4,115200,UART4_TX_C10,UART4_RX_C11);
    tim_interrupt_init_ms(TIM_6,2, 0,0);
     //tim_interrupt_disable(TIM_6);
     
    tim_interrupt_init_ms(TIM_7,5,1,1);
    //tim_interrupt_enable(TIM_7);
     tim_interrupt_disable(TIM_7);
    uart_rx_irq(UART_4,0);
}
//
//
void caidan()
{
  beep();
  if(key_judge(up)) 
  {
    
    t++;
    lcd_clear(WHITE);
    if(t>7) t=0;
  }
  
  if(key_judge(down)) 
  {
    t--;
    lcd_clear(WHITE);
    if(t<0) t=7;
  }
   lcd_showstr(0,(uint8)t,">");
/*---------------直立-----------------*/
  if(se==1)
  {         
      lcd_showstr(10,0,"yu_zi_di");
     lcd_showint8(75,0,(int)(yuan_zhi_dian));

     lcd_showint8(75,1,(int)(wan_point));
     lcd_showstr(10,1,"wan_point");
    
    lcd_showstr(120,1,"err");
    lcd_showint16(105,2,(err));
                 
     lcd_showstr(10,2,"kp");
     lcd_showint8(75,2,(int)(kp));
    
     lcd_showstr(10,3,"kd");
    lcd_showint8(75,3,kd);
    
    lcd_showstr(10,4,"LOW");
    lcd_showint8(75,4,LOW);
    
    lcd_showstr(10,5,"expd");
    lcd_showint8(75,5,expd);
                  
    

    if(key_judge(jia))
    {

      if(t==0) yuan_zhi_dian=yuan_zhi_dian+1; 
      if(t==1) wan_point=wan_point+1;
      if(t==2) kp=kp+1;
      if(t==3) kd=kd+1;
      if(t==4) LOW=LOW+1;
      if(t==5) expd=expd+1;

      if(t==8) se=8;
    }
    
    if(key_judge(jian))
    {
      if(t==0) yuan_zhi_dian=yuan_zhi_dian+1;
      if(t==1) wan_point=wan_point-1;
      if(t==2) kp=kp-1;
      if(t==3) kd=kd-1;
      if(t==4) LOW=LOW-1;
      if(t==5) expd=expd-1;

      if(t==8) se=8;
    }
  }
  
  /***************************转向**************/
  
  if(se==3)
  {    
    
    lcd_showstr(10,0,"P1");
    lcd_showint8(75,0,P1);
    
    lcd_showstr(10,1,"d1");
    lcd_showint8(75,1,d1);
    
    lcd_showstr(10,2,"kp_g");
    lcd_showint8(75,2,kp_g);
    
    lcd_showstr(10,3,"kd_g");
    lcd_showint8(75,3,kd_g);
    
    lcd_showstr(120,1,"duty");
    lcd_showint16(105,2,(duty));
    
    lcd_showstr(10,4,"ca_su");
    lcd_showint16(75,4,(ca_su));
    

    
//    lcd_showstr(10,6,"fuzz_kp");
//    lcd_showfloat(75,6,fuzz_kp,2,3);
  ////////////////////  
 
    
    
    
    
    
    
    
    
    if(key_judge(jia))
    {
      if(t==0) P1=P1+1;
      if(t==1) d1=d1+1;
      if(t==2) kp_g=kp_g+1;
      if(t==3) kd_g=kd_g+1;
      if(t==4) ca_su=ca_su+100;
      if(t==5) kp_tai=kp_tai+1;
      if(t==6) fuzz_kp=fuzz_kp+0.5;

      if(t==8) se=8;
    }
    
    if(key_judge(jian))
    {
      if(t==0) P1=P1-1;
      if(t==1) d1=d1-1;
      if(t==2) kp_g=kp_g-1;
      if(t==3) kd_g=kd_g-1;
      if(t==4) ca_su=ca_su-100;
      if(t==5) kp_tai=kp_tai-1;
      if(t==6) fuzz_kp=fuzz_kp-0.5;

      if(t==8) se=8;
    }
  }
  
  /***************************传球**************/
  if(se==4)
  {    
      
    lcd_showstr(10,0,"mc_dis");     lcd_showint16(75,0,mc_dis);
    lcd_showstr(10,1,"stop_time");  lcd_showint16(75,1,(stop_time)); 
    lcd_showstr(10,2,"s_cha_num");  lcd_showint16(75,2,s_cha_num);
    lcd_showstr(10,3,"s_cha_fx");   lcd_showint16(75,3,s_cha_fx);
    lcd_showstr(10,4,"gogogo_dis"); lcd_showint16(75,4,gogogo_dis);
    
    
    
//    lcd_showstr(10,4,"kp_speed");
//    lcd_showint16(75,4,kp_speed);
    
    
    
//    lcd_showstr(10,0,"mc_dis");
//    lcd_showint16(75,0,mc_dis);
//    
//    lcd_showstr(10,1,"stop_time");
//    lcd_showint16(75,1,(int)(stop_time));
        

    if(key_judge(jia))
    {
      if(t==0) mc_dis=mc_dis+100;
      if(t==1) stop_time=stop_time+1;
      if(t==2) s_cha_num=s_cha_num+1;
      if(t==3) s_cha_fx=s_cha_fx+1;
      if(t==4) gogogo_dis=gogogo_dis+10;
      
    }
    
    if(key_judge(jian))
    {
      if(t==0) mc_dis=mc_dis-100;
      if(t==1) stop_time=stop_time-1;
      if(t==2) s_cha_num=s_cha_num-1;
      if(t==3) s_cha_fx=s_cha_fx-1;
      if(t==4) gogogo_dis=gogogo_dis-10;
    }
    
    
  }
  
   /***************************高速*************/
  
  if(se==5)
  {    
      
    lcd_showstr(10,0,"kp_low");
    lcd_showint16(75,0,kp_low);
    
    lcd_showstr(10,1,"ex_sped");
    lcd_showint16(75,1,(int)(expd_speed));
    
    lcd_showstr(10,2,"kp_speed");
    lcd_showint16(75,2,kp_speed);
    
    lcd_showstr(10,3,"ex_spedlo");
    lcd_showint16(75,3,expd_speed_low);
    


    if(key_judge(jia))
    {
        if(t==0) kp_low=kp_low+1;
        if(t==1) expd_speed=expd_speed+1;
        if(t==2) kp_speed=kp_speed+1;
        if(t==3) expd_speed_low=expd_speed_low+1;
      
    }
    
    if(key_judge(jian))
    {
       if(t==0) kp_low=kp_low-1;
       if(t==1) expd_speed=expd_speed-1;
       if(t==2) kp_speed=kp_speed-1;
       if(t==3) expd_speed_low=expd_speed_low-1;
    }
    
    
  }
  
   /***************************yuan_su**************/
  if(se==6)
  {    
      
    lcd_showstr(10,0,"low_yaun");
    lcd_showint16(75,0,(low_yaun));
    
    lcd_showstr(10,1,"into_yuan");
    lcd_showint16(75,1,into_yuan);
    
    lcd_showstr(10,2,"out_yuan");
    lcd_showint16(75,2,out_yuan);
    
    lcd_showstr(10,3,"in_h_d");
    lcd_showint16(75,3,in_huan_dian);

    
    lcd_showstr(10,4,"drath_banma");
    lcd_showint16(75,4,drath_banma);
    
    lcd_showstr(10,5,"s_p_Angel");
    lcd_showint8(75,5,s_p_Angel);
    
    lcd_showstr(10,6,"s_p_mc");
    lcd_showint16(75,6,s_p_mc);
    
    lcd_showstr(10,7,"x_p_Angle");
    lcd_showint16(75,7,s_p_speed);
    

    
    
    
//    lcd_showstr(10,0,"mc_dis");
//    lcd_showint16(75,0,mc_dis);
//    
//    lcd_showstr(10,1,"stop_time");
//    lcd_showint16(75,1,(int)(stop_time));
        

    if(key_judge(jia))
    {
      if(t==0) low_yaun=low_yaun+1;
      if(t==1) into_yuan=into_yuan+1;
      if(t==2) out_yuan=out_yuan+1;
      if(t==3) in_huan_dian=in_huan_dian+1;
      if(t==4) drath_banma=drath_banma+1;
      if(t==5) s_p_Angel=s_p_Angel+1;
      if(t==6) s_p_mc=s_p_mc+1;
      if(t==7) s_p_speed=s_p_speed+1;
      
    }
    
    if(key_judge(jian))
    {
      if(t==0) low_yaun=low_yaun-1;
      if(t==1) into_yuan=into_yuan-1;
      if(t==2) out_yuan=out_yuan-1;
      if(t==3) in_huan_dian=in_huan_dian-1;
      if(t==4) drath_banma=drath_banma-1;
      if(t==5) s_p_Angel=s_p_Angel-1;
      if(t==6) s_p_mc=s_p_mc-1;
      if(t==7) s_p_speed=s_p_speed-1;
    }
    
    
  }
  
/*---------------图像-----------------*/
  if(se==2) 
  {
    if(t<4)
    {
      lcd_clear(WHITE);
      t=4;
    } 
    
    lcd_showfloat(60,4,err_ft,2,3);
    lcd_showstr(10,4,"err_ft");
   
    
    lcd_showstr(100,4,"drath");
    lcd_showint8(125,4,drath );
    
    lcd_showstr(10,5,"yidong");
    lcd_showint16(65,5,yidong);
    
    lcd_showint8(125,5,White);
    
    lcd_showstr(10,7,"add");
    lcd_showint16(40,7,add);
    
    lcd_showint16(100,6,sobel_yun);
    lcd_showstr(10,6,"sobel_yun");
    
   // lcd_showint16(0,6,S2_L);
   // lcd_showint16(0,6,S2_L);
   // lcd_showint16(70,6,S2_R);
    
  //  lcd_showstr(120,7,"err");
    lcd_showint8(115,7,(Angle));
    
   if(err_ft_bu==0) lcd_displayimage032(mt9v03x_image[0],160,60);
    //if(err_ft_bu==0) lcd_displayimage032_hui(image_Gamma[0],160,60);
    
   else lcd_displayimage032_hui(mt9v03x_image[0],160,60);
       
    

    if(key_judge(jia))
    {
      if(t==5) yidong=yidong+1;
      if(t==7) add=add+1;
      if(t==4) drath=drath+1;
      if(t==6) sobel_yun=sobel_yun+1;
//      if(t==2) kp_g=kp_g+1;
//      if(t==3) kd_g=kd_g+1;
    
      if(t==8) se=8;
    }
    
    if(key_judge(jian))
    {
      if(t==5) yidong=yidong-1;
      if(t==7) add=add-1;
      if(t==4) drath=drath-1;
      if(t==6) sobel_yun=sobel_yun-1;
//      if(t==2) kp_g=kp_g-1;
//      if(t==3) kd_g=kd_g-1;
//      
//    
//      if(t==8) se=8;
    }
    if(key_judge(ok)) err_ft_bu=~err_ft_bu;
    
 
  }
    
    
    
//    lcd_showint8(110,4,a);
//    lcd_showint8(110,5,b);
//    lcd_showint8(110,6,c);
//    lcd_showint8(110,7,d);
    
    
   // lcd_showint16(0,6,r);
    
    
    
  
  
/*---------------目录-----------------*/  
  if(se==0)
  {
    lcd_showstr(25,0,"go_go_go");
    lcd_showstr(25,1,"zhili");
    lcd_showstr(25,2,"image");
    lcd_showstr(25,3,"turn");
    lcd_showstr(25,4,"chuanqiu");
    lcd_showstr(25,5,"High speed");
    lcd_showstr(25,6,"yuan_su");
    lcd_showstr(25,7,"distence");
    lcd_showuint16(100,7,distence);
    if(key_judge(ok))
    {
      if(t==0)  
      {
//        GYROSCOPE_ANGLE_SIGMA_FREQUENCY=GYROSCOPE_ANGLE_SIGMA_FREQUENCY+27;
//        GYROSCOPE_ANGLE_RATIO=GYROSCOPE_ANGLE_RATIO-0.8;
        
        if(!gpio_get(bo_1))  //接力
        {
          stop_cuan=1;
          lcd_clear(WHITE);
          systick_delay_ms(1000); 
          tim_interrupt_disable(TIM_6);
          uart_rx_irq(UART_4,1);
          distence=200;
        while(1)
        {
          if(!gpio_get(bo_8)) //跑着接
          {
          lcd_showstr(10,0,"distence");
          lcd_showint16(75,0,(distence));
        //  get_icm20602_gyro();
          dataGet=0x00;
          kp=kp+10;
          kd=kd+5;
//          if(abs(icm_gyro_y)>=200) 
        // { 
//            tim_interrupt_disable(TIM_6);
//            uart_rx_irq(UART_4,1);        
            while(1)
            {
              lcd_showstr(10,0,"distence");
              lcd_showint16(75,0,(distence));    
              
              lcd_showstr(10,1,"dataGet");
              lcd_showint16(75,1,dataGet); 
              
//              if(ok_data==1)
//              {
//                 dist1=Dist[2]<<8|Dist[1];
//                 dist2=Dist[4]<<8|Dist[3];
//                 distence=dist2<<16|dist1; 
//                 dataGet=Dist[5]; 
//                 ok_data=0;
//              }
//              
             // uart_putchar(UART_4,'S');
              if(distence<gogogo_dis&&dataGet=='Z') break;
              //if(dataGet=='G') break;
              if(key_judge(ok)) break;
            }
            uart_rx_irq(UART_4,0);
            dataGet=0x00;
//          pwm_duty_updata(TIM_5, zuon, 0);
//          pwm_duty_updata(TIM_5, zuop, 250);//左轮正       
//          pwm_duty_updata(TIM_5, youn, 0); 
//          pwm_duty_updata(TIM_5, youp, 250); //右轮正//右轮正
//          systick_delay_ms(400); 
          tim_interrupt_enable(TIM_6); 
          break;  
        }
        else //躺着接
        {
          lcd_showstr(10,0,"distence");
          lcd_showint16(75,0,(distence));
          get_icm20602_gyro();
          if(abs(icm_gyro_y)>=200) 
          { 
//            tim_interrupt_disable(TIM_6);
//            uart_rx_irq(UART_4,1);        
            while(1)
            {
              
//              lcd_showstr(10,0,"distence");
//              lcd_showint16(75,0,(distence));
              
              uart_putchar(UART_4,'S');
              if(dataGet=='G') break;
              if(key_judge(ok)) break;
            }
            uart_rx_irq(UART_4,0);
            
            dataGet=0x00;
//          pwm_duty_updata(TIM_5, zuon, 0);
//          pwm_duty_updata(TIM_5, zuop, 250);//左轮正       
//          pwm_duty_updata(TIM_5, youn, 0); 
//          pwm_duty_updata(TIM_5, youp, 250); //右轮正//右轮正
//          systick_delay_ms(400); 
          tim_interrupt_enable(TIM_6);
      //    beep();  
          break;
          }
          
        }
        }
        
        }
//      kd_ping=kd;
//      kp_ping=kp;
      //  expd = expd-10;
      //  mc_quan=0;
       if(!gpio_get(bo_8)) kai=1;
       else kai=0;
       // if(s_p!=0) s_p=1000;  
      //  if(s_p==1) s_p=2;
        if(banma>=1) banma_mc=6000;
        kaishi=170;//开局屏蔽元素 多少时间
        mc_js=0;   //开启脉冲计数
        sancha_fx = 0; //三叉初始化0个
        stop = 0;
        if(!gpio_get(bo_1)) t=4; //默认去第几页
        else t=0;
        yuan_7=3;     
      }
      if(t==0) {se=0;t=1;}
      if(t==1) se=1;
      if(t==2) se=2;
      if(t==3) se=3;
      if(t==4) se=4;
      if(t==5) se=5;
      if(t==6) se=6;
      if(t==7) se=7;
      if(t==8) se=8;
      t=t-1;
      lcd_clear(WHITE);
    }
  }

/*---------------返回最初-----------------*/    
  if(key_judge(returnd))
  {
    lcd_clear(WHITE);
    se=0;
    t=0;
  }
}

//
//
////--------------------------------------------------------------------------
////-------------------------------判断按键是否按下---------------------------
////--------------------------------------------------------------------------
char key_judge(PIN_enum pin)
{
  if(gpio_get(pin)==0)
  {
    systick_delay_ms(30);
    if(gpio_get(pin)==0)
    {
      gpio_set(beepd,1);
      systick_delay_ms(10);
      gpio_set(beepd,0);
      return 1;
    }
    else return  0;
  }
  else return 0;
}
//
//
///*----------------------------------------------------------------------
//-----------------------------------蜂鸣器-------------------------------
//------------------------------------------------------------------------*/
void beep()
{
   
  if(beepds>temp1)   temp1++;
  if(temp1==2)  gpio_set(beepd,1);
  if(temp1==beepds)
  {
    temp1=0;
    gpio_set(beepd,0);
    beepds=0;
  }
}


void caidan_sta()
{
    lcd_showstr(25,0,"g_Adjust");
    lcd_showint16(90,0,GYROSCOPE_ANGLE_SIGMA_FREQUENCY);
    
    lcd_showstr(25,1,"g_pili*");
    lcd_showint16(90,1,(int)(GYROSCOPE_ANGLE_RATIO*10));
    if(key_judge(jian)) GYROSCOPE_ANGLE_SIGMA_FREQUENCY=GYROSCOPE_ANGLE_SIGMA_FREQUENCY-1;
    if(key_judge(jia)) GYROSCOPE_ANGLE_SIGMA_FREQUENCY=GYROSCOPE_ANGLE_SIGMA_FREQUENCY+1;
    if(key_judge(up)) GYROSCOPE_ANGLE_RATIO=GYROSCOPE_ANGLE_RATIO-0.2;
    if(key_judge(down)) GYROSCOPE_ANGLE_RATIO=GYROSCOPE_ANGLE_RATIO+0.2;
}


