// sem vlozte potrebne hlavickove subory --------------------------------
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
// ----------------------------------------------------------------------

int main(int argc, char* argv[])
{
    extern char* optarg;
    extern int optind, opterr, optopt;

    // lokalne premenne
    int c;
    int digit_optind = 0;

    // premenne pre argumenty prepinacov
    long size;
    char x;
    long pos1, pos2, num;

    // spracovanie prepinacov
    while (1)
    {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;

        // viac informacii o spracovani jednotlivych moznosti - pozri - // man 3
        // getopt
        
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
        c = getopt_long(argc, argv, "sft:l:", // doplnte dalsie volby (options)
            // podla zadania - aj ci su s argumentom
            long_options, &option_index);
        if (c == -1)
            break; // ziadne dalsie volby
        switch (c)
        {
            case 's': // spracovanie - moznost 's'
                printf("prepinac - s\n");
                // pokracovanie spracovania
                break;
            case 'f': // spracovanie - moznosť 'f'
                printf("prepinac - f\n");
                // pokracovanie spracovania
                break;
            case 't': // spracovanie - moznost 't'
                printf("prepinac - t\n");
                size = atoi(optarg); // spracovanie argumentu danej volby (option)
                printf("size=%ld\n", size);
                // pokracovanie spracovania
                break;
            case 'l': // spracovanie - option 'l'
                printf("prepinac - l\n");
                sscanf(optarg, "%c,%ld,%ld,%ld", &x, &pos1, &pos2,
                    &num); // spracovanie argumentu danej voľby (option)
                printf("x=%c\n", x);
                printf("pos1=%ld\n", pos1);
                printf("pos2=%ld\n", pos2);
                printf("num=%ld\n", num);
                // ...    			   pokracovanie spracovania
                break;

            // analogickym sposobom osetrite dalsie volby
            // ....
            // vsetky volby osetrene

            // osetrenie chyby spracovania prepinacov
            case '?':
            //  break;
            default:
                fprintf(stderr, "Usage: %s [s|f] [-t size] [-l x,pos1,pos2,num] \n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    // koniec spracovanie prepinacov
    // *****************************************************************************************************************

    //*******************************************
    //   Sem pridajte kod pre osetrenie prepinacov pred kopirovanim
    //******************************************

    //*******************************************
    //   Sem pridajte kod pre kopirovanie suborov
    //******************************************

    //*******************************************
    //   Sem pridajte kod pre vypis adresara
    //******************************************

    //*******************************************
    //   Sem pridajte kod pre osetrenie prepinacov po kopirovani
    //******************************************
}

