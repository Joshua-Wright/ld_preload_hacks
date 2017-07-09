//
// Created by j0sh on 7/9/17.
//
#ifndef _GNU_SOURCE
#define  _GNU_SOURCE
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/memfd.h>
#include <cstring>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include "../libmain.h"

const static char *const secret_message = "This is a secret!\n";
const static char *const secret_path = "/secret_file";
static int secret_fd;

static void con() __attribute__((constructor));

void con() {
    secret_fd = (int) syscall(__NR_memfd_create, secret_path, 0);
    ssize_t written = write(secret_fd, (void *) secret_message, strlen(secret_message));
    assert(written > 0); // write should always succeed
    lseek(secret_fd, 0, SEEK_SET);
}


extern "C"
int open(const char *pathname, int flags, ...) {

    va_list args;
    va_start(args, flags);

    if (strcmp(pathname, "/secret_file") == 0) {
        return secret_fd;
    } else {
        static auto *open_ = get_old_function(&open);
        return open_(pathname, flags, args);
    }

    va_end(args);
}
