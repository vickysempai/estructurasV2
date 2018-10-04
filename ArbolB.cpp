#include "ArbolB.h"
#include <iostream>
/*
bool ArbolB::BuscarNodo(int clave,Pagina *p,bool encontrado,int k)
{
	//Clave: Valor a insertar
	//P: Apuntador del tipo Pagina
	//Encontrado:boolean
	//K:posición
	
	// Este método examina la Pagina referenciada por P. De no //encontrarse el valor nuevo, K será el índice de la rama por 
	//donde bajar
	if (clave<clave[1])
	{
		encontrado=false;
		k=0;//desciende por el lado izquierdo
	}
	else
	{
		//examina las clave de la Pagina
		k=p->cuenta;
		while((clave<Pagina->clave[k])&&(k>1))
		{
			k=k-1;
			if(clave==Pagina->clave[k]){
				encontrado=true;
			}
		}
	}
}

*/
void ArbolB::insertar(int clave,Pagina *Raiz=NULL)
{
	//Clave: Valor a insertar
	//Raiz: Apuntador del tipo Pagina; este se encuentra la ArbolB
	
	//Variables internas
	//EmpujarArriba:boolean
	//X:TipoClave
	//Xr:Apuntador del tipo Pagina
	//P:Apuntador del tipo Pagina
	X=0;
	Pagina *Xr;
	bool EmpujarArriba = false;
	bool EA=Empujar(clave,Raiz,EmpujarArriba,X,Xr);
	if(EmpujarArriba)
	{
		// La propagación del proceso de división llego a la raíz, es     
		// creado un nuevo nodo  
		Pagina *p= new Pagina();//que crea una nueva Pagina, según la clase
		p->cuenta=1;
		p->clave[1]=clave;//Clave mediana que ha ascendido
		p->rama[0]=Raiz;
		//P->rama[1]=Xr;
		Raiz=p; //Nueva Raiz
	}
}


bool ArbolB::Empujar(int clave,Pagina *R = NULL,bool EmpujarArriba=false,int Mdna=0,Pagina *X=NULL)
{
	//Método de Empujar
	//Parámetros
	
	//C1: Valor a insertar
	//R: Apuntador del tipo Pagina
	//EmpujarArriba:boolean
	//Mdna:Tipo de la Información 
	//X:Apuntador del tipo de la Pagina
	
	//Variables Internas
	//K:Posicion
	//Esta:Booleana //Detectsa que la clave ya esta en el nodo
	if(R==NULL)
	{
		// Termina la recursión, estamos  en rama vacia
		EmpujarArriba=true;
		Mdna=clave;
		X=NULL;
	}
	else
	{
		bool Esta = BuscarNodo(clave,R,Esta,K);//K es la rama por donde seguir
		if(Esta)
		{
			cout<<"elemento repetido"<<endl;
			return false;
		}
		EmpujarArriba=Empujar(clave,R->rama[K],EmpujarArriba,Mdna,X);
		if(EmpujarArriba){
			if(R->cuenta<max)  //No esta lleno
			{
				EmpujarArriba=false;
				MeterHoja(Mdna,X,R,K);//Inserta la clave Mdna en el nodo   
				//R, posición k+1
			}
		}
		else//Nodo lleno 
		{
			EmpujarArriba=true;
			
		//	----------------------------------
		//	DividirNodo(Mdna,X,R,K,Mdna,Xr);
		//	----------------------------------
		}
	}
	return EmpujarArriba;
}
/*
void ArbolB::MeterHoja(int X,Pagina*Xder,Pagina *r, int k)
{
	//Método de MeterHoja
	//Parámetros
	
	//X: TipoClave
	//Xder: Apuntador del tipo Pagina
	//P: Apuntador del tipo Pagina
	//K:posición
	
	//Variables internas
	//I: Posicion
	// Se trabajara con P
	for(int i=4;i<k+1;i--){
	{
		clave[i+1]=clave[i];
		rama[i+1]=rama[i];
	}
	clave[k+1]=X;
	rama[k+1]=Xder;
	cuenta=cuenta+1;
}*/

