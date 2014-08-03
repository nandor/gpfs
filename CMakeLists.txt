# This file is part of the GPFS project.
# Licensing information can be found in the LICENSE file
# (C) 2014 The GPFS maniacs. All rights reserved.
cmake_minimum_required(VERSION 2.8)
project(gpfs)

add_definitions(-D_FILE_OFFSET_BITS=64)
set(CMAKE_C_FLAGS "-std=gnu99 -Wall ${CMAKE_C_FLAGS}")

set(SOURCES
  gpfs.c
  meta.c
  plus.c
  util.c
)

set(HEADERS
  gpfs.h
  meta.h
  plus.h
  util.h
)

set(LIBS
  png
  fuse
  curl
)

add_executable(gpfs ${SOURCES} ${HEADERS})
target_link_libraries(gpfs ${LIBS})
