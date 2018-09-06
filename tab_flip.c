#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 2048
#define NUM_STRINGS 6

char stringNames[] = "eBGDAE";
typedef struct {
    char *strings[6];
    int stringBufIndices[6];
} Tab;

/* Free tab object */
void freeTab(Tab *tab) {
    int stringNdx;
    for (stringNdx = 0; stringNdx < NUM_STRINGS; stringNdx++) {
        if (tab->strings[stringNdx] != NULL) {
            free(tab->strings[stringNdx]);
            tab->strings[stringNdx] = NULL;
        }
    }
}


/* Read the input file into our Tab data structure */
void initTab(FILE *inputFile, Tab *tab) {
    
    int stringNdx;

    for (stringNdx = 0; stringNdx < NUM_STRINGS; stringNdx++) {
        tab->strings[stringNdx] = malloc(BUF_SIZE * sizeof(char));
        fgets(tab->strings[stringNdx], BUF_SIZE, inputFile);
        tab->stringBufIndices[stringNdx] = 2;

        /* Check that each line begins with a string name and a "|" character */
        if (strlen(tab->strings[stringNdx]) < 2 
            || tab->strings[stringNdx][0] != stringNames[stringNdx] 
            || tab->strings[stringNdx][1] != '|') {
            perror ("Tab file does not contain correct tab format.");
            exit(EXIT_FAILURE);
        }
        int ndx;
        for (ndx = 0; ndx < strlen(tab->strings[stringNdx]); ndx++) {
            if (tab->strings[stringNdx][ndx] == '\r' || tab->strings[stringNdx][ndx] == '\n') {
                tab->strings[stringNdx][ndx] = '\0';
            }
        }
    }
}

void createCSVHeader(Tab *tab) {
    int stringNdx;
    for (stringNdx = NUM_STRINGS - 1; stringNdx >= 0; stringNdx--) {
        
        if (stringNdx > 0) {
            printf("%c,", tab->strings[stringNdx][0]);
        }
        else {
            printf("%c\n", tab->strings[stringNdx][0]);
        }
    }
}

/* Check if we have completed reading this line */
int isAtEndOfLine(Tab *tab, int stringNdx) {
    return tab->stringBufIndices[stringNdx] >= strlen(tab->strings[stringNdx]) ? 1 : 0;
}

/* Check if the current note/chord is empty */
int isLineEmpty(char notes[6][3]) {
    int isEmpty = 1;
    int stringNdx;
    for (stringNdx = 0; stringNdx < NUM_STRINGS; stringNdx++) {
        if (notes[stringNdx][0] != '-' && notes[stringNdx][0] != '\0') {
            return 0;
        }
    }
    
    return 1;
}

/* Check each string buffer and check if we have finished reading all of the lines */
int isDoneReading(Tab *tab) {
    int stringNdx, done = 1;
    for (stringNdx = 0; stringNdx < NUM_STRINGS; stringNdx++) {
        if (!isAtEndOfLine(tab, stringNdx)) {
            return 0;
        }
    }
    return 1;
}

/* This function sets all of the indices for the string buffers to the same value
This is used when we encounter a fret numbered 10-24 so that all of the other strings that do not have
double digit frets are reading from the same point in the tab. */
void equalizeIndices(Tab *tab, int maxIndex) {
    int stringNdx;
    for (stringNdx = NUM_STRINGS - 1; stringNdx >= 0; stringNdx--) {
        if (tab->stringBufIndices[stringNdx] != maxIndex) {
            tab->stringBufIndices[stringNdx] = maxIndex;
        }   
    }  
}

void printLine(char notes[6][3]) {
    int stringNdx;
    for (stringNdx = NUM_STRINGS - 1; stringNdx >= 0; stringNdx--) {
        if (stringNdx > 0) {
            printf("%s,", notes[stringNdx]);
        }
        else {
            printf("%s\n", notes[stringNdx]);
        }
        
    }
}
/* Checks to see if the first character is a '1' or a '2' so that we are only including frets 10-24 
    If the first number is a '2', then the second number must be 0-4 
*/
int isInFretRange(char notes[6][3], Tab *tab, int stringNdx) {
    if (notes[stringNdx][0] == '0') {
        return 1;
    }
    else if (notes[stringNdx][0] == '1') {
        return 1;
    }
    else if (notes[stringNdx][0] == '2') {
        switch (tab->strings[stringNdx][tab->stringBufIndices[stringNdx]]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
                return 1;
            default:
                return 0;
        }
    }
    else {
        return 0;
    }
}

int nextCharIsValidNumber(char notes[6][3], Tab *tab, int stringNdx) {
return tab->strings[stringNdx][tab->stringBufIndices[stringNdx]] != '-' /* If the next char is not a '-' */
          && notes[stringNdx][0] != '-' /* If the char we just read was not a '- */
          && isInFretRange(notes, tab, stringNdx) ? 1 : 0; /* If the fret number is valid (0-24) */
}

void parseTab(Tab *tab) {
    int stringNdx, stringBufNdx;
    /* A buffer to store our current line we are reading */
    char notes[6][3] = {0};

    while (!isDoneReading(tab)) {
        
        int maxBufIndex = -1; /* Keeps track of the string buffer index if we see a double character number */
        for (stringNdx = NUM_STRINGS - 1; stringNdx >= 0; stringNdx--) {
            /* Check if we have read this whole line yet */
            if (!isAtEndOfLine(tab, stringNdx)) {
                /* Set the first character of the column */
                stringBufNdx = tab->stringBufIndices[stringNdx]++;
                notes[stringNdx][0] = tab->strings[stringNdx][stringBufNdx];
                /* Check for two character string numbers (10-24) */
                if (!isAtEndOfLine(tab, stringNdx) && nextCharIsValidNumber(notes, tab, stringNdx)) {
                    /* If the char we just read was not a '-', and the next character isn't a '-' then it's the next char is a number too */
                    stringBufNdx = tab->stringBufIndices[stringNdx]++;
                    notes[stringNdx][1] = tab->strings[stringNdx][stringBufNdx];
                    maxBufIndex = tab->stringBufIndices[stringNdx];
                }
            }
        }
        if (!isLineEmpty(notes)) {
           printLine(notes);
        }

        /* If we read a double digit fret, maxBufIndex will be set */
        if (maxBufIndex > 0) {
            equalizeIndices(tab, maxBufIndex);
        }
        /* Clear our note buffer */
        memset(notes, '\0', 18);
    }

}

int main(int argc, char **argv) {
    FILE *inputFile;
    Tab *tab; 

    if (argc < 2) {
        perror("Usage: ./tab_flip /path/to/tab/file");
        exit(EXIT_FAILURE);
    }
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        perror("Unable to open input file");
        exit(EXIT_FAILURE);
    }
    tab = malloc(sizeof(Tab));
    initTab(inputFile, tab);
    createCSVHeader(tab);
    parseTab(tab);  
    freeTab(tab);

}