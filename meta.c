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
gpfs_create_file(struct gpfs_data *gpfs, const char *path) {
  struct gpfs_file *file;

  /* Allocate a new node */
  file = (struct gpfs_file*)malloc(sizeof(struct gpfs_file));
  memset(file, 0, sizeof(struct gpfs_file));

  file->nd.path = strdup(path);
  file->nd.type = GPFS_FILE;
  file->nd.stat.st_dev = S_IFREG;

  /* Add it to the root list */
  file->nd.next = gpfs->nodes;

  gpfs->nodes = &file->nd;

  /* Clear storage */
  file->data = NULL;
  file->size = 0ull;

  return file;
}


/**
 * Creates a new directory
 */
struct gpfs_dir *
gpfs_create_dir(struct gpfs_data *gpfs, const char *path) {
  struct gpfs_dir *dir;

  /* Allocate a new node */
  dir = (struct gpfs_dir*)malloc(sizeof(struct gpfs_dir));
  memset(dir, 0, sizeof(struct gpfs_dir));

  dir->nd.path = strdup(path);
  dir->nd.type = GPFS_DIR;
  dir->nd.stat.st_dev = S_IFDIR;

  /* Add it to the root list */
  dir->nd.next = gpfs->nodes;
  gpfs->nodes = &dir->nd;

  return dir;
}


/**
 * Retrieves file metadata
 * @param gpfs GPFS file system metadata
 * @param path Full path to the file
 * @return Pointer to the metadata or NULL
 */
struct gpfs_file *
gpfs_get_file(struct gpfs_data *gpfs, const char *path) {
  struct gpfs_node *node = gpfs_get_node(gpfs, path);

  if (!node || node->type != GPFS_FILE) {
    return NULL;
  }

  return (struct gpfs_file*)node;
}

/**
 * Retrieves dir metadata
 * @param gpfs GPFS file system metadata
 * @param path Full path to the dir
 * @return Pointer to the metadata or NULL
 */
struct gpfs_dir *
gpfs_get_dir(struct gpfs_data *gpfs, const char *path) {
  struct gpfs_node *node = gpfs_get_node(gpfs, path);

  if (!node || node->type != GPFS_DIR) {
    return NULL;
  }

  return (struct gpfs_dir*)node;
}

/**
 * Retrieves node metadata
 * @param gpfs GPFS file system metadata
 * @param path Full path to the node
 * @return Pointer to the metadata or NULL
 */
struct gpfs_node *
gpfs_get_node(struct gpfs_data *gpfs, const char *path) {
  struct gpfs_node *node;

  if (!gpfs->nodes) {
    return NULL;
  }

  for (node = gpfs->nodes; node; node = node->next) {
    if (!strcmp(node->path, path)) {
      return node;
    }
  }

  return NULL;
}




/**
 * Reads the permissions and owners of a file
 */
void
gpfs_node_stat(struct gpfs_data *gpfs, struct gpfs_node *node,
               struct stat *st) {
  memcpy(st, &node->stat, sizeof(struct stat));
}

/**
 * Frees memory occupied by a file object
 * @param file Pointer to the file metadata
 */
void
gpfs_free_node(struct gpfs_node *file) {
  if (file->path) {
    free(file->path);
  }

  free(file);
}
