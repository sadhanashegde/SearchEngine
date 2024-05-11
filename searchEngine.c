#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct trie
{
    struct trie *alpha[26];
    int wordflag;
};

typedef struct trie trie;

trie *root;

trie *createnode()
{
    trie *node = (trie*) malloc(sizeof(trie));
    if (node) {
        for (int i = 0; i < 26; i++)
            node->alpha[i] = NULL;
        node->wordflag = 0;
    }
    return node;
}
int search_insert_delete(trie **node, char *word, char mode)
{
    if (!(*node))
    {
        if (mode == 'i')
        {
            
            *node = createnode();
            root = *node;
        }
        else if (mode == 's' || mode == 'd')
        {
            printf("\nRoot node does not exist.");
            return 1;
        }
    }
    trie *current = *node;
    while (*word)
    {
        int index = (*word | ('A' ^ 'a')) - 'a';
        if (!current->alpha[index])
        {
            if (mode == 'i')
            {
                current->alpha[index] = createnode();
            }
            else if (mode == 's' || mode == 'd')
            {
                printf("\nNo node found for character '%c'.", *word);
                return 1; // Word not found
            }
        }
        current = current->alpha[index];
        word++;
    }
    if (mode == 's')
    {
        if (current && current->wordflag)
            return 0; // Word found
        else
            return 1; // Word not found
    }
    if (!current->wordflag)
    {
        if (mode == 'i')
        {
            current->wordflag = 1;
            return 0; // Insertion successful
        }
        else if (mode == 'd')
        {
            printf("\nWord not found for deletion.");
            return 1; // Word not found for deletion
        }
    }
    else if (mode == 'd')
    {
        current->wordflag = 0;
        return 0; // Deletion successful
    }
    else
        return 1; // Word already exists
}

int main()
{
    int ch;
	char data[][100] = {"tree", "queue", "stack", "dll", "graph","heap","array","trie","hash table","bst"};
	int num_words = sizeof(data) / sizeof(data[0]); // Calculate the number of words in the list

    for (int i = 0; i < num_words; i++) {
        search_insert_delete(&root, data[i], 'i'); // Insert each word into the trie
    }
    do
    {
        char word[100]; // Increased word size limit
        int result;
        printf("\n\n1. Enter the word to be inserted \n2. Search from data \n3. Delete from data \n4. Exit \n\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
           case 1:
		printf("Hello you want to insert to the data: ??");
		printf("\nEnter the word to be inserted: ");
		scanf("%s", word);
		result = search_insert_delete(&root, word, 'i');
		if (result == 0)
		{
        printf("\nInsertion successful!");
		}
		else if (result == 1)
		{
			printf("\nInsertion failed! The word already exists in the trie.");
		}
		break;

            case 2:
                printf("\nEnter the word to be searched: ");
                scanf("%s", word);
                result = search_insert_delete(&root, word, 's');
                if (result == 0)
                    printf("\nSearch successful!\nThe word is present in the trie.");
                else
                    printf("\nSearch unsuccessful!\nThe word is not present in the trie!");
                break;
            case 3:
                printf("\nEnter the word to be deleted: ");
                scanf("%s", word);
                result = search_insert_delete(&root, word, 'd');
                if (result == 0)
                    printf("\nDeletion successful!");
                else
                    printf("\nSearch unsuccessful!\nThe word is not present in the trie!");
                break;
            case 4:
                break;
            default:
                printf("\nInvalid choice. Please enter a valid option.");
                break;
        }
    }
    while (ch != 4);
    // Free allocated memory
    // Not necessary in this example since program exits immediately after, but good practice
    return 0;
}
