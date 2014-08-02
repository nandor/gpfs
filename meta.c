/* This file is part of the GPFS project.
 * Licensing information can be found in the LICENSE file
 * (C) 2014 The GPFS maniacs. All rights reserved.
 */
#include "gpfs.h"


/**
 * Creates a new file, attaching it to the root list.
 * @param gpfs GPFS data
 */
struct gpfs_file *
gpfs_create_file(struct gpfs_data *gpfs, const char *path)
{
  struct gpfs_file *file;

  /* Allocate a new node */
  file = (struct gpfs_file*)malloc(sizeof(struct gpfs_file));
  file->path = strdup(path);

  /* Add it to the root list */
  file->next = gpfs->files;
  gpfs->files = file;
}


/**
 * Frees memory occupied by a file object
 * @param file Pointer to the file metadata
 */
void
gpfs_free_file(struct gpfs_file *file)
{
  if (file->path)
  {
    free(file->path);
  }

  free(file);
}
