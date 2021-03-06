/*
 * This file is part of the spcct and licensed under the GNU General Public License.
 * http://www.gnu.org/licenses/gpl.txt
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <nqcommon.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

off_t nq_get_file_length(char * path);


#if !defined(NQDEBUG)

void nq_errmsg_exit(char *fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, arglist);
    fprintf(stderr, "\n");
    va_end(arglist);
    exit(1);
}

void nq_warnmsg(char *fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, arglist);
    fprintf(stderr, "\n");
    va_end(arglist);
}

void nq_errmsg(char *fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, arglist);
    fprintf(stderr, "\n");
    va_end(arglist);
}

void nq_normsg(char *fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);
    vfprintf(stdout, fmt, arglist);
    fprintf(stdout, "\n");
    va_end(arglist);

}

#endif /* NQDEBUG */



int nq_set_fd_nonblocking(int fd)
{
    int fd_flag;
    if((fd_flag = fcntl(fd, F_GETFL, 0)) < 0)
    {
        nq_errmsg("fcntl: %s", strerror(errno));
        return -1;
    }
    fd_flag |= O_NONBLOCK;
    if(fcntl(fd, F_SETFL, fd_flag) < 0)
    {
        nq_errmsg("fcntl: %s", strerror(errno));
        return -1;
    }
    return 0;
}




off_t nq_get_file_length(char * path)
{
    struct stat st_buf;

    if(stat (path, &st_buf) < 0)
    {
        nq_errmsg("stat: %s", strerror(errno));
        return (off_t)-1;
    }
    return st_buf.st_size;
}





