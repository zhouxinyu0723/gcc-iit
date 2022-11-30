# A-2
A-2.c
```
int Z;

void f()
{
        int a, b, c;
        a = Z;
        if (a < 10) {
                b = 5;
                c = 17;
        } else {
                b = 6;
                c = 20;
                if (a == 0) {
                        c = 0;
                }
        }
        Z = b * 10 + c;
}
```
**0. Dump A-2.c.005t.gimple**
```
f ()
{
  int a;
  int b;
  int c;

  a = Z;
  if (a <= 9) goto <D.1917>; else goto <D.1918>;
  <D.1917>:
  b = 5;
  c = 17;
  goto <D.1919>;
  <D.1918>:
  b = 6;
  c = 20;
  if (a == 0) goto <D.1920>; else goto <D.1921>;
  <D.1920>:
  c = 0;
  <D.1921>:
  <D.1919>:
  _1 = b * 10;
  _2 = c + _1;
  Z = _2;
}
```
**1. How have if-blocks  been translated into GIMPLE  statements? Can you differentiate between conditional and unconditional gotos?** 

The `< 10` is translated into `<= 9`. 

......

**2   Repeat  the  above compilation, but now  asking for  another  dump that of the pass  "cfg".  View  this  pass  and say whether this representation makes it easier to  read and understand GIMPLEs. Draw the control-flow graph  of the program A-2.c on a  piece of paper by looking at the CFG dump.

A-2.c.012t.cfg
```
f ()
{
  int c;
  int b;
  int a;

  <bb 2> :
  a = Z;
  if (a <= 9)
    goto <bb 3>; [INV]
  else
    goto <bb 4>; [INV]

  <bb 3> :
  b = 5;
  c = 17;
  goto <bb 6>; [INV]

  <bb 4> :
  b = 6;
  c = 20;
  if (a == 0)
    goto <bb 5>; [INV]
  else
    goto <bb 6>; [INV]

  <bb 5> :
  c = 0;

  <bb 6> :
  _1 = b * 10;
  _2 = c + _1;
  Z = _2;
  return;

}
```

cfg is more easy to understand