#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int generateRandom();
int max(int x, int y) { return (x > y)? x : y; }
int min(int x, int y) {return (x < y)? x : y ;}
struct node
{
    int key;
    struct node *left, *right;
};

// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (key <= node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}
int generateRandom() { return rand() % 1000 + 1; }
//A Utility function to return the maximum depth of a leaf in a tree.
int depthLeafUtil(struct node *root,int level)
{
    // Base Case
    if (root == NULL)
        return 0;

    // If this node is a leaf, return its level
    if (root->left==NULL && root->right==NULL)
        return level;

    // If not leaf, return the maximum value from left and right subtrees
    return max(depthLeafUtil(root->left, level+1),
               depthLeafUtil(root->right, level+1));
}
//A utility funtion to calculate minimum Depth leaf in a tree.
int minDepthLeafUtil(struct node *root,int level)
{
    // Base Case
    if (root == NULL)
        return 0;

    // If this node is a leaf, return its level
    if (root->left==NULL && root->right==NULL)
        return level;

    // If not leaf, return the minimum value from left and right subtrees
    return min(minDepthLeafUtil(root->left, level+1),
               minDepthLeafUtil(root->right, level+1));
}


// Driver Program to test above functions
int main()
{
  
    struct node *root = NULL;
    int arr[101]={0};
  
    int i=0,x,max_depth,min_depth,diff,j=0,k=0 ;
    for(j=0;j<50;j++)
      {
   srand(time(NULL));
   for(i=0;i<100;i++)
      {
  
        x=generateRandom();
        if(i==0)
          root=insert(root,x);
        else
          insert(root,x);
      }
   //inorder(root);
   max_depth=depthLeafUtil(root,0);
   min_depth=minDepthLeafUtil(root,0);
   diff=max_depth-min_depth;
   arr[diff]=arr[diff]+1;

      }
    for( k=0;k<101;k++)
      {
   printf("%d level differences %d runs\n",k,arr[k]);
      }
    return 0;
}
