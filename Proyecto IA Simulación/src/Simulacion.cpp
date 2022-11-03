//
// Created by Igna on 02/11/2021.
//

#include "Simulacion.h"

using namespace std;

Simulacion::Simulacion() {
    _mapa = Mapa();
    _posAgente = make_pair(-1,-1);
    _movimientos = 0;
    _objCompletados = 0;
}

Simulacion::Simulacion(Mapa m, Coordenada c, map<Color,Coordenada> obj) {
    _mapa = m;
    _posAgente = c;
    _movimientos = 0;
    _objCompletados = 0;

    for(int i = 0; i < m.alto(); i++) {
        vector<Color> v1(m.ancho(),"");
        _objetosXpos.push_back(v1);
    }

    for(pair<Color,Coordenada> o: obj) {
        _objetos.insert(o);
        _objetosXpos[o.second.first][o.second.second] = o.first;
        string_map<set<Objetivo>::iterator> vacio;
        _objetivosXcolor.insert(make_pair(o.first,vacio));
    }
}

Simulacion::~Simulacion() {
    // Ver como destruir el new de coloresObjetos
}

const Mapa& Simulacion::mapa() const{
    return _mapa;
}

const Coordenada& Simulacion::posJugador() const {
    return _posAgente;
}

const Nat& Simulacion::cantMovimientos() const {
    return _movimientos;
}

const set<Objetivo>& Simulacion::objetivosDisponibles() const {
    return _objDisponibles;
}

const Nat Simulacion::objetivosRealizados() const{
    return _objCompletados;
}

const set<Color>& Simulacion::coloresOjetos() {
    for(int i = 0; i < _mapa.ancho();i++) {
        for(int j = 0; j < _mapa.alto();j++) {
            if (!_objetosXpos[i][j].empty()) {
                _colObjetos.insert(_objetosXpos[i][j]);
            }
        }
    }

    return _colObjetos;
}

const Coordenada& Simulacion::posObjeto(Color c) const {
    return _objetos.at(c);
}

bool Simulacion::hayMovimiento(Coordenada c, Direccion d, const Mapa m) {
    bool result = true;
    if (_mapa.enRango(siguientePosicion(c,d))) {
        if ((_mapa.esPared(siguientePosicion(c,d)) && _mapa.esPiso(c))) {
            result = false;
        }
    } else {
        result = false;
        _movimientos--;
    }
    return result;
}

bool Simulacion::mover(Direccion d) {
    bool result = false;
    Coordenada posSigAgente = siguientePosicion(_posAgente,d);
    Coordenada posSigObjeto = siguientePosicion(posSigAgente,d);

    _movimientos++;

    if (hayMovimiento(_posAgente,d,_mapa)){
        if (!hayObjeto(posSigAgente)) {
            _posAgente = posSigAgente;
            result = true;
        } else if (_mapa.enRango(posSigObjeto) && hayMovimiento(posSigAgente,d,_mapa) && !hayObjeto(posSigObjeto) ) {
            // Actualizar la pos del objeto
            Color objeto = _objetosXpos[posSigAgente.first][posSigAgente.second];
            _objetosXpos[posSigAgente.first][posSigAgente.second] = "";
            _objetosXpos[posSigObjeto.first][posSigObjeto.second] = objeto;
            _objetos.insert(make_pair(objeto,posSigObjeto));

            // Chequear si se compleot un objetivo
            Color colorPos = _mapa.casilleros()[posSigObjeto.first][posSigObjeto.second];
            if (_objetivosXcolor.at(objeto).count(colorPos) == 1) {
                set<Objetivo>::iterator itObjetivo = _objetivosXcolor.at(objeto).at(colorPos);
                _objDisponibles.erase(itObjetivo);
                _objCompletados++;
                _objetivosXcolor.at(objeto).erase(colorPos);
            }
            _posAgente = posSigAgente;
            result = true;
        }
    }
    return result;
}

void Simulacion::agObjetivo(const Objetivo& o){
    set<Objetivo>::iterator it = _objDisponibles.insert(o).first;
    _objetivosXcolor.at(o.objeto()).insert(make_pair(o.receptaculo(),it));
    filtrarRealizados(_objDisponibles);
}

Coordenada Simulacion::siguientePosicion(Coordenada c, Direccion d) {
    Coordenada res = c;
    if (d == DERECHA){
        res.first++;
    }else if(d == IZQUIERDA){
        res.first--;
    }else if(d == ARRIBA){
        res.second++;
    }else if(d == ABAJO){
        res.second--;
    }
    return res;
}

void Simulacion::filtrarRealizados(set<Objetivo>& co){
    list<set<Objetivo>::iterator> aBorrar;

    for(Objetivo o: co){
        Coordenada posObj = posObjeto(o.objeto());
        if((_mapa.casilleros()[posObj.first][posObj.second]) == o.receptaculo()) {
            set<Objetivo>::iterator it = _objetivosXcolor.at(o.objeto()).at(o.receptaculo());
            _objetivosXcolor.at(o.objeto()).erase(o.receptaculo());
            aBorrar.push_back(it);
           _objCompletados++;
        }
    }

    for(set<Objetivo>::iterator o: aBorrar) {
        co.erase(o);
    }
}

bool Simulacion::hayObjeto(Coordenada c) {
    return c != _posAgente && !_objetosXpos[c.first][c.second].empty();
}

bool Simulacion::hayAlgunObjeto(Coordenada cor, set<Color> c) {
    bool res = false;
    for(Color col:c){
        if(posObjeto(col) == cor){
            res = true;
        }
    }
    return res;
}









