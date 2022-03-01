#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Osa
int isInteger(const char * str);
int checkFileFormat(char fileName[]);
int checkError(int numArg, char progName[], char seed[], char fileName[]);

// Devin


int has_Won(int row1[], int row2[], int row3[], int row4[], int row5[],
                int col1[], int col2[], int col3[], int col4[], int col5[], struct List *list);


void Printcard(int row1[], int row2[], int row3[], int row4[], int row5[], struct List *list);


int main(int argc, char* argv[]) {
        //Error Checking
        checkError(argc, argv[0], argv[1], argv[2]);

        FILE * filehandler;
        int row11, row12, row13, row14, row15;
        int row21, row22, row23, row24, row25;
        int row31, row32, row33, row34, row35;
        int row41, row42, row43, row44, row45;
        int row51, row52, row53, row54, row55;

        filehandler = fopen(argv[2], "r");

        fscanf(filehandler, "%2d %2d %2d %2d %2d", &row11, &row12, &row13, &row14, &row15);
        fscanf(filehandler, "%2d %2d %2d %2d %2d", &row21, &row22, &row23, &row24, &row25);
        fscanf(filehandler, "%2d %2d %2d %2d %2d", &row31, &row32, &row33, &row34, &row35);
        fscanf(filehandler, "%2d %2d %2d %2d %2d", &row41, &row42, &row43, &row44, &row45);
        fscanf(filehandler, "%2d %2d %2d %2d %2d", &row51, &row52, &row53, &row54, &row55);

        fclose(filehandler);

        //Filling the arrays for the rows
        int row1[] = {row11, row12, row13, row14, row15};
        int row2[] = {row21, row22, row23, row24, row25};
        int row3[] = {row31, row32, 0, row34, row35};
        int row4[] = {row41, row42, row43, row44, row45};
        int row5[] = {row51, row52, row53, row54, row55};

        //Filling the arrays for the columns
        int col1[] = {row11, row21, row31, row41, row51};
        int col2[] = {row12, row22, row32, row42, row52};
        int col3[] = {row13, row23, 0, row43, row53};
        int col4[] = {row14, row24, row34, row44, row54};
        int col5[] = {row15, row25, row35, row45, row55};

        //Filling the corner array
        int corners[] = {row11, row15, row51, row55};


        //The very first part
        struct List list;       // the call list
        INITIALIZE_list(75, &list);

        int seed = atoi(argv[1]);
        srand(seed);
        

        printf("CallList:\n\n");
        Printcard(row1, row2, row3, row4, row5, &list);
        printf("Enter any non-enter key for Call (q to quit): ");
        char input[75];
        fgets(input, 75, stdin);
        int calls = (strlen(input)) - 1 ;

        if (input[0] == 'q' || input[0] == 'Q') return 0;

        while (input[0] != 'q' || input[0] != 'Q')
        {
                if (calls != 0)
                {
                        for (int i = 0; i < calls; i++)
                        {
                                if (input[i] == 'q' || input[i] == 'Q')
                                {
                                system("clear");
                                 printf("CallList: ");
                                PRINT_list(&list);
                                Printcard(row1, row2, row3, row4, row5, &list);
                                printf("Enter any non-enter key for Call (q to quit):\n");
                                                return 0;
                                }
                                else {
                                
                                        long ran;
                                        ran = RANDOM(&list);
                                        ADD_list(ran, &list);
                                 }
                               
                        }

                }

                system("clear");


                 printf("CallList: ");
                 PRINT_list(&list);
                 Printcard(row1, row2, row3, row4, row5, &list);


                if (has_Won (row1, row2, row3, row4, row5, col1, col2, col3, col4, col5, &list) == 1)
                {
                printf("WINNER\n");
                exit (0);
                }

                printf("Enter any non-enter key for Call (q to quit): ");
                memset(input, 0, 75);
                fgets(input, 75, stdin);
                calls=0;
                calls = (strlen(input)) - 1 ;

                if (input[0] == 'q' || input[0] == 'Q') return 0;
        }

        return 0;
}
                                                              
                 
int checkError(int numArg, char progName[], char seed[], char fileName[]) {
        if (numArg != 3) {
                        fprintf(stderr, "Usage: %s seed cardFile\n", progName);
                        exit(1);
        }
        else if (isInteger(seed) == 0) {
                        fprintf(stderr, "Expected integer seed, but got %s\n", seed);
                        exit(2);
        }
        else if ( access( fileName, R_OK ) == -1 ) {
                        fprintf(stderr, "%s is nonexistent or unreadable\n", fileName);
                        exit(3);
        }
        else if (checkFileFormat(fileName) == 0) {
                fprintf(stderr, "%s has bad format\n", fileName);
                exit(4);
        }
        return 0;
}

int isInteger(const char * str) {
        while (*str) {
        char c = *str;

                if (c < '0' || c > '9') {
                        return 0;
                }

        str++;
        }
        return 1;
}

