#include <stdio.h>

#include "misc.h"


int main(int argc, char* argv[])
{
    struct CopymasterOptions cpm_options = ParseCopymaterOptions(argc, argv);

    //-------------------------------------------------------------------
    // Kontrola hodnot prepinacov
    //-------------------------------------------------------------------

    // Vypis hodnot prepinacov odstrante z finalnej verzie
    
    printf("infile:        %s\n", cpm_options.infile);
    printf("outfile:       %s\n", cpm_options.outfile);
    
    printf("fast:          %d\n", cpm_options.fast);
    printf("slow:          %d\n", cpm_options.slow);
    printf("create:        %d\n", cpm_options.create);
    printf("create_mode:   %o\n", (unsigned int)cpm_options.create_mode);
    printf("overwrite:     %d\n", cpm_options.overwrite);
    printf("append:        %d\n", cpm_options.append);
    printf("lseek:         %d\n", cpm_options.lseek);
    
    printf("lseek_options.x:    %d\n", cpm_options.lseek_options.x);
    printf("lseek_options.pos1: %ld\n", cpm_options.lseek_options.pos1);
    printf("lseek_options.pos2: %ld\n", cpm_options.lseek_options.pos2);
    printf("lseek_options.num:  %lu\n", cpm_options.lseek_options.num);
    
    printf("directory:     %d\n", cpm_options.directory);
    printf("delete_opt:    %d\n", cpm_options.delete_opt);
    printf("chmod:         %d\n", cpm_options.chmod);
    printf("chmod_mode:    %o\n", (unsigned int)cpm_options.chmod_mode);
    printf("inode:         %d\n", cpm_options.inode);
    printf("inode_number:  %lu\n", cpm_options.inode_number);
    
    printf("umask:\t%d\n", cpm_options.umask);
    for(unsigned int i=0; i<kUMASK_OPTIONS_MAX_SZ; ++i) {
        if (cpm_options.umask_options[i][0] != 0) {
            printf("umask_options[%u]: %s\n", i, cpm_options.umask_options[i]);
        }
        else {
            break;
        }
    }
    
    printf("link:          %d\n", cpm_options.link);
    printf("truncate:      %d\n", cpm_options.truncate);
    printf("truncate_size: %ld\n", cpm_options.truncate_size);
    printf("sparse:        %d\n", cpm_options.sparse);

    
    //-------------------------------------------------------------------
    // Osetrenie prepinacov pred kopirovanim
    //-------------------------------------------------------------------
    
    if (cpm_options.fast && cpm_options.slow) {
        FatalError(' ', "CHYBA PREPINACOV", 20); // TODO znak pre prefix
    }
    
    // TODO Nezabudnut dalsie kontroly kombinacii prepinacov ...
    
    //-------------------------------------------------------------------
    // Kopirovanie suborov
    //-------------------------------------------------------------------
    
    // TODO Implementovat kopirovanie suborov
    
    // cpm_options.infile
    // cpm_options.outfile
    
    //-------------------------------------------------------------------
    // Vypis adresara
    //-------------------------------------------------------------------
    
    if (cpm_options.directory) {
        // TODO Implementovat vypis adresara
    }
        
    //-------------------------------------------------------------------
    // Osetrenie prepinacov po kopirovani
    //-------------------------------------------------------------------
    
    // TODO Implementovat osetrenie prepinacov po kopirovani
    
    return 0;
}

