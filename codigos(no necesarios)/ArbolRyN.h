#ifndef ARBOLRYN_H
#define ARBOLRYN_H

#include "NodoRyN.h"

class RyN
{
public:
	nodoRyN *primeroRN;
	void insercion(int key, string definicion); // para insertar un numero en el arbol
	void solucionarRojoRojo(nodoRyN *node, int h); // para solucionar un hijo rojo en un nodo rojo
	void liberar(nodoRyN *node); // para liberar la memoria cuando desea salir del programa
	void mostrar(nodoRyN * actual,int indent); // muestra el padre e hijos del numero insertado y tambien el color del nodo
	nodoRyN *buscar(int key) // para buscar un numero en el arbol
	{
		nodoRyN *ayudante;
		ayudante = primeroRN;
		if (!ayudante)
			return NULL;
		do
		{
			if (key == ayudante->llave)
				return ayudante;
			else if (key < ayudante->llave)
				ayudante = ayudante->izquierdo;
			else if (key > ayudante->llave)
				ayudante = ayudante->derecho;
		}
		while (ayudante);
		return NULL;
	}
	
};

#endif
