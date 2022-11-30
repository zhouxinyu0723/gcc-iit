# C
vf-1.cpp
```
#include <iostream>
using namespace std;

class A
{ 
       public:
               virtual void f() {cout << "\tA:f" << endl;}
               virtual void f(string i) {cout << "\tA:f." << i << endl;}
               virtual void g() {cout << "\tA:g" << endl;}
};

class B : public A
{     public:
              virtual void g() {cout << "\tB:g" << endl;}
              void f() {cout << "\tB:f" << endl;}
};

class C : public B
{ 
     public:
              void f() {cout<< "\tC:f" << endl;}
};

int main()
{ 
        A  a, *array[3];
        B  b;
        C  c;
        
        array[0]=&a;
        array[1]=&b;
        array[2]=&c;
        for (int i=0;i<3;i++)
        {
                cout << i ;
                array[i]->f();
                array[i]->f("x");
                array[i]->g();
         }
}         
```
**1 Examine class dump. View Results: ./a.out > vf-1.out vi -O vf-1.cpp vf-2.cpp.002t.class vf-1.out**
vf-1.out
```
0       A:f
        A:f.x
        A:g
1       B:f
        A:f.x
        B:g
2       C:f
        A:f.x
        B:g
```
g++ -fdump-lang-class C/vf-2.cpp
```
Vtable for A
A::_ZTV1A: 5 entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI1A)
16    (int (*)(...))A::f
24    (int (*)(...))A::f
32    (int (*)(...))A::g

Class A
   size=8 align=8
   base size=8 base align=8
A (0x0x7f9c5c331420) 0 nearly-empty
    vptr=((& A::_ZTV1A) + 16)

Vtable for B
B::_ZTV1B: 5 entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI1B)
16    (int (*)(...))B::f
24    (int (*)(...))A::f
32    (int (*)(...))B::g

Class B
   size=8 align=8
   base size=8 base align=8
B (0x0x7f9c5c1dd1a0) 0 nearly-empty
    vptr=((& B::_ZTV1B) + 16)
  A (0x0x7f9c5c3315a0) 0 nearly-empty
      primary-for B (0x0x7f9c5c1dd1a0)

Vtable for C
C::_ZTV1C: 5 entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI1C)
16    (int (*)(...))C::f
24    (int (*)(...))A::f
32    (int (*)(...))B::g

Class C
   size=8 align=8
   base size=8 base align=8
C (0x0x7f9c5c1dd208) 0 nearly-empty
    vptr=((& C::_ZTV1C) + 16)
  B (0x0x7f9c5c1dd270) 0 nearly-empty
      primary-for C (0x0x7f9c5c1dd208)
    A (0x0x7f9c5c3316c0) 0 nearly-empty
        primary-for B (0x0x7f9c5c1dd270)
```
**Compare the results of vf-1.out with the vtable present in class dump. Do they match? Why or why not?**

They match

**2 Examine cfg dump. View Results: vi -O vf-2.cpp vf-2.cpp.014t.cfg**

**a) Look  at  main  function.  Each  declaration of  an  object  has  a constructor  call.   Examine  the  function  definition   of  class constructors.  Why does  the constructor  of child  class call  its parent class? What does it imply?**

