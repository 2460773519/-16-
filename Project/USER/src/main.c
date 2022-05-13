#include "headfile.h"
/**            
 *                             _ooOoo_                                                       
 *                            o8888888o
 *                            88" . "88
 *                            (| -_- |)
 *                            O\  = /O
 *                          ____/`---'\____
 *                       .'  \\|     |//  `.
 *                      /  \\|||  :  |||//  \   
 *                     /  _||| v|| 金 |||||-  \
 *                     |   | \\\  -  /// |   |
 *                     | \_|   ''\---/''  |   |
 *                     \  .-\__  `-`  ___/-. / 
 *                   ___`. .'  /--.--\  `. . __
 *                ."" '<  `.___\_<|>_/___.'  >'"". 
 *               | | :  `- \`.;`\ _ /`;.`/ - ` : | |  
 *               \  \ `-.   \_ __\ /__ _/   .-` /  /  
 *          ======`-.____`-.___\_____/___.-`____.-'======
 *                             `=    ---='
 *          ^^^^^^^^^^^7月8日代码^^^^^^^^^^^^^^^^^^^^^^^^^  哈尔滨和桂林    
*/     //7月4
//7月4日 尝试gamma校正图像，没什么效果，上坡识别起步有时会误判，尝试每一个点动态差比和阈值效果不明显，
//车模速度量改为除2.2为了弯道出弯不那么外切.修复三叉不打角，放光点没找到没补线，所以加了else
//7月13 写了赛道里面的灯管问题，两种情况，对应不同的处理用拨码切换。参数没多大调整，换了一个轮子，会
//更软一些，抓地力强，但比较会抬轮。到比赛的时候要自动适应赛道。
//7月14 加强三叉的识别加严了，斑马第二状态来了一个备用识别 50行和43行。跑接时如果直立轮子起飞三轮赶紧减速

int main(void)  
{ 
  
    csh();//初始化
   // BuildTable(2.2);
//     while(1)        
//        {    
//          uart_putchar(UART_4,'S');
////              pwm_duty_updata(TIM_5, zuon, 700);
////              pwm_duty_updata(TIM_5, zuop, 0);//左轮正       
////              pwm_duty_updata(TIM_5, youn, 0); 
////              pwm_duty_updata(TIM_5, youp, 700); //右你吧 
//        }
      while(1)        
        {                
          if(mt9v03x_finish_flag)  
           {  
            // systick_start();
             
              mt9v03x_finish_flag=0;  
              if(yaokong==0) find_side();
             // use_time=systick_getval_ms();
              // get_setion_image(30);
    //////////////遥控车///////////////////
          if(yaokong==1)
             {
              uart_query(UART_4,&fon);
              if(fon!='B'&&beepds==0) beepds=5; 
             //systick_start(); 
              if(fon=='A')  stop=0; //beep
              if(fon=='C')  STOP(); //停车
              if(fon=='E') duty=70; //左
              if(fon=='G') duty=-70;//右
              if(fon=='I'&&expd>=10) expd=expd-5; //减速
              if(fon=='K'&&expd<100) expd=expd+5; //加速
              if(fon=='B') duty=0;
              
             // las_fon=fon;
              }
    /////////////////遥控车///////////
            // use_time=systick_getval_ms();
            if(stop==1)  
            {    
//              S2_L=regression(L_side,35,45);
//              S2_R=regression(R_side,35,45);
//              yidong=Sobel(mt9v03x_image[30],L_side[30]-10);
            // S2_L= -regression(R_side,30,45);
            //  lcd_displayimage032(mt9v03x_image[0],160,60);
             caidan();        
             //ABS();
//            S2_R=fabs(regression(R_side,35,45));
//            S2_L=fabs(regression(L_side,35,45));  
            //caidan_sta(); 

            }
            else
            {     
           //   laya_send(); 
             // beep();
              if(key_judge(ok)&&kaishi==0) STOP();           
            }
             beep();
          //use_time=systick_getval_ms();
             //laya_send(); 
//                send_data[0]=S2_L;    
//                send_data[1]=S2_R;
//                send_data[2]=Angle;
//                send_data[3]=low_mov;
//                send_data[4]=speed_Angle;
//                Data_Send(UART_4,send_data);   
//                uart_putchar(UART_4,0x33);
            }
        }     

}



  


  