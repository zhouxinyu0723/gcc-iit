# A-5
A-5.c
```
int main()
{
    int a[3];
    int b[] = {1, 2, 3};
    int i, *p;
    for (i=0; i<3; i++) {
        a[i] = b[i];
    }
    p = a;
    *(p + 2) = 5;
}
```
**0. Dump A-5.c.012t.cfg**
```
main ()
{
  int d;
  int c;
  int b;
  int a;
  int D.1920;
  int _10;

  <bb 2> :
  d_3 = 10;
  if (c_4(D) > d_3)
    goto <bb 3>; [INV]
  else
    goto <bb 4>; [INV]

  <bb 3> :
  a_7 = 3;
  b_8 = 2;
  goto <bb 5>; [INV]

  <bb 4> :
  a_5 = 2;
  b_6 = 3;

  <bb 5> :
  # a_1 = PHI <a_7(3), a_5(4)>
  # b_2 = PHI <b_8(3), b_6(4)>
  c_9 = a_1 + b_2;
  _10 = 0;

  <bb 6> :
<L3>:
  return _10;

}
```
**1   Do you notice that each usage of local variable as an operand uses a suffix that can be tracked to it's assignment? Why do some variables have a suffix `(D)'?**

Local variables are suffixed with different numbers in every different assignment.

The suffix (D) is added if the varible is not initialized or the variable is a formal paramenter.

**2   Find the point in the CFG in  which the paths of the two  assignments to variable 'a'  and 'b' merge. You will notice  that PHI statements have  been  introduced.  Can  you   guess  the  syntax  of  the  PHI statements?**

syntex is # <variable_name>_<num_suffix> = PHI <...(bb_num1), ...(bb_num2)>

**3   Can you think of an example in which a PHI node merges more than two versions of a variable?**

in switch 