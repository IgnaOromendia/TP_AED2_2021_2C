//
// Created by Igna on 01/11/2021.
//


#include "Mapa.h"

Mapa::Mapa(): _alto(0), _ancho(0) {}

Mapa::Mapa(Nat alto, Nat ancho, map<Color,Coordenada> rs) {
    _ancho = ancho;
    _alto = alto;

    for(int i = 0; i < ancho; i++) {
        vector<Color> fila;
        for(int j = 0; j < alto; j++) {
            fila.push_back("");
        }
        _casilleros.push_back(fila);
    }

    for(pair<Color,Coordenada> c: rs ) {
        _receptaculos.insert(c);
        _casilleros[c.second.first][c.second.second] = c.first;
    }
}

Mapa::~Mapa() {
    // Creemos q no hace falta xq no usamos nigun new
}

const Nat& Mapa::ancho() const {
    return _ancho;
}

const Nat& Mapa::alto() const{
    return _alto;
}

const string_map<Coordenada>& Mapa::receptaculos() const {
    return _receptaculos;
}

bool Mapa::esPared(Coordenada p) const {
    bool result = false;
    for(Coordenada c: _paredes){
        if(p==c){
            result = true;
        }
    }
    return result;
}

bool Mapa::esRampa(Coordenada p) const {
    bool result = false;
    for(Coordenada c: _rampas){
        if (p==c){
            result = true;
        }
    }
    return result;
}

bool Mapa::esPiso(Coordenada p) const {
    bool result = true;
    for(Coordenada c: _rampas){
        if (p==c){
            result = false;
        }
    }
    for(Coordenada c: _paredes){
        if (p==c){
            result = false;
        }
    }
    return result;
}

Mapa Mapa::nuevoMapa(Nat alto, Nat ancho, map<Color,Coordenada> rs) {
    return Mapa(alto,ancho,rs);
}

void Mapa::agregarPared(Coordenada p) {
    _paredes.insert(p);
}

void Mapa::agregarRampa(Coordenada p) {
    _rampas.insert(p);
}


bool Mapa::enRango(Coordenada p) const {
    bool res = false;
    if(0 <= p.first && p.first <= _ancho - 1 && 0 <= p.second && p.second <= _alto - 1){
        res = true;
    }
    return res;
}

Nat Mapa::dist(Coordenada p1, Coordenada p2) const {
    return (p1.first - p2.first) + (p1.second - p2.second);
}

vector<vector<Color>> Mapa::casilleros() const {
    return _casilleros;
}












