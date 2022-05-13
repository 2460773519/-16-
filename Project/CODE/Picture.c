#include "Picture.h"

   // if(s_p==0&&stop==0&&yuan==0&&kaishi==0&&banma==0) out_stop();
//    if(stop==0&&sp_yaun_su==0) into_home();
//    if(stop==0&&sp_yaun_su==0&&yuan==0) sancha_bu();
//    if(stop==0&&banma==0&&sp_yaun_su==0) yuanhuan_bu(); 
////图像处理相关变量
float err_ft,dt_err_ft;
int LOW=27,low_yaun=5,low_mov=0,err_ft_bu=0;//0-35
int add=0;
int HIGHT=20;
int White =210;
int Black =210;
int drath=8,drath_banma=27,sobel_yun=20;
int yidong=50;
int L_side[MT9V03X_H]={0},R_side[MT9V03X_H]={0};
int mid[MT9V03X_H]={0};
int  mc_js=0;
int fash_lanya=0;
int sancha_qian=25;
int a_bu[2],b_bu[2],bu_yes=1;
int err_ft_chan=0;
int r;
int yuan_1=0,yuan_2=0,yuan_3=0,yuan_4=0,yuan_5=0,yuan_6=0,yuan_7=0,yuan_8=0,yuan=0,yuan_L=0,yuan_R=0,yuan_x=0,yuan_low=0,yuan_time=0;
int S2_R=0,S2_L=0;//方差
int i_angle=0;
int sancha_fx=0;
int banma=0;
int sz2[3]={0};
float qu_l,qu_r;
char s_cha_num = 1,s_cha_fx=1;  //三叉个数  1 左左 2 左右 3 右左 4 右右   
int sobel_sz[20];
int drath_piont=0;
int sancha_bu_time=8;
int into_yuan=50,out_yuan=79,in_huan_dian=30;
int gui_low=0;
//uint8 image_Gamma[MT9V03X_H][MT9V03X_W];
int g_GammaLUT[256];//全局数组：包含256个元素的gamma校正查找表
int sobe_l[MT9V03X_H]={0},sobe_r[MT9V03X_H]={0};
int yuan_zhi_dian=18;

void BuildTable(float fPrecompensation)
{
   int i;
   float f;
   for(i=0;i<256;i++)
   {
     f=(i+0.5F)/256;//归一化
     f=(float)pow(f,1/2.2);
     g_GammaLUT[i]=(int)(f*256-0.5F);//反归一化
   }
 }

void get_image_Gamma()
{
  int i,j;
  for(i=0;i<MT9V03X_H;i++)
  {
    for(j=0;j<MT9V03X_W;j++)
    {
    //  image_Gamma[i][j]=g_GammaLUT[mt9v03x_image[i][j]];
      mt9v03x_image[i][j]=g_GammaLUT[mt9v03x_image[i][j]];
    }
  }
}

void otsuThreshold()
{
  int max[15]={0};
  int i,j;
  int sum1=0;
  int sum2=0;
  int  temp=0;
  for(i=54;i<59;i++)
  {
    for(j=L_side[i];j<R_side[i];j++)
    {
      temp++;
      
      sum1+=mt9v03x_image[i][j];
    }
  }
  sum2=sum1/temp;
  
  drath_piont=sum2;
//  Black=sum2+5+add;
//  White=sum2+5+add;
}





/************************************************/
/*              差比和                */
/************************************************/
int ddd,dd1,dd2;

int l_dra(uint8 *imgIn, int j)
{
  int dra;
  uint8 *next,*now;
  
  now=&*(imgIn);
  next=&*(imgIn-j);
  dd1=*now;
  dd2=*next;
  dra=100*(*now-*next)/(*now+*next);
  ddd=dra;
  
    return dra;
}
/************************************************/
int dde,de1,de2;

int r_dra(uint8 *imgIn, int j)
{

  int dra;
  uint8 *next,*now;
  
  now=&*(imgIn);
  next=&*(imgIn+j);
  de1=*now;
  de2=*next;

  dra=100*(*now-*next)/(*now+*next);
  dde=dra;
    return dra;
   
}

/*******************200-90***************************/ 
 //x        y  k= -10/100 y=-(sum-100)/10+5;
 //200  =  -5
 //100  =    5
                      

int get_setion_image(int y) //获取边界周围的平均值 基准阈值为8 +- 6
{
  int sum=0,m=0,i,j;
  float k;
  int temp[2];
   

  
  return k;
  
}


