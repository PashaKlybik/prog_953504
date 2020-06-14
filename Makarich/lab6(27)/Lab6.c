#include<stdio.h>
#include<string.h>

struct Nodes
{
    char* word;
    int count;
    struct Nodes* next;
};

struct Tree
{
	char* word;
	int count;
	struct Tree* left;
	struct Tree* right;
};

struct Nodes* ReadFromFile(struct Nodes* node);
struct Nodes* AddNode(struct Nodes* node, char* word);
struct Nodes* SortNodes(struct Nodes* node);
struct Tree* AddTreeNode(struct Tree* node, struct Nodes* nodes);
struct Tree* FullTree(struct Tree* node, struct Nodes* nodes);
void PrintWords(struct Tree* node);
void DeleteNodes(struct Nodes** nodes);
void DeleteTree(struct Tree** node);


int main()
{
    struct Tree* root = NULL;
    struct Nodes* nodes = NULL;

    nodes = ReadFromFile(nodes);
    root = FullTree(root, nodes);
    PrintWords(root);
    DeleteNodes(&nodes);
    DeleteTree(&root);

	system("pause");
	return 0;
}

struct Nodes* ReadFromFile(struct Nodes* node)
{
    FILE* file;
    file = fopen("text.TXT", "r");

    if (file == NULL)
    {
        printf("Couldn't open file");
        exit(1);
    }

    while (!feof(file)) 
    {
        char symbol;
        char word[30] = "";
        int i = 0;

        while (!feof(file))
        {
            symbol = tolower(getc(file));
            
            if (symbol < 97 || symbol > 122)
                break;

            word[i++] = symbol;
        }

        node = AddNode(node, word);
    }
    
    node = SortNodes(node);

    fclose(file);
    return node;
}

struct Nodes* AddNode(struct Nodes* node, char* word)
{
    if (!node)
    {
        node = (struct Nodes*)malloc(sizeof(struct Nodes));

        if (!node)
        {
            printf("Not enough memory");
            exit(1);
        }

        node->next = NULL;
        node->word = strdup(word);
        node->count = 1;
    }
    else if (!strcmp(node->word, word))
        node->count++;
    else
        node->next = AddNode(node->next, word);

    return node;
}

struct Nodes* SortNodes(struct Nodes* node)
{
    for (struct Nodes* i = node; i; i = i->next)
    {
        for (struct Nodes* j = node; j; j = j->next)
        {
            if (i->count > j->count)
            {
                struct Node* temp = i->count;
                i->count = j->count;
                j->count = temp;
            }
        }
    }

    return node;
}

struct Tree* AddTreeNode(struct Tree* treenode, struct Nodes* nodes)
{
    if (!treenode)
    {
        treenode = (struct Tree*)malloc(sizeof(struct Tree));

        if (!treenode)
        {
            printf("Not enough memory");
            exit(1);
        }

        treenode->left = NULL;
        treenode->right = NULL;

        treenode->word = strdup(nodes->word);
        treenode->count = nodes->count;
    }
    else if (nodes->count < treenode->count)
        treenode->left = AddTreeNode(treenode->left, nodes);
    else
        treenode->right = AddTreeNode(treenode->right, nodes);

    return treenode;
}

struct Tree* FullTree(struct Tree* node, struct Nodes* nodes)
{
    struct Nodes* temp = nodes;

    while (temp)
    {
        node = AddTreeNode(node, temp);
        temp = temp->next;
    }

    return node;
}

void PrintWords(struct Tree* node)
{
    if (!node)
        return;

    PrintWords(node->right);
    printf("%s - %d\n", node->word, node->count);
    PrintWords(node->left);
}

void DeleteNodes(struct Nodes** nodes)
{
    struct Nodes* temp;

    while (*nodes)
    {
        temp = *nodes;
        *nodes = (*nodes)->next;
        free(temp);
    }
}

void DeleteTree(struct Tree** node)
{
    if (*node == NULL)
        return;

        DeleteTree(&((*node)->left));
        DeleteTree(&((*node)->right));
        free(*node);
}