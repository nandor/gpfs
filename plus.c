/* This file is part of the GPFS project.
 * Licensing information can be found in the LICENSE file
 * (C) 2014 The GPFS maniacs. All rights reserved.
 */
#include "gpfs.h"


/**
 * Google+ context.
 */
struct {
  /** Access token */
  char *token;
  /** CURL context */
  CURL *curl;
} plus;


/**
 * @param plus Google+ Context
 */
void plus_init() {
  curl_global_init(CURL_GLOBAL_DEFAULT);

  memset(&plus, 0, sizeof(plus));
  if (!(plus.curl = curl_easy_init())) {
    perror("Cannot init CURL");
  }
}


/**
 * @param plus Google+ Context
 */
void plus_auth() {
  size_t size = 0;

  /* Ask the user to login and paste the request token */
  puts("Google+ Authentication URL:\n\n");
  puts(REQUEST_URL);
  puts("\n\nAccess token:\n");
  getline(&plus.token, &size, stdin);
}


/**
 * @param plus Google+ Context
 */
void plus_free() {
  if (plus.curl) {
    curl_easy_cleanup(plus.curl);
    plus.curl = NULL;
  }
  curl_global_cleanup();
}
