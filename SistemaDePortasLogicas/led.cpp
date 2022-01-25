#include "led.h"

LED::LED(int x, int y) : Porta(x, y){image.load("C:/Users/rafae/Documents/SistemaDePortasLogicas/imagens/led.png");}

int LED::get_tipo(){return 6;}

void LED::sinal(){
   if(entrada_i == 0)
       sinal_emitido = 0;
   else
       sinal_emitido = entradas[0]->get_sinal();
}
