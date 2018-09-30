#ifndef UTIL_H
#define UTIL_H

#include <sys/types.h>

struct CopymasterOptionsLseek {
    int x;
    off_t pos1;
    off_t pos2;
    size_t num;
};

struct CopymasterOptions {
    const char * infile;
    const char * outfile;
    int fast;
    int slow;
    int create;
    int create_mode;
    int overwrite;
    int append;
    int lseek;
    struct CopymasterOptionsLseek lseek;
    int directory;
    int delete_opt;
    int chmod;
    int umask;
    int link;
    int truncate;
    off_t truncate_size;
    int sparse;
};

#endif /* UTIL_H */
