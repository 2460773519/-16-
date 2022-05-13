#ifndef _Picture_h
#define _Picture_h

#define yu White
#include "headfile.h"
extern float err_ft,dt_err_ft;
extern int LOW,low_yaun,low_mov,err_ft_bu,Black;
extern int  mc_js,sobel_yun;
extern int  sancha_qian;
extern int fash_lanya;
extern int a_bu[2],b_bu[2],bu_yes;
extern int err_ft_chan;
extern int yuan_1,yuan_2,yuan_3,yuan_4,yuan_5,yuan_6,yuan_7,yuan,yuan_L,yuan_R,yuan_x;
extern int stop;
extern int yidong;
extern int r;
extern int S2_R,S2_L;//·½²î
extern int sancha_fx;
extern int banma;
extern int i_angle;
extern int sz2[3];
extern int add,drath,drath_banma;
extern char s_cha_num,s_cha_fx;  //Èı²æ¸öÊı  1 ×ó×ó 2 ×óÓÒ 3 ÓÒ×ó 4 ÓÒÓÒ 
extern int sobel_sz[20];
extern int into_yuan,out_yuan,in_huan_dian,yuan_zhi_dian;
extern int gui_low,wan_point;
//extern uint8 image_Gamma[MT9V03X_H][MT9V03X_W];


extern int White;
extern int Black;
extern int L_side[MT9V03X_H];
extern int R_side[MT9V03X_H];
extern int mid[MT9V03X_H];
extern int HIGHT;
extern float variance(int *array);
extern uint8 OTSU(uint8 *imgIn , uint8 Line , uint8 Col_start , uint8 Col_end);
//
////º¯ÊıÉùÃ÷
extern void yuanhuan_bu();
extern void sancha_bu();
extern void into_home();
extern void out_stop();
void find_side();
extern float process_curvity(int x1, int y1, int x2, int y2, int x3, int y3);
extern float qu_l,qu_r;
extern void poly_fiting();;
extern void guigui();
extern int Sobel(uint8 *imgIn, int j);
extern int left_around_Sobel(uint8 *imgIn, int j);
extern uint32 m_sqrt(uint32 x);
//
#endif