# A-1
A-1
```
int Z;

void main()
{
        int a, b, c;
        int p = 6;
        int q;
        double r;

        a = 10;
        b = 20;
        c = a * b + 25;
        p = 6;
        q = Z;
        r = 34.5;
        Z = r;
        Z = Z + 1;
}
```
**0.  Dump A-1.c.005t.gimple**

gcc-4.7.2 -c -fdump-tree-gimple A-1.c
```
main ()
{
  int a;
  int b;
  int c;
  int p;
  int q;
  double r;

  p = 6;
  a = 10;
  b = 20;
  _1 = a * b;
  c = _1 + 25;
  p = 6;
  q = Z;
  r = 3.45e+1;
  _2 = (int) r;
  Z = _2;
  Z.0_3 = Z;
  _4 = Z.0_3 + 1;
  Z = _4;
}
```
**1. How  do the  declarations  look in  the  GIMPLE? Specifically,  what happens to multiple  variables declared and initialized  on the same line? What happens to global declaration [int Z]?**

The declarations are very similar to the normal declaration in c program.

Multiple variables declared are parsed into multiple lines. Each line contains one declaration.

Global declaration [int Z] disappears in GIMPLE.

**2. How are complex  expressions such as [c  = a * b + 25] broken down? Can you  determine a  rule as  to when temporary variables  will be introduced?**

It is splited into one multiplication and one addition. 

Temporary variables will be introduced if a operation is slited into multiple operations.       

**3. How are floats/doubles represented in GIMPLE? What happens when a float/double is assigned to an integer in [Z = r]?**

It will be declared with the keyword `double` instead of `int`.

<span style="color: red">Floats/doubles  are  displayed  in   scientific  notation</span>

During assignment explicit casts with keyword `int` appear

**4   How  are reads/writes  to the  global variable  Z performed?  Why is there a temporary introduced  for the statement [Z = Z  + 1] but not for the statements [q = Z] or [Z = p]?**

reads/writes  to the  global variable  Z requires a load or store operation.

Because the global variable have to be loaded into the register first before operation and have to store back to main memory after operation. 

<span style="color: red">every read/write  to global variables  **must** refer to main  memory as they can be accessed by  other entities (threads, I/O devices, etc). Hence,  any operation  on global  variables (such  as the  increment shown  in this  example)  has  to go  through  an  indirection of  a temporary version of the global  inside registers (as this temporary value is  not visible to  I/O devices, etc). Global  temporaries are named similar to the global variable but with a numeric suffix.</span>

To this, I disagree. I think global variable is usually stored (for the large part of its life time) in the main memmory because it is expensive to store them in register. And because they are in main memory, when follow the RISC design principle. The load ans store of main memory is one specific instruction.