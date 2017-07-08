# LD_PRELOAD hacks

`LD_PRELOAD` allows you to intercept functions in a dynamically linked executable
This repo contains a simple example:

```
$ make do_not_use_rand.so uses_rand
gcc -Wall -Wextra -fPIC -pie -g3 -c do_not_use_rand.c -o do_not_use_rand.o
g++ --std=gnu++14 -Wall -Wextra -fPIC -pie -Wl,-E -c libmain.cpp -o libmain.o
g++ --std=gnu++14 -Wall -Wextra -fPIC -pie -Wl,-E do_not_use_rand.o libmain.o -o do_not_use_rand.so
g++ --std=gnu++14 -Wall -Wextra -fPIC -pie -Wl,-E -c uses_rand.cpp -o uses_rand.o
g++ --std=gnu++14 -Wall -Wextra -fPIC -pie -Wl,-E uses_rand.o -o uses_rand

$ ./uses_rand
4 random numbers:
        2056664359
        119779328
        1058352291
        817726622

$ LD_PRELOAD=do_not_use_rand.so ./uses_rand
4 random numbers:
Do not use rand()
        42
Do not use rand()
        42
Do not use rand()
        42
Do not use rand()
        42

$ ./do_not_use_rand.so ./uses_rand
4 random numbers:
Do not use rand()
        42
Do not use rand()
        42
Do not use rand()
        42
Do not use rand()
        42
```

Here we simply re-implement `rand()`, and we can change the functionality without recompiling the existing executable.


## TODO
* Add a wrapper wround `dlsym()` that handles C++ type-name mangling
