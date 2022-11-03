//
// Created by Igna on 01/11/2021.
//

#ifndef TP3_ALGO2LANDIA_STRING_MAP_H
#define TP3_ALGO2LANDIA_STRING_MAP_H

#include <string>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    INSERT
    * Inserta un par clave, valor en el diccionario
    **/
    void insert(const pair<string, T>&);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    /** OPTATIVO
    * operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string &key);
private:

    struct Nodo {
        vector<Nodo*> siguientes;
        T* definicion;
        /** Constructores **/
        Nodo(): siguientes(256, nullptr), definicion(nullptr) {}
        Nodo(T* def): siguientes(256, nullptr), definicion(def) {}
    };

    Nodo* raiz;
    int _size;
    // O(|clave.first|) = O(|c|)
    /** Insertar recursivo O(|c|)**/
    void insertR(Nodo* nodo,const pair<string,T>& clave, int indice) const;
    /** Busqueda O(|c|) **/
    T& buscar(Nodo* nodo,const string& clave, int indice) const;
    /** Borrar todos O(|c|) **/
    void eliminarTodos(Nodo* nodo);
    /** Copiar O(|c|) **/
    void copiar(Nodo* n, Nodo* r);
    /** Cantidad de hijos O(|c|) **/
    int cantHijos(Nodo* nodo);
    /** Eliminar recursivo O(|c|)**/
    void eliminar(Nodo* nodo, const string& clave, int indice);
    /** Algun hijo con def**/
    bool defEnHijos(Nodo* nodo);
};

#include "string_map.cpp"

#endif //TP3_ALGO2LANDIA_STRING_MAP_H
