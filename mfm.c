#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>


int main(int argc, char** argv) {

    if (argc<=1) {
        printf("./mfm -h to get help\n");
        exit(EXIT_SUCCESS);
    }

    int options=0;
    int argcompt=1;

    char* executable;
    char* nommain;
    char** fichiers;
    fichiers=malloc(100*sizeof(char*));
    int compteurf=0;
    while ((options = getopt (argc, argv, "he:m:f:")) != -1) {
        switch (options) {
            case 'h':
                printf ("\n--------------------------------------------------------------------------------------------------\n");
                printf ("./mfm -e [EXE NAME] -m [MAIN NAME] -f [FILE1 NAME] ... -f [FILEn NAME]\n");   
                printf ("\nEx:\n./mfm -e exe -m main -f fonctions\n./mfm -e exe -m main -f piles -f files -f listes");                            
                printf ("\n--------------------------------------------------------------------------------------------------\n\n");
                exit(EXIT_SUCCESS);
                break;
            case 'e':
                executable=optarg;
                break;
            case 'm':
                nommain=optarg;
                break;
            case 'f':
                fichiers[compteurf]=optarg;
                compteurf++;
                break;
        }
        argcompt++; 
    }



    FILE* mf=NULL;
    mf=fopen("makefile", "w");
    if (mf == NULL) {
        printf("ERROR OPENING MAKEFILE\n");
    }

    //executable
    printf("EXE : %s\n", executable);
    fprintf(mf, "%s:", executable); 
    for (int iii = 0; iii < compteurf; iii++){
        fprintf(mf, " %s.o", fichiers[iii]);
    }
    fprintf(mf, " %s.o\n", nommain);
	fprintf(mf, "	gcc");
    for (int iiii = 0; iiii < compteurf; iiii++){
        fprintf(mf, " %s.o", fichiers[iiii]);
    }
    fprintf(mf, " %s.o -o %s -Wall\n", nommain, executable);

    //fichiers
    for (int i = 0; i < compteurf; i++) {
        printf("FILE %d : %s\n",i+1, fichiers[i]);
        fprintf(mf, "%s.o: %s.c %s.h\n", fichiers[i], fichiers[i], fichiers[i]); 
	    fprintf(mf, "	gcc -c %s.c  -o %s.o -Wall\n", fichiers[i], fichiers[i]);
    }
    
    //main
    printf("MAIN : %s\n", nommain);
    fprintf(mf, "%s.o: %s.c", nommain, nommain); 
    for (int ii = 0; ii < compteurf; ii++){
        fprintf(mf, " %s.h", fichiers[ii]);
    }
    fprintf(mf, "\n");
	fprintf(mf, "	gcc -c %s.c -o %s.o -Wall\n", nommain, nommain);

    //clean
    fprintf(mf, "clean:\n");
    fprintf(mf, "	rm -f *.o\n");



    return 0;
}
