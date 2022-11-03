//
// Created by Igna on 01/11/2021.
//

#include "Objetivo.h"

Objetivo::Objetivo(): _colorObjeto(""), _colorDestino("") {};

Objetivo::Objetivo(const Color &objeto, const Color &receptaculo): _colorDestino(receptaculo), _colorObjeto(objeto) {}

const Color& Objetivo::objeto() const {
    return _colorObjeto;
}

const Color& Objetivo::receptaculo() const {
    return _colorDestino;
}

bool Objetivo::operator==(Objetivo o) const {
    return _colorObjeto == o.objeto() && _colorDestino == o.receptaculo();
}

bool Objetivo::operator<(Objetivo o) const {
    return _colorDestino + _colorObjeto < o.objeto() + o.receptaculo();
}





