#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
  int key;
  struct node *left, *right;
} node;


void freeTree( node *node)
{
  if (node == NULL)
    return;
  freeTree(node->left);
  freeTree(node->right);
  free(node);

}

int maxLevel(node *root)
{
    if (root == NULL)
        return -1;
    int leftDepth = maxLevel(root->left);
    int rightDepth = maxLevel(root->right);
    
    if(leftDepth > rightDepth)
        return leftDepth + 1;
    else
     return rightDepth +1;
}



node *newNode(int item)
{
  node *temp = (node*) malloc(sizeof(node));
  temp->key = item;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

node *insertNode(node *root, int key)
{
  if (root == NULL)
    return newNode(key);
  else if (key > root->key)
    root->right = insertNode(root->right, key);
  else if (key <= root->key)
    root->left = insertNode(root->left, key);

return root;
}

int generateRandom()
{
  return rand() % 1000 + 1;
}

int minLevel(node *root)
{
int leftDepth, rightDepth;
leftDepth = 0;
rightDepth = 0;
  if (root->left == NULL && root->right == NULL)
      return 1;
  if (root->left != NULL)
      leftDepth = minLevel(root->left);
  if (root->right != NULL)
      rightDepth = minLevel(root->right);
  if (rightDepth < leftDepth)
      return rightDepth + 1;
  else
    return leftDepth + 1;
}

int main()
{   
    printf("CS 2123 Assignment 4 written by Grecia Gonzalez.\n");
    srand(time(NULL));
    int nextNum, i, j, leveldiff;
        int list[100] = {0};
    
for (j=0; j<50; j++){
    nextNum = generateRandom();
    node *root = newNode(nextNum);

  for (i = 0; i < 100; i++)
  {
     nextNum = generateRandom();
     insertNode(root, nextNum);
   }
    leveldiff = maxLevel(root) - minLevel(root);
    list[leveldiff]++;
    freeTree(root);
}
printf("Level Difference\t#Runs\n");
for (i = 0; i<50; i++)
printf("%d\t\t\t%d\n", i, list[i]);

}

