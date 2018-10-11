#ifndef ARBOLRYN_H
#define ARBOLRYN_H

#include "NodoRyN.h"
#include <string>

class RyN
{
public:
	nodoRyN *primeroRN = NULL;
	void insercion(string ciudad,string codigo,string pNombre); // para insertar un numero en el arbol
	void insertarProducto(string pCodSuper,string pCodProducto,string pNombre,int pCant,float pPrecio); 
	void solucionarRojoRojo(nodoRyN *node, int h); // para solucionar un hijo rojo en un nodo rojo
	void liberar(nodoRyN *node); // para liberar la memoria cuando desea salir del programa
	void mostrar(nodoRyN * actual); // muestra el padre e hijos del numero insertado y tambien el color del nodo
	void mostrarInventarios(nodoRyN *actual);
	nodoRyN *buscar(string codigo) // para buscar un numero en el arbol
	{
		nodoRyN *ayudante;
		ayudante = primeroRN;
		if (ayudante == NULL)
			return NULL;
		while (ayudante != NULL)
		{	
			if (stoi(codigo) == stoi(ayudante->codSuper))
				return ayudante;
			else if (stoi(codigo) < stoi(ayudante->codSuper))
				ayudante = ayudante->izquierdo;
			else if (stoi(codigo) > stoi(ayudante->codSuper))
				ayudante = ayudante->derecho;
		}
		return NULL;
	}
};

#endif
