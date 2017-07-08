CXX				= g++
CC				= gcc
LD				= ld
CXXFLAGS	= --std=gnu++14 -Wall -Wextra -fPIC -pie -Wl,-E
CFLAGS	  = -Wall -Wextra -fPIC -pie -g3
# LIBFLAGS	= -E

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

%.so: %.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

uses_rand: uses_rand.o
	$(CXX) $(CXXFLAGS) $^ -o $@

do_not_use_rand.so: do_not_use_rand.o libmain.o
	$(CXX) $(CXXFLAGS) $^ -o $@

all: libmain.so uses_rand do_not_use_rand.so

clean:
	rm -f *.o *.so uses_rand do_not_use_rand
