int main()
{
    int a, b;
    switch (a)
    {
        case 1:
            b = 2;
            break;
        case 2:
            b = 3;
            break;
        case 3:
            b = 4;
        case 4:
            b = 5;
            break;
        case 5:
        case 6:
            b = 6;
            break;
        default:
            b = 7;
    }
    return b;
}