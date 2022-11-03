#include "aed2_mapa.h"

aed2_Mapa::aed2_Mapa(): _mapa(Mapa()) {}

aed2_Mapa::aed2_Mapa(Nat ancho, Nat alto, set<Coordenada> elevaciones, map<Color, Coordenada> receptaculos) {
    _mapa = Mapa(alto,ancho,receptaculos);

    for(Coordenada c: elevaciones) {
        _mapa.agregarPared(c);
    }

    _receptaculos = receptaculos;
}

void aed2_Mapa::agregarRampa(Coordenada c) {
    _mapa.agregarRampa(c);
}

Nat aed2_Mapa::ancho() const {
    return _mapa.ancho();
}

Nat aed2_Mapa::alto() const {
    return _mapa.alto();
}

TipoCasillero aed2_Mapa::tipoCasillero(Coordenada c) const {
    if (_mapa.esRampa(c)) {
        return RAMPA;
    } else if (_mapa.esPiso(c)) {
        return PISO;
    } else{
        return ELEVACION;
    }
}

const map<Color,Coordenada>& aed2_Mapa::receptaculos() const {
    return _receptaculos;
}

Coordenada aed2_Mapa::receptaculo(Color c) {
    return _mapa.receptaculos().at(c);
}

// Catedra -> nuestro
Mapa aed2_Mapa::mapa() const {
    return _mapa;
}

// nuestro -> catedra
aed2_Mapa::aed2_Mapa(Mapa m) {
    _mapa = m;
    vector<vector<Color>> casilleros = _mapa.casilleros();
    for(int i = 0; i < casilleros.size(); i++){
        for(int j =0 ; j< casilleros[0].size(); j++){
            Color col = casilleros[i][j];
            Coordenada coord = make_pair(i,j);
            if(!col.empty()) {
                _receptaculos.insert(make_pair(col,coord));
            }
        }
    }
}