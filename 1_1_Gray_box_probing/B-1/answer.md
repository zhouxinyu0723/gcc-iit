# B-1
B-1.c
```
int AddTwo(int a)
{
    a = a + 2;
    return a;
}

int main()
{
    int x = 3;
    x = AddTwo(x);
    return x;
}

```
**0. Dump B-1.c.019t.ssa**
```
;; Function AddTwo (AddTwo, funcdef_no=0, decl_uid=1911, cgraph_uid=1, symbol_order=0)

AddTwo (int a)
{
  int _3;

  <bb 2> :
  a_2 = a_1(D) + 2;
  _3 = a_2;
  return _3;

}

;; Function main (main, funcdef_no=1, decl_uid=1913, cgraph_uid=2, symbol_order=1)

main ()
{
  int x;
  int _5;

  <bb 2> :
  x_1 = 3;
  x_4 = AddTwo (x_1);
  _5 = x_4;
  return _5;

}
```

**1   The body  of AddTwo(x)  seems to  be inlined into  the call  of main rendering the function useless (nobody else is calling it). Then why is the definition of AddTwo(x) still there all the way till the last pass (B-1.c.*.optimized)?**

<span style="color: red">The function body exists because it may be called from another file. The compiler cannot know about this before link time.</span>

**2   Is there any way to get rid of it?**

<span style="color: red">If the function was declared with the "static" keyword (which, in C, is something  like "private  to this file  only") then  the function body will disappear if there is no caller within the file.</span>