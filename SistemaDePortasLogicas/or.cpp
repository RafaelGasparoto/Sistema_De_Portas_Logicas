#include "or.h"

OR::OR(int x, int y) : Porta(x, y){image.load("C:/Users/rafae/Documents/SistemaDePortasLogicas/imagens/OR.png");}

int OR::get_tipo(){return 4;}

void OR::sinal(){
    sinal_emitido = 0;
    for(int i = 0; i < entrada_i; i++){
        if(entradas[i]->get_sinal() == 3 and sinal_emitido != 1)
            sinal_emitido = 3;
        else if(entradas[i]->get_sinal() == 1)
            sinal_emitido = 1;
    }
}
