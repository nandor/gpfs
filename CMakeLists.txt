# This file is part of the GPFS project.
# Licensing information can be found in the LICENSE file
# (C) 2014 The GPFS maniacs. All rights reserved.
cmake_minimum_required(VERSION 2.8)
project(gpfs)

add_definitions(-D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26)
set(CMAKE_C_FLAGS "-std=gnu99 -Wall ${CMAKE_C_FLAGS}")

set(SOURCES
  gpfs.c
)

set(HEADERS
  gpfs.h
)

set(LIBS
  png
  fuse
)

add_executable(gpfs ${SOURCES} ${HEADERS})
target_link_libraries(gpfs ${LIBS})
