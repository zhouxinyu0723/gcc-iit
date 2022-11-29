# B-3
B-3.c
```
#include <stdio.h>
int main ()
{
   int a, b;
   for (a=4 ; a<100; a++) {
       if (a < 4)
           b = b + 2;
       else
           b = b * 2;
   }
   printf ("%d%d", a, b);
}
```
**0. Dump B-3.c.102t.vrp1**
```
;; Function main (main, funcdef_no=0, decl_uid=1911, cgraph_uid=1, symbol_order=1) (executed once)

main ()
{
  int a;
  int i;
  int N.0_9;

  <bb 2> [local count: 214748369]:
  N.0_9 = N;
  a_10 = N.0_9 + 10;
  a_15 = N.0_9 + a_10;
  a_20 = N.0_9 + a_15;
  a_25 = N.0_9 + a_20;
  return a_25;

}
```
**1   In the file B-3.c, what values  can variable 'a' take? Will the 'if' condition [a  < 4] ever  be true?  Inspect the file  B-3.c.*.vrp1 to analyze the dump.**

'a' can take all integers from 4 to 100

the if condition can never be true

vrp1 will try to calculate the probability of branches and eliminate fack branches.
