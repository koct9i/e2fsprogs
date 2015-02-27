#define _LARGEFILE_SOURCE

#include "config.h"
#if HAVE_ERRNO_H
#include <errno.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <fcntl.h>
#include <sys/ioctl.h>

#include "e2p.h"

int fgetproject(const char *name, unsigned *project)
{
#if HAVE_EXT2_IOCTLS
	int fd, ret, save_errno = 0;

	fd = open(name, O_RDONLY | O_NONBLOCK | O_NOCTTY);
	if (fd < 0)
		return -1;
	ret = ioctl(fd, FS_IOC_GETPROJECT, project);
	if (ret < 0)
		save_errno = errno;
	close(fd);
	if (ret < 0)
		errno = save_errno;
	return ret;
#else /* ! HAVE_EXT2_IOCTLS */
	errno = EOPNOTSUPP;
	return -1;
#endif /* ! HAVE_EXT2_IOCTLS */
}

int fsetproject(const char *name, unsigned project)
{
#if HAVE_EXT2_IOCTLS
	int fd, ret, save_errno = 0;

	fd = open(name, O_RDONLY | O_NONBLOCK | O_NOCTTY);
	if (fd < 0)
		return -1;
	ret = ioctl(fd, FS_IOC_SETPROJECT, &project);
	if (ret < 0)
		save_errno = errno;
	close(fd);
	if (ret < 0)
		errno = save_errno;
	return ret;
#else /* ! HAVE_EXT2_IOCTLS */
	errno = EOPNOTSUPP;
	return -1;
#endif /* ! HAVE_EXT2_IOCTLS */
}
