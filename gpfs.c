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
  struct gpfs *gpfs;

  gpfs = (struct gpfs*)malloc(sizeof(struct gpfs_data));

  return gpfs;
}


/**
 * Destroys the GPFS filesystem
 */
static void gpfs_destroy(void *data)
{
  struct gpfs_data *gpfs;

  if (!(gpfs = (struct gpfs_data*)data))
  {
    return;
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
static int gpfs_getattr(const char *path, struct stat *stat)
{
  struct gpfs_data *gpfs;

  assert((gpfs = (struct gpfs_data*)fuse_get_context()->private_data));

  return 0;
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

  assert((gpfs = (struct gpfs_data*)fuse_get_context()->private_data));

  return 0;
}


/**
 * Fuse function pointer struct
 */
static struct fuse_operations gpfs_operations =
{
  .init    = gpfs_init,
  .open    = gpfs_open,
  .release = gpfs_release,
  .getattr = gpfs_getattr,
  .readdir = gpfs_readdir,
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
