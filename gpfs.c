/* This file is part of the GPFS project.
 * Licensing information can be found in the LICENSE file
 * (C) 2014 The GPFS maniacs. All rights reserved.
 */
#include "gpfs.h"


/**
 * Initialises the GPFS filesystem
 */
static void* gpfs_init(struct fuse_conn_info *conn)
{
  struct gpfs_data *gpfs;

  /* Initialize the gpfs data */
  gpfs = (struct gpfs_data*)malloc(sizeof(struct gpfs_data));

  /* Load or create the file list */
  if (!access("~/.gpfs/meta", F_OK))
  {
    assert(!"Not implemented");
  }
  else
  {
    gpfs->last_uid = 0ull;
    gpfs->nodes = NULL;

    gpfs_create_dir(gpfs, "/");
    gpfs_create_file(gpfs, "/test");
    gpfs_create_file(gpfs, "/test2");

    gpfs_create_dir(gpfs, "/x");
    gpfs_create_file(gpfs, "/x/a");
  }

  return gpfs;
}


/**
 * Destroys the GPFS filesystem
 */
static void gpfs_destroy(void *data)
{
  struct gpfs_data *gpfs;
  struct gpfs_node *file, *next;

  if (!(gpfs = (struct gpfs_data*)data))
  {
    return;
  }

  if (gpfs->nodes)
  {
    for (file = gpfs->nodes; file; file = next)
    {
      next = file->next;
      gpfs_free_node(file);
    }
  }

  free(gpfs);
}


/**
 * Opens a GPFS file
 * @param path  Path to the file
 * @param fi    FUSE file info
 * @return      Status
 */
static int gpfs_open(const char *path, struct fuse_file_info *fi)
{
  struct gpfs_data *gpfs;

  assert((gpfs = (struct gpfs_data*)fuse_get_context()->private_data));

  return 0;
}


/**
 * Flushes a GPFS file
 * @param path  Path to the file
 * @param fi    FUSE file info
 * @return      Status
 */
static int gpfs_flush(const char *path, struct fuse_file_info *fi)
{
  return 0;
}


/**
 * Reads from a GPFS file
 */
static int gpfs_read(const char *path, char *buf, size_t len,
                     off_t off, struct fuse_file_info *fi)
{
  struct gpfs_data *gpfs;
  struct gpfs_file *file;
  size_t size;

  assert((gpfs = (struct gpfs_data*)fuse_get_context()->private_data));
  if (!(file = gpfs_get_file(gpfs, path)))
  {
    return -ENOENT;
  }

  if (off > file->size)
  {
    return 0;
  }

  size = (off + len > file->size) ? (file->size - off) : len;
  memcpy(buf, file->data + off, size);
  return size;
}


/**
 * Writes to a GPFS file
 */
static int gpfs_write(const char *path, const char *buf, size_t len,
                      off_t off, struct fuse_file_info *fi)
{
  struct gpfs_data *gpfs;
  struct gpfs_file *file;

  assert((gpfs = (struct gpfs_data*)fuse_get_context()->private_data));
  if (!(file = gpfs_get_file(gpfs, path)))
  {
    return -ENOENT;
  }

  if (len + off > file->size)
  {
    file->data = (uint8_t*)realloc(file->data, len + off);
    file->size = len + off;
  }

  memcpy(file->data + off, buf, len);
  return len;
}


/**
 * Closes a GPFS file
 * @param
 */
static int gpfs_release(const char *path, struct fuse_file_info *fi)
{
  struct gpfs_data *gpfs;

  assert((gpfs = (struct gpfs_data*)fuse_get_context()->private_data));

  return 0;
}


/**
 * Reads a GPFS file attribute
 * @param path Path to the file
 * @param stat Stat structure
 * @return     Status
 */
static int gpfs_getattr(const char *path, struct stat *st)
{
  struct gpfs_data *gpfs;
  struct gpfs_node *node;

  assert((gpfs = (struct gpfs_data*)fuse_get_context()->private_data));

  node = gpfs->nodes;
  while (node)
  {
    if (strcmp(path, node->path))
    {
      node = node->next;
      continue;
    }

    gpfs_node_stat(gpfs, node, st);
    return 0;
  }

  return -ENOENT;
}


/**
 * Opens a GPFS directory
 * @param path Path to the directory
 * @param fill Function to fill an entry
 * @param off  Offset
 * @param fi   File info
 * @return     Status
 */
static int gpfs_readdir(const char *path, void *buf, fuse_fill_dir_t fill,
                        off_t off, struct fuse_file_info *fi)
{
  struct gpfs_data *gpfs;
  struct gpfs_node *node, *file;
  size_t dir_path_len, file_path_len;
  struct stat st;

  assert((gpfs = (struct gpfs_data*)fuse_get_context()->private_data));

  dir_path_len = strcmp(path, "/") ? strlen(path) : 0;
  node = gpfs->nodes;
  while (node)
  {
    if (strcmp(path, node->path))
    {
      node = node->next;
      continue;
    }

    if (node->type != GPFS_DIR)
    {
      return -ENOTDIR;
    }

    fill(buf, ".", NULL, 0);
    fill(buf, "..", NULL, 0);

    for (file = gpfs->nodes; file; file = file->next)
    {
      file_path_len = strlen(file->path);

      if (!strcmp(file->path, path))
      {
        continue;
      }

      if (file_path_len <= dir_path_len ||
          file->path[dir_path_len] != '/' ||
          strncmp(file->path, path, dir_path_len) ||
          strchr(file->path + dir_path_len + 1, '/'))
      {
        continue;
      }

      gpfs_node_stat(gpfs, file, &st);
      fill(buf, file->path + dir_path_len + 1, &st, 0);
    }

    return 0;
  }

  return -ENOENT;
}

/**
 * Create a GPFS directory
 * @param path Path to the directory
 * @param mode Mode of the directory
 * @return     Status
 */
int gpfs_mkdir(const char *path, mode_t mode) {
  struct gpfs_data *gpfs;

  assert((gpfs = (struct gpfs_data*)fuse_get_context()->private_data));

  // TODO(tache): add mode
  gpfs_create_dir(gpfs, path);
  return 0;
}

/**
 * Create non-directory, non-symbolic GPFS file
 * @param path Path to the file
 * @param mode Mode of the file
 * @param dev Type of the file
 * @return     Status
 */
int gpfs_mknod(const char * path, mode_t mode, dev_t type) {
  struct gpfs_data *gpfs;

  assert((gpfs = (struct gpfs_data*)fuse_get_context()->private_data));

  // TODO(tache): use mode and type
  gpfs_create_file(gpfs, path);

  return 0;
}


/**
 * Fuse function pointer struct
 */
static struct fuse_operations gpfs_operations =
{
  .mknod   = gpfs_mknod,
  .mkdir   = gpfs_mkdir,
  .open    = gpfs_open,
  .read    = gpfs_read,
  .write   = gpfs_write,
  .flush   = gpfs_flush,
  .readdir = gpfs_readdir,
  .release = gpfs_release,
  .getattr = gpfs_getattr,
  .init    = gpfs_init,
  .destroy = gpfs_destroy,
};


/**
 * Entry point of the application
 * @param argc Number of arguments
 * @param argv Argument values
 * @return 0 on success or error code
 */
int main(int argc, char **argv)
{
  return fuse_main(argc, argv, &gpfs_operations, NULL);
}
