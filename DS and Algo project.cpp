



// KD trees.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>// A C++ program to demonstrate delete in K D tree
using namespace std;
const int k = 2;
struct Node
{
	int point[k]; // To store k dimensional point
	Node *left, *right;
};

// A method to create a node of K D tree
struct Node* newNode(int arr[])
{
	struct Node* temp = new Node;

	for (int i=0; i<k; i++)
	temp->point[i] = arr[i];

	temp->left = temp->right = NULL;
	return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node *insertRec(Node *root, int point[], unsigned depth)
{
	// Tree is empty?
	if (root == NULL)
	return newNode(point);

	// Calculate current dimension (cd) of comparison
	unsigned cd = depth % k;

	// Compare the new point with root on current dimension 'cd'
	// and decide the left or right subtree
	if (point[cd] < (root->point[cd]))
		root->left = insertRec(root->left, point, depth + 1);
	else
		root->right = insertRec(root->right, point, depth + 1);

	return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node* insert(Node *root, int point[])
{
	return insertRec(root, point, 0);
}

// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(int point1[], int point2[])
{
    // Compare individual pointinate values
    for (int i = 0; i < k; ++i)
        if (point1[i] != point2[i])
            return false;
  
    return true;
}

// Searches a Point represented by "point[]" in the K D tree.
// The parameter depth is used to determine current axis.
bool searchRec(Node* root, int point[], unsigned depth)
{
	// Base cases
	if (root == NULL)
		return false;
	if (arePointsSame(root->point, point))
		return true;

	// Current dimension is computed using current depth and total
	// dimensions (k)
	unsigned cd = depth % k;

	// Compare point with root with respect to cd (Current dimension)
	if (point[cd] < root->point[cd])
		return searchRec(root->left, point, depth + 1);

	return searchRec(root->right, point, depth + 1);
}

// Searches a Point in the K D tree. It mainly uses
// searchRec()
bool search(Node* root, int point[])
{
	// Pass current depth as 0
	return searchRec(root, point, 0);
}
// A utility function to find minimum of three integers
Node *minNode(Node *x, Node *y, Node *z, int d)
{
    Node *res = x;
    if (y != NULL && y->point[d] < res->point[d])
       res = y;
    if (z != NULL && z->point[d] < res->point[d])
       res = z;
    return res;
}
  
// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
Node *find_MinRec(Node* root, int d, unsigned depth)
{
    // Base cases
    if (root == NULL)
        return NULL;
  
    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;
  
    // Compare point with root with respect to cd (Current dimension)
    if (cd == d)
    {
        if (root->left == NULL)
            return root;
        return find_MinRec(root->left, d, depth+1);
    }
  
    // If current dimension is different then minimum can be anywhere
    // in this subtree
    return minNode(root,
               find_MinRec(root->left, d, depth+1),
               find_MinRec(root->right, d, depth+1), d);
}
  
// A wrapper over findMinRec(). Returns minimum of d'th dimension
Node *find_Min(Node* root, int d)
{
    // Pass current level or depth as 0
    return find_MinRec(root, d, 0);
}
  
// A utility method to determine if two Points are same
// in K Dimensional space

  
// Copies point p2 to p1
void copyPoint(int p1[], int p2[])
{
   for (int i=0; i<k; i++)
       p1[i] = p2[i];
}
  
// Function to delete a given point 'point[]' from tree with root
// as 'root'.  depth is current depth and passed as 0 initially.
// Returns root of the modified tree.
Node *deleteNodeRec(Node *root, int point[], int depth)
{
    // Given point is not present
    if (root == NULL)
        return NULL;
  
    // Find dimension of current node
    int cd = depth % k;
  
    // If the point to be deleted is present at root
    if (arePointsSame(root->point, point))
    {
        // 2.b) If right child is not NULL
        if (root->right != NULL)
        {
            // Find minimum of root's dimension in right subtree
            Node *min = find_Min(root->right, cd);
  
            // Copy the minimum to root
            copyPoint(root->point, min->point);
  
            // Recursively delete the minimum
            root->right = deleteNodeRec(root->right, min->point, depth+1);
        }
        else if (root->left != NULL) // same as above
        {
            Node *min = find_Min(root->left, cd);
            copyPoint(root->point, min->point);
            root->right = deleteNodeRec(root->left, min->point, depth+1);
        }
        else // If node to be deleted is leaf node
        {
            delete root;
            return NULL;
        }
        return root;
    }
  
    // 2) If current node doesn't contain point, search downward
    if (point[cd] < root->point[cd])
        root->left = deleteNodeRec(root->left, point, depth+1);
    else
        root->right = deleteNodeRec(root->right, point, depth+1);
    return root;
}
  
// Function to delete a given point from K D Tree with 'root'
 Node* deleteNode(Node *root, int point[])
{
   // Pass depth as 0
   return deleteNodeRec(root, point, 0);
}
 int min(int x, int y, int z)
{
    return min(x, min(y, z));
}
  
  int findMinRec(Node* root, int d, unsigned depth)
{
    // Base cases
    if (root == NULL)
        return INT_MAX;
  
    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;
  
    // Compare point with root with respect to cd (Current dimension)
    if (cd == d) {
        if (root->left == NULL)
            return root->point[d];
        return min(root->point[d], findMinRec(root->left, d, depth + 1));
    }
  
    // If current dimension is different than minimum can be anywhere
    // in this subtree
    return min(root->point[d],
               findMinRec(root->left, d, depth + 1),
               findMinRec(root->right, d, depth + 1));
}
  
// A wrapper over findMinRec(). Returns minimum of d'th dimension
int findMin(Node* root, int d)
{
    // Pass current level or depth as 0
    return findMinRec(root, d, 0);
}
int _tmain(int argc, _TCHAR* argv[])

{
	cout<<endl;
	cout<<"Submitted By: "<<endl;
    cout<<"              MAHNOOR MUNIR(2020-BSE-016)"<<endl;
	cout<<"               AFRA SAADAT(2020-BSE-002) "<<endl;
	cout<<endl;
	cout<<"Submitted To:"<<endl;
	cout<<"               MAM SIDRA"<<endl;
	cout<<endl;
	cout<<"Project Title: "<<endl;
	cout<<"               KD TREES(K-Dimensional)"<<endl;
	cout<<endl;

	int ch,y=0,n;
	struct Node* root = NULL;
    int points[][k]= { { 30, 40 }, { 5, 25 },
       { 70, 70 }, { 10, 12 }, { 50, 30 }, { 35, 45 } };

     n = sizeof(points) / sizeof(points[0]);
    for (int i = 0; i < n; i++)
        root = insert(root, points[i]);
	cout<<endl;
   
    do
    {
                cout<<"\n\t What do you want to see? " ;
                cout<<"\n 1. Insertion in the tree ";
                cout<<"\n 2. Deletion of node from the tree";
				cout<<"\n 3. Minimum value among X and Y dimension";
				cout<<"\n 4. Searching of a node from the tree";
                cout<<"\n 5. Exit " ;
                cout<<"\nEnter Your Choice: "; 
				cin>>ch;
                switch(ch)
                {
case 1 : 
		
  cout<<"Points in tree are (30,40), (5,25), (70,70), (10,12), (50,30), (35,45)"<<endl;
    
	cout<<endl;
	
  break;

   case 2:
            
               cout<<"DELETION: "<<endl;
	cout<<endl;
// Delete (30, 40);

    root = deleteNode(root, points[0]);
  
    cout << "Root after deletion of (30, 40)\n";
    cout << root->point[0] << ", " << root->point[1] << endl;
  cout<<endl;
               break;
				
   case 3 :
					cout<<"MINIMUM VALUE AMONG X AND Y DIMENSIONS:"<<endl;
  cout<<endl;
      cout << "Minimum of 0'th dimension is " << findMin(root, 0) << endl;
    cout << "Minimum of 1'th dimension is " << findMin(root, 1) << endl;
	  cout<<endl;
                   		  
                 		  break;
	case 5 : 
		y=1;
                   		break;
               	default : cout<<"\nEnter a Valid Choice.";
   case 4 :
	cout<<"SEARCH: "<<endl;
	cout<<endl;

	int point1[] = {10, 19};
	cout<<"Searching for Point{10, 19} = ";
	(search(root, point1))? cout << "Found\n": cout << "Not Found\n";

	int point2[] = {50,30};
		cout<<"Searching for Point{50, 30} = ";
	(search(root, point2))? cout << "Found\n": cout << "Not Found\n";
		cout<<endl;
  
  break;
               	
                }
                cout<<endl;
    }while(y!=1);

	system("pause");
	return 0;
}

