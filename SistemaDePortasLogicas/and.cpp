#include "and.h"

AND::AND(int x, int y) : Porta(x, y){image.load(":/images/imagens/AND.png");}

int AND::get_tipo(){return 3;}

void AND::sinal(){
    sinal_emitido = 0;
    for(int i = 0; i < entrada_i; i++){
        if(entradas[i]->get_sinal() == 3)
            sinal_emitido = 3;
        if(get_sinal() == 0 and entradas[i]->get_sinal() == 1)
            sinal_emitido = 1;
    }
}
