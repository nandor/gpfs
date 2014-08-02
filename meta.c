/* This file is part of the GPFS project.
 * Licensing information can be found in the LICENSE file
 * (C) 2014 The GPFS maniacs. All rights reserved.
 */
#include "gpfs.h"


/**
 * Creates a new file, attaching it to the root list.
 * @param gpfs GPFS data
 */
struct gpfs_node *
gpfs_create_file(struct gpfs_data *gpfs, const char *path)
{
  struct gpfs_node *file;

  /* Allocate a new node */
  file = (struct gpfs_node*)malloc(sizeof(struct gpfs_node));
  file->path = strdup(path);
  file->type = GPFS_FILE;

  /* Add it to the root list */
  file->next = gpfs->nodes;
  gpfs->nodes = file;
}


/**
 * Creates a new directory
 */
struct gpfs_node *
gpfs_create_dir(struct gpfs_data *gpfs, const char *path)
{
  struct gpfs_node *file;

  /* Allocate a new node */
  file = (struct gpfs_node*)malloc(sizeof(struct gpfs_node));
  file->path = strdup(path);
  file->type = GPFS_DIR;

  /* Add it to the root list */
  file->next = gpfs->nodes;
  gpfs->nodes = file;
}


/**
 * Frees memory occupied by a file object
 * @param file Pointer to the file metadata
 */
void
gpfs_free_node(struct gpfs_node *file)
{
  if (file->path)
  {
    free(file->path);
  }

  free(file);
}
