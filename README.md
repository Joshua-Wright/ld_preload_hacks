# LD_PRELOAD hacks

`LD_PRELOAD` allows you to intercept functions in a dynamically linked executable
This repo contains a simple example:

```
$ ./uses_rand
4 random numbers:
        2056664359
        119779328
        1058352291
        817726622

$ LD_PRELOAD=do_not_use_rand ./uses_rand
4 random numbers:
Do not use rand()
        1326602991
Do not use rand()
        1127297187
Do not use rand()
        1024382161
Do not use rand()
        1450142426


$ ./do_not_use_rand ./uses_rand
4 random numbers:
Do not use rand()
        1359644483
Do not use rand()
        660942923
Do not use rand()
        461682392
Do not use rand()
        1405775803

$ cat /secret_file
cat: /secret_file: No such file or directory

$ ./see_hidden_file cat /secret_file
This is a secret!
```

Here we simply re-implement `rand()`, and we can change the functionality without recompiling the existing executable.
