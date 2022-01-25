#include "porta.h"

Porta::Porta(int x, int y){
    this->x = x;
    this->y = y;
    target.setRect(x-20, y-20, 40, 40);
    id = qtObj;
    click = false;
    sinal_emitido = 0;
    entrada_i = 0;
    saida_i = 0;
    qtObj++;
}

Porta::~Porta(){
    qtObj--;
}

int Porta::get_entrada_i(){
    return entrada_i;
}

int Porta::get_saida_i(){
    return saida_i;
}

int Porta::get_id_saida(int j){
    return id_saida[j];
}

int Porta::get_id_entrada(int j){
    return id_entrada[j];
}

Porta *Porta::get_entradas(int i){
    return entradas[i];
}

void Porta::teste(Porta *P2){

    if(this->get_tipo() == 6 and !P2->saidas.contains(this))
        throw 1;
    if((P2->get_tipo() == 1 or P2->get_tipo() == 2) and !P2->saidas.contains(this))
        throw 2;
    if(P2->get_tipo() == 6 and !P2->entradas.isEmpty() and !P2->entradas.contains(this))
        throw 3;
    if(P2->get_tipo() == 5 and !P2->entradas.isEmpty() and !P2->entradas.contains(this) and !P2->saidas.contains(this))
        throw 4;
    insere_ou_remove_ligacao(this, P2);
}

void Porta::insere_ou_remove_ligacao(Porta *P1, Porta *P2){
    if(P1->entradas.contains(P2)){
        P1->entradas.removeOne(P2);
        P2->saidas.removeOne(P1);

        P2->saida_i--;
        P1->entrada_i--;

        P1->sinal();
        P1->sinais();
    }else if(P1->saidas.contains(P2)){
        P2->entradas.removeOne(P1);
        P1->saidas.removeOne(P2);

        P1->saida_i--;
        P2->entrada_i--;

        P2->sinal();
        P2->sinais();
    }
    else{
        P2->set_entrada(P1);
        P1->set_saida(P2);
    }
}

void Porta::set_entrada(Porta* P1){
    this->id_entrada.push_back(P1->id);
    this->entradas.push_back(P1);
    this->entrada_i++;
    this->sinal();
    this->sinais();
}

void Porta::set_saida(Porta* P2){
    this->id_saida.push_back(P2->id);
    this->saidas.push_back(P2);
    this->saida_i++;
    this->sinal();
    this->sinais();
}

void Porta::sinais(){
    for(int i = 0; i < saida_i; i++){
        saidas[i]->sinal();
        saidas[i]->sinais();
    }

}

void Porta::remover_porta(){
    for(int i = 0; i < entrada_i; i++){
           for(int k = 0; k < entradas[i]->saida_i; k++){
               if(entradas[i]->saidas[k] == this){
                   entradas[i]->saidas.remove(k);
                   entradas[i]->saida_i--;
                   entradas[i]->sinal();
               }
           }
     }

    for(int i = 0; i < saida_i; i++){
          for(int k = 0; k < saidas[i]->entrada_i; k++){
              if(saidas[i]->entradas[k] == this){
                  saidas[i]->entradas.remove(k);
                  saidas[i]->entrada_i--;
                  saidas[i]->sinal();
                  saidas[i]->sinais();
              }
          }
    }
}

int Porta::get_id(){
    return id;
}
void Porta::sinal(){};

int Porta::get_qtd_obj(){
    return qtObj;
}

QPoint Porta::get_ponto(){
    QPoint ponto(x, y);
    return ponto;
}

int Porta::get_x(){
    return x;
}

int Porta::get_y(){
    return y;
}

bool Porta::get_click(){
    return click;
}

void Porta::set_click(bool st){
    click = st;
}

QRect Porta::get_target(){
    return target;
}

QImage Porta::get_image(){
    return image;
}

int Porta::get_sinal(){
    return sinal_emitido;
}
