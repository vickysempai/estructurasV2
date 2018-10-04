#ifndef _ARBOLB_H
#define	_ARBOLB_H

#include "Pagina.h"

using namespace std;

class ArbolB {
   public:
   Pagina *Raiz;
   ArbolB():Raiz(NULL) {}
    
    //bool BuscarNodo(int clave,Pagina p,bool encontrado,int k);
    bool Empujar(int clave,Pagina *R,bool EmpujarArriba,int Mdna,Pagina *X);
    //void MeterHoja(int clave,Pagina*xr,Pagina *r, int k);
    void insertar(int clave,Pagina *Raiz);
    
   bool EmpujarArriba;
};

#endif	/* _ARBOLB_H */


