#include "verdade.h"

Verdade::Verdade(int x, int y) : Porta(x, y){
    sinal_emitido = 1;
    image.load(":/images/imagens/verdade.png");
}

int Verdade::get_tipo(){return 2;}
