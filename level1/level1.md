# Level 0

## 1. Identity

```bash
$ id
uid=2030(level1) gid=2030(level1) groups=2030(level1),100(users)
```

## 2. Home directory

```bash
$ pwd
/home/user/level1

$ ls -la
-rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level1
```

## 3. Analyzing the file

Testing it :

```bash
$ ./level1

```

Nothing...

**Let's use gdb**

```bash
gdb ./level1

(gdb) disas main
Dump of assembler code for function main:
	0x08048480 <+0>:	push   %ebp
	0x08048481 <+1>:	mov    %esp,%ebp
	0x08048483 <+3>:	and    $0xfffffff0,%esp
	0x08048486 <+6>:	sub    $0x50,%esp
	0x08048489 <+9>:	lea    0x10(%esp),%eax
	0x0804848d <+13>:	mov    %eax,(%esp)
	0x08048490 <+16>:	call   0x8048340 <gets@plt>
	0x08048495 <+21>:	leave  
	0x08048496 <+22>:	ret
```

Here is the main implementation in C :
```c
int main(void)
{
    char buffer[64];

    gets(buffer);
    return 0;
}
```

Just a gets() call and quit.

List the functions of the program :
```bash
(gdb) info function
[...]
0x08048444  run
[...]
```

This function isn't called anywhere -> strange

Let's analyze this function :
```bash
Dump of assembler code for function run:
   0x08048444 <+0>:	push   %ebp
   0x08048445 <+1>:	mov    %esp,%ebp
   0x08048447 <+3>:	sub    $0x18,%esp
   0x0804844a <+6>:	mov    0x80497c0,%eax
   0x0804844f <+11>:	mov    %eax,%edx
   0x08048451 <+13>:	mov    $0x8048570,%eax
   0x08048456 <+18>:	mov    %edx,0xc(%esp)
   0x0804845a <+22>:	movl   $0x13,0x8(%esp)
   0x08048462 <+30>:	movl   $0x1,0x4(%esp)
   0x0804846a <+38>:	mov    %eax,(%esp)
   0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
   0x08048472 <+46>:	movl   $0x8048584,(%esp)
   0x08048479 <+53>:	call   0x8048360 <system@plt>
   0x0804847e <+58>:	leave  
   0x0804847f <+59>:	ret    
```

There is a call to syscall

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