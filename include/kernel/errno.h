/**
 * \file errno.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Error codes returned by kernel functions
 */
#ifndef H_ERRNO
#define H_ERRNO

/** Permission denied */
#define EACCES (1)

/** Bad file descriptor */
#define EBADF (2)

/** Device or resource busy */
#define EBUSY (3)

/** File exists */
#define EEXIST (4)

/** Operation in progress */
#define EINPROGRESS (5)

/** Invalid argument */
#define EINVAL (6)

/** I/O error */
#define EIO (7)

/** No buffer space available */
#define ENOBUFS (8)

/** No such device */
#define ENODEV (9)

/** Not enough space */
#define ENOMEM (10)

/** No space left on device */
#define ENOSPC (11)

/** Function not supported */
#define ENOSYS (12)

/** Not supported */
#define ENOTSUP (13)

/** No such device or address */
#define ENXIO (14)

/** Operation not permitted */
#define EPERM (15)

#endif
