#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libmain.h"


// very large buffer because we must preserve LD_PRELOAD (however big it was)
// TODO dynamically-size buffer
const size_t BUFSIZE = 100 * 1024;
const char *LD_PRELOAD = "LD_PRELOAD";

int main(int argc, char **argv) {
    if (argc <= 1) {
        std::cout << "Usage: " << argv[0] << " COMMAND [ARGS...]" << std::endl;
        return 1;
    }

    using std::string;
    char pathbuf[BUFSIZE] = {0};
    ssize_t pathbuf_written = readlink("/proc/self/exe", pathbuf, BUFSIZE);
    pathbuf[pathbuf_written] = '\0';

    string new_ld_preload = pathbuf;
    const char *existing_ld_preload = getenv(LD_PRELOAD);
    if (existing_ld_preload != NULL) {
        new_ld_preload += ":" + string(existing_ld_preload);
    }
    setenv(LD_PRELOAD, new_ld_preload.c_str(), 1);

    char **argv2 = argv + 1;
    execvp(argv[1], argv2);

    perror(argv[0]);
    return -1;
}
