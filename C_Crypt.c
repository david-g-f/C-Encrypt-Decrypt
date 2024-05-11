#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER 255

/* TODO
 *
 * Program will be ran through terminal with a second argument being the file, and a third argument choosing whether to encrypt or decrypt. 
 * This will work with .txt files for now.
 * 
*/
void fileEncrypt(FILE* in, FILE* out) 
{
    int min = 1;
    int max = 64;

    int randKey = 1 + (rand() % (max)); // Generates a number between 1 and 64 inclusive
    printf("Your generated key for this file is: %d\n", randKey);

    int len;
    char buffer[BUFFER]; // Stores chunks of text data from input file to edit.

    while (fgets(buffer, (sizeof(char) * BUFFER), in) != 0){
        len = strlen(buffer);
        for (int i = 0; i < len; i++){
            buffer[i] -= randKey;
        }
        fputs(buffer, out);
    }

} 

void fileDecrypt(FILE* in, FILE* out, int key)
{
    int len;
    char buffer[BUFFER];

    while(fgets(buffer, (sizeof(char) * BUFFER), in) != 0){
        len = strlen(buffer);
        for (int i = 0; i < len; i++){
            buffer[i] += key;
        }
        fputs(buffer, out);
    }

} 

void removeSub(char* str, const char* delim){ //Auxiliary function for ease of life
    char* match = strstr(str, delim); // Locate the substring of a given delimiter in a string
    if (match != NULL){
        *match = '\0'; // If substring exists, replace it with a null terminator.
    }
}

int main(int argc, char *argv[]){

    srand(time(NULL)); // Random number key generator purposes
    const char delim1[] = ".txt";
    const char delim2[] = "_crypt.txt";

    // Error handling
    if (argc < 3){
        fprintf(stderr, "Too little arguments passed.\nUsage: <filename> [-e/-d options]\n");
        return 1;
    }
    if (argc > 3){
        fprintf(stderr, "Too many arguments passed.\n");
        return 1;
    }

    // Basic command-line parsing
    if (strcmp(argv[2], "-e") == 0){
        FILE * inp = fopen(argv[1], "r");
        if (inp == NULL){
            fprintf(stderr, "Error reading file %s during encryption.\n", argv[1]);
            return 1;
        }

        char * fName = argv[1];
        removeSub(fName, delim1);

        char * fileName = strcat(fName, "_crypt.txt");
        FILE * out = fopen(fileName, "w");
        
        fileEncrypt(inp, out);
        fclose(inp);
        fclose(out);

        printf("Success in encrypting file. Results stored in %s.\n", fileName);
        return 0;
    }

    else if(strcmp(argv[2], "-d") == 0){
        int key;
        printf("Enter the key that was designated to you from encryption.\nNOTE that an inaccurate key may result in jumbled and/or inaccurate text.\n");
        scanf("%d", &key);
        printf("\nYou have entered %d.\n", key);
        
        FILE * inp = fopen(argv[1], "r");
        if (inp == NULL){
            fprintf(stderr, "Error reading file %s during decryption.\n", argv[1]);
            return 1;
        }
        char * fName = argv[1];
        removeSub(fName, delim2);

        char * fileName = strcat(fName, "_decrypt.txt");
        FILE * out = fopen(fileName, "w");

        fileDecrypt(inp, out, key);
        fclose(inp);
        fclose(out);

        printf("Success in decrypting file %s with given key %d. Results stored in %s.\n", argv[1], key, fileName);
        return 0;
    }

    else{
        fprintf(stderr, "Error parsing given option. Please try again (-e or -d).\n");
        return 1;
    }

}