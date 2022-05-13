#include "FUZZ.h"

#define NB 0
#define NM 1
#define NS 2
#define ZO 3
#define PS 4
#define PM 5
#define PB 6
float E_Value;                   //ƫ�����������
float EC_Value;                  //ƫ�����������
float e_Max = 20.0;                     //ƫ�Χ
float e_Min = -20.0;
float ec_Max = 4.0;                    //ƫ��仯�ʷ�Χ    
float ec_Min = -4.0; 
float DirP_Value = 0.0;                         //���ֵ--P���������� 
struct Fuzzy_Membership          //�����Ƚṹ��
{
  int Set_1;
  int Set_2;
  int Set_3;
  int Set_4;
  float Set_1_Member;
  float Set_2_Member;
  float Set_3_Member;
  float Set_4_Member;
};
struct Fuzzy_Membership E_Member;
struct Fuzzy_Membership EC_Member;
struct Fuzzy_Membership DirP_Member;
struct Fuzzy_Membership DirD_Member;


//int Fuzzy_DirP_Rule[7][7] =      //����Pģ������� ԭʼ
//{
//    {6, 6, 6, 6, 6, 4, 0},
//    {6, 6, 6, 6, 4, 2, 0},
//    {6, 4, 2, 2, 0,-2,-4},
//    {4, 4, 2, 0,-2,-4,-4},
//    {-4,-2,0, 2, 2, 4, 6},
//    {0, 2, 4, 6, 4, 6, 6},
//    {0, 4, 6, 6, 6, 6, 6}
//};


/*
int Fuzzy_DirP_Rule[7][7] =      //����Pģ������� 19-7-12 14;39������1��ԭ��Ϊ����������
{
    {6, 6, 6, 6, 6, 4, 0},
    {6, 6, 6, 6, 4, 2, 0},
    {6, 4, 2, 2, 0,-2,-4},
    {4, 4, 2, 4, 4,-4,-4},
    {-4,-2,0, 6, 6, 4, 6},
    {0, 2, 4, 6, 4, 6, 6},
    {0, 4, 6, 6, 6, 6, 6}
};
*/
  //   e
     //-3  -2 -1  0 1  2  3//
int Fuzzy_DirP_Rule[7][7] =      //����Pģ������� 19-7-12 15:02������2��ԭ��Ϊ�˸�����������
{                                 // ec
    {6, 6, 6, 6, 6, 4, 0},    // -3
    {6, 6, 6, 6, 4, 2, 0},    // -2
    {6, 4, 2, 2, 0,-2,-4},   /// -1

    {4, 4, 2, 6, 6,-2,-2},   //   0 
    {-6,-4,-2, 6, 6, 4, 6},  //   1
    {0, 2, 4, 6, 4, 6, 6},   //   2
    {0, 4, 6, 6, 6, 6, 6}    //   3
};


//
//int Fuzzy_DirP_Rule[7][7] =      //����Pģ������� 19-7-12 15:11������3��ԭ��Ϊ�˸����������У�������һ������
//{   -3  -2 -1  0 1  2  3

//    {6, 6, 6, 6, 6, 4, 0}, -3
//    {6, 6, 6, 6, 4, 2, 0}, -2
//    {6, 4, 6, 6, -2,-4,-6}, -1
//    {4, 4, 2, 6, 6,-2,-2},  0
//    {-6,-4,-2, 6, 6, 4, 6}, 1
//    {0, 2, 4, 6, 4, 6, 6},  2
//    {0, 4, 6, 6, 6, 6, 6}   3
//};


//int Fuzzy_DirP_Rule[7][7] =      //����Pģ������� 19-7-13 8:51������4��ԭ�򣺼�С����
//{
//    {6, 6, 6, 6, 6, 4, 6},
//    {-4, -2, -2, 6, 4, 4, 6},
//    {6, 4, 6, 2, 2,6,6},
//    {4, 4, 2, 6, 6,-2,-2},
//    {6, 6, 2, 6, 6, 4, 6},
//    {6, 4, 4, 6, -2, -2, -4},
//    {6, 4, 6, 6, 6, 6, 6}
//};

