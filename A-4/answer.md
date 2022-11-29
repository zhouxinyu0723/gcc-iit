# A-4
A-4.c
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
**0. Dump A-4.c.012t.cfg**
```
main ()
{
  int * p;
  int i;
  int b[3];
  int a[3];
  int D.1920;

  <bb 2> :
  b[0] = 1;
  b[1] = 2;
  b[2] = 3;
  i = 0;
  goto <bb 4>; [INV]

  <bb 3> :
  _1 = b[i];
  a[i] = _1;
  i = i + 1;

  <bb 4> :
  if (i <= 2)
    goto <bb 3>; [INV]
  else
    goto <bb 5>; [INV]

  <bb 5> :
  p = &a;
  _2 = p + 8;
  *_2 = 5;
  a = {CLOBBER};
  b = {CLOBBER};
  D.1920 = 0;

  <bb 6> :
<L3>:
  return D.1920;

}
```

**1   How is array declaration and initialization handled?**

Declare by key pattern `data_type \[array_size\]`

Explicit initialization is done with elementwise assignments.

**2   Why does the statement a[i] = b[i] get broken down to two steps with an intermediate temporary?**

Because usually array is stored in main memory. And due to risc architecture, load ans store with main memory should be in a single instruction.

**3   Why are there CLOBBER statements at the end?**

<span style="color: red">CLOBBER statements are used for  address-escaped variables. It is an annotation  to  signify  that  the  scope  of this  address-escaped variable has ended.</span>