int checkFileFormat(char fileName[]) {
        FILE * filehandler;
        filehandler = fopen(fileName, "r");
        int rows = 0;
        char ch;

        while(!feof(filehandler)){
                ch=fgetc(filehandler);

                if (ch == '\n') {
                        rows++;
                }
        }

        fclose(filehandler);

        if (rows != 5) {
                return 0;
        }

        filehandler = fopen(fileName, "r");

        int row11, row12, row13, row14, row15;
        int row21, row22, row23, row24, row25;
        int row31, row32, row33, row34, row35;
        int row41, row42, row43, row44, row45;
        int row51, row52, row53, row54, row55;

        fscanf(filehandler, "%2d %2d %2d %2d %2d", &row11, &row12, &row13, &row14, &row15);
        fscanf(filehandler, "%2d %2d %2d %2d %2d", &row21, &row22, &row23, &row24, &row25);
        fscanf(filehandler, "%2d %2d %2d %2d %2d", &row31, &row32, &row33, &row34, &row35);
        fscanf(filehandler, "%2d %2d %2d %2d %2d", &row41, &row42, &row43, &row44, &row45);
        fscanf(filehandler, "%2d %2d %2d %2d %2d", &row51, &row52, &row53, &row54, &row55);
        fclose(filehandler);

        int entries[25] = {row11, row12, row13, row14, row15,
                           row21, row22, row23, row24, row25,
                           row31, row32, row33, row34, row35,
                           row41, row42, row43, row44, row45,
                           row51, row52, row53, row54, row55};

        int col1[5] = {row11, row21, row31, row41, row51};
        int col2[5] = {row12, row22, row32, row42, row52};
        int col3[5] = {row13, row23, row33, row43, row53};
        int col4[5] = {row14, row24, row34, row44, row54};
        int col5[5] = {row15, row25, row35, row45, row55};

        int counter;
        for (counter = 0; counter < 5; counter++) {
                if (col1[counter] < 1 || col1[counter] > 15) {
                        return 0;
                }
                else if (col2[counter] < 16 || col2[counter] > 30) {
                        return 0;
                }
                else if (col3[counter] < 31 || col3[counter] > 45) {
                        if (col3[counter] != 0 && counter == 3 ) {
                                return 0;
                        }
                }
                else if (col4[counter] < 46 || col4[counter] > 60) {
                        return 0;
                }
                else if (col5[counter] < 61 || col5[counter] > 75) {
                        return 0;
                }
                else {
                }
        }

        int loop;
        int looper;
        int duplicate = 1;
        for (loop = 0; loop < 25; loop++) {
                for (looper = 0; looper < 25; looper++) {
                        if (loop == looper) {
                                continue;
                        }
                        else if (entries[loop] == entries[looper]) {
                                return 0;
                        }
                }
                looper = 0;
        }

        if (row33 != 0) { //Check if middle of matrix is a zero
                return 0;
        }
        return 1;

}


int has_Won(int row1[], int row2[], int row3[], int row4[], int row5[],
                int col1[], int col2[], int col3[], int col4[], int col5[], struct List *list)
{
int r1 = 0;
int r2 = 0;
int r3 = 1;
int r4 = 0;
int r5 = 0;
int c1 = 0;
int c2 = 0;
int c3 = 1;
int c4 = 0;
int c5 = 0;
int corner = 0;



for (int i=0; i < 5; i++) {
        if (CHECK_list (row2[i], list) == 1)
        {
        r2++;
        }
}


for (int i=0; i < 5; i++) {
        if (CHECK_list (row1[i], list) == 1)
        {
        r1++;
        }
}


for (int i=0; i < 5; i++) {
        if (CHECK_list (row3[i], list) == 1)
        {
        r3++;
        }
}

for (int i=0; i < 5; i++) {
        if (CHECK_list (row4[i], list) == 1)
        {
        r4++;
        }
}



for (int i=0; i < 5; i++) {
        if (CHECK_list (row5[i], list) == 1)
        {
        r5++;
        }
}


for (int i=0; i < 5; i++) {
        if (CHECK_list (col2[i], list) == 1)
        {
        c2++;
        }
}

for (int i=0; i < 5; i++) {
        if (CHECK_list (col1[i], list) == 1)
        {
        c1++;
        }
}

for (int i=0; i < 5; i++) {
        if (CHECK_list (col3[i], list) == 1)
        {
        c3++;
        }
}

for (int i=0; i < 5; i++) {
        if (CHECK_list (col4[i], list) == 1)
        {
        c4++;
        }
}

for (int i=0; i < 5; i++) {
        if (CHECK_list (col5[i], list) == 1)
        {
        c5++;
        }
}

if (CHECK_list (row1[0], list) == 1 && CHECK_list (row1[4], list) == 1 && CHECK_list (row5[0], list) == 1 && CHECK_list (row5[4], list) == 1) //|| (CHECK_list (row1[5], list) == 1)
{
corner++;
}



   
if (r1 == 5 || r2 == 5 || r3 == 5 || r4 == 5 || r5 == 5 || c1 == 5 || c2 == 5 || c3 == 5 || c4 == 5 || c5 == 5 || corner == 1)
{
return 1;
}
else {
return 0;
}

}









void Printcard(int row1[], int row2[], int row3[], int row4[], int row5[], struct List *list) {

printf("L   I   N   U   X\n");

for (int i=0; i < 5; i++) {
        if (CHECK_list (row1[i], list) == 1)
        {
        printf("%02dm ", row1[i]);
        }
        else {
        printf("%02d  ", row1[i]);
        }
}

printf("\n");
for (int i=0; i < 5; i++) {
        if (CHECK_list (row2[i], list) == 1)
        {
        printf("%02dm ", row2[i]);
        }
        else {
       printf("%02d  ", row2[i]);
}
}

printf("\n");
for (int i=0; i < 5; i++) {
        if (i == 2)
        {
         printf("%02dm ", row3[i]);
        }
        else {
                if (CHECK_list (row3[i], list) == 1)
                {
                printf("%02dm ", row3[i]);
                }
                else {
                printf("%02d  ", row3[i]);
                }
        }
}

printf("\n");
for (int i=0; i < 5; i++) {
        if (CHECK_list (row4[i], list) == 1)
        {
        printf("%02dm ", row4[i]);
        }
        else {
       printf("%02d  ", row4[i]);
}
}

printf("\n");
for (int i=0; i < 5; i++) {
        if (CHECK_list (row5[i], list) == 1)
        {
        printf("%02dm ", row5[i]);
        }
        else {
       printf("%02d  ", row5[i]);
}
}

printf("\n");

}

