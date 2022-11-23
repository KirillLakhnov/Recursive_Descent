#include "Recursive_descent.h"

int main ()
{
    char string[250] = "";
    fgets (string, 250, stdin);

    printf ("\n%lf\n", GetG (string));
    
    return 0;
}