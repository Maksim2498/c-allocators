cmake_minimum_required(VERSION 3.12)

project(allocators
        VERSION      1.0.0
        LANGUAGES    C
        DESCRIPTION  "A small C99 library providing allocators"
        HOMEPAGE_URL https://github.com/Maksim2498/c-allocators)

add_library(fominmv-alloc
            src/all.h
            src/allocator.h src/allocator.c
            src/default.h   src/default.c
            src/force.h     src/force.c)

set_target_properties(fominmv-alloc PROPERTIES
            VERSION             ${PROJECT_VERSION}
            C_STANDARD          99
            C_STANDARD_REQUIRED YES
            C_EXTENSIONS        NO
            PUBLIC_HEADER       "src/all.h;src/allocator.h;src/default.h;src/force.h")

            include(GNUInstallDirs)

install(TARGETS fominmv-alloc
        LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fominmv/allocator)