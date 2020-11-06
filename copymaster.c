#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h> 
#include "options.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void FatalError(char c, const char* msg, int exit_status);
void PrintCopymasterOptions(struct CopymasterOptions* cpm_options);


int main(int argc, char* argv[])
{
    struct CopymasterOptions cpm_options = ParseCopymasterOptions(argc, argv);

    //-------------------------------------------------------------------
    // Kontrola hodnot prepinacov
    //-------------------------------------------------------------------

    // Vypis hodnot prepinacov odstrante z finalnej verzie
    
    //PrintCopymasterOptions(&cpm_options);
    
    //-------------------------------------------------------------------
    // Osetrenie prepinacov pred kopirovanim
    //-------------------------------------------------------------------
    
    if (cpm_options.fast && cpm_options.slow) {
        fprintf(stderr, "CHYBA PREPINACOV\n"); 
        exit(EXIT_FAILURE);
    }
    
    // TODO Nezabudnut dalsie kontroly kombinacii prepinacov ...
    
    //-------------------------------------------------------------------
    // Kopirovanie suborov
    //-------------------------------------------------------------------
    
    
    if(argc <= 3){
        struct stat inf;
        char buf[1];
        int n;
        int des = open (cpm_options.infile, O_RDONLY);
        if(des < 0){
            return 21;
        }
        n = stat(cpm_options.infile, &inf);
        if(n < 0){
            return 21;
        }
        int des2 = open(cpm_options.outfile, O_WRONLY|O_CREAT|O_TRUNC, inf.st_mode);
        
        while (read(des,buf,1) > 0){
            write(des2, buf,1);
        }
        if(des2 < 0){
            close(des); 
            close(des2);
            return 21;
        }
    
        close(des); 
        close(des2);
    }
    if(cpm_options.fast){ 
        struct stat inf;
        int count;
        
        int des0 = open (cpm_options.infile, O_RDONLY);
        stat(cpm_options.infile, &inf);
        int desC = open(cpm_options.outfile, O_WRONLY|O_CREAT|O_TRUNC, inf.st_mode);
        
        count = lseek(des0,0L,SEEK_END); //zistim pocet znakov originalu
        char buffer[count];
        buffer[count] = '\0';
        //printf("count buffer  : %d\n",count);
        read( des0 ,&buffer ,count);    //nacitanie celeho originalu do buf
        //printf("fast buffer 1 : %s\n",buffer);
        write(desC,&buffer ,count);       //prepisanie celeho buf do kopie
        //printf("fast buffer 2 : %s\n",buffer);
        /*
        if(desC < 0){
            printf("INA CHYBA");
        }
        */
        close(des0);
        close(desC);
        //printf("FAST\n");//TEST
    }
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


void FatalError(char c, const char* msg, int exit_status)
{
    fprintf(stderr, "%c:%d\n", c, errno); 
    fprintf(stderr, "%c:%s\n", c, strerror(errno));
    fprintf(stderr, "%c:%s\n", c, msg);
    exit(exit_status);
}

void PrintCopymasterOptions(struct CopymasterOptions* cpm_options)
{
    if (cpm_options == 0)
        return;
    
    printf("infile:        %s\n", cpm_options->infile);
    printf("outfile:       %s\n", cpm_options->outfile);
    
    printf("fast:          %d\n", cpm_options->fast);
    printf("slow:          %d\n", cpm_options->slow);
    printf("create:        %d\n", cpm_options->create);
    printf("create_mode:   %o\n", (unsigned int)cpm_options->create_mode);
    printf("overwrite:     %d\n", cpm_options->overwrite);
    printf("append:        %d\n", cpm_options->append);
    printf("lseek:         %d\n", cpm_options->lseek);
    
    printf("lseek_options.x:    %d\n", cpm_options->lseek_options.x);
    printf("lseek_options.pos1: %ld\n", cpm_options->lseek_options.pos1);
    printf("lseek_options.pos2: %ld\n", cpm_options->lseek_options.pos2);
    printf("lseek_options.num:  %lu\n", cpm_options->lseek_options.num);
    
    printf("directory:     %d\n", cpm_options->directory);
    printf("delete_opt:    %d\n", cpm_options->delete_opt);
    printf("chmod:         %d\n", cpm_options->chmod);
    printf("chmod_mode:    %o\n", (unsigned int)cpm_options->chmod_mode);
    printf("inode:         %d\n", cpm_options->inode);
    printf("inode_number:  %lu\n", cpm_options->inode_number);
    
    printf("umask:\t%d\n", cpm_options->umask);
    for(unsigned int i=0; i<kUMASK_OPTIONS_MAX_SZ; ++i) {
        if (cpm_options->umask_options[i][0] == 0) {
            // dosli sme na koniec zoznamu nastaveni umask
            break;
        }
        printf("umask_options[%u]: %s\n", i, cpm_options->umask_options[i]);
    }
    
    printf("link:          %d\n", cpm_options->link);
    printf("truncate:      %d\n", cpm_options->truncate);
    printf("truncate_size: %ld\n", cpm_options->truncate_size);
    printf("sparse:        %d\n", cpm_options->sparse);
}
