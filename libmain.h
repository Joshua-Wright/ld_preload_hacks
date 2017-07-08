//
// Created by j0sh on 7/8/17.
//

#ifndef LD_PRELOAD_HACKS_LIBMAIN_H
#define LD_PRELOAD_HACKS_LIBMAIN_H

#include <dlfcn.h>

// reads mangled name from current process's symbol table
// (mangling the name at runtime is non-trivial)
template<typename Func>
Func *get_old_function(Func *current) {
    Dl_info info;
    dladdr((void *) current, &info);
    return reinterpret_cast<Func *>(dlsym(RTLD_NEXT, info.dli_sname));
}

#endif //LD_PRELOAD_HACKS_LIBMAIN_H
