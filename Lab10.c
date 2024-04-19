#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int data;
    struct Trie *next[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* dictionary = malloc(sizeof(struct Trie));
    dictionary->data = 0;
    int i;
    for (i=0; i<26; i++){
        dictionary->next[i] = NULL;
    }
    return dictionary;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int nexti;
    for(int i = 0; i < strlen(word); i++){
        nexti = word[i] - 'a';
        if(pTrie->next[nexti] == NULL){
            pTrie->next[nexti] = createTrie();
        }
        pTrie = pTrie->next[nexti];  
    }
    pTrie->data++;
    return;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int nexti;
    for(int i = 0; i < strlen(word); i++){
        nexti = word[i] - 'a';
        if (pTrie->next[nexti] == NULL) {
            return 0;
        }
        pTrie = pTrie->next[nexti];
    }
    return pTrie->data;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i=0; i<26; i++){
        if(pTrie->next[i] != NULL){
            deallocateTrie(pTrie->next[i]);
        }
    }
    free(pTrie);
    return NULL;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *input = fopen(filename, "r");
    int total;
    fscanf(input, "%d", &total);
    for(int i = 0; i < total; i++){
        pInWords[i] = malloc(256 * sizeof(char)); 
        fscanf(input, "%s", pInWords[i]);
    }
    fclose(input);
    return total;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}