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

  return file;
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

  return file;
}

void
gpfs_node_stat(struct gpfs_data *gpfs, struct gpfs_node *node, struct stat *st)
{
  memset(st, 0, sizeof(st));
  switch (node->type)
  {
    case GPFS_FILE:
    {
      st->st_mode = S_IFREG | 0755;
      st->st_size = 0;
      st->st_nlink = 1;
      break;
    }
    case GPFS_DIR:
    {
      st->st_mode = S_IFDIR | 0755;
      st->st_nlink = 2;
      break;
    }
  }
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
