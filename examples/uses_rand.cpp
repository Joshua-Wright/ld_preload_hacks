#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>

int main(int, char **) {
    srand(time(NULL));

    std::cout << "4 random numbers:" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "\t" << rand() << std::endl;
    }
}
