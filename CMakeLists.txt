cmake_minimum_required(VERSION 3.7)

include_directories(src)

add_executable(v6sh
    v6sh.c
    src/read_bynary.c
    src/analyzer.c
    src/hexdump.c
    src/command.c
)
