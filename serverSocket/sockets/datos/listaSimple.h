#include <iostream>
#include <string>
using namespace std;

class nodoL{
public:
	nodoL(){NULL;}
	nodoL(string cc,string ced,string nomb,string tel,string tip){codCiudad = cc;cedula = ced;nombre = nomb;telefono = tel;tipo=tip;siguiente=NULL;}
	nodoL(string cc,string ced,string nomb,string tel,string tip,nodoL *signodo){
        codCiudad = cc;cedula = ced;nombre = nomb;telefono = tel;tipo=tip;siguiente=signodo;}
			
	string codCiudad,cedula,nombre,telefono,tipo;
    nodoL *siguiente;
	
	// obtener codigo de ciudad
	string OcodCiudad(){ return codCiudad;}
	
	// obtener cedula
	string Ocedula(){ return cedula;}
	
	// obtener nombre
	string Onombre(){ return nombre;}
	
	// obtener nombre
	string Otelefono(){ return telefono;}
	
    friend class lista;
};

typedef nodoL *pnodoL;

class lista {
   public:
    lista() { primero = actual = NULL; }
    ~lista();
    
    void InsertarInicio(string cc,string ced,string nomb,string tel,string tip);
    void InsertarFinal(string cc,string ced,string nomb,string tel,string tip);
    void InsertarPos (string cc,string ced,string nomb,string tel,string tip, int pos);
    void EliminarInicio();
    void EliminarFinal();
    void EliminarPos(int pos);
    bool ListaVacia() { return primero == NULL; } 
    void Imprimir();
    void Borrar(string cc,string ced,string nomb,string tel,string tip);
    void Mostrar();
    void Siguiente();
    void Primero();
    void Ultimo();
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    bool buscar(string pCodigo);
    pnodoL buscarNodo(string cedula);
    int buscarPosicion(string cedula);
    int largoLista();
    
   private:
    pnodoL primero;
    pnodoL actual;
};

lista::~lista()
{
   pnodoL aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   actual = NULL;
}

int lista::largoLista(){
    int cont=0;

    pnodoL aux;
    aux = primero;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
    
}

void lista::InsertarInicio(string cc,string ced,string nomb,string tel,string tip)
{
   if (ListaVacia())
     primero = new nodoL(cc,ced,nomb,tel,tip);
   else
     primero=new nodoL (cc,ced,nomb,tel,tip);
}
 
void lista::InsertarFinal(string cc,string ced,string nomb,string tel,string tip)
{
   if (ListaVacia())
     primero = new nodoL(cc,ced,nomb,tel,tip);
   else
     { pnodoL aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoL(cc,ced,nomb,tel,tip);
      }    
}


void lista::InsertarPos(string cc,string ced,string nomb,string tel,string tip,int pos)
{
   if (ListaVacia())
     primero = new nodoL(cc,ced,nomb,tel,tip);
   else{
        if(pos <=1){
          pnodoL nuevo = new nodoL(cc,ced,nomb,tel,tip);
          nuevo->siguiente= primero;
          primero= nuevo;     
        }      
        else{
             pnodoL aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             pnodoL nuevo= new nodoL(cc,ced,nomb,tel,tip);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             
        }
        }
}
      
void lista::BorrarFinal()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodoL aux = primero;
                while (aux->siguiente->siguiente != NULL) {
                    aux = aux->siguiente;

                }
                
              pnodoL temp = aux->siguiente;
              aux->siguiente= NULL;

                
                delete temp;
            }
        }
}

void lista::BorrarInicio()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodoL aux = primero;
                primero=primero->siguiente;                
                delete aux;
            }
        }
}



void lista:: borrarPosicion(int pos){
     if(ListaVacia()){
              cout << "Lista vacia" <<endl;
    }else{
         if((pos>largoLista())||(pos<0)){
        cout << "Error en posicion" << endl;
        }else{
        if(pos==0){
        primero=primero->siguiente;
        }else{
          int cont=2;
            pnodoL aux=  primero;
            while(cont<pos){
             aux=aux->siguiente;
             cont++;
            }
            aux->siguiente=aux->siguiente->siguiente;
            }
        }
     }

}
 

void lista::Mostrar()
{
   nodoL *aux;
   
   aux = primero;
   while(aux) {
      cout << aux->nombre << ";" << aux->cedula << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

void lista::Siguiente()
{
   if(actual) actual = actual->siguiente;
}

void lista::Primero()
{
   actual = primero;
}

void lista::Ultimo()
{
   actual = primero;  
   if(!ListaVacia()) 
      while(actual->siguiente) Siguiente();
}

bool lista::buscar(string pCodigo){
    pnodoL aux = primero;
    while(aux != NULL){
        if(aux->cedula == pCodigo){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

int lista::buscarPosicion(string cedula){
    int cont = 0;
    pnodoL aux = primero;
    while(aux != NULL){
        if(aux->cedula == cedula){
            return cont;
        }
        aux = aux->siguiente;
        cont++;
    }
    return -1;
}

pnodoL lista::buscarNodo(string cedula){
    pnodoL aux = primero;
    while(aux != NULL){
        if(aux->cedula == cedula){
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}