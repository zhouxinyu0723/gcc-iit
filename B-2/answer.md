# B-2
B-2.c
```
int N;

int main()
{
    int i, a = 10;
    for(i= 0; i < 4; i++)
    {
        a = a + N;
    };
    return a;
}

```
**0. Dump B-2.c.161t.cunroll**
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

**1   What will happen if "a = a + N" is replaced by "a = a + 1"?**

```
;; Function main (main, funcdef_no=0, decl_uid=1911, cgraph_uid=1, symbol_order=1) (executed once)

main ()
{
  int a;
  int i;

  <bb 2> [local count: 214748369]:
  return 14;

}
```

Result will be calculated directly.