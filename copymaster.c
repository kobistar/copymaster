#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "options.h"


void FatalError(char c, const char* msg, int exit_status);
void PrintCopymasterOptions(struct CopymasterOptions* cpm_options);


int main(int argc, char* argv[]){
    
    if(argc < 3){
        printf("ZADAJ VSTUPNY A VYSTUPNY SUBOR\n");
        exit(20);
    }

    struct CopymasterOptions cpm_options = ParseCopymasterOptions(argc, argv);
    
    char *dFile=argv[argc-1];       //outfile -do filename si ulozime nazov copy suboru
    char *sFile=argv[argc-2];       //infile - do filename si ulozime nazov orig suboru
    struct stat stat_buff;
    
    //nasttaveniai prepinacov 
    if (cpm_options.create && cpm_options.overwrite){
        fprintf(stderr, "CHYBA PREPINACOV\n");
        exit(EXIT_FAILURE);
    }

    if (cpm_options.fast && cpm_options.slow) {
        fprintf(stderr, "CHYBA PREPINACOV\n");
        exit(EXIT_FAILURE);
    }
    if(cpm_options.link || cpm_options.sparse || cpm_options.directory){
        if(argc > 4){
            fprintf(stderr, "CHYBA PREPINACOV\n");
            exit(EXIT_FAILURE);
        }
    }
    
    stat(sFile,&stat_buff);
    int fd1,fd2;  //f1 In f2 OUT
    int noFlag = 1;
    
    if(cpm_options.link == 1){
        
        fd1 = open(sFile,O_RDONLY);
        
        if (fd1 == -1){
            if (errno == 2){
                FatalError(errno, "-:VSTUPNY SUBOR NEEXISTUJE\n", 30);
            } 
            else{
                FatalError(errno, "-:INA CHYBA\n", 30);
            }
        }
        close(fd1);
        int link_tmp;
        /*
        if (== -1){
            if (errno == 2){
                FatalError(errno, "-:VYSTUPNY SUBOR UZ EXISTUJE\n", 30);
            } */
            
        link_tmp = link(sFile,dFile);
        
        if(link_tmp < 0){
            FatalError(errno, "-:VYSTUPNY SUBOR NEVYTVORENY\n", 30);
        }
        exit(0);
    }
    
    if((fd1=open(sFile,  O_RDONLY)) == -1){
        if (errno == 2) {
            FatalError(errno, "-:VSTUPNY SUBOR NEEXISTUJE\n", 21);
        }
        else{
            FatalError(errno, "-:INA CHYBA\n", 21);
        }
    }
    
    if(cpm_options.inode == 1){
        
        if(stat_buff.st_ino != cpm_options.inode_number){  //pri -i kopiruje ak plati podmienka
            noFlag = 0;
            FatalError(errno,"-:ZLY INODE\n",27);
        }
        else{
            fd2 = open(dFile, O_CREAT|O_WRONLY, stat_buff.st_mode);
        }
        if(fd2 == -1){
            if(errno == 2){
                FatalError(errno, "-:INA CHYBA\n",27);
            }
        }    
        if(!S_ISREG(stat_buff.st_mode)){ //a infile je obycajny subor
            FatalError(errno,"-:ZLY TYP VSTUPNEHO SUBORU\n",27);
        }
    }
    if(cpm_options.append){
        
        fd2 = open(dFile, O_CREAT|O_WRONLY|O_APPEND, stat_buff.st_mode);
        
        if(fd2 == -1){
            if (errno == 2){
                FatalError(errno, "-:SUBOR NEEXISTUJE\n", 22);
            } 
            else{
                FatalError(errno, "-:INA CHYBA\n", 22);
            }
        }
    }
    else if (cpm_options.overwrite == 1){
        fd2  = open(dFile, O_WRONLY|O_TRUNC, stat_buff.st_mode);
        
        if(fd2 == -1){
            if (errno == 2) {
                FatalError(errno, "-:SUBOR NEEXISTUJE\n", 24);
            } 
            else{
                FatalError(errno, "-:INA CHYBA\n", 24);
            }
        }
    }
    else if(cpm_options.create == 1){
        fd2 = open(dFile, O_EXCL|O_CREAT|O_WRONLY|O_TRUNC, cpm_options.create_mode);
        
        if(fd2 == -1){
            if (errno == 2) {
                FatalError(errno, "-:SUBOR EXISTUJE\n", 23);
            }
            else{
                FatalError(errno, "-:INA CHYBA\n", 23);
            }
        }
        if(cpm_options.create < 0 || cpm_options.create > 777){
            FatalError(errno, "-:ZLE PRAVA\n",23);
        }
    }
    
    else if(cpm_options.lseek == 1){
        noFlag = 0;
        
        int pos1 = cpm_options.lseek_options.pos1;
        int pos2 = cpm_options.lseek_options.pos2;
        int num = cpm_options.lseek_options.num;
        
        char buff[num];

        fd2 = open (dFile, O_CREAT | O_WRONLY, stat_buff.st_mode);
        if(fd2 == -1){
            if(errno == 2)
                FatalError(errno, "-:INA CHYBA\n", 33);
        }
        if(lseek(fd1,pos1,SEEK_SET) != pos1){
            FatalError(errno, "-:CHYBA POZICIE infile",33);
        }
        if(lseek(fd2,pos2,SEEK_SET) != pos2){
            FatalError(errno, "-:CHYBA POZICIE oufile",33);
        }
        read(fd1,buff,num);
        
        write(fd2,buff,num);
    }
    else{
        fd2 = open(dFile,O_WRONLY|O_CREAT|O_TRUNC, stat_buff.st_mode);
        
        if(fd2 == -1){
            if (errno == 2) {
                FatalError(errno, "-:SUBOR EXISTUJE\n", 21);
            }
            else{
                FatalError(errno, "-:INA CHYBA\n", 21);
            }
        }
    }

    int bufSize = stat_buff.st_size;
    int n;
    char buffer[(int) bufSize];  
    
    if(cpm_options.slow == 1){
        
        for(int i = 0; i < bufSize; i++){
            read(fd1,&buffer,1);
            write(fd2,&buffer,1);
        }
    }
    else{
        if(cpm_options.fast == 1){
            read(fd1,&buffer,bufSize);
            write(fd2,&buffer,bufSize);   
        }
        if(noFlag  == 1){
            while((n = read(fd1, &buffer, 1)) > 0){
                write(fd2, &buffer, 1);
            }
        }
    }
    
    if(cpm_options.truncate == 1){
      
        stat(sFile,&stat_buff);
        if(truncate(sFile,cpm_options.truncate_size) < 0){
            FatalError(errno,"-:ZAPORNA VELKOST",31);
        }
    }

    close(fd1);
    close(fd2);
    
    if(cpm_options.delete_opt == 1){
        if(remove(cpm_options.infile) < 0){             //zmazanie originalu az po zatvoreni
            if (errno == 2) {
                FatalError(errno, "-:SUBOR NEBOL ZMAZANY\n", 26);
            }
            else{
                FatalError(errno, "-:INA CHYBA\n", 26);
            }
        }
    }
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
