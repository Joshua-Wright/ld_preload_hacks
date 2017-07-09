# (c) Copyright 2017 Josh Wright
cmake_minimum_required(VERSION 3.3)
project(ld_preload_hacks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")

add_executable(uses_rand examples/uses_rand.cpp)

add_executable       (do_not_use_rand libmain.cpp examples/do_not_use_rand.cpp libmain.h)
set_target_properties(do_not_use_rand PROPERTIES
	                  COMPILE_FLAGS " -fPIC -pie -Wl,-E"
                      LINK_FLAGS " -fPIC -pie -Wl,-E"
                      )
target_link_libraries(do_not_use_rand dl)

add_executable       (see_hidden_file libmain.cpp libmain.h examples/see_hidden_file.cpp)
set_target_properties(see_hidden_file PROPERTIES
		COMPILE_FLAGS " -fPIC -pie -Wl,-E"
		LINK_FLAGS " -fPIC -pie -Wl,-E"
		)
target_link_libraries(see_hidden_file dl)
