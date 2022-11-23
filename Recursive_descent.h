#ifndef RECURSIVE_DESCENT_H
#define RECURSIVE_DESCENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>

enum MATH_FUNC {
    SIN_FUNC = 1,
    COS_FUNC = 2,
    CTG_FUNC = 3,
    TG_FUNC  = 4,
    
    ARCSIN_FUNC = 5,
    ARCCOS_FUNC = 6,
    ARCCTG_FUNC = 7,
    ARCTG_FUNC  = 8,

    LN_FUNC = 9,
};

enum MATH_CONST {
    EXP_CONST = 1,
    PI_CONST  = 2,
};

enum UNARY_SIGN {
    UNARY_PLUS    = 1,
    UNARY_MINUS   = 2,
    NO_UNARY_SIGN = 3,
};

double GetG (const char* str);

double GetE ();

double GetT ();

double GetPow ();

int GetUnarySign ();

double GetP ();

double GetFunc ();

double GetConst ();

double GetN ();

double GetFact (double val);

//==============================================

int is_math_func ();

int is_math_const ();

int factorial (int value);

#endif //RECURSIVE_DESCENT_H