#include<stdio.h>
#include<stdlib.h>
#include <time.h>

struct bt
{
    int k;
    struct bt *left, *right;
};

struct bt *newNode(int i)
{
    struct bt *n = (struct bt *)malloc(sizeof(struct bt));
    n->k = i;
    n->left = n->right = NULL;
    return n;
}

struct bt* insert(struct bt *n, int k)
{
    if (n == NULL)
        return newNode(k);

    if (k < n->k) {
        n->left = insert(n->left, k);
    } else if (k > n->k) {
        n->right = insert(n->right, k);
    }

    return n;
}

void arrToBST(int *tmp, struct bt *n, int *i)
{
    if (n == NULL)
        return;

    arrToBST(tmp, n->left, i);
    n->k = tmp[*i];
    (*i)++;
    arrToBST(tmp, n->right, i);
}

int nodeSize(struct bt *n)
{
    if (n == NULL)
        return 0;

    return nodeSize(n->left) + nodeSize(n->right) + 1;
}

void storeInOrder(struct bt *n, int tmp[], int *i)
{
    if (n == NULL)
        return;

    storeInOrder(n->left, tmp, i);
    tmp[*i] = n->k; (*i)++;
    storeInOrder(n->right, tmp, i);
}

void *binaryTreeToBST(struct bt *n)
{
    int s = nodeSize(n);

    int *tmp = malloc(s * sizeof(int));
    int i = 0;
    storeInOrder(n, tmp, &i);

    int c(const void *a, const void *b) {
        return (*(int*)a - *(int*)b);
    }
    qsort(tmp, s, sizeof(tmp[0]), c);

    i = 0;
    arrToBST(tmp, n, &i);

    free(tmp);
}

void printBST(struct bt *n)
{
    if (n == NULL)
        return;

    printBST(n->left);
    printf("%d\n", n->k);
    printBST(n->right);
}

void main(void)
{
    struct bt *n = NULL;

    // generate random node values binary tree
    srand (time(NULL));
    int randomInt() {
        return 1 + rand() / (RAND_MAX / (200 - 1 + 1) + 1);
    }

    n = insert(n, randomInt());

    int i;
    for (i = 1; i < randomInt(); ++i)
    {
        insert(n, randomInt());
    }

    // simulate duplicates
    int d = randomInt();
    for (i = 1; i < randomInt(); ++i)
    {
        insert(n, d);
    }

    binaryTreeToBST(n);
    printf("BST values: \n");
    printBST(n);
}