void find_side() //方法2
{
  int y=MT9V03X_H-1;
  int lside=MT9V03X_W/2,rside=MT9V03X_W/2;
  int flage_L=0,L_save=0,R_save=159,flage_R=0,find_error=0;
  int use_drath=drath;
  int use_drath_l=drath,use_drath_r=drath;
  int sb_flage=0,sp_flage=0;
  int i,j;
  int zuo=0,you=0;
  int gui_1=0,gui_2=0,gui_3=0,gui_4=0;
  int sobel_num=0;
  int max_yun=0,flash_i=0;
  float k=0;
  int no_mid=0,n;
  static int las_l=0,las_r=0;
  int temp;
  int can_break=1;
  int on_lignt=0;
  
 // get_image_Gamma();
 
  Black=OTSU(mt9v03x_image[0],20,0,MT9V03X_W)+add;
  if(Black>=120) Black=120;
  White=Black;
  otsuThreshold();
  
  k=(180-drath_piont)/20.0-3;
  if(k<-5) k=-5;
  if(k>5)k=5;
  use_drath_l=k+drath;
  use_drath_r=k+drath;

     for(n=50;n>18;n=n-1)  //判断右边界是否跳变很多 连续
     {
       if((R_side[n] - R_side[n-2])>5 || (R_side[n] - R_side[n-2])<-1||R_side[n]==154)
       {
         break;
       }
     }
     
     if(n==18)     can_break=0;
     
    for(n=55;n>18;n=n-1)  //判断右边界是否跳变很多 连续
    {
       if((L_side[n-2] - L_side[n])>5 || (L_side[n-2] - L_side[n])<-1||L_side[n]==5)
       {
         break;
       }
    }
     
     if(n==18)     can_break=0;
    if(mt9v03x_image[59][MT9V03X_W/2]<Black) //中间为黑
    {
      for(lside=79;lside<159;lside++)                         
      {
        if(mt9v03x_image[y][lside]>Black&&mt9v03x_image[y][lside+1]>Black&&mt9v03x_image[y][lside+2]>Black)
        {
          L_side[y]=lside;
          break;
        }
        else
        {
          L_side[y]=5;
        }
      }
      
      for(rside=79;rside>1;rside--)                          
      {
        if(mt9v03x_image[y][rside]>Black&&mt9v03x_image[y][rside-1]>Black&&mt9v03x_image[y][rside-2]>Black)
        {
          R_side[y]=rside;
          break;
        }
        else
        {
          R_side[y]=154;
        }
      }  
    }
   else
   {
     for(lside=79;lside>5;lside--)
     {
         if(l_dra(&mt9v03x_image[59][lside],5)>use_drath)
         {
           if(mt9v03x_image[59][lside-5-2]<White)
           {
            L_side[59]=lside-5;
            break;
           }
           else
           {
             if(lside<=30)  L_side[59]=lside-5;
           }
         }
     }
     if(lside==5) L_side[59]=5;
     
      for(rside=79;rside<154;rside++) 
      {
        if(r_dra(&mt9v03x_image[59][rside],5)>use_drath)
        {
          if(mt9v03x_image[59][rside+5+2]<White)
          {
           R_side[59]=rside+5;
           break;
          }
          else
          {
            if(rside>=129) R_side[59]=rside+5;
          }
        }
      }
      if(rside==154) R_side[59]=154;
   }
   
 //  sobe_l[59]= Sobel(mt9v03x_image[59],L_side[59]);
   
  for(y=58;y>=0;y--)   //找 58 个点
  {   
    //////////////////////确定起始位置///////////////////////////////////////////////////////////////
    sobe_l[y+1]= Sobel(mt9v03x_image[y+1],L_side[y+1]);
//    if(sobe_l[y+1]>350)  sobe_l[y+1]=350;
//    if(sobe_r[y+1]>350)  sobe_r[y+1]=350;
    
    sobe_r[y+1]= Sobel(mt9v03x_image[y+1],R_side[y+1]);

    
    if(y<55) 
    {       
      if(abs(sobe_l[y+1]-sobe_l[y+2])>=150&&y>10) sobe_l[y+1]=sobe_l[y+2];
      if(abs(sobe_r[y+1]-sobe_r[y+2])>=150&&y>10) sobe_r[y+1]=sobe_r[y+2];
      
      temp=((sobe_l[y+1]+sobe_l[y+2]+sobe_l[y+3])/3-225)/15;
      if(temp>3) temp=3;
      if(temp<-3) temp=-3;
      use_drath_l=drath+temp;
      
      temp=((sobe_r[y+1]+sobe_r[y+2]+sobe_r[y+3])/3-225)/15;
      if(temp>3) temp=3;
      if(temp<-3) temp=-3;
      use_drath_r=drath+temp;
        
      if(use_drath_l<=2) use_drath_l=2;
      if(use_drath_l>15) use_drath_l=15;
      
      if(use_drath_r<=2) use_drath_r=2;
      if(use_drath_r>15) use_drath_r=15;
    }
    
    
     if(L_side[y+1]<30) //边界小于30时
     {
        if(L_side[59]==5&&L_side[58]==5&&L_side[57]==5&&L_side[56]==5&&
       R_side[59]==154&&R_side[57]==154&&R_side[58]==154&&R_side[56]==154)  //1 同时丢 十字里面 分2情况
        {
          for(i=59;i>10;i--)
          {
             if(L_side[i]!=154) break;
          }
          if(R_side[i]==5)  //右长 左偏 加边界
          {
            for(i=1;i<20;i++)
          {
          if(mt9v03x_image[y][79-i*5]>=White&&mt9v03x_image[y-5][79-i*5]>=White)
            {
              i++;
              L_save=79+i*5;
              break;
            }
          }
           }
          else
          {
           for(i=1;i<20;i++)
           {
            if(mt9v03x_image[y][79+i*5]>=White&&mt9v03x_image[y-5][79+i*5]>=White)
            {
              L_save=79-i*5;
              break;
            }
           }
          }
        }
        

       
        else if(L_side[59]!=5&&L_side[58]!=5&&L_side[57]!=5&&L_side[56]!=5&&
               R_side[59]!=154&&R_side[57]!=154&&R_side[58]!=154&&R_side[56]!=154) //两边都没丢 三岔 往回加
       {
           for(i=0;i<20;i++)
          {
            if(mt9v03x_image[y][79-i*5]>=White&&mt9v03x_image[y-1][79-i*5]>=White) //减的情况
            {
              
              L_save=79-i*5;
              break;
            }
          }
       }
       
       else if(L_side[59]==5&&L_side[58]==5&&L_side[57]==5&&L_side[56]==5)   //只丢右 边了一遍 
       {
           for(i=1;i<20;i++)
          {
            if(mt9v03x_image[y][79-i*5]>=White&&mt9v03x_image[y-5][79-i*5]>=White) //加的情况
            {
              
              L_save=79-i*5;
              break;
            }
          }
       }
       
        else    //  只丢左边
       {
          for(i=1;i<20;i++)
          {
          if(mt9v03x_image[y][79+i*5]>=White&&mt9v03x_image[y-5][79+i*5]>=White)
            {
              i++;
              L_save=79+i*5;
              break;
            }
          }
       }
     }
     else
     {
       L_save=L_side[y+1];
        for(i=5;i<90;i++)
        {
          if(mt9v03x_image[y][L_side[y+1]+i*1]>=White&&L_save==L_side[y+1])
          {
            L_save=L_side[y+1]+1*i+3;
            break;
          }
        }
     }
     
     if(L_save>=R_side[y+1])   L_save = R_side[y+1];
     
     
     if(R_side[y+1]>129) //左边小于129 的情况
     {
       if(L_side[59]==5&&L_side[58]==5&&L_side[57]==5&&L_side[56]==5&&
       R_side[59]==154&&R_side[57]==154&&R_side[58]==154&&R_side[56]==154)  //同时丢
        {
          for(i=59;i>10;i--)
          {
             if(R_side[i]!=154) break;
          }
          if(L_side[i]==5)  //左边长
          {
               for(i=1;i<20;i++)
              {
                if(mt9v03x_image[y][79+i*5]>=White&&mt9v03x_image[y-5][79+i*5]>=White)
                {
                   R_save=79-i*5;
                   break;
                }
              }
          }
        else
        {
           for(i=1;i<20;i++)
          {
            if(mt9v03x_image[y][79-i*5]>=White&&mt9v03x_image[y-5][79-i*5]>=White)
            {
              
               R_save=79+i*5;
               break;
            }
          }
          
        }
        }
       
        else if(L_side[59]!=5&&L_side[58]!=5&&L_side[57]!=5&&L_side[56]!=5&&
               R_side[59]!=154&&R_side[57]!=154&&R_side[58]!=154&&R_side[56]!=154)
        {
           for(i=0;i<20;i++)
          {
            if(mt9v03x_image[y][79+i*5]>=White&&mt9v03x_image[y-1][79+i*5]>=White)
            {
              
               R_save=79+i*5;
               break;
            }
          }
        }
       else  if(R_side[59]==154&&R_side[57]==154&&R_side[58]==154&&R_side[56]==154)
       {
       for(i=1;i<20;i++)
        {
          if(mt9v03x_image[y][79+i*5]>=White&&mt9v03x_image[y-5][79+i*5]>=White)
          {
             R_save=79+i*5;
             break;
          }
        }
       }
        else
        {
           for(i=1;i<20;i++)
          {
            if(mt9v03x_image[y][79-i*5]>=White&&mt9v03x_image[y-5][79-i*5]>=White)
            {
               R_save=79-i*5;
               break;
            }
          }
          
        }
     }
     
     else
     {
        R_save=R_side[y+1];
        for(i=5;i<90;i++)
        {
          if(mt9v03x_image[y][R_side[y+1]-i*1]>=White&&R_save==R_side[y+1])
          {
            R_save=R_side[y+1]-1*i-3;
            break;
          }
        }

     }
     
      if(R_save<=L_side[y+1])   R_save = L_side[y+1];    
     if(y<=55&&y>=30&&banma==0)
     {
       for(i=L_side[y+1]+2;i<L_side[y+1]+30;i++)
       {
         if(mt9v03x_image[y][i]<White&&mt9v03x_image[y+1][i+1]<White&&mt9v03x_image[y+1][i+2]>=White)
         {
         //  if(beepds==0) beepds=3;
           L_save=i+10;
           break;
         }
       }
       
       for(i=R_side[y+1]-2;i>R_side[y+1]-30;i--)
       {
         if(mt9v03x_image[y][i]<White&&mt9v03x_image[y+1][i-1]<White&&mt9v03x_image[y+1][i-2]>=White)
         {
       //   if(beepds==0) beepds=3;
           R_save=i-10;
           break;
         }
         
       }
     }
      
      
      //////////////////////////////////算出每个点的起找位置////////////////////
     on_lignt=0;
      for(lside=L_save;lside>5;lside--) //左边界
      {
         if(l_dra(&mt9v03x_image[y][lside],5)>use_drath_l&&on_lignt==0)
         {
           if(abs(lside-5-L_side[y+1])<=3)//连续的边界找到了
           {
             if(mt9v03x_image[y][lside-5-2]<White)
             {
                 L_side[y]=lside-5; 
                 break;
             }
             else
             {
               if(y>=10)
               {
                sobel_num=r_dra(&mt9v03x_image[y][lside+2],5);
                if(sobel_num<use_drath_l-1) //100
                {
                //  if(beepds==0&&y>=40) beepds=3;
                   L_side[y]=lside-5; 
                   break;
                }
                else 
                {
                  if(gpio_get(bo_5)) //灯管里 二值找
                  {
                    on_lignt=1;
                    lside=lside+5;
                  }         
                  else     //灯管里  往里减着找
                  {
                    lside=lside-2;
                  }
                //  break;
                }
               }
             }
           }
           else
           {
             if(mt9v03x_image[y][lside-5-2]<White)
             {
                 L_side[y]=lside-5; 
                 break;
             }
           }
         }
         
        if(on_lignt==1&&mt9v03x_image[y][lside]>White&&mt9v03x_image[y][lside-1]<White&&mt9v03x_image[y][lside-2]<White)
        {
          L_side[y]=lside;
          break;
        }
         
        }
      
      if(lside==5)  L_side[y]=5;
     ///////////////验证////y!=27&&y!=29&&y!=28////////////////////////////////
      
//      S2_R=sobel_num=Sobel(mt9v03x_image[y],L_side[y]);
//       if(y<=55&&y>=20&&sobel_num<=sobel_yun&&L_side[y+1]!=5&&banma==0)
//       {
//            max_yun=0;
//            flash_i=0;
//          for(i=0;i<20;i++)
//          {
//            sobel_sz[i]=Sobel(mt9v03x_image[y],L_side[y+1]+i-3);
//            if(max_yun<sobel_sz[i])
//            {
////            if(mt9v03x_image[y][L_side[y+1]+i-3+3]>=White)
////            {
//              max_yun=sobel_sz[i];
//              flash_i=i;
//          //  }
//            }
//        }
//        
////         if(i==20) 
////         {
////           if(L_side[y]-L_side[y+1]<0)   L_side[y]=L_side[y+1]+1;
////           if(L_side[y]-L_side[y+1]>0)   L_side[y]=L_side[y+1]-1;
////         }
//          L_side[y]=L_side[y+1]+flash_i-3;
//      }  
      
      on_lignt=0;
      for(rside=R_save;rside<154;rside++) //右边界
      {
        
         if(r_dra(&mt9v03x_image[y][rside],5)>use_drath_r&&on_lignt==0) 
         {
           if(abs(rside-R_side[y+1]+5)<=3)  //连续
           {
             if(mt9v03x_image[y][rside+5+2]<White)
             {
                R_side[y]=rside+5;
                break;
             }
             else  //可能是灯管或准确边界
             {
               if(y>10)
               {
                 S2_R=sobel_num= l_dra(&mt9v03x_image[y][rside-2],5);
                
                // S2_R=sobel_num=Sobel(mt9v03x_image[y],rside+5-4);
                 if(sobel_num<use_drath_r-1) 
                 {
                    R_side[y]=rside+5;
                    break;
                 }
                 else 
                {
                   if(gpio_get(bo_5)) 
                   {
                      on_lignt=1;
                      rside=rside-5;
                   }
                   else
                   {
                      rside=rside+2;
                   }
                }
               }
               
             }
           }
           else
           {
            if(mt9v03x_image[y][rside+5+2]<White)
            {
                R_side[y]=rside+5;
                break;
            }
           }             
         }
          if(on_lignt==1&&mt9v03x_image[y][rside]>=White&&mt9v03x_image[y][rside+1]<White&&mt9v03x_image[y][rside+2]<White)
          {
                R_side[y]=rside;
                break;
          }
      }
       if(rside==154) R_side[y]=154; 
      
       if(y>=1&&y<=40&&yuan==0&&err_ft_chan==0&&banma==0&&can_break==1) // 归线不找了 18归 25用
       {
         mid[y]=(L_side[y]+R_side[y])/2; 
        if(mt9v03x_image[y][mid[y]]<White&&mt9v03x_image[y+1][mid[y+1]]<White)
        {
          break;
        }
       }
       
      
      
      //////////////////y!=27&&y!=29&&y!=28&&////验证////////////////////// 
      
//       S2_R=sobel_num=Sobel(mt9v03x_image[y],R_side[y]);
//       if(y<=55&&y>=20&&sobel_num<=sobel_yun&&R_side[y+1]!=154&&banma==0)
//       {
//         //if(beepds==0) beepds=3;
//         max_yun=0;
//         flash_i=0;
//        
//        for(i=0;i<20;i++)
//        {
//          sobel_sz[i]=Sobel(mt9v03x_image[y],R_side[y+1]-i+3);
//          if(max_yun<sobel_sz[i])
//          {
////            if(mt9v03x_image[y][R_side[y+1]-i]>=White)
////            {
//              max_yun=sobel_sz[i];
//              flash_i=i;
//              //break;
//           // }
//          }          
//        }
//        //if(sobel_sz[flash_i]>sobel_sz[flash_i+1]&&sobel_sz[flash_i]>sobel_sz[flash_i+1])
////        {
////          if(R_side[y]-R_side[y+1]<0)  R_side[y]=R_side[y+1]+1;
////          if(R_side[y]-R_side[y+1]>0)  R_side[y]=R_side[y+1]-1;
////        }
//             R_side[y]=R_side[y+1]-flash_i+3;
//      }  
//         
  }  
   gui_low=y+5;
   
//   
   for(;y>=0;y--)
   {
     L_side[y]=5;
     R_side[y]=154;
   }   

    
    /*if(stop==0&&banma==0&&sp_yaun_su==0)****if(stop==0) *****if(stop==0 && banma==0) ********///////////////////////////////////////////////////////////////
    if(s_p==0&&stop==0&&yuan==0&&kaishi==0&&banma==0) out_stop();
    if(stop==0&&sp_yaun_su==0) into_home();
    if(stop==0&&sp_yaun_su==0&&yuan==0) sancha_bu();
    if(stop==0&&banma==0&&sp_yaun_su==0) yuanhuan_bu();  
    
    //if(stop==1) yuanhuan_bu();
 //   if(stop==1)  sancha_bu();
   // if(stop==1) into_home();
   // into_home();
    for(y=59;y>=0;y--)
    {  
       mid[y]=(L_side[y]+R_side[y])/2;      //寻找中线
      
      if(err_ft_chan==0&&abs(mid[y]-mid[y+1])>=5&&y<=58&&yuan==0) mid[y] = (mid[y+1]+mid[y])/2;
    }
  //  sancha_bu();
}




