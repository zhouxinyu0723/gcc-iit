# A-3
A-3.c
```
int main()
{
        int sum = 0;
        int i, j;

        while(sum < 100) {
                sum = sum * 2;
        }

        for(i=0; i<25; i++) {
                for(j=0; j<50; j++) {
                        sum = sum + i*j;
                }
        }
}
```
**0. Dump A-3.c.012t.cfg**
```
main ()
{
  int j;
  int i;
  int sum;
  int D.1925;

  <bb 2> :
  sum = 0;
  goto <bb 4>; [INV]

  <bb 3> :
  sum = sum * 2;

  <bb 4> :
  if (sum <= 99)
    goto <bb 3>; [INV]
  else
    goto <bb 5>; [INV]

  <bb 5> :
  i = 0;
  goto <bb 10>; [INV]

  <bb 6> :
  j = 0;
  goto <bb 8>; [INV]

  <bb 7> :
  _1 = i * j;
  sum = sum + _1;
  j = j + 1;

  <bb 8> :
  if (j <= 49)
    goto <bb 7>; [INV]
  else
    goto <bb 9>; [INV]

  <bb 9> :
  i = i + 1;

  <bb 10> :
  if (i <= 24)
    goto <bb 6>; [INV]
  else
    goto <bb 11>; [INV]

  <bb 11> :
  D.1925 = 0;

  <bb 12> :
<L9>:
  return D.1925;

}
```
**1. Identify the basic blocks that correspond  to the while loop. How is the GIMPLE for a while loop different from simple if-else jumps?**

bb 2,3,4 corresponds to while loop. 

**2 . ...for loop...**

...