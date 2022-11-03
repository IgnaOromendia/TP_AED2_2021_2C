//
// Created by Igna on 02/11/2021.

#ifndef TP3_ALGO2LANDIA_SIMULACION_H
#define TP3_ALGO2LANDIA_SIMULACION_H

#include "Tipos.h"
#include "Mapa.h"
#include "Objetivo.h"

using namespace std;

class Simulacion {
public:
    Simulacion();

    Simulacion(Mapa m, Coordenada c, map<Color,Coordenada> obj);

    ~Simulacion();

    const Mapa& mapa() const;

    const Coordenada& posJugador() const;

    const Nat& cantMovimientos() const;

    const set<Objetivo>& objetivosDisponibles() const;

    const Nat objetivosRealizados() const;

    const set<Color>& coloresOjetos();

    const Coordenada& posObjeto(Color c) const;

    bool mover(Direccion d);

    void agObjetivo(const Objetivo& o);

    bool hayMovimiento(Coordenada c, Direccion d, const Mapa m);

    Coordenada siguientePosicion(Coordenada c, Direccion d);

    void filtrarRealizados(set<Objetivo>& co);

    bool hayObjeto(Coordenada c);

    bool hayAlgunObjeto(Coordenada cor, set<Color> c);

private:
    /** Estructura **/
    Nat _movimientos;
    Nat _objCompletados;
    Coordenada _posAgente;
    Mapa _mapa;
    vector<vector<Color>> _objetosXpos;
    string_map<string_map<set<Objetivo>::iterator>> _objetivosXcolor;
    string_map<Coordenada> _objetos;
    set<Objetivo> _objDisponibles;

    set<Color> _colObjetos;
};

#endif //TP3_ALGO2LANDIA_SIMULACION_H
