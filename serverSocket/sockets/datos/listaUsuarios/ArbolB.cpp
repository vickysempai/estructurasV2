#include "ArbolB.h"
/*
ArbolB::ArbolB() {
	
}
*/
bool ArbolB::buscarNodo(Pagina* actual, string &cl, int & k)
{
	int index;
	bool encontrado;
	if (cl < actual->Oclave(1).Ocedula())
	{
		encontrado = false;
		index = 0;
	}
	else
	{ // orden descendente	
		index = actual->Ocuenta();
		while (cl < actual->Oclave(index).Ocedula() && (index > 1))
			index--;
		encontrado = cl == actual->Oclave(index).Ocedula();
	}
	k = index;
	return encontrado;
}

Pagina* ArbolB::buscar( string &cl, int &n)
{
	return buscar( raiz, cl, n);
}
Pagina* ArbolB::buscar(Pagina* actual, string &cl, int &n)
{
	if (actual == NULL)
	{
		return NULL;
	}
	else
	{
		bool esta = buscarNodo(actual, cl, n);
		if (esta) // la clave se encuentra en el nodo actual
			return actual;
		else
			return buscar(actual->Orama(n), cl, n); //llamada recursiva
	}
}
// m�todo p�blico
void ArbolB::insertar(tipoClave& cl )
{
	raiz = insertar(raiz, cl);
}
//m�todo privado
Pagina* ArbolB::insertar(Pagina* raiz, tipoClave& cl)
{
	bool subeArriba;
	tipoClave mediana;
	Pagina* nd;
	subeArriba = empujar(raiz, cl, mediana, nd);
	if (subeArriba)
	{
		// El �rbol crece en altura por la ra�z.
		// sube una nueva clave mediana y un nuevo hijo derecho nd
		// en la implementaci�n se mantiene que las claves que son
		// menores que mediana se encuentran en raiz y las mayores en nd
		Pagina* p;
		p = new Pagina(orden); // nuevo nodo
		p->Pcuenta(1); // tiene una sola clave
		p->Pclave(1,mediana);
		p->Prama(0,raiz); // claves menores
		p->Prama(1,nd); // claves mayores
		raiz = p;
	}
	return raiz;
}

bool ArbolB::empujar(Pagina* actual, tipoClave& cl, tipoClave &mediana, Pagina *& nuevo)
{
	int k;
	bool subeArriba = false;
	if (actual == NULL)
	{ // env�a hacia arriba la clave cl y su rama derecha NULL
		// para que se inserte en la P�gina padre
		subeArriba = true;
		mediana = cl;
		nuevo = NULL;
		// el dato P�gina de nuevo est� a NULL
	}
	else
	{
		bool esta;
		esta = buscarNodo(actual, cl.cedula, k);
		if (esta){
			//cout<< "\nClave duplicada";
		    subeArriba = false;
			return false;}
		// siempre se ejecuta
		subeArriba = empujar(actual->Orama(k), cl, mediana, nuevo);
		// devuelve control; vuelve por el camino de b�squeda
		if (subeArriba)
		{
			if (actual->nodoLLeno()) // hay que dividir la p�gina
				dividirNodo(actual, mediana, nuevo, k);
	    	else
		    { //cabe en la p�gina, se inserta la mediana y su rama derecha
			    subeArriba = false;
			    cout<<actual->nodoLLeno();
			    meterPagina(actual, mediana, nuevo, k);
		    }
	}
	return subeArriba;
}}

void ArbolB::meterPagina(Pagina* actual, tipoClave& cl,
						 Pagina *ramaDr, int k)
{
	// desplaza a la derecha los elementos para hacer un hueco
	for (int i = actual->Ocuenta(); i >= k + 1; i--)
	{
		actual->Pclave(i + 1, actual->Oclave(i));
		actual->Prama(i + 1, actual->Orama(i));
	}
	// pone la clave y la rama derecha en la posici�n k+1
	actual->Pclave(k + 1, cl);
	actual->Prama(k + 1, ramaDr);
	// incrementa el contador de claves almacenadas
	actual->Pcuenta(actual->Ocuenta()+1) ;
}

void ArbolB::dividirNodo(Pagina* actual, tipoClave &mediana,
						 Pagina * &nuevo, int pos)
{
	int i, posMdna, k;
	Pagina *nuevaPag;
	k = pos;
	// posici�n de clave mediana
	posMdna = (k <= orden/2) ? orden/2 : orden/2 + 1;
	nuevaPag = new Pagina(orden);
	for (i = posMdna + 1; i < orden; i++)
	{
		/* desplazada la mitad derecha a la nueva P�gina, la clave
		mediana se queda en P�gina actual */
		nuevaPag->Pclave(i - posMdna, actual->Oclave(i));
		nuevaPag->Prama(i - posMdna, actual->Orama(i));
	}
	nuevaPag->Pcuenta ((orden - 1) - posMdna); // claves de nueva P�gina
	actual->Pcuenta(posMdna); // claves en P�gina origen
	// inserta la clave y rama en la P�gina que le corresponde
	if (k <= orden / 2)
		meterPagina(actual, mediana, nuevo, pos); // en P�gina origen
	else
	{
		pos = k - posMdna;
		meterPagina(nuevaPag, mediana, nuevo, pos); // en P�gina nueva
	}
	// extrae clave mediana de la P�gina origen
	mediana = actual->Oclave(actual->Ocuenta());
	// Rama0 del nuevo nodo es la rama de la mediana
	nuevaPag->Prama(0, actual->Orama(actual->Ocuenta()));
	actual->Pcuenta(actual->Ocuenta() -1); // se quita la mediana
	nuevo = nuevaPag; // devuelve la nueva P�gina
}
void ArbolB::escribir( )
{
	escribir (raiz, 1);
}
void ArbolB::escribir( Pagina * r, int h)
{
	int i;
	if (r != NULL)
	{
		escribir( r->Orama(0),h + 5);
		for (i = 1; i <= r->Ocuenta()/2;i++)
		{ // llamadas recursivas a la mitad de los sub�rboles
			escribir(r->Orama(i),h + 5);
			cout << endl;
		}
		// visualizaci�n de las claves de la p�gina apuntada por r
		for (i = 1; i<= r->Ocuenta();i++)
		{
			for (int j = 0; j <= h; j++)
				cout << " ";
			cout << r->Oclave(i).Ocedula() << endl;
		}
		// llamadas recursivas a la otra mitad de los sub�rboles
		for (i = r->Ocuenta() / 2 + 1 ; i<= r->Ocuenta();i++)
			escribir(r->Orama(i),h + 5);
		cout << endl;
	}
}
void ArbolB::listarCreciente()
{
	inOrden(raiz) ;
}
void ArbolB::inOrden(Pagina *r)
{
	if (r)
	{
		inOrden(r->Orama(0));
		for (int k = 1; k <= r->Ocuenta(); k++)
		{
			cout << r->Oclave(k).Ocedula()<<";"<< r->Oclave(k).Onombre() << " - ";
			inOrden(r->Orama(k));
		}
	}
}
