#include <cstdlib>
#include "ListaDC.h"

int listaDC::largoLista()
{
    int cont=0;

    pnodoDC aux = primero;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
        do
        {
          aux=aux->siguiente;
          cont++;
        }while(aux!=primero);
    return cont;
    }
    
}

void listaDC::InsertarInicio(string v)
{
  
   if (ListaVacia())
   {
	   
     primero = new nodo(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     pnodoDC nuevo=new nodo (v);
     nuevo->siguiente=primero;
     nuevo->anterior= primero->anterior;
     primero->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primero= nuevo;
   }
}
 
void listaDC::InsertarFinal(string v)
{
   if (ListaVacia())
     {
     primero = new nodo(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoDC nuevo = new nodo(v);
     nuevo->anterior = primero->anterior;
     nuevo->siguiente=primero->anterior->siguiente;
     primero->anterior->siguiente=nuevo;
     primero->anterior=nuevo;
    }    
}


void listaDC::InsertarPos(string v,int pos)
{
   if (ListaVacia())
   {
     primero = new nodo(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   } 
   else
   {
      if(pos <=1)
        InsertarInicio(v);    
       else
       {
        if (pos==largoLista())
          InsertarFinal(v);
        else
        {     
             pnodoDC aux= primero;
             int i =2;
             do
             {
                   i++;
                   aux=aux->siguiente;
             }while((i != pos )&&(aux->siguiente!= primero));
             
             pnodoDC nuevo= new nodo(v);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             aux->siguiente->anterior=aux;
             nuevo->siguiente->anterior=nuevo;                           
        }
       }
   }
}   

void listaDC::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoDC temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoDC aux = primero;
         do{
              aux = aux->siguiente;
		 }
         while (aux->siguiente->siguiente != primero);
         pnodoDC temp = aux->siguiente;
         aux->siguiente= primero;
         primero->anterior=aux;
         delete temp;
      }
    }
}

void listaDC::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoDC temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoDC aux = primero->anterior;
        pnodoDC temp= primero;
        aux->siguiente=primero->siguiente;
        primero=primero->siguiente; 
        primero->anterior=aux;
        delete temp;
      }
    }
}

void listaDC:: borrarPosicion(int pos)
{
    
  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else
  {
   if((pos>largoLista())||(pos<0))
        cout << "Error en posicion" << endl;
   else
   {
      if(pos==1)
        BorrarInicio();
      else
      {
       int cont=2;
       pnodoDC aux=  primero;
       do
       {
         aux=aux->siguiente;
         cont++;
       }while(cont<pos);
       pnodoDC temp = aux->siguiente;
       aux->siguiente=aux->siguiente->siguiente;
       delete temp;
     }
    }
  }
}

void listaDC::Mostrar()
{
   pnodoDC aux=primero;
   do
     {
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
   while(aux->siguiente!=primero);
   
	cout<<aux->valor<<"->";
	cout<<endl;
}   

void listaDC::agregarArbol(ArbolB* b,avlTree* a)
{
	pnodoDC aux=primero;
	do
	{
		if(aux->valor=="3")
		{
			aux->arbolavl=a;
			aux = aux->siguiente;
		}
		else
		{
			aux->arbolb=b;
			aux = aux->siguiente;
		}
	}while(aux!=primero);																							 	 
}
