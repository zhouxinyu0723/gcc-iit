#include <stdio.h>

int *p, *q;
void callme (int);

int main ()
{
        int a, b, *c;
        p = &b;
        callme (a);
        return 0;
}

void callme (int a)
{
        int *d;
        a = *(p + 3);
        q = &a;
        d = q;
}

