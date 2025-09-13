cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# project
add_executable(output
    main.c ../utils/src/button.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(output pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(output)
