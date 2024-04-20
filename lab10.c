#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
};

// Inserts the word to the trie structure
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = (struct TrieNode *)malloc(sizeof(struct TrieNode));
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                current->children[index]->children[j] = NULL;
            }
            current->children[index]->count = 0; // Initialize count to 0
        }
        current = current->children[index];
    }
    current->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0;
        }
        current = current->children[index];
    }
    return current->count;
}

// Deallocates the trie structure
void deallocateTrie(struct TrieNode *root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            deallocateTrie(root->children[i]);
        }
    }
    free(root);
}

// Initializes a trie structure
struct TrieNode *createTrie() {
    struct TrieNode *root = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        root->children[i] = NULL;
    }
    root->count = 0;
    return root;
}

// Reads the dictionary file and stores words in the array
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return 0;
    }

    int numWords = 0;
    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[numWords] = strdup(word);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void) {
    char *inWords[256];
    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    struct TrieNode *root = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }

    // Test with some sample words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }

    // Deallocate the trie
    deallocateTrie(root);
    root = NULL; // Set to NULL after deallocation

    if (root != NULL)
        printf("There is an error in this program\n");

    return 0;
}
