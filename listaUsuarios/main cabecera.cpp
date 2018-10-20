#include<iostream>
#include<cstdio>
#include<sstream>
#include "avl.h"
using namespace std;

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
	}
	return 0;*/
}

	
