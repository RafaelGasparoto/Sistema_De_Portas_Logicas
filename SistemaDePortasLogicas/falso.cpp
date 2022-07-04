#include "falso.h"

Falso::Falso(int x, int y) : Porta(x, y){
    sinal_emitido = 3;
    image.load(":/images/imagens/falso.png");
}

int Falso::get_tipo(){return 1;}
