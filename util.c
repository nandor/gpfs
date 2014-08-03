/* This file is part of the GPFS project.
 * Licensing information can be found in the LICENSE file
 * (C) 2014 The GPFS maniacs. All rights reserved.
 */
#include "gpfs.h"


/**
 * Prepends a path with the user's home directory
 * @param path Path to the file
 * @return Path with home dir prepended
 */
char *
homepath(const char *path) {
  char *buf, *home;

  home = getenv("HOME");
  assert(home);
  buf = (char*)malloc(strlen(home) + strlen(path) + 2);
  assert(buf);

  strcpy(buf, home);
  strcat(buf, "/");
  strcat(buf, path);

  return buf;
}
