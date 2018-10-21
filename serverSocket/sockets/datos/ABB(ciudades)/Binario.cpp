#include <iostream>
#include <string>
#include "Pila.h"
#include "NodoBinario.h"
#include "Binario.h"

using namespace std;

void NodoBinario::InsertaBinario(string cod,string name)
{
    if(Hizq==NULL){
        Hizq = new NodoBinario(cod,name);
    }
    else if(Hder==NULL){
        Hder = new NodoBinario(cod,name);
    }else if(Hder->Hizq == NULL || Hder->Hder == NULL){
        Hder->InsertaBinario(cod,name);
    }else{
        Hizq->InsertaBinario(cod,name);
    }
}

void Binario::InsertaNodo(string cod,string name)
{
    if(raiz==NULL){
        raiz = new NodoBinario(cod,name);
    }else{
        raiz->InsertaBinario(cod,name);
    }
}

void Binario::PreordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    while(p.Vacia()==false || (Act!=NULL)){
        cout<<Act->codigo<<";"<<Act->nombre<<" - ";
        if(Act!=NULL){
            cout<<Act->codigo<<";"<<Act->nombre<<" - ";
            p.Push(Act);
            Act = Act->Hizq;
        }else{
            Act=p.Pop();
            Act=Act->Hder;
        }
    }
}

void Binario::InordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    bool band=true;
    while(band){
        
        while(Act!=NULL){
            p.Push(Act);
            Act = Act->Hizq;
        }
        if(!p.Vacia()){
            Act=p.Pop();
            cout<<Act->codigo<<";"<<Act->nombre<<" - ";
            Act=Act->Hder;          
        }
        if(p.Vacia() & Act==NULL){
            break;
        }
    }
}

void Binario::PostordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    Pila p2;
    while(!p.Vacia() || Act!=NULL){
        if(Act!=NULL){
            p2.Push(new NodoBinario(Act->codigo,Act->nombre));            
            p.Push(Act);
            Act = Act->Hder;
        }else{            
            Act=p.Pop();
            Act = Act->Hizq;
        }
    }
    while(!p2.Vacia()){
        NodoBinario *salida=p2.Pop();
        cout<<salida->codigo<<";"<<salida->nombre<<" - ";
    }
}

void PreordenR(NodoBinario *R){
    
    if(R==NULL){
        return;
    }else{
        cout<<R->codigo<<";"<<R->nombre<<" - ";
        PreordenR(R->Hizq);
        PreordenR(R->Hder);
    }
}

void InordenR(NodoBinario *R){

    if(R==NULL){
        return;
    }else{
        InordenR(R->Hizq);
        cout<<R->codigo<<";"<<R->nombre<<" - ";
        InordenR(R->Hder);
    }
}

void PostordenR(NodoBinario *R){

    if(R==NULL){
        return;
    }else{
        PostordenR(R->Hizq);
        PostordenR(R->Hder);
        cout<<R->codigo<<";"<<R->nombre<<" - ";
    }
}

bool Binario::buscar(string cod){
    NodoBinario *Act = raiz;
    Pila p;
    Pila p2;
    while(!p.Vacia() || Act!=NULL){
        if(Act!=NULL){
            p2.Push(new NodoBinario(Act->codigo,Act->nombre));            
            p.Push(Act);
            Act = Act->Hder;
        }else{            
            Act=p.Pop();
            Act = Act->Hizq;
        }
    }
    while(!p2.Vacia()){
        NodoBinario *salida=p2.Pop();
        if(salida->codigo == cod){
            return true;
        }
    }
    return false;
}

