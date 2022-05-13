#ifndef _FUZZY_H_
#define _FUZZY_H_

#include "headfile.h"

float Fuzzy_DirP(float e, float ec);
float Fuzzy_DirD(float e, float ec);
void E_Membership(float e);
void EC_Membership(float ec);
void LinearQuantization(float e, float ec);

#endif