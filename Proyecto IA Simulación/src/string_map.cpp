//
// Created by Igna on 01/11/2021.
//

#ifndef TP3_ALGO2LANDIA_STRING_MAP_CPP
#define TP3_ALGO2LANDIA_STRING_MAP_CPP

#include "string_map.h"

template <typename T>
string_map<T>::string_map(): raiz(new Nodo()), _size(0) {}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; }
// Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    eliminarTodos(this->raiz);
    delete raiz;
    this->_size = d.size();
    raiz = new Nodo();
    if (cantHijos(d.raiz) > 0) {
        copiar(d.raiz, raiz);
    }
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    eliminarTodos(raiz);
    delete raiz;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    //return buscar(raiz,clave,0);
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    Nodo* actual = raiz;
    for(int i = 0; i < clave.size();i++) {
        if (actual->siguientes[int(clave[i])] != nullptr) {
            actual = actual->siguientes[int(clave[i])];
        } else {
            return 0;
        }
    }
    return actual->definicion == nullptr ? 0 : 1;
}

template<class T>
void string_map<T>::insert(const pair<string, T> & clave) {
    insertR(raiz,clave,0);
    _size++;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    return buscar(raiz,clave,0);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    return buscar(raiz,clave,0);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    eliminar(raiz,clave,0);
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    for(int i = 0; i < raiz->siguientes.size();i++) {
        if (raiz->siguientes[i] != nullptr) {
            return false;
        }
    }
    return true;
}

/** Mis Funciones **/

template<class T>
void string_map<T>::insertR(Nodo *nodo, const pair<string, T> &clave,int indice) const {
    Nodo* local = nodo;
    if (indice < clave.first.size() - 1) {
        if (local->siguientes[clave.first[indice]] == nullptr) {
            local->siguientes[clave.first[indice]] = new Nodo();
        }
        insertR(local->siguientes[clave.first[indice]],clave,indice+1);
    } else {
        T* def = new T(clave.second);
        if (local->siguientes[clave.first[indice]] != nullptr) {
            local = local->siguientes[clave.first[indice]];
            if(local->definicion != nullptr) {
                delete local->definicion;
            }
            local->definicion = def;
        } else {
            local->siguientes[clave.first[indice]] = new Nodo(def);
        }
    }
}

template<class T>
T& string_map<T>::buscar(Nodo *nodo, const string &clave,int indice) const {
    Nodo* local = nodo;
    if (indice < clave.size()) {
        if (local->siguientes[clave[indice]] != nullptr) {
            return buscar(local->siguientes[clave[indice]],clave,indice+1);
        }
    } else{
        return *local->definicion;
    }
}

template<class T>
void string_map<T>::eliminarTodos(Nodo *nodo) {
    if (nodo != nullptr) {
        for(int i = 0; i < nodo->siguientes.size();i++) {
            if(nodo->siguientes[i] != nullptr) {
                if(nodo->siguientes[i]->definicion != nullptr) {
                    delete nodo->siguientes[i]->definicion;
                    nodo->siguientes[i]->definicion = nullptr;
                }
                eliminarTodos(nodo->siguientes[i]);
                delete nodo->siguientes[i];
                nodo->siguientes[i] = nullptr;
            }
        }
    }
}

template<class T>
void string_map<T>::copiar(Nodo* n, Nodo* r) {
    for(int i = 0; i < n->siguientes.size();i++) {
        if(n->siguientes[i] != nullptr) {
            if(n->siguientes[i]->definicion != nullptr) {
                T* def = new T(*(n->siguientes[i]->definicion));
                r->siguientes[i] = new Nodo(def);
            } else {
                r->siguientes[i] = new Nodo();
            }
            copiar(n->siguientes[i],r->siguientes[i]);
        }
    }
}

template<class T>
int string_map<T>::cantHijos(Nodo *nodo) {
    int hijos = 0;
    for(int i = 0; i < nodo->siguientes.size();i++) {
        if (nodo->siguientes[i] != nullptr) {
            hijos++;
        }
    }
    return hijos;
}

template<class T>
void string_map<T>::eliminar(Nodo *nodo, const string &clave, int indice) {
    if(indice < clave.size()) {
        if(nodo->siguientes[clave[indice]] != nullptr) { // Encuento la clave
            eliminar(nodo->siguientes[clave[indice]],clave,indice+1);
            if(cantHijos(nodo) == 1 && defEnHijos(nodo)) {
                delete nodo->siguientes[clave[indice]];
                nodo->siguientes[clave[indice]] = nullptr;
            }
        }
    } else {
        delete nodo->definicion;
        nodo->definicion = nullptr;
        _size--;
    }
}

template<class T>
bool string_map<T>::defEnHijos(Nodo *nodo) {
    bool result = false;
    for(int i = 0; i < nodo->siguientes.size(); i++) { // O(256 * n), n = # veces q entro
        if(nodo->siguientes[i] != nullptr) {
            result = nodo->siguientes[i]->definicion == nullptr && defEnHijos(nodo->siguientes[i]);
        }
    }
    return result;
}

#endif //TP3_ALGO2LANDIA_STRING_MAP_CPP
