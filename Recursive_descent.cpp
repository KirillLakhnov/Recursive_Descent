#include "Recursive_descent.h"

const char* str_all;

double GetG (const char* str)
{
    str_all = str;
    double val = GetE ();

    assert (*str_all == '\0');

    printf ("GET_G = %lf\n", val);
    return val;
}

double GetE ()
{
    double val = GetT ();

    while (*str_all == '+' || *str_all == '-')
    {
        char op = *str_all;
        str_all++;

        double val2 = GetT ();

        if (op == '+')
        {
            val += val2;
        }
        else
        {
            val -= val2;
        }
    }

    printf ("GET_E = %lf\n", val);

    return val;
}

double GetT ()
{
    double val = GetPow ();

    while (*str_all == '*' || *str_all == '/')
    {
        char op = *str_all;
        str_all++;

        double val2 = GetPow ();

        if (op == '*')
        {
            val *= val2;
        }
        else
        {
            val /= val2;
        }
    }

    printf ("GET_T = %lf\n", val);

    return val;
}

double GetPow ()
{
    double val = GetP ();

    while (*str_all == '^')
    {
        char op = *str_all;
        str_all++;

        double val2 = GetP ();

        if (op == '^')
        {
            val = pow(val, val2);
        }
    }

    printf ("GET_Pow = %lf\n", val);

    return val;
}

int GetUnarySign ()
{
    if (*str_all == '-')
    {
        str_all++;
        return UNARY_MINUS;
    }
    else if (*str_all == '+')
    {
        str_all++;
        return UNARY_PLUS;
    }

    return NO_UNARY_SIGN;
}

double GetP ()
{
    double val = 0;

    int unary_sign = GetUnarySign ();

    if (*str_all == '(')
    {
        str_all++;
        val = GetE ();

        assert (*str_all == ')');

        str_all++;
    }
    else
    {
        val = GetFunc ();
    }

    if (unary_sign != 0)
    {
        if (unary_sign == UNARY_MINUS)
        {
            val = (-1)*val;
        }
    }

    //val = GetFact (val);

    printf ("GET_P = %lf\n", val);
    return val;
}

double GetFunc ()
{
    double val = 0;

    int math_func = is_math_func ();

    if (math_func != 0)
    {
        val = GetP ();
        //val = GetFact (val);

        if (math_func == SIN_FUNC)
        {
            val = sin (val*(M_PI/180));
        }
        else if (math_func == COS_FUNC)
        {
            val = cos (val*(M_PI/180));
        }
        else if (math_func == TG_FUNC)
        {
            val = tan (val*(M_PI/180));
        }
        else if (math_func == CTG_FUNC)
        {
            val = (1./tan (val*(M_PI/180)));
        }
        else if (math_func == ARCSIN_FUNC)
        {
            if (val > 1 || val < -1)
            {
                assert (0 && "Syntax error: the argument of the arcsin lies in the range [-1, 1]");
            }
            val = asin (val);
        }
        else if (math_func == ARCCOS_FUNC)
        {
            if (val > 1 || val < -1)
            {
                assert (0 && "Syntax error: the argument of the arccos lies in the range [-1, 1]");
            }
            val = acos (val);
        }
        else if (math_func == ARCTG_FUNC)
        {
            val = atan (val);
        }
        else if (math_func == ARCCTG_FUNC)
        {
            val = M_PI_2 - atan (val);
        }
        else if (math_func == LN_FUNC)
        {
            val = log (val);
        }
    }
    else
    {
        val = GetConst ();
    }

    printf ("GET_FUNC = %lf\n", val);

    return val;
}

double GetConst ()
{
    double val = 0;

    int math_const = is_math_const ();

    printf ("MATH_CONST = %d\n", math_const);

    if (math_const != 0)
    {
        if (math_const == PI_CONST)
        {
            val = M_PI;
        }
        else if (math_const == EXP_CONST)
        {
            val = exp(1);
        }
    }
    else
    {
        val = GetN ();
    }

   // val = GetFact (val);

    printf ("GET_CONST = %lf\n", val);

    return val;
}

double GetN ()
{
    double val = 0;

    const char* s_old = str_all;
    while ('0' <= *str_all && *str_all <= '9')
    {
        val = val*10 + *str_all - '0';
        str_all++;
    }

    assert (str_all != s_old);

    printf ("GET_N %lf\n", val);

    return val;
}

double GetFact (double val)
{
    if (*str_all == '!')
    {
        if ((val != (int)val))
        {
            assert (0 && "Syntax error: the factorial argument must be an integer");
        }
        val = factorial (val);

        str_all++;
    }

    printf ("GET_FACT = %lf\n", val);

    return val;
}

//==============================================

int is_math_func ()
{
    char math_func[250] = {0};

    const char* str_old = str_all;
    int index = 0;

    while (isalpha (*str_all) != 0)
    {
        math_func[index] = *str_all;

        index++;
        str_all++;
    }

    if (strcmp (math_func, "sin") == 0)
    {
        return SIN_FUNC;
    }
    else if (strcmp (math_func, "cos") == 0)
    {
        return COS_FUNC;
    }
    else if (strcmp (math_func, "tg") == 0)
    {
        return TG_FUNC;
    }
    else if (strcmp (math_func, "ctg") == 0)
    {
        return CTG_FUNC;
    }
    else if (strcmp (math_func, "arcsin") == 0)
    {
        return ARCSIN_FUNC;
    }
    else if (strcmp (math_func, "arccos") == 0)
    {
        return ARCCOS_FUNC;
    }
    else if (strcmp (math_func, "arctg") == 0)
    {
        return ARCTG_FUNC;
    }
    else if (strcmp (math_func, "arcctg") == 0)
    {
        return ARCCTG_FUNC;
    }
    else if (strcmp (math_func, "ln") == 0)
    {
        return LN_FUNC;
    }

    str_all = str_old;
    return 0;
}

int is_math_const ()
{
    char math_const[250] = {0};

    const char* str_old = str_all;
    int index = 0;

    while (isalpha (*str_all) != 0)
    {
        math_const[index] = *str_all;

        index++;
        str_all++;
    }

    if (strcmp (math_const, "pi") == 0)
    {
        return PI_CONST;
    }
    else if (strcmp (math_const, "exp") == 0)
    {
        return EXP_CONST;
    }

    str_all = str_old;
    return 0;
}

int factorial (int value)
{
    if (value < 0)
    {
        assert (0 && "Math error: the factorial argument must be more or equaly zero");
    }
    if (value == 0)
    {
        return 1;
    }

    int factorial_value = 1;

    for (int index = 1; index <= value; index++)
    {
        factorial_value *= index;
    }

    return factorial_value;
}