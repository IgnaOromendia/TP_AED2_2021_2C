//
// Created by Igna on 01/11/2021.
//

#ifndef TP3_ALGO2LANDIA_MAPA_H
#define TP3_ALGO2LANDIA_MAPA_H

#include "Tipos.h"

using namespace std;
typedef string color;

class Mapa {
public:
    Mapa();

    Mapa(Nat alto, Nat ancho, map<Color,Coordenada> rs);

    ~Mapa();

    const Nat& ancho() const;

    const Nat& alto() const;

    const string_map<Coordenada>& receptaculos() const;

    bool esPared(Coordenada p) const;

    bool esRampa(Coordenada p) const;

    Mapa nuevoMapa(Nat alto, Nat ancho, map<Color,Coordenada> rs);

    void agregarPared(Coordenada p);

    void agregarRampa(Coordenada p);

    bool enRango(Coordenada p) const;

    bool esPiso(Coordenada p) const;

    Nat dist(Coordenada p1, Coordenada p2) const;

    vector<vector<Color>> casilleros() const;

private:
    /** Estructura de Mapa **/
    Nat _ancho;
    Nat _alto;
    vector<vector<Color>> _casilleros;
    string_map<Coordenada>_receptaculos;
    set<Coordenada> _paredes;
    set<Coordenada> _rampas;
};






#endif //TP3_ALGO2LANDIA_MAPA_H
