/*
* C++ program to Implement AVL Tree
*/
#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include "struct avl node.h"
#define pow2(n) (1 << (n))
using namespace std;

/*
* Class Declaration
*/

class avlTree
{
public:
	avl_node* root;
	int height(avl_node *);
	int diff(avl_node *);
	avl_node *rr_rotation(avl_node *);
	avl_node *ll_rotation(avl_node *);
	avl_node *lr_rotation(avl_node *);
	avl_node *rl_rotation(avl_node *);
	avl_node* balance(avl_node *);
	avl_node* insert(avl_node *, string cc,string ced,string nomb,string tel );
	void display(avl_node *, int);
	void inorder(avl_node *);
	void preorder(avl_node *);
	void postorder(avl_node *);
	avl_node* obtenerUsuario(string cedula);
	avl_node* obtenerUsuario(avl_node*root,string cedula);
	avlTree()
	{
		root = NULL;
	}
};

/*
* Main Contains Menu
*/

int main()
{
	int choice, item;
	avlTree avl;
	avl.root= avl.insert(avl.root,"1","2","3","5");
	avl.root= avl.insert(avl.root,"6","7","8","9");
	avl.root= avl.insert(avl.root,"10","20","30","50");
	//avl.root= avl.insert(avl.root,2);
	//avl.root= avl.insert(avl.root,1);
	avl.postorder(avl.root);
	avl_node* victor;
	victor=avl.obtenerUsuario("7");
	if(victor)
	    cout<<victor->nombre;
	/*
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
		cout<<"6.Exit"<<endl;
		cout<<"Enter your Choice: ";
		cin>>choice;
		switch(choice)
		{
		case 1:
			cout<<"Enter value to be inserted: ";
			cin>>item;
			root = avl.insert(root, item);
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
			cout<<"Inorder Traversal:"<<endl;
			avl.inorder(root);
			cout<<endl;
			break;
		case 4:
			cout<<"Preorder Traversal:"<<endl;
			avl.preorder(root);
			cout<<endl;
			break;
		case 5:
			cout<<"Postorder Traversal:"<<endl;
			avl.postorder(root);    
			cout<<endl;
			break;
		case 6:
			exit(1);    
			break;
		default:
			cout<<"Wrong Choice"<<endl;
		}
	}*/
	return 0;
}

/*
* Height of AVL Tree
*/
int avlTree::height(avl_node *temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int l_height = height (temp->left);
		int r_height = height (temp->right);
		int max_height = max (l_height, r_height);
		h = max_height + 1;
	}
	return h;
}

/*
* Height Difference 
*/
int avlTree::diff(avl_node *temp)
{
	int l_height = height (temp->left);
	int r_height = height (temp->right);
	int b_factor= l_height - r_height;
	return b_factor;
}

/*
* Right- Right Rotation
*/
avl_node *avlTree::rr_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}
/*
* Left- Left Rotation
*/
avl_node *avlTree::ll_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

/*
* Left - Right Rotation
*/
avl_node *avlTree::lr_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->left;
	parent->left = rr_rotation (temp);
	return ll_rotation (parent);
}

/*
* Right- Left Rotation
*/
avl_node *avlTree::rl_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->right;
	parent->right = ll_rotation (temp);
	return rr_rotation (parent);
}

avl_node *avlTree::obtenerUsuario(string cedula)
{
	return obtenerUsuario(root,cedula);
}

avl_node *avlTree::obtenerUsuario(avl_node* root,string cedula)
{
	if (root == NULL)
	{
		return NULL;
	}
	else if (root->cedula==cedula)
	{
		return root;
	}
	else if (cedula < root->cedula)
	{
		return obtenerUsuario(root->left,cedula);
	}
	else if (cedula >= root->cedula)
	{
		return obtenerUsuario(root->right, cedula);
	}
	return NULL;
}

/*
* Balancing AVL Tree
*/
avl_node *avlTree::balance(avl_node *temp)
{
	int bal_factor = diff (temp);
	if (bal_factor > 1)
	{
		if (diff (temp->left) > 0)
			temp = ll_rotation (temp);
		else
			temp = lr_rotation (temp);
	}
	else if (bal_factor < -1)
	{
		if (diff (temp->right) > 0)
			temp = rl_rotation (temp);
		else
			temp = rr_rotation (temp);
	}
	return temp;
}

/*
* Insert Element into the tree
*/
avl_node *avlTree::insert(avl_node *root, string cc,string ced,string nomb,string tel)
{
	if (root == NULL)
	{
		root = new avl_node;
		root->cedula = ced;
		root->codCiudad=cc;
		root->telefono = tel;
		root->nombre=nomb;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (ced < root->cedula)
	{
		root->left = insert(root->left,cc,ced, nomb, tel);
		root = balance (root);
	}
	else if (ced >= root->cedula)
	{
		root->right = insert(root->right, cc, ced, nomb, tel);
		root = balance (root);
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
		cout<<ptr->cedula;
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
	cout<<tree->cedula<<"  ";
	inorder (tree->right);
}
/*
* Preorder Traversal of AVL Tree
*/
void avlTree::preorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	cout<<tree->cedula<<"  ";
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
	cout<<tree->cedula<<"  ";
}
