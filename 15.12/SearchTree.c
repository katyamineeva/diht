#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define BST struct Node

typedef struct Node Node;
int arrLen;

struct Node
{
    int key;
    int value;
    Node* parent;
    Node* leftChild;
    Node* rightChild;
};

int search(BST* tree, int key)
{
    if (tree == NULL || tree->key == key)
    {
        return INT_MAX;
    }

    if (tree->key >= key)
    {
        search(tree->leftChild, key);
    }
    if (tree->key < key)
    {
        search(tree->rightChild, key);
    }
}

Node* createNode(Node* father, Node* left, Node* right, int k, int val)
{
    Node* tmp = (Node*) malloc(sizeof(Node));

    tmp->parent = father;
    tmp->leftChild = left;
    tmp->rightChild = right;
    tmp->key = k;
    tmp->value = val;

    return tmp;
}


void add(Node* root, int key, int value)
{
    if (root->key <= key)
    {
        if (root->rightChild != NULL)
        {
            add(root->rightChild, key, value);
        }
        else
        {
            Node* tmp = createNode(root, NULL, NULL, key, value);
            root->rightChild = tmp;
        }
    }
    if (root->key > key)
    {
        if (root->leftChild != 0)
        {
            add(root->leftChild, key, value);
        }
        else
        {
            Node* tmp = createNode(root, NULL, NULL, key, value);
            root->leftChild = tmp;
        }
    }
}


BST* makeBSearchTree(BST* tree, int* values, int* keys, int left, int right)
{
    if (right - left == 0)
    {
        add(tree, keys[left], values[left]);
    }
    if (right - left > 0)
    {
        int mid = (left + right) / 2;
        add(tree, keys[mid], values[mid]);

        makeBSearchTree(tree, values, keys, left, mid - 1);
        makeBSearchTree(tree, values, keys, mid + 1, right);
    }
}

void deleteTree(BST* tree)
{
    if (tree->leftChild != NULL)
    {
        deleteTree(tree->leftChild);
    }
    if (tree->rightChild != NULL)
    {
        deleteTree(tree->rightChild);
    }
    free(tree);
}

int Partition(int* a, int left, int right, int pivot, int* a2)
{
    Swap(&a[right], &a[pivot]);
    Swap(&a2[right], &a2[pivot]);
    int PivotInd = right;
    --right;
    int PivotValue = a[PivotInd];

    while (left < right)
    {

        while (a[left] <= PivotValue && left < right)
        {
            ++left;
        }
        while (a[right] >= PivotValue && left < right)
        {
            --right;
        }
        Swap(&a[left], &a[right]);
        Swap(&a2[left], &a2[right]);


        if (left + 1 == right)
        {
            break;
        }
        if (right - left > 1)
        {
            ++left;
            --right;
        }
    }

    if (a[right] >= PivotValue)
    {
        Swap(&a[right], &a[PivotInd]);
        Swap(&a2[right], &a2[PivotInd]);
        PivotInd = right;
    }
    else
    {
        Swap(&a[right + 1], &a[PivotInd]);
        Swap(&a2[right + 1], &a2[PivotInd]);
        PivotInd = right + 1;
    }
    return PivotInd;
}

void QuickSort(int* a, int left, int right, int* a2)
{
    if (right - left > 0)
    {
        int pivot = Partition(a, left, right, right, a2);
        QuickSort(a, left, pivot - 1, a2);
        QuickSort(a, pivot + 1, right, a2);
    }
}

void Swap(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int** ReadData()
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &arrLen);


    int** array = (int**) malloc(2 * sizeof(int*));
    array[0] = (int*) malloc(arrLen * sizeof(int));
    array[1] = (int*) malloc(arrLen * sizeof(int));
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fscanf(input, "%d", &array[0][i]);
    }
    for (i = 0; i < arrLen; ++i)
    {
        fscanf(input, "%d", &array[1][i]);
    }
    fclose(input);
    return array;
}


int main()
{
    int** array = ReadData();
    int* values = array[0];
    int* keys = array[1];

    QuickSort(keys, 0, arrLen - 1, values);
    BST* tree = (BST*) malloc(sizeof(BST));
    makeBSearchTree(tree, values, keys, 0, arrLen - 1);

    deleteTree(tree);
    free(array);
    free(keys);
    return 0;
}
