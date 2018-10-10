#include "ArbolRyN.h"


void RyN::insercion(string ciudad,string codigo,string pNombre)
{
	int ladohijo;
	nodoRyN *hijo;
	nodoRyN *ayudante;
	int bandera;
	if(primeroRN==NULL)
	{
		primeroRN = new nodoRyN(ciudad,codigo,pNombre);
		primeroRN->color = 'N';
	}
	else
	{
		hijo = new nodoRyN(ciudad,codigo,pNombre);
		ayudante=primeroRN;
		do
		{
			hijo->padre = ayudante;
			bandera = 1;
			if (stoi(codigo) == stoi(ayudante->codSuper))
			{
				if (ayudante->izquierdo)
					ayudante = ayudante->izquierdo;
				else
					ayudante->izquierdo = hijo, bandera = 0, ladohijo = 1;
			}
			else
			{
				if (ayudante->derecho)
					ayudante = ayudante->derecho;
				else
					ayudante->derecho = hijo, bandera = 0, ladohijo = 2;
			}
		}
		while (bandera == 1);
		if (ayudante->color == 'R')
			solucionarRojoRojo(ayudante, ladohijo);
	}
}

void RyN::insertarProducto(string pCodSuper,string pCodProducto,string pNombre,int pCant,float pPrecio)
{
	nRN super = buscar(pCodSuper);
	super->inventario->insertar(pCodSuper,pCodProducto,pNombre,pCant,pPrecio);
} 


void RyN::solucionarRojoRojo(nodoRyN *node, int h)
{
	int ladohijo;
	nodoRyN *abuelo;
	nodoRyN *tio;
	nodoRyN *ayudante;
	abuelo = node->padre;
	if (abuelo->izquierdo && abuelo->derecho)
	{
		if (node == abuelo->izquierdo)
			tio = abuelo->derecho;
		else
			tio = abuelo->izquierdo;
		
		if (tio->color =='R')
		{
			tio->color = 'N';
			node->color = 'N';
			if (abuelo != primeroRN)
				abuelo->color = 'R';
			if (abuelo->padre)
			{
				ayudante = abuelo->padre;
				if (ayudante->izquierdo == abuelo)
					ladohijo = 1;
				else
					ladohijo = 2;
				if (ayudante->color == 'R')
					solucionarRojoRojo(ayudante, ladohijo);
			}
			return;
		}
	}
	if (h == 1 && abuelo->izquierdo == node)
	{
		node->color = 'N', abuelo->color = 'R';
		ayudante = node->derecho, node ->derecho = abuelo, node->padre = abuelo->padre;
		abuelo->padre = node, abuelo->izquierdo = ayudante;
		if (ayudante)
			ayudante->padre = abuelo;
		if (node->padre)
		{
			ayudante = node->padre;
			if (ayudante->izquierdo == node->derecho)
				ayudante->izquierdo = node;
			else
				ayudante->derecho = node;
		}
		else
			primeroRN = node;
	}
	else if (h == 2 && abuelo->derecho == node)
	{
		node->color = 'N', abuelo->color = 'R';
		ayudante = node->izquierdo, node->izquierdo = abuelo, node->padre = abuelo->padre;
		abuelo->padre = node, abuelo->derecho = ayudante;
		if (ayudante)
			ayudante->padre = abuelo;
		if (node->padre)
		{
			ayudante = node->padre;
			if (ayudante->izquierdo == node->izquierdo)
				ayudante->izquierdo = node;
			else
				ayudante->derecho = node;
		}
		else
			primeroRN = node;
	}
	else if (h == 2 && abuelo->izquierdo == node)
	{
		tio = node->derecho, ayudante = tio->izquierdo, abuelo->izquierdo = tio;
		tio->padre = abuelo, tio->izquierdo = node, node->padre = tio;
		node->derecho = ayudante;
		if (ayudante)
			ayudante->padre = node;
		solucionarRojoRojo(tio, 1);
	}
	else if (h==1 && (abuelo->derecho = node))
	{
		tio = node->izquierdo, ayudante = tio->derecho, abuelo->derecho = tio;
		tio->padre = abuelo, tio->derecho = node, node->padre = tio;
		node->izquierdo = ayudante;
		if (ayudante)
			ayudante->padre = node;
		solucionarRojoRojo(tio, 2);
	}
}

void RyN::liberar(nodoRyN *node)
{
	if (node)
	{
		if (node->izquierdo)
			liberar(node->izquierdo);
		if (node->derecho)
			liberar(node->derecho);
		delete node;
	}
}


void RyN::mostrar(nodoRyN* actual)
{
	if (actual != NULL)
	{
		cout << actual->codCiudad << ";" << actual->codSuper << ";" << actual->nombre << "|" << actual->color << "-> ";
		actual->inventario->mostrar(actual->inventario->raiz);
		mostrar(actual->izquierdo);
		mostrar(actual->derecho);
	}
}

void RyN::mostrarInventarios(nodoRyN *actual){
	if(actual != NULL){
		actual->inventario->mostrar(actual->inventario->raiz);
		mostrarInventarios(actual->izquierdo);
		mostrarInventarios(actual->derecho);
	}
}
