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
**0. Dump B-4.c.033t.fre1**
```
;; Function main (main, funcdef_no=0, decl_uid=1910, cgraph_uid=1, symbol_order=0)

;; 1 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2
;; 2 succs { 1 }
main ()
{
  int c;
  int b;
  int a;
  int _1;
  int _2;

  <bb 2> :
  _1 = a_4(D) + c_5(D);
  _2 = _1 + b_6(D);
  b_7 = _1 * _2;
  return b_7;

}
```
