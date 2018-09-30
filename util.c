#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>

#include "util.h"


struct CopymasterOptions ParseCopymaterOptions(int argc, char *argv[]) {
    
    extern int optind;
    extern char* optarg;

    struct CopymasterOptions cpm_options = {0};
    
    // premenne pre argumenty prepinacov
    char c, x;
    unsigned long long num;
    long pos1, pos2;
    

    while (1)
    {
        // viac informacii o spracovani jednotlivych prepinacov 
        //  - pozri: man 3 getopt
        
        int option_index = 0;
        
        static struct option long_options[] = {
            { "fast",      no_argument,       0, 'f' },
            { "slow",      no_argument,       0, 's' }, 
            { "create",    required_argument, 0, 'c' },
            { "overwrite", no_argument,       0, 'o' }, 
            { "append",    no_argument,       0, 'a' }, 
            { "lseek",     required_argument, 0, 'l' }, 
            { "directory", required_argument, 0, 'D' }, 
            { "delete",    no_argument,       0, 'd' },
            { "chmod",     required_argument, 0, 'm' }, 
            { "inode",     required_argument, 0, 'i' },
            { "umask",     required_argument, 0, 'u' }, 
            { "link",      no_argument,       0, 'K' },
            { "truncate",  required_argument, 0, 't' },
            { "sparse",    no_argument,       0, 'S' },
            { 0,             0,               0,  0  },
        };
        c = getopt_long(argc, argv, "fsc:oal:Ddm:i:u:lt:s", 
                        long_options, &option_index);
        if (c == -1)
            break; 
        
        switch (c)
        {
            case 'f':
                cpm_options.fast = 1;
                break;
            case 's': 
                cpm_options.slow = 1;
                break;
            case 'c': 
                cpm_options.create = 1;
                sscanf(optarg, "%o", &cpm_options.create_mode);
                break;
            case 'o': 
                cpm_options.overwrite = 1;
                break;
            case 'a': 
                cpm_options.append = 1;
                break;
            case 'l': 
                sscanf(optarg, "%c,%ld,%ld,%llu", &x, &pos1, &pos2, &num); 
                cpm_options.lseek_options.pos1 = (off_t)pos1;
                cpm_options.lseek_options.pos2 = (off_t)pos2;
                cpm_options.lseek_options.num = (size_t)num;
                switch (x) 
                {
                    case 'b':
                        cpm_options.lseek_options.x = SEEK_SET;
                        break;
                    case 'e':
                        cpm_options.lseek_options.x = SEEK_END;
                        break;
                    case 'c':
                        cpm_options.lseek_options.x = SEEK_CUR;
                        break;
                }
                break;
            case 'D': 
                cpm_options.directory = 1;
                break;
            case 'd': 
                cpm_options.delete_opt = 1;
                break;
            case 'm': 
                cpm_options.chmod = 1;
                sscanf(optarg, "%o", &cpm_options.chmod_mode);
                break;
            case 'i': 
                cpm_options.inode = 1;
                sscanf(optarg, "%lu", &cpm_options.inode_number);
                break;
            case 'u': 
                // TODO
                cpm_options.umask = 1;
                sscanf(optarg, "%o", &cpm_options.umask_mode);
                break;
            case 'k': 
                cpm_options.link = 1;
                break;
            case 't':
                cpm_options.truncate = 1;
                sscanf(optarg, "%ld", &pos1);
                cpm_options.truncate_size = (off_t)pos1; 
                break;
            case '?':
            default:
                fprintf(stderr, "Usage: %s [s|f] [-t size] [-l x,pos1,pos2,num] \n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
        
    // Kontrola ci boli zadanie parametre infile a outfile
    if (optind + 1 >= argc) {
        FatalError(' ', "CHYBA PREPINACOV", 20); // TODO toto by mala byt unikatna chyba
        exit(EXIT_FAILURE);
    }
    
    cpm_options.infile = argv[optind];
    cpm_options.outfile = argv[optind + 1];
    
    return cpm_options;
}

void FatalError(char c, const char* msg, int exit_status)
{
    fprintf(stderr, "%c:%d\n", c, errno); // removed space
    fprintf(stderr, "%c:%s\n", c, strerror(errno));
    fprintf(stderr, "%c:%s\n", c, msg);
    exit(exit_status);
}
