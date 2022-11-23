#include "Recursive_descent.h"

int main ()
{
    char string[250] = "";
    scanf ("%s", string);

    printf ("\n%lf\n", GetG (string));
    
    return 0;
}