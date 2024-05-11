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
 * 
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

} 

int main(int argc, char *argv[]){

    srand(time(NULL)); // Random number key generator purposes

    // Error handling
    if (argc < 3){
        fprintf(stderr, "Too little arguments passed.\nUsage: %s <filename> [-e/-d options]\n");
        return 1;
    }
    if (argc > 3){
        fprintf(stderr, "Too many arguments passed.\n");
        return 1;
    }

    // Basic command-line parsing
    if (argv[2] = "-e"){
        FILE * inp = fopen(argv[1], "r");
        if (inp == NULL){
            fprintf(stderr, "Error reading file %s during encryption.\n", argv[1]);
            return 1;
        }
        FILE * out = fopen("crypt.txt", "w");
        
        fileEncrypt(inp, out);
        fclose(inp);
        fclose(out);

        printf("Success in encrypting file. Results stored in crypt.txt.\n");
        return 0;
    }

    else if(argv[2] = "-d"){
        int key;
        printf("Enter the key that was designated to you from encryption.\n NOTE that an inaccurate key may result in jumbled and/or inaccurate text.\n");
        scanf("%d", &key);
        printf("\nYou have entered %d.\n", key);
        
        FILE * inp = fopen(argv[1], "r");
        if (inp == NULL){
            fprintf(stderr, "Error reading file %s during decryption.\n", argv[1]);
            return 1;
        }
        FILE * out = fopen("decrypt.txt", "w");

        fileDecrypt(inp, out, key);
        fclose(inp);
        fclose(out);

        printf("Success in decrypting file %s with given key %d. Results stored in decrypt.txt.\n", argv[1], key);
        return 0;
    }

    else{
        fprintf(stderr, "Error parsing given option. Please try again (-e or -d).\n");
        return 1;
    }


    // FILE * readFile; // Opens file in read format
    // FILE * outputFile; // Create a file to store the output

    // int len;
    // char buff[BUFFER];

    // readFile = fopen(argv[1], "r");
    // if (readFile == NULL){
    //     fprintf(stderr, "Error opening and reading file %s.\n", argv[1]);
    //     return 1;
    // }

    // outputFile = fopen("crypt.txt", "w");

    // while (fgets(buff, (sizeof(char) * BUFFER), readFile) != NULL) // Take in all lines of string from the file.
    // {
    //     len = strlen(buff);
    //     for (int i = 0; i < len; i++){
    //         buff[i] -= 45; // Subtract 45 from the ASCII value of each letter in the chunk read.
    //     }
    //     fputs(buff, outputFile); // Enter the converted string into the output file.
    // }



}