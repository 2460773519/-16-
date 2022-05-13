#ifndef _MENU_h
#define _MENU_h

#define up      C6
#define down    C9
#define jia     G7
#define jian    G4
#define returnd      D15
#define ok   G1
#define beepd   D3

#define bo_1   E12
#define bo_2   E11
#define bo_3   E10
#define bo_4   E9
#define bo_5   G0
#define bo_6   F15
#define bo_7   F14
#define bo_8   F13




#include "headfile.h"
extern int stop;
extern int kaishi;
extern int beepds;
extern int ok_data;

//
//
////º¯ÊıÉùÃ÷
extern void caidan_sta();
extern void beep();
extern char key_judge(PIN_enum pin);


#endif