void sancha_bu()
{
  int i;
  int fangxiao=0;
  int it;
  float k;
  int y1;
  int n,m;
  int sz1[3]={0},sz2[3]={0};

  static int te=0;//40 38 38 37 55 52 52 49&&L_side[n]!=5  &&R_side[n]!=154
  
     for(n=30;n<=40;n++)
     {
      if(sp_yaun_su==0&&kaishi==0&&yuan_7==0&&te==0&&R_side[n]<R_side[n-2] && R_side[n-2]<R_side[n-3] && R_side[n-4]<R_side[n-5]&& R_side[n-5]<R_side[n-6]&&R_side[n]!=154
         &&mt9v03x_image[n-2][R_side[n]-8]>=White)
      {
       //  S2_R=fabs(regression(R_side,n-7,n));
     //   sz1[0]=1;   
        if(fabs(regression(R_side,n-5,n))<=33&&fabs(regression(R_side,n-5,n))>=2) sz1[0]=n;
      }
      if(L_side[n]>L_side[n-2] && L_side[n-2]>L_side[n-3]&& L_side[n-4]>L_side[n-5]&& L_side[n-5]>L_side[n-6] &&L_side[n]!=5
         &&mt9v03x_image[n-2][L_side[n]+8]>=White) 
      {
       S2_L=fabs(regression(L_side,n-7,n));
      //  sz2[0]=1;
       if(fabs(regression(L_side,n-5,n))<=33&&fabs(regression(L_side,n-5,n))>=2) sz2[0]=n;
      }
      if(sz1[0]!=0&&sz2[0]!=0&&abs(sz1-sz2)<=7)
      {
        for(i=55;i>5;i--)
        {
         // if(mt9v03x_image[i][75]>=White && mt9v03x_image[i-1][75]<White)  sz2[0]=i;
                   
          if(mt9v03x_image[i][79]>=White&&mt9v03x_image[i-1][79]<White) break;
               
        //  if(mt9v03x_image[i][84]>=White && mt9v03x_image[i-1][84]<White)  sz2[2]=i; 
        }
        if(i!=5)
        {
          if(kai==1||kai==2)
          {
            kai=3; //强制跑
            kp=kp-10;
            kd=kd-5;
          }
           if(stop_cuan==1) //开局三叉
           {
           //  beepds=5;
             sancha_bu_time=(45-speed/5)*2;
             if(sancha_bu_time<=30) sancha_bu_time=30;
             stop_cuan=0;
           }
           else sancha_bu_time=16;
           err_ft_chan=1;
           //beep();
           beepds=5;
           te=1;
           sancha_fx++;        
         if(gpio_get(bo_1)) sancha_fx=1;// 三叉是否停车
         
         if(sancha_fx==2&&s_cha_num==1) 
           {
             mc_js=1;
            // sancha_fx=0;
           }
           
           if(sancha_fx==4&&s_cha_num==2) 
           {
             mc_js=1;
            // sancha_fx=0;
           }
           
           if(sancha_fx==6&&s_cha_num==3) 
           {
             mc_js=1;
            // sancha_fx=0;
           }
           
            if(sancha_fx==8&&s_cha_num==4) 
           {
             mc_js=1;
             //sancha_fx=0;
           }
           break;
        }
       }
     }
  
  
    

   if(te>=1) te++;
   
   if(te>sancha_bu_time+10)  //屏蔽时间
   {
    // beepds=5;
     err_ft_chan=0;
     te=0;
//      if(sancha_fx==2&&s_cha_num==1) 
//     {
//       mc_js=1;
//       sancha_fx=0;
//     }
//     
//     if(sancha_fx==4&&s_cha_num==2) 
//     {
//       mc_js=1;
//       sancha_fx=0;
//     }
//     
//     if(sancha_fx==6&&s_cha_num==3) 
//     {
//       mc_js=1;
//       sancha_fx=0;
//     }
//     
//      if(sancha_fx==8&&s_cha_num==4) 
//     {
//       mc_js=1;
//       sancha_fx=0;
//     }
    
   }
   
   
   if(te>=1&&te<=sancha_bu_time) //补线时间
   {
     if(s_cha_num==1) 
     {
       if(s_cha_fx==1) //左
       {
         if(sancha_fx==1)  fangxiao=0;
         if(sancha_fx==2)  fangxiao=1; 
       }
       
       if(s_cha_fx==4) //右
       {
         if(sancha_fx==1)  fangxiao=1;
         if(sancha_fx==2)  fangxiao=0; 
       }
     }
     
     if(s_cha_num==2)
     {
       if(s_cha_fx==1) //左左左右
       {
         if(sancha_fx==1)  fangxiao=0;
         if(sancha_fx==2)  fangxiao=0; 
         if(sancha_fx==3)  fangxiao=0;
         if(sancha_fx==4)  fangxiao=1;
       }
       
       if(s_cha_fx==2) //左右右右
       {
         if(sancha_fx==1)  fangxiao=0;
         if(sancha_fx==2)  fangxiao=1; 
         if(sancha_fx==3)  fangxiao=1;
         if(sancha_fx==4)  fangxiao=1;
       }
       
       if(s_cha_fx==3) //右左左左
       {
         if(sancha_fx==1)  fangxiao=1;
         if(sancha_fx==2)  fangxiao=0; 
         if(sancha_fx==3)  fangxiao=0;
         if(sancha_fx==4)  fangxiao=0;
       }
       
       if(s_cha_fx==4) //右右右左
       {
         if(sancha_fx==1)  fangxiao=1;
         if(sancha_fx==2)  fangxiao=1; 
         if(sancha_fx==3)  fangxiao=1;
         if(sancha_fx==4)  fangxiao=0;
       }
       
     }
     
     if(s_cha_num==3||s_cha_num==4) //3或4个三叉
     {
       if(sancha_fx==s_cha_num*2)  fangxiao=1;
       else fangxiao=0;
     }
     
     if(gpio_get(bo_1)) 
     {
       if(s_cha_fx==1) fangxiao=0;
       if(s_cha_fx==4) fangxiao=1;
     }
     
     
     
     
    
     
     
     if(fangxiao==0) //1右补
     {
        for(i=55;i>10;i--)
        {
          if((mt9v03x_image[i][79]>=White && mt9v03x_image[i-1][79]<White)||i==11)
          {     
               k=1.0*(159-79)/(59-i)*1.0;
               for(it=10;it<59;it++)
               {
                 y1=k*(it-59)+159; 
                 if(y1>=159) y1=159;
                 if(y1<=0) y1=0;
                 R_side[it]=y1;
               }      
              break;
          }
        }      
      }
//     
     if(fangxiao==1)//0左补
     {
       for(i=55;i>10;i--)
        {
          if((mt9v03x_image[i][79]>=White && mt9v03x_image[i-1][79]<White)||i==11)
          {     
               k=1.0*(0-79)/(59-i)*1.0;
               for(it=10;it<59;it++)
               {
                 y1=k*(it-59); 
                 if(y1>=159) y1=159;
                 if(y1<=0) y1=0;
                 L_side[it]=y1;
               }      
              break;
          }
        }
     }
     
   }
  
}
 
 


