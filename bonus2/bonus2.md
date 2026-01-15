# Bonus2

## 1. Context

```bash
$ id
uid=2012(bonus2) gid=2012(bonus2) groups=2012(bonus2),100(users)

$ pwd
/home/user/bonus2

$ ls -la
[...]
-rwsr-s---+ 1 bonus3 users  5664 Mar  6  2016 bonus2
[...]
```

## 2. Program behavior

```bash
$ ./bonus2 42 43
Hello 42
```

Expects two inputs and prints `Hello input1`.

## 3. Code overview

The program expects exactly **two arguments**.

It builds a 72-byte buffer by:
- copying up to **40 bytes** from `av[1]`
- then copying up to **32 bytes** `from av[2]`

It reads the `LANG` environment variable:
- "fi" -> Finnish greeting
- "nl" -> Dutch greeting
- otherwise -> English greeting

`greetuser() :`
- copies a greeting into a **64-byte local buffer**
- appends the user-controlled string with `strcat()`
- prints the result

## 4. Exploit

`strcat()` does no bounds checking.
The combined greeting + user input can **overflow the 64-byte buffer**.
This allows a **stack-based buffer overflow** in `greetuser()`.

**User input is safely copied in `main()`, but unsafely concatenated in `greetuser()`.**

## 5. Getting the flag

```bash
```

End of simulation