int Fuzzy_DirD_Rule[7][7] =      //����Dģ�������
{
    {6,  4,  2, -2, 0, -2, -2},
    {6,  4,  2,  0,-2, -4, -6},
    {6,  4,  2,  0, 0, -2,  2},
    {2, -2, -2, -2,-2, -3,  2},
    {2, -2,  0,  0, 2,  4,  6},
    {-6,-4, -2,  0, 2,  4,  6},
    {-2,-2,  0, -2, 2,  4,  6}
};


/*
* ����Ӧģ��PID--P
* ��̬����P�Ĵ�С
*/
float Fuzzy_DirP(float e, float ec)
{
  LinearQuantization(e, ec);                            //������������
  E_Membership(E_Value);                                 //����ƫ���������
  EC_Membership(EC_Value);                               //����ƫ��仯�ʵ�������
  
  DirP_Member.Set_1 = Fuzzy_DirP_Rule[E_Member.Set_1][EC_Member.Set_1];         //��ѯ�����
  DirP_Member.Set_2 = Fuzzy_DirP_Rule[E_Member.Set_1][EC_Member.Set_2];
  DirP_Member.Set_3 = Fuzzy_DirP_Rule[E_Member.Set_2][EC_Member.Set_1];
  DirP_Member.Set_4 = Fuzzy_DirP_Rule[E_Member.Set_2][EC_Member.Set_2];
  
  DirP_Member.Set_1_Member = E_Member.Set_1_Member * EC_Member.Set_1_Member;    //�������������1
  DirP_Member.Set_2_Member = E_Member.Set_1_Member * EC_Member.Set_2_Member;    //�������������2
  DirP_Member.Set_3_Member = E_Member.Set_2_Member * EC_Member.Set_1_Member;    //�������������3
  DirP_Member.Set_4_Member = E_Member.Set_2_Member * EC_Member.Set_2_Member;    //�������������4
                                                                                //����P����������
  DirP_Value = (DirP_Member.Set_1) * DirP_Member.Set_1_Member + (DirP_Member.Set_2) * DirP_Member.Set_2_Member + (DirP_Member.Set_3) * DirP_Member.Set_3_Member + (DirP_Member.Set_4) * DirP_Member.Set_4_Member;
  
  return (DirP_Value / 6.0);
}

/*
* ����Ӧģ��PID--D
* ��̬����D�Ĵ�С
*/
float Fuzzy_DirD(float e, float ec)
{
  float DirD_Value = 0.0;                         //���ֵ--P���������� 

  LinearQuantization(e, ec);                       //������������
  E_Membership(e);                                 //����ƫ���������
  EC_Membership(ec);                               //����ƫ��仯�ʵ�������
  
  DirD_Member.Set_1 = Fuzzy_DirD_Rule[E_Member.Set_1][EC_Member.Set_1];         //��ѯ�����
  DirD_Member.Set_2 = Fuzzy_DirD_Rule[E_Member.Set_1][EC_Member.Set_2];
  DirD_Member.Set_3 = Fuzzy_DirD_Rule[E_Member.Set_2][EC_Member.Set_1];
  DirD_Member.Set_4 = Fuzzy_DirD_Rule[E_Member.Set_2][EC_Member.Set_2];
  
  DirD_Member.Set_1_Member = E_Member.Set_1_Member * EC_Member.Set_1_Member;    //�������������1
  DirD_Member.Set_2_Member = E_Member.Set_1_Member * EC_Member.Set_2_Member;    //�������������2
  DirD_Member.Set_3_Member = E_Member.Set_2_Member * EC_Member.Set_1_Member;    //�������������3
  DirD_Member.Set_4_Member = E_Member.Set_2_Member * EC_Member.Set_2_Member;    //�������������4
                                                                                //����P����������
  DirD_Value = (DirD_Member.Set_1 * DirD_Member.Set_1_Member + (DirD_Member.Set_2) * DirD_Member.Set_2_Member + (DirD_Member.Set_3) * DirD_Member.Set_3_Member + (DirD_Member.Set_4) * DirD_Member.Set_4_Member);
  
  return (DirD_Value / 6.0);
}

