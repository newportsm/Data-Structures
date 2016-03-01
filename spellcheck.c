#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file);

/*
 Load the contents of file into hashmap ht
 */
void loadDictionary(FILE* file, struct hashMap* ht);

char* getFileName();
void makeLower(char* word);

int main (int argc, const char * argv[]) {
    clock_t timer;
    int tableSize = 1000;
    struct hashMap* hashTable = createMap(tableSize);
    const int MAX_ADDED_WORDS = 1024;
    char** addedWords = malloc(sizeof(char*) * MAX_ADDED_WORDS);
    int addedWordsCount = 0;
    
    char* fileName = getFileName();
    
    timer = clock();
    FILE* dictionary = fopen(fileName, "r");
    
    if (dictionary == NULL)
    {
        printf("No file %s exists!", fileName);
        free(fileName);
        return 1;
    }
    
    loadDictionary(dictionary,hashTable);
    
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    
    char* word = (char*)malloc(256*sizeof(char));
    int quit=0;
    while(!quit){
        printf("Enter a word: ");
        scanf("%s",word);
        
        /*ensure we have lowercase input*/
        makeLower(word);
        
        if (atMap(hashTable, word) == NULL)
        {
            char* choice = (char*)malloc(256 * sizeof(char));
            
            printf("%s appears to be misspelled or not in dictionary.\n", word);
            printf("Would you like to add it to the dictionary? (y/n) [n]: ");
            
            scanf("%s", choice);
            makeLower(choice);
            
            if (strcmp("y", choice) == 0 || strcmp("yes", choice) == 0)
            {
                if (addedWordsCount >= MAX_ADDED_WORDS)
                {
                    printf("No more words can be added to memory.\n"
                           "You may quit the program and elect to write all words in memory to the dictionary file.");
                    free(choice);
                    continue;
                }
                
                insertMap(hashTable, word, 0);
                addedWords[addedWordsCount] = malloc(sizeof(char) * (strlen(word) + 1));
                strcpy(addedWords[addedWordsCount], word);
                addedWordsCount++;
            }
            
            free(choice);
        }
        else
            printf("%s is in the dictionary.\n", word);
        
        /* Don't remove this. It is used for grading*/
        if(strcmp(word,"quit")==0)
            quit=!quit;
    }
    
    if (addedWordsCount > 0)
    {
        char* choice = (char*)malloc(256 * sizeof(char));
        
        printf("Would you like to write out the added words to the dictionary file? (y/n) [n]: ");
        scanf("%s", choice);
        makeLower(choice);
        
        if (strcmp("y", choice) == 0 || strcmp("yes", choice) == 0)
        {
            fclose(dictionary);
            dictionary = NULL;
            dictionary = fopen(fileName, "a+");
            if (dictionary == NULL)
            {
                printf("Could not open %s for writing!", fileName);
            }
            else
            {
                int i;
                for (i = 0; i < addedWordsCount; i++)
                {
#ifdef _WIN32
                    fprintf(dictionary, "\r\n");
                    fprintf(dictionary, addedWords[i]);
                    
#else
                    fprintf(dictionary, "\n");
                    fprintf(dictionary, addedWords[i]);
                    
#endif
                }
            }
        }
        
        int i;
        for (i = 0; i < addedWordsCount; i++)
            free(addedWords[i]);
        free(choice);
    }
    
    
    free(word);
    free(addedWords);
    free(fileName);
    deleteMap(hashTable);
    fclose(dictionary);
    dictionary = NULL;
    return 0;
}

void loadDictionary(FILE* file, struct hashMap* ht)
{
    while (1)
    {
        char* word = getWord(file);
        if (word == NULL)
            break;
        else
        {
            insertMap(ht, word, 0);
            free(word);
            continue;
        }
    }
}

void makeLower(char* word)
{
    size_t i;
    for (i = 0; i < strlen(word); i++)
        word[i] = tolower(word[i]);
}

char* getFileName()
{
    char* fileName = (char*)malloc(sizeof(char) * 1024);
#ifdef _WIN32
    printf("Please enter a path to a dictionary file [.\\dictionary.txt]: ");
#else
    printf("Please enter a path to a dictionary file [./dictionary.txt]: ");
#endif
    
    fgets(fileName, 1024, stdin);
    
    /* strip newline*/
    char* newline = strchr(fileName, '\n');
    if (newline != NULL)
        *newline = '\0';
    
    if (strcmp(fileName, "\0") == 0)
        strcpy(fileName, "dictionary.txt");
    
    return fileName;
}

void printValue(ValueType v) {
    printf("Value:%d", v);
}


char* getWord(FILE *file)
{
    int length = 0;
    int maxLength = 16;
    char character;
    
    char* word = (char*)malloc(sizeof(char) * maxLength);
    assert(word != NULL);
    
    while( (character = fgetc(file)) != EOF)
    {
        if((length+1) > maxLength)
        {
            maxLength *= 2;
            word = (char*)realloc(word, maxLength);
        }
        if((character >= '0' && character <= '9') || /*is a number*/
           (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
           (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
           (character == 39)) /*or is an apostrophy*/
        {
            word[length] = character;
            length++;
        }
        else if(length > 0)
            break;
    }
    
    if(length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}