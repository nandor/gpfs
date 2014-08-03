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
  struct gpfs_file *file;

  /* Allocate a new node */
  file = (struct gpfs_file*)malloc(sizeof(struct gpfs_file));
  file->nd.path = strdup(path);
  file->nd.type = GPFS_FILE;

  /* Add it to the root list */
  file->nd.next = gpfs->nodes;
  gpfs->nodes = &file->nd;

  /* Clear storage */
  file->data = NULL;
  file->size = 0ull;

  return &file->nd;
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


/**
 * Retrieves file metadata
 * @param gpfs GPFS file system metadata
 * @param path Full path to the file
 * @return Pointer to the metadata or NULL
 */
struct gpfs_file *
gpfs_get_file(struct gpfs_data *gpfs, const char *path)
{
  struct gpfs_node *node;

  if (!gpfs->nodes)
  {
    return NULL;
  }

  for (node = gpfs->nodes; node; node = node->next)
  {
    if (node->type == GPFS_FILE && !strcmp(node->path, path))
    {
      return (struct gpfs_file*)node;
    }
  }

  return NULL;
}


/**
 * Reads the permissions and owners of a file
 */
void
gpfs_node_stat(struct gpfs_data *gpfs, struct gpfs_node *node, struct stat *st)
{
  struct gpfs_file *file;
  struct gpfs_dir *dir;

  memset(st, 0, sizeof(struct stat));
  switch (node->type)
  {
    case GPFS_FILE:
    {
      file = (struct gpfs_file*)node;

      st->st_mode = S_IFREG | 0755;
      st->st_size = file->size;
      st->st_nlink = 1;
      break;
    }
    case GPFS_DIR:
    {
      dir = (struct gpfs_dir*)node;

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
