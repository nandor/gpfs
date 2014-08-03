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
 * CURL response
 */
struct response
{
  /** Response body */
  char *data;

  /** Length of the response */
  size_t length;
};


/**
 * @param plus Google+ Context
 */
void plus_init() {
  curl_global_init(CURL_GLOBAL_DEFAULT);

  memset(&plus, 0, sizeof(plus));
  if (!(plus.curl = curl_easy_init())) {
    perror("Cannot init CURL");
    exit(EXIT_FAILURE);
  }
}


/**
 * @param plus Google+ Context
 */
void plus_auth() {
  FILE *token_file;
  char *token_path;
  size_t size = 0;

  /* Ask the user to login and paste the request token */
  token_path = homepath(".gpfs/token");
  if (access(token_path, F_OK)) {
    puts("Google+ Authentication URL:\n\n");
    puts(REQUEST_URL);
    puts("\n\nAccess token:\n");
    getline(&plus.token, &size, stdin);

    token_file = fopen(token_path, "w");
    fputs(plus.token, token_file);
    fclose(token_file);
  } else {
    token_file = fopen(token_path, "r");
    getline(&plus.token, &size, token_file);
    fclose(token_file);
  }

  /* TODO(nandor): authentication */
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
