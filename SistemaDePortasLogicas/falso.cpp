#include "falso.h"

Falso::Falso(int x, int y) : Porta(x, y){
    sinal_emitido = 3;
    image.load("C:/Users/rafae/Documents/SistemaDePortasLogicas/imagens/falso.png");
}

int Falso::get_tipo(){return 1;}
