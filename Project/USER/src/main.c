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
 *                     /  _||| v|| �� |||||-  \
 *                     |   | \\\  -  /// |   |
 *                     | \_|   ''\---/''  |   |
 *                     \  .-\__  `-`  ___/-. / 
 *                   ___`. .'  /--.--\  `. . __
 *                ."" '<  `.___\_<|>_/___.'  >'"". 
 *               | | :  `- \`.;`\ _ /`;.`/ - ` : | |  
 *               \  \ `-.   \_ __\ /__ _/   .-` /  /  
 *          ======`-.____`-.___\_____/___.-`____.-'======
 *                             `=    ---='
 *          ^^^^^^^^^^^7��8�մ���^^^^^^^^^^^^^^^^^^^^^^^^^  �������͹���    
*/     //7��4
//7��4�� ����gammaУ��ͼ��ûʲôЧ��������ʶ������ʱ�����У�����ÿһ���㶯̬��Ⱥ���ֵЧ�������ԣ�
//��ģ�ٶ�����Ϊ��2.2Ϊ��������䲻��ô����.�޸����治��ǣ��Ź��û�ҵ�û���ߣ����Լ���else
//7��13 д����������ĵƹ����⣬�����������Ӧ��ͬ�Ĵ����ò����л�������û������������һ�����ӣ���
//����һЩ��ץ����ǿ�����Ƚϻ�̧�֡���������ʱ��Ҫ�Զ���Ӧ������
//7��14 ��ǿ�����ʶ������ˣ�����ڶ�״̬����һ������ʶ�� 50�к�43�С��ܽ�ʱ���ֱ������������ָϽ�����

int main(void)  
{ 
  
    csh();//��ʼ��
   // BuildTable(2.2);
//     while(1)        
//        {    
//          uart_putchar(UART_4,'S');
////              pwm_duty_updata(TIM_5, zuon, 700);
////              pwm_duty_updata(TIM_5, zuop, 0);//������       
////              pwm_duty_updata(TIM_5, youn, 0); 
////              pwm_duty_updata(TIM_5, youp, 700); //����� 
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
    //////////////ң�س�///////////////////
          if(yaokong==1)
             {
              uart_query(UART_4,&fon);
              if(fon!='B'&&beepds==0) beepds=5; 
             //systick_start(); 
              if(fon=='A')  stop=0; //beep
              if(fon=='C')  STOP(); //ͣ��
              if(fon=='E') duty=70; //��
              if(fon=='G') duty=-70;//��
              if(fon=='I'&&expd>=10) expd=expd-5; //����
              if(fon=='K'&&expd<100) expd=expd+5; //����
              if(fon=='B') duty=0;
              
             // las_fon=fon;
              }
    /////////////////ң�س�///////////
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



  


  