/*---------------------------------------------------
----------------------入库---------------------------
//-----------------------------------------------------*///stop==0&&
void into_home()
{
  int stop_x,stop_Color=0,stop_Black=1,stop_White=1;
  int y1,it,i,n,m;
  float x=59,y=0,k_x=0,las_kx=0,k;
  int sum=0;
  
//  if(banma==0&&kaishi==0)
//  {   
    
//  for(n=24;n<27;n++)
//  {
//    for(m=40;m<119;m=m+1)
//    {
//      
////      if(((mt9v03x_image[n][m]-mt9v03x_image[n][m+5])*100/(mt9v03x_image[n][m]+mt9v03x_image[n][m+5]))>drath_banma)
////      {
////        stop_Color++;
////      }
//      if(mt9v03x_image[n][m]>=White&&mt9v03x_image[n][m+1]<White|| mt9v03x_image[n][m]<White&&mt9v03x_image[n][m+1]>=White) stop_Color++;
//      
//    }
//    
//     if(stop_Color>drath_banma)
//    {
//     // beep();
//      beepds=5;
//      banma=1;
//      yuan_7=3;
//    }
//    
//  }
//  }
//  
  if(banma==0&&kaishi==0)
  {  
  
  for(n=28;n<31;n++)
  {
    for(m=40;m<119;m=m+1)
    {
//      if(((mt9v03x_image[n][m]-mt9v03x_image[n][m+5])*100/(mt9v03x_image[n][m]+mt9v03x_image[n][m+5]))>drath_banma)
//      {
//        stop_Color++;
//      }
      // if(mt9v03x_image[n][m]>=White&&mt9v03x_image[n][m+1]<White|| mt9v03x_image[n][m]<White&&mt9v03x_image[n][m+1]>=White) stop_Color++;
      
      if(abs(mt9v03x_image[n][m]-mt9v03x_image[n][m+1])>sobel_yun)  stop_Color++;
      
      
    }
  }
  
    if(stop_Color>drath_banma)
    {
     // beep();
      stop_Color=0;
      //beepds=10;
      banma=1;
      yuan_7=3;
    }
  }
  // if(banma_mc>999&&beepds==0) beepds=5;
  if(banma==1)
  {
        for(m=40;m<119;m=m+1)
        {
    //      if(((mt9v03x_image[n][m]-mt9v03x_image[n][m+5])*100/(mt9v03x_image[n][m]+mt9v03x_image[n][m+5]))>drath_banma)
    //      {
    //        stop_Color++;
    //      }
           if(mt9v03x_image[43][m]>=White&&mt9v03x_image[43][m+1]<White|| mt9v03x_image[43][m]<White&&mt9v03x_image[43][m+1]>=White) stop_Color++;
          
        }
        
        if(stop_Color>=9)
        {
          banma=2;
        //  beepds=10;
        }
        
        for(m=40;m<119;m=m+1)
        {
    //      if(((mt9v03x_image[n][m]-mt9v03x_image[n][m+5])*100/(mt9v03x_image[n][m]+mt9v03x_image[n][m+5]))>drath_banma)
    //      {
    //        stop_Color++;
    //      }
           if(mt9v03x_image[50][m]>=White&&mt9v03x_image[50][m+1]<White|| mt9v03x_image[50][m]<White&&mt9v03x_image[50][m+1]>=White) stop_Color++;
          
        }
        
        if(stop_Color>=9)
        {
          banma=2;
        //  beepds=10;
        }
        
        
   }
  if(banma>=1&&banma_mc>=3100)
  {
    banma=0;
    banma_mc=0;
    beepds=10;
    //yuan_7=3;
  }
  
  if(banma_mc==6000)
  {
    banma=0;
    banma_mc=0;
  }
  
  
}


