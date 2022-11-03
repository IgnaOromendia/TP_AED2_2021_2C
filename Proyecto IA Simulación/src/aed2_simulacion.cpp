#include "aed2_simulacion.h"

aed2_Simulacion::aed2_Simulacion(const aed2_Mapa &mapa, const map<Color, Coordenada> &objetos, Coordenada inicio) {
    _sim = Simulacion(mapa.mapa(),inicio,objetos);
    for(Objetivo o: _sim.objetivosDisponibles()){
        _listObjetivos.push_back(o);
    }
    set<Color> colObjetos = _sim.coloresOjetos();
    for(Color c: colObjetos) {
        _posObjetos.insert(make_pair(c,_sim.posObjeto(c)));
    }
}

const aed2_Mapa aed2_Simulacion::mapa() const{
    return _sim.mapa();
}

void aed2_Simulacion::mover(Direccion d) {
    _sim.mover(d);
    _listObjetivos.clear();
    for(Objetivo o: _sim.objetivosDisponibles()){
        _listObjetivos.push_back(o);
    }
    set<Color> colObjetos = _sim.coloresOjetos();
    for(Color c: colObjetos) {
        _posObjetos[c] = _sim.posObjeto(c);
    }
}

Coordenada aed2_Simulacion::posAgente() const{
    return _sim.posJugador();
}

void aed2_Simulacion::agregarObjetivo(Objetivo o) {
    _sim.agObjetivo(o);
    _listObjetivos.clear();
    for(Objetivo o: _sim.objetivosDisponibles()){
        _listObjetivos.push_back(o);
    }
}

const map<Color, Coordenada>& aed2_Simulacion::posObjetos() const{
    return _posObjetos;
}

const list<Objetivo>& aed2_Simulacion::objetivosDisponibles() const {
    return _listObjetivos;
}

Nat aed2_Simulacion::movimientos() const{
    return _sim.cantMovimientos();
}

Nat aed2_Simulacion::objetivosResueltos() const {
    return _sim.objetivosRealizados();
}