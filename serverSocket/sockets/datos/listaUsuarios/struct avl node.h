/*
* C++ program to Implement AVL Tree
*/
#ifndef NODOAVL_H
#define NODOAVL_H

#include<iostream>
#include<cstdio>
#include "listaCarrito.h"
using namespace std;

/*
* Node Declaration
*/
class avl_node
{
public:
	avl_node(){NULL;}
	avl_node(string cc,string ced,string nomb,string tel){codCiudad = cc;cedula = ced;nombre = nomb;telefono = tel;}
	
	string codCiudad;
	string cedula;
	string nombre;
	string telefono;
	avl_node *left;
	avl_node *right;
	listaC carrito;
	int descuento = 5;
	int facturas = 0;

};

#endif
