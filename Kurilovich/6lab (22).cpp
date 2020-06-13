#include <iostream>

struct tree
{
    int inf;
    tree* l = nullptr;
    tree* r = nullptr;
};

struct List
{
    int num;
    List* next = nullptr;
    List* prev = nullptr;
};

void Add(List** top, int n)
{
    List* newList = new List();
    newList->num = n;
    newList->prev = nullptr;
    newList->next = nullptr;
    List* run = *top;

    if (run == nullptr)
    {
        *top = newList;
    }
    else
    {
        newList->next = *top;
        run->prev = newList;
        *top = newList;
    }
}

void In_Order(tree* tre, List** r, List** l) {
    if (tre == nullptr) { return; }
    if (tre->inf % 2 == 0) {
        Add(&*r, tre->inf);
    }
    else {
        Add(&*l, tre->inf);
    }
    In_Order(tre->l, r, l);
    In_Order(tre->r, r, l);
}

void Add(tree** tre, int value) {

    tree* branch = new tree();
    branch->inf = value;
    branch->l = nullptr;
    branch->r = nullptr;
    tree* root = &**tre;

    if (*tre == nullptr) {
        *tre = branch;
    }
    else {
        while (true) {
            if (root->inf < value) {
                if (root->r == nullptr) {
                    root->r = branch;
                    return;
                }
                root = root->r;
            }
            else {
                if (root->l == nullptr) {
                    root->l = branch;
                    return;
                }
                root = root->l;
            }
        }
    }

}

void Print(List* top) {
    while (top != nullptr) {
        printf("   %d", top->num);
        top = top->next;
    }
}

void DeleteTree(tree* node)
{
    if (node)
    {
        DeleteTree(node->l);
        DeleteTree(node->r);
        free(node);
    }
}

List* DeleteHead(List* root)
{
    struct List* temp;
    temp = root->next;
    temp->prev = NULL;
    free(root);
    return(temp);
}

int main()
{
    tree* tre = nullptr;
    List* r = nullptr;
    List* l = nullptr;

    Add(&tre, 5);
    Add(&tre, 1);
    Add(&tre, 2);
    Add(&tre, 3);
    Add(&tre, 4);
    Add(&tre, 6);
    Add(&tre, 7);
    Add(&tre, 8);
    Add(&tre, 9);
    Add(&tre, 10);

    In_Order(tre, &r, &l);

    Print(r);
    printf("\n");
    Print(l);
    free(r);
    free(l);
    DeleteTree(tre);
    
    system("pause");
    return 0;
}
