#include<bits/stdc++.h>
using namespace std;

int min(int x, int y) { return (x < y)? x: y; }

struct node
{
	int data;
	int vc;     //To store the vertex cover for subtree :: Memoization
	struct node *left, *right;
};

int vCover(struct node *root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 0;

	if (root->vc != 0)
		return root->vc;

	// Calculate size of vertex cover when root is part of it
	int size_incl = 1 + vCover(root->left) + vCover(root->right);

	// Calculate size of vertex cover when root is not part of it
	int size_excl = 0;
	if (root->left)
	size_excl += 1 + vCover(root->left->left) + vCover(root->left->right);
	if (root->right)
	size_excl += 1 + vCover(root->right->left) + vCover(root->right->right);

	root->vc = min(size_incl, size_excl);

	return root->vc;
}

struct node* newNode( int data )
{
	struct node* temp = (struct node *) malloc( sizeof(struct node) );
	temp->data = data;
	temp->left = temp->right = NULL;
	temp->vc = 0;
	return temp;
}

//Imputting the binary tree
void ask(struct node * head)
{
	char response;

	cout<<"Does "<<head->data<<" have a left branch? (y/n)"<<endl;
	cin>>response;

	if(response == 'y' || response == 'Y'){
		cout<<"Enter the left branch value"<<endl;
		int info;
		cin>>info;

		head->left=newNode(info);
		ask(head->left);
	}

	cout<<"Does "<<head->data<<" have a right branch? (y/n)"<<endl;
	char response2;
	cin>>response2;

	if(response2 == 'y' || response2 == 'Y'){
		cout<<"Enter the right branch value"<<endl;
		int info;
		cin>>info;

		head->right=newNode(info);
		ask(head->right);
	}
}

int main()
{
	int info;
	cout<<"Enter the root value"<<endl;
 	cin>>info;

	struct node *root = newNode(info);
	ask(root);

	cout<<"Size of the smallest vertex cover is "<<vCover(root)<<endl;

	return 0;
}
