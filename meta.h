/* This file is part of the GPFS project.
 * Licensing information can be found in the LICENSE file
 * (C) 2014 The GPFS maniacs. All rights reserved.
 */
#ifndef __GPFS_META_H__
#define __GPFS_META_H__

/**
 * Node types
 */
enum gpfs_node_type
{
  GPFS_FILE,
  GPFS_DIR
};


/**
 * Node metadata
 */
struct gpfs_node
{
  /** Full path of the node */
  char *path;

  /** Type of the node */
  enum gpfs_node_type type;

  /** Next file in the list */
  struct gpfs_node *next;
};


struct gpfs_node * gpfs_create_file(struct gpfs_data *, const char *);
struct gpfs_node * gpfs_create_dir(struct gpfs_data *, const char *);
void               gpfs_free_node(struct gpfs_node *);


#endif /*__GPFS_META_H__*/