void yuanhuan_bu()
{
  int n,m;
  int sz1[3]={0};
  float k;
  int y1,it,i;
  float x=59,y=0,k_x=0,las_kx=0;
  float k_cha=0;
 if(sp_yaun_su==0&&kaishi==0&&yuan_1==0&&err_ft_chan==0&&yuan_R==0&&yuan_L==0)
   {
     if(((L_side[35]-L_side[29])>=13&&(L_side[35]-L_side[27])>=13&&(L_side[35]-L_side[28])>=13)||
       ((L_side[44]-L_side[37])>=100&&(L_side[44]-L_side[38])>=100&&(L_side[44]-L_side[39])>=100))//左边界跳变
              {
//                if((mt9v03x_image[27][20]>=White&&mt9v03x_image[28][20]>=White)||
//                   (mt9v03x_image[39][20]>=White&&mt9v03x_image[38][20]>=White&&mt9v03x_image[39][79]>=White && mt9v03x_image[38][79]>=White)) //左边跳变里面的点为白
//                {
                   for(n=55;n>yuan_zhi_dian;n=n-1)  //判断右边界是否跳变很多 连续
                   {
                     if((R_side[n] - R_side[n-2])>8 || (R_side[n] - R_side[n-2])<-3||R_side[n]==154)
                     {
                       break;
                     }
                   }
                 if(n==yuan_zhi_dian) 
                 { 
                   sz2[0]=regression(R_side,45,55);
                   sz2[1]=regression(R_side,35,45);
                   sz2[2]=regression(R_side ,20, 35);
                   if(abs(sz2[0]-sz2[1])<=5&& abs(sz2[1]-sz2[2])<=5) //判断右边界整体斜率是否相似
                   {
                     if(sz2[0]<-2&&sz2[0]>-35&&sz2[1]<-2&&sz2[1]>-35&&sz2[2]<-2&&sz2[2]>-35)//右边界斜率在正常范围 圆环咯
                     {    
                       
                       for(i=0;i<3;i++)
                       {
                         if(mt9v03x_image[20][R_side[20]-i]<(Black)||mt9v03x_image[22][R_side[22]-i]<(Black)||mt9v03x_image[24][R_side[24]-i]<(Black)
                          )  break; //屏蔽难受的斑马线
                       }
                       i=3;//是否屏蔽斑马线
                       if(i==3)
                       {
                         if((L_side[44]-L_side[37])>=10&&(L_side[44]-L_side[38])>=10&&(L_side[44]-L_side[39])>=10)
                         {
                           
                              for(n=55;n>18;n=n-1)  //判断右边界是否跳变很多 连续
                               {
                                 if((R_side[n] - R_side[n-3])>14 || (R_side[n] - R_side[n-3])<-1||R_side[n]==144)
                                 {
                                   break;
                                 }
                               }
                             if(n==18)  yuan_low=1;
                             else yuan_7=3;
                           
                          //  beepds=5;
                           yuan_7=3;
                         }
                               beepds=5;
                               LOW=LOW+low_yaun;
      //                        if(LOW>=39) LOW=39;
                               yuan=1;                
                               yuan_1=1;
                               yuan_L=1;
                             //  beep();
                           
                        }
                     
//                         if((L_side[44]-L_side[37])>=10&&(L_side[44]-L_side[38])>=10&&(L_side[44]-L_side[39])>=10) 
//                         {
//                           beepds=5;
//                           LOW=LOW+4;
//  //                        if(LOW>=39) LOW=39;
//                           yuan=1;                
//                           yuan_1=1;
//                           yuan_L=1;
//                         //  beep();
//                           yuan_low=1;
//                         
//                         }
                       }
                    
                     }
                   }
               //  }
                     
                }
                
              
             
   }
  
  
  if(yuan_L==1) //左圆环 处理
  {
    
  if(yuan_1==1 && yuan_3==0) //补线走直
  {
    if(yuan_low==0)
    {
      if(yuan_2==0)
      {
          for(n=55;n>45;n=n-1)  //判断右边界是否跳变很多 连续
          {
           if(L_side[n]!=5)   break;
          }
         if(n==45) 
         {
           yuan_2=1; //入环1
          // beepds=5;
         }
      }
    }
    if(yuan_low==1)
    {
      if(mt9v03x_image[38][20]<White&&mt9v03x_image[39][20]<White) yuan_2=1;
    }
    
     if(yuan_3==0&&yuan_2==1)
    {
       for(n=55;n>45;n=n-1)  //判断右边界是否跳变很多 连续
       {
       if(L_side[n]==5)   break;
       }
       if(n==45) 
       {
         yuan_3=1;//开始入环 2
         beepds=5;
       }
     }
    
     for(n=45;n>=5;n--)
    {
      if((mt9v03x_image[n][77]>=White && mt9v03x_image[n-1][77]<White)||n==6)//找39列第n行黑白跳变
      {
              k=1.0*(77-15)/(n-59)*1.0;
               for(it=10;it<=59;it++)
               {
                 y1=k*(it-59)+15; 
                 if(y1>=159) y1=159;
                 if(y1<=0) y1=0;
                 L_side[it]=y1;
               } 
               break;
      }
    } 
  }
  

  
  if(yuan_3==1&&yuan_4!=2) //补线入环
  {
    if(mt9v03x_image[40][140]>=White && mt9v03x_image[39][140]>=White&&R_side[40]>=140&&R_side[39]>=140)  yuan_4=1; //右边白了
    if(yuan_4==1&&mt9v03x_image[40][140]<White && mt9v03x_image[39][140]<White) { yuan_4=2;beepds=5;}//白到黑 关入环
    
    
    for(n=in_huan_dian;n>5;n--)
    {
      if((mt9v03x_image[n][60]>=White && mt9v03x_image[n-1][60]<White && mt9v03x_image[n-2][60]<White)||n==5)  break;
    }
         k=1.0*(into_yuan-129)/(n-52);
         for(it=10;it<=45;it++)
          {
            y1=k*(it-50)+129; 
               if(y1>=159) y1=159;
               if(y1<=0) y1=0;
               R_side[it]=y1;
          }
    
  }
  
  // if(yuan_4==2 && mt9v03x_image[41][159]<White && mt9v03x_image[42][159]<White&&yuan_5==0) 
  if(yuan_4==2&&yuan_5==0)  //白到黑
  {
    for(n=22;n>17;n--)  // 44 - 32
     {
       if(((R_side[(n-1)*2] - R_side[(n)*2])>15)) //判断右边是不是完全进入环内了 出环补
       {
         beepds=5;
         yuan_5=1;
         break;
       }
     }
  }
  

   
  if(yuan_5==1&&yuan_6==0)  //判断边界连续
  {
//      if(mt9v03x_image[40][155]<White&&mt9v03x_image[42][155]<White) //关出环补
//      {
        for(n=42;n>20;n--)
          {
            if(R_side[n]-R_side[n-1]<=-10|| R_side[n-2]==154 || -regression(R_side,30,45)>=20 || (R_side[n]==R_side[n-3])
               ) break;
            
          }
        if(n==20) 
        {
          beepds=5;
          yuan_6=1;
        }
   //  }
    
    
     for(n=40;n>10;n--)  //出环补
     {
      if(mt9v03x_image[n][80]>=White && mt9v03x_image[n-1][80]<White)  break;
     }
         k=1.0*(out_yuan-130)/(n-59);
         for(it=n;it<=59;it++)
          {
            y1=k*(it-59)+130; 
               if(y1>=159) y1=159;
               if(y1<=0) y1=0;
               R_side[it]=y1;
           }

  }
  
     if(yuan_6==1&&yuan_7==0&&mt9v03x_image[59][1]<White&&mt9v03x_image[59][1]<White&&mt9v03x_image[58][1]<White)//左下角为黑
     {
      // beepds=2;
       yuan_7=1;
     }
     
     if(yuan_7==1&&mt9v03x_image[58][1]>=White&&yuan_7==1&&mt9v03x_image[58][2]>=White
        &&mt9v03x_image[57][1]>=White&&yuan_7==1&&mt9v03x_image[57][2]>=White
          &&mt9v03x_image[56][1]>=White&&yuan_7==1&&mt9v03x_image[56][2]>=White
            &&mt9v03x_image[55][1]>=White&&yuan_7==1&&mt9v03x_image[55][2]>=White) //左下角变白了) //左下角变白了
     {
       yuan_7=2;
     //  beepds=2;
     }
     
     if(yuan_7==2&&mt9v03x_image[59][1]<White&&mt9v03x_image[59][1]<White&&mt9v03x_image[58][1]<White
        &&mt9v03x_image[58][1]<White&&mt9v03x_image[58][1]<White&&mt9v03x_image[57][1]<White)//左下角在次为黑 ，出环咯
     {
         for(n=55;n>35;n=n-1)  //判断右边界是否跳变很多 连续
         {
           if((L_side[n] - L_side[n-2])>0 || (L_side[n] - L_side[n-2])<-5 || L_side[n]==5)
           {
             break;
           }
         }
         if(n==35) yuan_7=3;
     //  beepds=2;
     }
  
  
    if(yuan_6==1) //出环走直
  {
    //yuan_7++;
    for(n=55;n>5;n--)
    {  
      if(mt9v03x_image[n][77]>=White && mt9v03x_image[n-1][77]<White)  break;
    }
         k=1.0*(77-15)/(n-59);
         for(it=n;it<=59;it++)
          {
            y1=k*(it-59)+15; 
               if(y1>=159) y1=159;
               if(y1<=0) y1=0;
               L_side[it]=y1;
           }
  }
  


 }
 
 
 /************右***************************************stop==0&&****/
  if(sp_yaun_su==0&&kaishi==0&&yuan_1==0&&err_ft_chan==0&&yuan_R==0&&yuan_L==0)
   {
     if((-(R_side[35]-R_side[29])>=13&&-(R_side[35]-R_side[27])>=13&&-(R_side[35]-R_side[28])>=13)||
        (-(R_side[44]-R_side[37])>=100&&-(R_side[44]-R_side[38])>=100&&-(R_side[44]-R_side[39])>=100))//左边界跳变
              {
//               if((mt9v03x_image[27][139]>=White&&mt9v03x_image[28][139]>=White) ||
//                  (mt9v03x_image[38][139]>=White&&mt9v03x_image[39][139]>=White&&mt9v03x_image[38][79]>=White && mt9v03x_image[39][79]>=White))
//                {
                   for(n=55;n>yuan_zhi_dian;n=n-1)  //判断右边界是否跳变很多 连续
                   {
                     if((L_side[n-2] - L_side[n])>8 || (L_side[n-2] - L_side[n])<-3||L_side[n]==5)
                     {
                       break;
                     }
                   }
                 if(n==yuan_zhi_dian) 
                 { 
                   sz2[0]=regression(L_side,45,55);
                   sz2[1]=regression(L_side,35,45);
                   sz2[2]=regression(L_side,20,35);
                   if(abs(sz2[0]-sz2[1])<=5&& abs(sz2[1]-sz2[2])<=5) //判断右边界整体斜率是否相似
                   {
                     if(sz2[0]>2&&sz2[0]<35&&sz2[1]>2&&sz2[1]<35&&sz2[2]>2&&sz2[2]<35)//右边界斜率在正常范围 圆环咯
                     {
                       
                       for(i=0;i<3;i++)
                       {
                         if(mt9v03x_image[20][L_side[20]+i]<(Black)||mt9v03x_image[22][L_side[22]+i]<(Black)||mt9v03x_image[24][L_side[24]+i]<(Black)
                          )  break; //屏蔽难受的斑马线
                       }
                       i=3;
                       if(i==3)
                       {
                          if((-(R_side[44]-R_side[37])>=10&&-(R_side[44]-R_side[38])>=10&&-(R_side[44]-R_side[39])>=10)) 
                          {
                                for(n=55;n>18;n=n-1)  //判断右边界是否跳变很多 连续
                                 {
                                   if((L_side[n-3] - L_side[n])>14 || (L_side[n-3] - L_side[n])<-1||L_side[n]==15)
                                   {
                                     break;
                                   }
                                 }
                               if(n==18)  yuan_low = 1;
                               else yuan_7=3;
                             //  beepds=5;
                               yuan_7=3;
                               
                          }
                           beepds=5;
                               LOW=LOW+low_yaun;
      //                        if(LOW>=39) LOW=39;
                               yuan=1;                
                               yuan_1=1;
                               yuan_R=1;
                             //  beep();  
                       }
                  
                     }
                   }
                 }
                     
              //  }
                
              }
             
   }
   if(yuan_R==1) //左圆环 处理
  {
    
    if(yuan_1==1 && yuan_3==0) //补线走直
    {
    if(yuan_low==0)
    {
      if(yuan_2==0)
      {
          for(n=55;n>45;n=n-1)  //判断右边界是否跳变很多 连续
          {
           if(R_side[n]!=154)   break;
          }
         if(n==45) 
         {
           yuan_2=1; //入环1
         //  beepds=5;
         }
      }
    }
    if(yuan_low==1)
    {
      if(mt9v03x_image[38][139]<White&&mt9v03x_image[39][139]<White) yuan_2=1;
    }
    
     if(yuan_3==0&&yuan_2==1)
    {
       for(n=55;n>45;n=n-1)  //判断右边界是否跳变很多 连续
       {
       if(R_side[n]==154)   break;
       }
       if(n==45) 
       {
         yuan_3=1;//开始入环 2
         beepds=5;
       }
     }
    
    for(n=45;n>=5;n--)  
    {
      if((mt9v03x_image[n][82]>=White && mt9v03x_image[n-1][82]<White)||n==6)//补线走直
      {
              k=1.0*(82-144)/(n-59)*1.0;
               for(it=10;it<=59;it++)
               {
                 y1=k*(it-59)+144; 
                 if(y1>=159) y1=159;
                 if(y1<=0) y1=0;
                 R_side[it]=y1;
               } 
               break;
      }
    } 
  }

  
  
  if(yuan_3==1&&yuan_4!=2) //补线入环
  {
     if(mt9v03x_image[40][19]>=White && mt9v03x_image[39][19]>=White&&L_side[40]<=19&&L_side[39]<=19)  yuan_4=1; //右边白了
     if(yuan_4==1&&mt9v03x_image[40][19]<White && mt9v03x_image[39][19]<White) { yuan_4=2; beepds=5;}//白到黑 关入环
     
    for(n=in_huan_dian;n>5;n--)
    {
      if((mt9v03x_image[n][99]>=White && mt9v03x_image[n-1][99]<White&& mt9v03x_image[n-2][99]<White)||n==5)  break;
    }
         k=1.0*(159-into_yuan-30)/(n-52);
         for(it=10;it<=45;it++)
          {
            y1=k*(it-50)+30; 
               if(y1>=159) y1=159;
               if(y1<=0) y1=0;
               L_side[it]=y1;
           }
     
  }
 // if(yuan_4==2 && mt9v03x_image[41][1]<White && mt9v03x_image[42][1]<White&&yuan_5==0)  //白到黑
  if(yuan_4==2&&yuan_5==0)  //白到黑
  {
    for(n=22;n>17;n--)
     {
       if((-(L_side[(n-1)*2] - L_side[(n)*2]))>15) //判断右边是不是完全进入环内了 出环补
       {
         beepds=5;
         yuan_5=1;
         break;
       }
     }
  }
  

   
  if(yuan_5==1&&yuan_6==0)  //判断边界连续
  {
    
//    if(mt9v03x_image[43][0]<White&&mt9v03x_image[46][0]<White) //关出环补
//    {
        for(n=42;n>20;n--)
          {
            if((L_side[n-1]-L_side[n])<=-10 || L_side[n-2]==5 || regression(L_side,30,45)>=20 || (L_side[n-3] == L_side[n])) break;
          }
        if(n==20)
        {
          beepds=5;
          yuan_6=1;
        }
  //  }
    
//        if(mt9v03x_image[43][159]<White&&mt9v03x_image[46][159]<White) //关出环补
//    {
//        for(n=47;n>25;n--)
//          {
//            if(R_side[n]-R_side[n-1]<=-4 || R_side[n-2]>=154 || -regression(R_side,40,50)>=18 || (R_side[n]==R_side[n-2])) break;
//            
//          }
//        if(n==25) 
//        {
//          beepds=5;
//          yuan_6=1;
//        }
//    }
    
    
     for(n=40;n>10;n--)  //出环补
     {
      if(mt9v03x_image[n][79]>=White && mt9v03x_image[n-1][79]<White)  break;
     }
     
         k=1.0*(159-out_yuan-29)/(n-59);
         for(it=n;it<=59;it++)
          {
               y1=k*(it-59)+29; 
               if(y1>=159) y1=159;
               if(y1<=0) y1=0;
               L_side[it]=y1;
          }

  }
  
  
     if(yuan_6==1&&yuan_7==0&&mt9v03x_image[59][159]<White&&mt9v03x_image[59][158]<White&&mt9v03x_image[58][159]<White)//左下角为黑
     {
       yuan_7=1;
     }
     
     if(yuan_7==1&&mt9v03x_image[58][158]>=White&&mt9v03x_image[58][157]>=White
        &&mt9v03x_image[57][158]>=White&&mt9v03x_image[57][157]>=White
          &&mt9v03x_image[56][158]>=White&&mt9v03x_image[56][157]>=White
            &&mt9v03x_image[55][158]>=White&&mt9v03x_image[55][157]>=White) //左下角变白了
     {
       yuan_7=2;
     //  beepds=2;
     }
     
     if(yuan_7==2&&mt9v03x_image[59][159]<White&&mt9v03x_image[59][158]<White&&mt9v03x_image[58][158]<White
        &&mt9v03x_image[58][159]<White&&mt9v03x_image[58][158]<White&&mt9v03x_image[57][158]<White)//左下角在次为黑 ，出环咯
     {
           for(n=55;n>35;n=n-1)  //判断右边界是否跳变很多 连续
         {
           if((R_side[n] - R_side[n-2])<0 || (R_side[n] - R_side[n-2])>5 || R_side[n]==154)
           {
             break;
           }
         }
         if(n==35) yuan_7=3;
     }
  
  if(yuan_6==1) //出环走直
  {
    //yuan_7++;
    for(n=55;n>5;n--)
    {
      if((mt9v03x_image[n][82]>=White && mt9v03x_image[n-1][82]<White)||n==6)  break;
    }
         k=1.0*(82-144)/(n-59);
         for(it=n;it<=59;it++)
          {
            y1=k*(it-59)+144; 
               if(y1>=159) y1=159;
               if(y1<=0) y1=0;
               R_side[it]=y1;
           }
  }
 }
 
  //if(yuan!=0&&yuan_3==0) yuan_time++;
  if(banma_mc>=9000)
  {
    beepds=20;
    yuan_7 = 3;
  }
  
 // if(yuan==1) beepds=0;
 
  if(yuan_7>=3)
  {
    
    if(yuan==1)
    {
      LOW=LOW-low_yaun;
      beepds=5;
    }
    yuan=0;
    yuan_1=0;
    yuan_2=0;
    yuan_3=0;
    yuan_4=0;
    yuan_5=0;
    yuan_6=0;
    yuan_7=0;
    yuan_8=0;
    yuan_L=0;
    yuan_R=0;
    yuan_x=0;
    yuan_low=0;
    banma_mc=0;
  }
  
  //  if(yuan==1) beepds=0;
}





