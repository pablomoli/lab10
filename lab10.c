#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
	struct Trie *children[26];
	int count;
};
void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *createTrie();
int readDictionary(char *filename, char **pInWords);

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	struct Trie *t = pTrie;

	if (t == NULL)
	{
		t = createTrie();
		pTrie = t;
	}
	int len = strlen(word);
	for (int i = 0; i < len; i++)
	{
		int index = word[i] - 'a';
		if(t->children[index] == NULL){
			t->children[index] = createTrie();
		}
		t = t->children[index];
	}
	t->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	struct Trie *t = pTrie;
	int len = strlen(word);

	for (int i = 0; i < len; i++)
	{
		int index = word[i] - 'a';
		if(t->children[index] == NULL){
			return 0;
		}
		t = t->children[index];
	}

	return t->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	if(pTrie == NULL){
		return NULL;
	}
	for (int i = 0; i < 26; i++)
	{
		pTrie->children[i] = deallocateTrie(pTrie->children[i]);
	}
	free(pTrie);
	return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
	struct Trie *t = (struct Trie *)malloc(sizeof(struct Trie));
	t->count = 0;
	for (int i = 0; i < 26; i++)
	{
		t->children[i] = NULL;
	}
	return t;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE *in = fopen(filename, "r");
	if(in ==NULL){
		return 0;
	}

	int count;
	char word[256];

	fscanf(in, "%d", &count);

	for (int i = 0; i < count; i++)
	{
		fscanf(in, "%s", word);
		pInWords[i] = strdup(word);
	}

	return count;
}

int main(void)
{
	char *inWords[256];

	// read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	// for (int i = 0; i < numWords; ++i)
	// {
	// 	printf("%s\n", inWords[i]);
	// }

	struct Trie *pTrie = createTrie();
	for (int i = 0; i < numWords; i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i = 0; i < 5; i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}