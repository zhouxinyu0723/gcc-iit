
int foo (int, int, int);

int main ()
{
        int a, b, c;
        char d;

        a = 2;
        b = c--;
        a = foo (a, b, c);
        if (b < (a + c))
                c = ~c;
        else
                c = a + 3;
        d = (char) b;
        return 0;
}

int foo (int p, int q, int r)
{
        q = p + r - 4;
        return 0;
}
