#include "ArbolAA.h"

void ArbolAA::giro(NodoAA *temp)
{
	NodoAA *ptr = temp->izquierda;
	if (temp->padre->izquierda == temp)
		temp->padre->izquierda = ptr;
	else
		temp->padre->derecha = ptr;
	ptr->padre = temp->padre;
	temp->padre = ptr;
	temp->izquierda = ptr->derecha;
	if (temp->izquierda != NULL)
		temp->izquierda->padre = temp;
	ptr->derecha = temp;
	temp->nivel = (temp->izquierda ? temp->izquierda->nivel + 1 : 1);
}

/*
* Reparto del arbol
*/
bool ArbolAA::reparto(NodoAA *temp)
{
	NodoAA* ptr = temp->derecha;
	if (ptr && ptr->derecha && (ptr->derecha->nivel == temp->nivel))
	{
		if (temp->padre->izquierda == temp)
			temp->padre->izquierda = ptr;
		else
			temp->padre->derecha = ptr;
		ptr->padre = temp->padre;
		temp->padre = ptr;
		temp->derecha = ptr->izquierda;
		if (temp->derecha != NULL)
			temp->derecha->padre = temp;
		ptr->izquierda = temp;
		ptr->nivel = temp->nivel + 1;
		return true;
	}
	return false;
}

/*
* Rebalancear el arbol
*/
void ArbolAA::rebalancear(NodoAA* temp)
{
	temp->izquierda = NULL;
	temp->derecha = NULL;
	temp->nivel = 1;
	for (temp = temp->padre; temp != raiz; temp = temp->padre)
	{
		if (temp->nivel != (temp->izquierda ? temp->izquierda->nivel + 1 : 1 ))
		{
			giro(temp);
			if (temp->derecha == NULL)
				temp = temp->padre;
			else if (temp->nivel != temp->derecha->nivel)
				temp = temp->padre;
		}
		if (temp->padre != raiz)
		{
			if (reparto(temp->padre) == false)
				break;
		}
	}
}

/*
* Funcion para insertar en el arbol
*/
int ArbolAA::insertar(string pCodSuper,string pCodProducto,string pNombre,int pCant,float pPrecio)
{
	NodoAA *temp = new NodoAA(pCodSuper,pCodProducto,pNombre,pCant,pPrecio);
	temp->nivel = 1;
	temp->cont = 0;
	temp->izquierda = NULL;
	temp->derecha = NULL;
	temp->padre = NULL;
	temp = insertarAux(raiz, temp);
	return temp->cont;
}

/*
* Funcion auxiliar para insertar en el arbol
*/
NodoAA* ArbolAA::insertarAux(NodoAA* temp, NodoAA* aux)
{
	if (raiz == NULL)
	{
		aux->cont = 1;
		aux->padre = NULL;
		aux->izquierda = NULL;
		aux->derecha = NULL;
		raiz = aux;
		return raiz;
	}
	if (aux->cantidad > temp->cantidad)
	{
		if (temp->izquierda)
			return insertarAux(temp->izquierda, aux);
		temp->izquierda = aux;
		aux->padre = temp;
		aux->cont = 1;
		rebalancear(aux);
		return aux;
	}
	if (aux->cantidad > temp->cantidad)
	{
		if (temp->derecha)
			return insertarAux(temp->derecha, aux);
		temp->derecha = aux;
		aux->padre = temp;
		aux->cont = 1;
		rebalancear(aux);
		return aux;
	}
	temp->cont++;
	delete aux;
	return temp;
}
/*
* Contador del numero de NodoAAs del arbol
*/
int ArbolAA::contNodoAA(NodoAA* temp)
{
	if (!temp)
		return 0;
	int cont = 1;
	cont = cont + contNodoAA(temp->izquierda);
	cont = cont + contNodoAA(temp->derecha);
	return cont;
}

NodoAA *ArbolAA::buscar(string c){
	NodoAA *actual = raiz;
	while(!Vacio(actual)){
		if(c == actual->codProducto){
			return actual;
		}
		else if(c > actual->codProducto){
			actual = actual->derecha;
		}
		else if(c < actual->codProducto){
			actual = actual->izquierda;
		}
	}
	return NULL;
}

void ArbolAA::mostrar(NodoAA *actual){
	if (actual != NULL)
	{
		cout << actual->codSuper << ";" << actual->codProducto << ";" << actual->nombre << ";" << actual->cantidad << ";" << actual->precioU << " - ";
		mostrar(actual->izquierda);
		mostrar(actual->derecha);
	}
	cout << endl;
}
