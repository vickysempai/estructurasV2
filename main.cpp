#include <iostream>
#include "ArbolB.h"
#include "Pagina.h"
using namespace std;

int main(){/*
	Pagina feo(3);
	feo.Pclave(1,2);
	feo.Pclave(2,5);
	//cout<<feo.Oclave(1)<<endl;
	*/
	ArbolB b(5);
	b.insertar(6);
	b.insertar(11);
	b.insertar(5);
	b.insertar(8);
	b.insertar(9);/*
	b.insertar(12);
	b.insertar(21);
	b.insertar(14);
	b.insertar(10);
	b.insertar(19);
	b.insertar(28);*/
	
	b.escribir();
	b.listarCreciente();
	
	return (EXIT_SUCCESS);
}
