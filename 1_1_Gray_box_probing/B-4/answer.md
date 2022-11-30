# B-4
B-4.c
```
int main()
{
    int a, b, c;
    b = (a + c + b) * (c + a);
    return b;
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

**1   How many  times is the expression  (a + c) computed  in the original code (as seen in the SSA pass)? What about after the FRE pass?**

two times.

one time.

**2   Have  there been  any more  optimizations  after FRE?  How will  you check?**

No. This can be checked by making comparision with the *.optimized file

**3   Why did  we have  to put a  "return b" in  this assignment?  What if "return b" is changed to "return 0"? Will it make any difference?**

To make sure the result is not meaningless. "return 0" makes compiler to return 0 directly.

