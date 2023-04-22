//Rohan Suresh

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie {
    int flag;
    struct Trie *children[26];
}Trie;

void insert(struct Trie **ppTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
int numberOfOccurences(struct Trie *pTrie, char *word);


void insert(struct Trie **ppTrie, char *word) {
    if(*ppTrie == NULL) {
        return;
    }
    Trie *temp = *ppTrie;
    int length = strlen(word);
    for(int i = 0; i < length; i++) {
        int index = word[i] - 'a';
        if(temp->children[index] == NULL) {
            temp->children[index] = calloc(1, sizeof(Trie));
        }
        temp = temp->children[index];
    }
    temp->flag++;
}

int numberOfOccurences(struct Trie *pTrie, char *word) {
    if (pTrie == NULL) {
        return 0;
    }
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[index];
    }
    return pTrie->flag;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        if (pTrie->children[i] != NULL) {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}



int main(void) {
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    Trie *trie = calloc(1, sizeof(Trie));
    for(int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurences(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}