float process_curvity(int x1, int y1, int x2, int y2, int x3, int y3)
{
    float K;
    int S_of_ABC = ((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2;
    //面积的符号表示方向
    int q1 = (int)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    int AB = sqrt(q1);
    q1 = (int)((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    int BC = sqrt(q1);
    q1 = (int)((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
    int AC = sqrt(q1);
    if (AB * BC * AC == 0)
    {
        K = 0;
    }
    else
        K = (float)4 * S_of_ABC / (AB * BC * AC);
    return K;
}



float variance(int *array)
{
    int sum=0;
    int length = 40;
    float average=0;
    float var;
    for (int i = 0; i <= length;i++)
        {
            sum += *(array+i);//求和
        }
        average = sum / length;//求平均值

        for (int i = 0; i <= length;i++)
        {
            var += pow(array[i]-average,2)/length;//求方差
        }
        return  (var);
}

//void out_stop()
//{
//  int black_numbers=0,i=0;
//  if(stop==0&&s_p==0&&kaishi==0)
//  {
//    for(i=0;i<mt9v03x_image[59][MT9V03X_W-1];i++)
//    {
//      if(mt9v03x_image[59][i]<Black)
//      {
//        black_numbers++;
//      }
//    }
//    if(black_numbers>=110)
//    {
//     STOP();
//    }
//  }
//}

void out_stop()
{
  static int stop_delay=0;
  Black=Black-30;
  if((mt9v03x_image[59][69]<Black&&mt9v03x_image[57][69]<Black&&mt9v03x_image[59][89]<Black&&mt9v03x_image[57][89]<Black||mt9v03x_image[58][69]<Black&&mt9v03x_image[55][69]<Black&&mt9v03x_image[58][89]<Black&&mt9v03x_image[55][89]<Black)&&
    (mt9v03x_image[59][39]<Black&&mt9v03x_image[59][120]<Black)&&
     (L_side[59]<=18&&R_side[59]>=141||L_side[57]<=18&&R_side[57]>=141)&&
     (L_side[20]<=18&&R_side[20]>=141||L_side[25]<=18&&R_side[25]>=141||L_side[28]<=18&&R_side[28]>=141))
  {
    if(stop_delay==0)
      stop_delay=1;
  }
  if(stop_delay>=1)
  {
    stop_delay++;
  }
  if(stop_delay==2)
  {
    if(s_p==0)
    {
      STOP();
      stop_delay=0;
    }
    else
      stop_delay=0;
  }
  Black=Black+30;
}

///*---------------------------------------------------
//----------------寻找二值化阈值（大津法）-----------
//-----------------------------------------------------*/
uint8 OTSU(uint8 *imgIn , uint8 Line , uint8 Col_start , uint8 Col_end)
{
  int i,j,Pixe_Count=(Col_end-Col_start)*(55-Line); //像素点总数
  uint8 MinValue,MaxValue;
  int PixelFront=0,PixelAfter=0; //前景、背景像素点数
  float Per_Front=0,Per_After=0;//前景和背景像素点比例
  float  ave_front=0,ave_after=0; //前景、背景灰度平均值
  uint32 Pixel_Value_Front=0,Pixel_Value_After=0; //前景、背景灰度总值  
  uint32 Pixel_Value_Total=0;//灰度总值
  int pixelCount[256]={0};
  float g,g_max=0; 
  uint8 Threshold=0;
  for (i = Line; i < 55; i++)
  {
    for (j = Col_start; j < Col_end; j++)
    {
        pixelCount[(int)imgIn[i * MT9V03X_W + j]]++;  //统计灰度级中每个像素的个数 
    }
  }
 
  for (MinValue = 0; MinValue < 255 && *(pixelCount+MinValue) == 0; MinValue++) ;        //获取最小灰度的值
  for (MaxValue = 255; MaxValue > MinValue && *(pixelCount+MaxValue) == 0; MaxValue--) ; //获取最大灰度的值
  for (i = MinValue; i <= MaxValue; i++)
  {
      Pixel_Value_Total += pixelCount[i] * i;//灰度总值
  }  
  //---------计算最大类间方差
  for (i = MinValue; i < MaxValue; i++)  //i作为阈值，全值遍历
  {
    
      PixelFront += pixelCount[i];       //统计前景点数
      PixelAfter = Pixe_Count - PixelFront;  //统计背景点数
      
      Per_Front = (float)PixelFront/Pixe_Count;    //前景像素百分比  w0
      Per_After = (float)PixelAfter/Pixe_Count;    //背景像素百分比  w1  
      Pixel_Value_Front +=  pixelCount[i]*i;//前景灰度总值
      Pixel_Value_After = Pixel_Value_Total-Pixel_Value_Front; //背景灰度总值
        
      ave_front = (float)Pixel_Value_Front/PixelFront;//前景平均灰度 u0
      ave_after = (float)Pixel_Value_After/PixelAfter; //背景平均灰度 u1
      
      g=Per_Front*Per_After*(ave_front-ave_after)*(ave_front-ave_after);
      if(g>g_max)
      {
        g_max=g; 
        Threshold=i;
      }
  }
  return Threshold;
}

uint32 m_sqrt(uint32 x)
{
  uint16 ans=0,p=0xffff;
  while(p!=0)
  {
    ans+=p;
    if(ans*ans>x)
    {
    ans-=p;
    }
    p=(uint16)(p/2);
  }
  return(ans);
}

int Sobel(uint8 *imgIn, int j)
{
  int x,y;
  uint16 grad;
  uint8 *up,*down;
  //运用一对卷积数列分别作用于x,y方向 
     up=&*(imgIn - 159);
     down=&*(imgIn + 159);
    //x方向梯度
        x=  *( up  + j+1)  //a2 imgIn - lineByte
        +2* *(imgIn+ j+1)  //a3
        +   *(down + j+1)  //a4
        -   *(up   + j-1)  //a0
        -2* *(imgIn+ j-1)  //a7
        -   *(down + j-1); //a6         
     //y方向梯度
        y=  *(up   + j-1)  //a0
        +2* *(up   +  j )  //a1
        +   *(up   + j+1)  //a2
        -   *(down + j-1)  //a6
        -2* *(down +  j )  //a5
        -   *(down + j+1); //a4
     grad=m_sqrt( (uint32)(x*x+y*y) );
   return grad;   
}

