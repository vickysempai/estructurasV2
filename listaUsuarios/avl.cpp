#include "avl.h"
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
void avlTree::insert( string cc,string ced,string nomb,string tel){
root=insert(root, cc, ced, nomb, tel);
}
avl_node *avlTree::insert(avl_node *root, string cc,string ced,string nomb,string tel)
{
	cout<<2;
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