/*
* ������������
* ����ƫ���ƫ��仯�ʵ���������
*/
void LinearQuantization(float e, float ec)
{
  E_Value = 6.0 * e / (e_Max);     
  EC_Value = 6.0 * ec / (ec_Max);
}

/*
* ƫ�������Ⱥ���
*/
void E_Membership(float e)
{
  if(e >= -6 && e < -4)
  {
    E_Member.Set_1 = NB;
    E_Member.Set_2 = NM;
    E_Member.Set_1_Member = -0.5 * e - 2.0;
    E_Member.Set_2_Member = 0.5 * e + 3.0;
  }
  else if(e >= -4 && e < -2)
  {
    E_Member.Set_1 = NM;
    E_Member.Set_2 = NS;
    E_Member.Set_1_Member = -0.5 * e - 1.0;
    E_Member.Set_2_Member = 0.5 * e + 2.0;
  }
  else if(e >= -2 && e < 0)
  {
    E_Member.Set_1 = NS;
    E_Member.Set_2 = ZO;
    E_Member.Set_1_Member = -0.5 * e;
    E_Member.Set_2_Member = 0.5 * e + 1.0;
  }
  else if(e >= 0 && e < 2)
  {
    E_Member.Set_1 = ZO;
    E_Member.Set_2 = PS;
    E_Member.Set_1_Member = -0.5 * e + 1.0;
    E_Member.Set_2_Member = 0.5 * e;
  }
  else if(e >= 2 && e < 4)
  {
    E_Member.Set_1 = PS;
    E_Member.Set_2 = PM;
    E_Member.Set_1_Member = -0.5 * e + 2.0;
    E_Member.Set_2_Member = 0.5 * e - 1.0;
  }
  else if(e >= 4 && e <= 6)
  {
    E_Member.Set_1 = PM;
    E_Member.Set_2 = PB;
    E_Member.Set_1_Member = -0.5 * e + 3.0;
    E_Member.Set_2_Member = 0.5 * e - 2.0;
  }
}

/*
* ƫ��仯�������Ⱥ���
*/
void EC_Membership(float ec)
{
  if(ec >= -6 && ec < -4)
  {
    EC_Member.Set_1 = NB;
    EC_Member.Set_2 = NM;
    EC_Member.Set_1_Member = -0.5 * ec - 2.0;
    EC_Member.Set_2_Member = 0.5 * ec + 3.0;
  }
  else if(ec >= -4 && ec < -2)
  {
    EC_Member.Set_1 = NM;
    EC_Member.Set_2 = NS;
    EC_Member.Set_1_Member = -0.5 * ec - 1.0;
    EC_Member.Set_2_Member = 0.5 * ec + 2.0;
  }
  else if(ec >= -2 && ec < 0)
  {
    EC_Member.Set_1 = NS;
    EC_Member.Set_2 = ZO;
    EC_Member.Set_1_Member = -0.5 * ec;
    EC_Member.Set_2_Member = 0.5 * ec + 1.0;
  }
  else if(ec >= 0 && ec < 2)
  {
    EC_Member.Set_1 = ZO;
    EC_Member.Set_2 = PS;
    EC_Member.Set_1_Member = -0.5 * ec + 1.0;
    EC_Member.Set_2_Member = 0.5 * ec;
  }
  else if(ec >= 2 && ec < 4)
  {
    EC_Member.Set_1 = PS;
    EC_Member.Set_2 = PM;
    EC_Member.Set_1_Member = -0.5 * ec + 2.0;
    EC_Member.Set_2_Member = 0.5 * ec - 1.0;
  }
  else if(ec >= 4 && ec <= 6)
  {
    EC_Member.Set_1 = PM;
    EC_Member.Set_2 = PB;
    EC_Member.Set_1_Member = -0.5 * ec + 3.0;
    EC_Member.Set_2_Member = 0.5 * ec - 2.0;
  }
}
