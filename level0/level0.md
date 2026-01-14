# Level0

## 1. Context

```bash
$ id
uid=2020(level0) gid=2020(level0) groups=2020(level0),100(users)

$ pwd
/home/user/level0

$ ls -la
[...]
-rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0
[...]
```

## 3. Analyzing the file

Testing it :

```bash
$ ./level0 
Segmentation fault (core dumped)

$ ./level0 42
No !
```

Our program expects an input, but which one ?

**For this problem, we need to use gdb.**

```bash
gdb ./level0

(gdb) disas main
Dump of assembler code for function main:
[...]
	0x08048ed4 <+20>:	call   0x8049710 <atoi>       # Call to function atoi
	0x08048ed9 <+25>:	cmp    $0x1a7,%eax            # Compare the result with a special number : 423 -> probably the right solution
[...]
```

## 4. Getting the flag

```bash
$ ./level0 423
```

** It launched a new shell.**

```bash
$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```

End of simulation