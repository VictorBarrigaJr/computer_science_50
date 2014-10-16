/***
 * CS50 Study, data structures, trees
 * binary_tree_insertion.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 * function that inserts a node containing val into the tree pointed to by 
 * global root variable. Return true if successful, and return false if you 
 * failed for some reason (e.g., lack of sufficient heap memory, value already
 * in tee, etc.).
 *
 * jharvard@run.cs50.net (~): ../a.out
 * Inserting 0 ...success!
 * Inserting 1 ...success!
 * Inserting 2 ...success!
 * Inserting 3 ...fail!
 * Inserting 4 ...success!
 * Inserting 5 ...success!
 * Inserting 6 ...fail!
 * Inserting 7 ...fail!
 * Inserting 8 ...success!
 * Inserting 9 ...fail!
 * Tree contains 0? true
 * Tree contains 1? true
 * Tree contains 2? true
 * Tree contains 3? true
 * Tree contains 4? true
 * Tree contains 5? true
 * Tree contains 6? true
 * Tree contains 7? true
 * Tree contains 8? true
 * Tree contains 9? true
 **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int n;
    struct node *left;
    struct node *right;
}node;

node *root;

bool insert(int val);
bool search(node *root, int val);

int main(void)
{
    // create root node
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        printf("Out of memory!\n");
        return 1;
    }
    root->n = 7;
    root->left = NULL;
    root->right = NULL;
    
    // create more nodes
    node *three = malloc(sizeof(node));
    if (three == NULL)
    {
        printf("Out of memory!\n");
        return 1;
    }
    three->n = 3; 
    three->left = NULL;
    three->right = NULL;
    
    node *six = malloc(sizeof(node));
    if (six == NULL)
    {
        printf("Out of memory!\n");
        return 1;
    }
    six->n = 6;
    six->left = NULL;
    six->right = NULL;
    
    node *nine = malloc(sizeof(node));
    if (nine == NULL)
    {
        printf("Out of memory!\n");
        return 1;
    }
    nine->n = 9;
    nine->left = NULL;
    nine->right = NULL;

    // link together nodes
    root->left = three;
    root->right = nine;
    three->right = six;

    // testing insert
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("Inserting %i ...%s!\n", i, insert(i)? "success" : "fail");
    }
    for(i = 0; i < 10; i++)
    {
        printf("Tree contains %i? %s\n", i, search(root, i)? "true" : "false");
    }

    return 0;
}

bool insert(int val)
{
    // search for insertion point
    node *cur = root;
    node *prev = NULL;
    while(cur != NULL)
    {
        prev = cur;
        if(cur->n < val)
        {
            cur = cur->right;
        }
        else if(cur->n > val)
        {
            cur = cur->left;
        }
        else
        {
            return false;
        }
    }
    
    // build new node
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        return false;
    }
    new->n = val;
    new->left = NULL;
    new->right = NULL;
    
    // insert node
    if (prev->n > val)
    {
        prev->left = new;
    }
    else
    {
        prev->right = new;
    }

    return true;
}

bool search(node *root, int val)
{
    // if root is NULL
    if (root == NULL)
    {
        // return false
        return false;
    }
    // if root-> is val
    if (root->n == val)
    {
        // return true
        return true;
    }
    // if val is less than root->n
    else if (val < root->n)
    {
        // search left child
        return search(root->left, val);
    }
    // if val is greater than root->n
    else
    {
        // search right child
        return search(root->right, val);
    }
}
