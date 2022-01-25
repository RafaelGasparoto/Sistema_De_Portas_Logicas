#include "not.h"

NOT::NOT(int x, int y) : Porta(x, y){image.load("C:/Users/rafae/Documents/SistemaDePortasLogicas/imagens/NOT.png");}

int NOT::get_tipo(){return 5;}

void NOT::sinal(){
    sinal_emitido = 0;
    for(int i = 0; i < entrada_i; i++){
        if(entradas[0]->get_sinal() == 3)
            sinal_emitido = 1;
        else if(entradas[0]->get_sinal() == 1)
            sinal_emitido = 3;
    }
}
