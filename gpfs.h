/* This file is part of the GPFS project.
 * Licensing information can be found in the LICENSE file
 * (C) 2014 The GPFS maniacs. All rights reserved.
 */
#ifndef __GPFS_H__
#define __GPFS_H__


/* C includes */
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Linux includes */
#include <sys/stat.h>
#include <unistd.h>

/* Libraries */
#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <png.h>


/**
 * GPFS state
 */
struct gpfs_data
{
  /** Linked list of nodes */
  struct gpfs_node *nodes;

  /** Last used file UID */
  uint64_t last_uid;
};


/* GPFS includes */
#include "meta.h"


#endif /*__GPFS_H__*/
