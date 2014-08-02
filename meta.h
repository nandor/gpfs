/* This file is part of the GPFS project.
 * Licensing information can be found in the LICENSE file
 * (C) 2014 The GPFS maniacs. All rights reserved.
 */
#ifndef __GPFS_META_H__
#define __GPFS_META_H__


/**
 * File metadata
 */
struct gpfs_file
{
  /** Full path of the file */
  const char *name;

  /** Next file in the list */
  struct gpfs_file *next;
};


#endif /*__GPFS_META_H__*/
