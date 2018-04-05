#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct node
{
   int key;
   struct node *left, *right;
};

struct node *newNode(int item)
{
   struct node *temp = (struct node *)malloc(sizeof(struct node));
   temp->key = item;
   temp->left = temp->right = NULL;
   return temp;
}

void inorder(struct node *root)
{
   if (root != NULL)
   {
       inorder(root->left);
       printf("%d \n", root->key);
       inorder(root->right);
   }
}

struct node* insert(struct node* node, int key)
{

   if (node == NULL) return newNode(key);//empty
if (key < node->key)
       node->left = insert(node->left, key);
   else if (key > node->key)
       node->right = insert(node->right, key);
   return node;
}
int generateRandom()
{
return rand() % 100 + 1;
}

int main()
{
int number[100],i;
srand ( time(NULL) );
   struct node *root = NULL;
   for(i=0;i<100;i++)
   {
   number[i] = generateRandom();
   }
   for(i=0;i<100;i++)
   {
   root = insert(root, number[i]);
   insert(root, number[i+1]);
   }
   inorder(root);
   return 0;
}
