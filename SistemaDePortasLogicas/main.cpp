#include "janelaprincipal.h"
#include <QApplication>

janelaPrincipal *janelaPrincipal::instancia = NULL;

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    janelaPrincipal *janela = janelaPrincipal::get_instancia();
    janela->show();
    return app.exec();
}
