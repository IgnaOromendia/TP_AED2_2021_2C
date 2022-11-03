#ifndef OBJETIVO_H
#define OBJETIVO_H

#include "Tipos.h"

using namespace std;

class Objetivo {
  public:
    
    Objetivo();

    Objetivo(const Color& objeto, const Color& receptaculo);

    const Color& objeto() const;

    const Color& receptaculo() const;

    bool operator==(Objetivo o) const;

    bool operator<(Objetivo o) const;
  
  private:
    Color _colorObjeto;
    Color _colorDestino;
};

#endif
