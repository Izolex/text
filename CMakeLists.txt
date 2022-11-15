cmake_minimum_required(VERSION 3.23)
project(text_search)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -fsanitize=address -fsanitize=undefined -g3 -Wall -Wextra -Werror -O0 \
        -Wimplicit-function-declaration -Wimplicit-int -Wold-style-definition \
        -Wstrict-prototypes -Wmissing-declarations -Wmissing-prototypes -Wout-of-line-declaration \
    ")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

add_subdirectory(test)
