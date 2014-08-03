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
gpfs_create_file(struct gpfs_data *gpfs, const char *path, mode_t mode,
    dev_t unused_type)
{
  struct gpfs_file *file;
  struct gpfs_node *node;

  /* Allocate a new node */
  file = (struct gpfs_file*)malloc(sizeof(struct gpfs_file));
  node = (struct gpfs_node*)file;

  node->path = strdup(path);
  node->mode = mode;
  node->type = GPFS_FILE;

  /* Add it to the root list */
  node->next = gpfs->nodes;
  gpfs->nodes = node;

  return file;
}


/**
 * Creates a new directory
 */
struct gpfs_dir *
gpfs_create_dir(struct gpfs_data *gpfs, const char *path, mode_t mode)
{
  struct gpfs_dir *dir;
  struct gpfs_node *node;

  /* Allocate a new node */
  dir = (struct gpfs_dir*)malloc(sizeof(struct gpfs_dir));
  node = (struct gpfs_node*)dir;
  node->path = strdup(path);
  node->mode = mode;
  node->type = GPFS_DIR;

  /* Add it to the root list */
  node->next = gpfs->nodes;
  gpfs->nodes = node;

  return dir;
}


void
gpfs_node_stat(struct gpfs_data *gpfs, struct gpfs_node *node, struct stat *st)
{
  struct gpfs_node *iter = gpfs->nodes;

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
