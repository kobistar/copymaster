#include <stdio.h>

#include "util.h"


int main(int argc, char* argv[])
{
    struct CopymasterOptions cpm_options = ParseCopymaterOptions(argc, argv);

    // Kontrola hodnot prepinacov
    
    printf("infile:\t%s\n", cpm_options.infile);
    printf("outfile:\t%s\n", cpm_options.outfile);
    
    printf("fast:\t%d\n", cpm_options.fast);
    printf("slow:\t%d\n", cpm_options.slow);
    printf("create:\t%d\n", cpm_options.create);
    printf("create_mode:\t%d\n", cpm_options.create_mode);
    printf("overwrite:\t%d\n", cpm_options.overwrite);
    printf("append:\t%d\n", cpm_options.append);
    printf("lseek:\t%d\n", cpm_options.lseek);
    
    printf("lseek_options.x:\t%d\n", cpm_options.lseek_options.x);
    printf("lseek_options.pos1:\t%ld\n", cpm_options.lseek_options.pos1);
    printf("lseek_options.pos2:\t%ld\n", cpm_options.lseek_options.pos2);
    printf("lseek_options.num:\t%lu\n", cpm_options.lseek_options.num);
    
    printf("directory:\t%d\n", cpm_options.directory);
    printf("delete_opt:\t%d\n", cpm_options.delete_opt);
    printf("chmod:\t%d\n", cpm_options.chmod);
    printf("chmod_mode:\t%d\n", cpm_options.chmod_mode);
    printf("inode:\t%d\n", cpm_options.inode);
    printf("inode_number:\t%lu\n", cpm_options.inode_number);
    printf("umask:\t%d\n", cpm_options.umask);
    printf("umask_mode:\t%o\n", (unsigned int)cpm_options.umask_mode);
    printf("link:\t%d\n", cpm_options.link);
    printf("truncate:\t%d\n", cpm_options.truncate);
    printf("truncate_size:\t%ld\n", cpm_options.truncate_size);
    printf("sparse:\t%d\n", cpm_options.sparse);

    
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

