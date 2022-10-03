/*
Ibrahim Pulatov
Professor Haque
CSCI-340
AVL Tree
*/


//C++ program to Implement AVL Tree
//Balance Factor = Height of left subtree-Height of right subtree
//Height of null tree = 0
//Height of leaf nodes =1

#include<bits/stdc++.h> 
#include<iostream>
#include<cstdio>

using namespace std;
 
/*
 * Node Declaration
 */
struct avl_node
{
    int data;
    struct avl_node *left;
    struct avl_node *right;
}*root;
 
/*
 * Class Declaration
 */
class avlTree
{
    public:
        int height(avl_node *);
        int diff(avl_node *);
        avl_node *rr_imbalance(avl_node *);
        avl_node *ll_imbalance(avl_node *);
        avl_node *lr_imbalance(avl_node *);
        avl_node *rl_imbalance(avl_node *);
        avl_node* balance(avl_node *);
        avl_node* insert(avl_node *, int );
        avl_node* remove(avl_node *, int ); //extra credi
        void display(avl_node *, int);
        void inorder(avl_node *);
        void preorder(avl_node *);
        void postorder(avl_node *);
        avlTree()
        {
            root=NULL;     
        }
};
 
/*
 * Main Contains Menu
 */
int main()
{
    int choice, item, n, i;
    avlTree avl;
     ifstream file; 
    // opening file "input.txt" 
    // in (read) mode 
    // ios::in Open for input operations. 
    file.open("input.txt",ios::in); 
    // If no file is created, then 
    // show the error message. 
    if(!file) 
    { 
        cout<<"Error in creating file!!!"; 
        return 0; 
    } 
    cout<<"File opened successfully."; 
    file>>n;

    for(i = 0; i < n; i++)
    {
        file>>item;
        root = avl.insert(root, item);
    }
    
     while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display Balanced AVL Tree"<<endl;
        cout<<"3.InOrder traversal"<<endl;
        cout<<"4.PreOrder traversal"<<endl;
        cout<<"5.PostOrder traversal"<<endl;
        cout<<"6.Remove Element from the tree"<<endl;
        cout<<"7. Exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            int userNum;
            cout << "Enter the number you want to insert "<<endl;
            cin >> userNum;
            root = avl.insert(root, userNum);    
                break;
            case 2:
                if (root == NULL)
                {
                    cout<<"Tree is Empty"<<endl;
                    continue;
                }
                cout<<"Balanced AVL Tree:"<<endl;
                avl.display(root, 1);
                break;
            case 3:
              avl.inorder(root);
                break;
            case 4:
              avl.preorder(root);
              break;
            case 5:
            avl.postorder(root);   
                break;
            case 6:
              int Num;
              cin>>Num;
              cout << "Enter the number you want to remove "<<endl;
              root = avl.remove(root, Num);
                break;
            case 7:
                file.close();
                exit(1);    
                break;
            default:
                cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}
 
//recursive function to find the height of AVL tree
// leaf node height is 1, null left/right child height is 0 
int avlTree::height(avl_node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
 
//Calculate and return the balance factor
int avlTree::diff(avl_node *temp)
{
    if(temp == NULL){
      return 0;
    }
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
 
// Case: Right subtree of right child
avl_node *avlTree::rr_imbalance(avl_node *parent)
{
  avl_node *temp;
  temp = parent -> right;

  parent -> right = temp -> left;
  temp -> left = parent;
  return temp; 
}

// Case: Left subtree of left child 
avl_node *avlTree::ll_imbalance(avl_node *parent)
{
  avl_node *temp;
  temp = parent -> left;

  parent -> left = temp -> right;
  temp -> right = parent;
 
  return temp;
}
 
//Right subtree of Left child
avl_node *avlTree::lr_imbalance(avl_node *parent)
{
  avl_node *temp;
  temp = parent ->left;

  parent->left = rr_imbalance(parent->left);
  parent = ll_imbalance(parent);

  return parent;
}
 
//Left subtree of Right child
avl_node *avlTree::rl_imbalance(avl_node *parent)
{
  avl_node *temp;
  temp = parent ->right;

  parent->right = ll_imbalance(parent->right);
  parent = rr_imbalance(parent);
  
  return parent;
}
 
/*
Balancing AVL Tree
*/
avl_node *avlTree::balance(avl_node *temp)
{
 int temp_bf = diff(temp);
 
    //if (bf of temp>1) and (bf of temp->left>0) => Case LL imbalance
    if(temp_bf > 1){
      if(diff(temp->left) > 0)
        temp= ll_imbalance(temp);
    }
    //if (bf of temp>1) and (bf of temp->left<=0) => Case LR imbalance
    if(temp_bf > 1) {
      if(diff(temp->left) <= 0)
        temp= lr_imbalance(temp);
    }
    //if (bf of temp<-1) and (bf of temp->right>0) => Case RL imbalance
    if(temp_bf < -1){
      if(diff(temp->right) > 0)
        temp= rl_imbalance(temp);
    }
    //if (bf of temp<-1) and (bf of temp->right<=0) => Case RR imbalance
    if(temp_bf < -1) {
      if(diff(temp->right) <= 0)
        temp= rr_imbalance(temp);
    }
    return temp;
}
 
/*
 * Insert Element into the tree
 */
avl_node *avlTree::insert(avl_node *root, int value)
{
    if (root == NULL)
    {
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->data)
    {
        root->left = insert(root->left, value);
        root = balance (root);
    }
    else if (value >= root->data)
    {
        root->right = insert(root->right, value);
        root = balance (root);
    }
    return root;
}

/* 
Remove element from the tree
*/
avl_node *avlTree::remove(avl_node *root, int value){
  avl_node *temp;

  if(root == NULL)
    return root;
  
  else if(value < root->data){
    root ->left = remove(root->left, value);
    root = balance (root);
  }
  else if(value >= root->data){
    root ->right = remove(root -> right, value);
    root = balance(root);
  }

return root;
}

/*
 * Display AVL Tree
 */

void avlTree::display(avl_node *ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->data;
        display(ptr->left, level + 1);
    }
}

/*
 * Inorder Traversal of AVL Tree
 */
void avlTree::inorder(avl_node *tree)
{
    if (tree == NULL)
        return;
    inorder (tree->left);
    cout<<tree->data<<"  ";
    inorder (tree->right);
}
/*
 * Preorder Traversal of AVL Tree
 */
void avlTree::preorder(avl_node *tree)
{
    if (tree == NULL)
        return;
    cout<<tree->data<<"  ";
    preorder (tree->left);
    preorder (tree->right);
 
}
 
/*
 * Postorder Traversal of AVL Tree
 */
void avlTree::postorder(avl_node *tree)
{
    if (tree == NULL)
        return;
    postorder ( tree ->left );
    postorder ( tree ->right );
    cout<<tree->data<<"  ";
}