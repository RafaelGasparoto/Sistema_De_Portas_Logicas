#include "janelaprincipal.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QMouseEvent>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

int Porta::qtObj;

janelaPrincipal::janelaPrincipal(QWidget *parent) : QMainWindow(parent) {
    barraMenu();
    setFixedSize(900, 900);
    P1 = P2 = NULL;
    x = y = 0;
}

janelaPrincipal* janelaPrincipal::get_instancia(){
    if(instancia == NULL)
        instancia = new janelaPrincipal();
    return instancia;
}

void janelaPrincipal::barraMenu(){

    bar = new QMenuBar(this);
    arquivo = new QMenu("Arquivo",this);
    inserir = new QMenu("Inserir",this);

    bar->setFixedSize(900,25);
    bar->addMenu(arquivo);
    bar->addMenu(inserir);


    acaoNovo = new QAction("Novo", this);
    acaoAbrir = new QAction("Abrir", this);
    acaoSalvar = new QAction("Salvar", this);
    acaoSair = new QAction("Sair", this);

    arquivo->addAction(acaoNovo);
    arquivo->addAction(acaoAbrir);
    arquivo->addAction(acaoSalvar);
    arquivo->addAction(acaoSair);

    connect(acaoNovo, SIGNAL(triggered(bool)), this, SLOT(selecionaNovo()));
    connect(acaoSalvar, SIGNAL(triggered(bool)), this, SLOT(selecionaSalvar()));
    connect(acaoAbrir, SIGNAL(triggered(bool)), this, SLOT(selecionaAbrir()));
    connect(acaoSair, SIGNAL(triggered(bool)), this, SLOT(selecionaSair()));

    acaoNovo->setShortcut(tr("Ctrl+N"));
    acaoAbrir->setShortcut(tr("Ctrl+O"));
    acaoSalvar->setShortcut(tr("Ctrl+S"));
    acaoSair->setShortcut(tr("Alt+F4"));

    acaoVerdade = new QAction("Verdadeiro", this);
    acaoFalso = new QAction("Falso", this);
    acaoLED = new QAction("LED", this);
    acaoNOT = new QAction("NOT", this);
    acaoAND = new QAction("AND", this);
    acaoOR = new QAction("OR", this);

    inserir->addAction(acaoVerdade);
    inserir->addAction(acaoFalso);
    inserir->addAction(acaoLED);
    inserir->addSeparator();
    inserir->addAction(acaoNOT);
    inserir->addAction(acaoAND);
    inserir->addAction(acaoOR);

    acaoVerdade->setShortcut(tr("F5"));
    acaoFalso->setShortcut(tr("F6"));
    acaoLED->setShortcut(tr("F7"));
    acaoNOT->setShortcut(tr("F9"));
    acaoAND->setShortcut(tr("F10"));
    acaoOR->setShortcut(tr("F11"));

    connect(acaoVerdade, SIGNAL(triggered(bool)), this, SLOT(selecionaVerdade()));
    connect(acaoLED, SIGNAL(triggered(bool)), this, SLOT(selecionaLED()));
    connect(acaoFalso, SIGNAL(triggered(bool)), this, SLOT(selecionaFalso()));
    connect(acaoNOT, SIGNAL(triggered(bool)), this, SLOT(selecionaNOT()));
    connect(acaoOR, SIGNAL(triggered(bool)), this, SLOT(selecionaOR()));
    connect(acaoAND, SIGNAL(triggered(bool)), this, SLOT(selecionaAND()));
}

void janelaPrincipal::limpaMemoria(){
    int qtd = Porta::get_qtd_obj();

    for(int i = 0; i < qtd; i++){
        portas[i]->remover_porta();
        delete portas[i];
    }
    portas.clear();
    P1 = P2 = NULL;

    update();
}

void janelaPrincipal::selecionaNovo(){
    limpaMemoria();
}

void janelaPrincipal::selecionaSair(){
    limpaMemoria();

    delete bar;
    delete arquivo;
    delete inserir;
    delete acaoNovo;
    delete acaoAbrir;
    delete acaoSalvar;
    delete acaoSair;
    delete acaoVerdade;
    delete acaoFalso;
    delete acaoLED;
    delete acaoNOT;
    delete acaoAND;
    delete acaoOR;

    close();
}

void janelaPrincipal::selecionaAbrir(){
    QString nomeArquivo = QFileDialog::getOpenFileName(0,tr("carregar"));

    if(nomeArquivo.isEmpty()){
        return;
    }else{
        QFile arquivo(nomeArquivo);
        if(!arquivo.open(QIODevice::ReadOnly)){
            QMessageBox::information(this, tr("não foi possivel abrir o arquivo"), arquivo.errorString());
            return;
        }
        QDataStream in(&arquivo);

        in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        int qtd, tipo, qtd_entrada, qtd_saida, id_saida, id_entrada;

        limpaMemoria();

        in >> qtd;

        for(int i = 0; i < qtd; i++){
            in >> x >> y >> tipo;

            if(tipo == 1)
               criaObjeto(falso, &criaF);

            if(tipo == 2)
                criaObjeto(verdade, &criaV);

            if(tipo == 3)
                criaObjeto(And, &criaAND);

            if(tipo == 4)
                criaObjeto(Or, &criaOR);

            if(tipo == 5)
                criaObjeto(Not, &criaNOT);

            if(tipo == 6)
                criaObjeto(led, &criaL);
        }

        for(int i = 0; i < qtd; i++){
            in >> qtd_entrada;
            for(int j = 0; j < qtd_entrada; j++){
                in >> id_entrada;
                for(int l = 0; l < qtd; l++){
                   if(id_entrada == portas[l]->get_id()){
                       P2=portas[i];
                       P1=portas[l];
                       P2->set_entrada(P1);
                   }
               }
            }

            in >> qtd_saida;
            for(int j = 0; j < qtd_saida; j++){
                in >> id_saida;
                for(int l = 0; l < qtd; l++){
                    if(id_saida == portas[l]->get_id()){
                        P1=portas[i];
                        P2=portas[l];
                        P1->set_saida(P2);
                    }
                }
            }
        }

        P1 = P2 = NULL;

        arquivo.close();
    }
}

void janelaPrincipal::selecionaSalvar(){
    QString nomeArquivo = QFileDialog::getSaveFileName(this, tr("salvando"));
    if(nomeArquivo.isEmpty()){
        return;
    }else{
        QFile arquivo(nomeArquivo);
        if(!arquivo.open(QIODevice::WriteOnly)){
            QMessageBox::information(this, tr("não foi possivel salvar"), arquivo.errorString());
            return;
        }
        QDataStream out(&arquivo);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        out << Porta::get_qtd_obj();

        for(int i = 0; i < Porta::get_qtd_obj(); i++){
            out << portas[i]->get_x();
            out << portas[i]->get_y();
            out << portas[i]->get_tipo();
        }

        for(int i = 0; i < Porta::get_qtd_obj(); i++){
            out << portas[i]->get_entrada_i();
            for(int j = 0; j < portas[i]->get_entrada_i(); j++)
                out << portas[i]->get_id_entrada(j);

            out << portas[i]->get_saida_i();
            for(int j = 0; j < portas[i]->get_saida_i(); j++){
                out << portas[i]->get_id_saida(j);
            }
        }

        arquivo.close();
    }
}

template <class T>
void janelaPrincipal::criaObjeto(T *tipo_objeto, bool *permissao){
    tipo_objeto = new T(x, y);
    portas.push_back(tipo_objeto);
    *permissao = false;
}

void janelaPrincipal::selecionaVerdade(){criaV = true;}
void janelaPrincipal::selecionaFalso(){criaF = true;}
void janelaPrincipal::selecionaAND(){criaAND = true;}
void janelaPrincipal::selecionaOR(){criaOR = true;}
void janelaPrincipal::selecionaNOT(){criaNOT = true;}
void janelaPrincipal::selecionaLED(){criaL = true;}

void janelaPrincipal::mousePressEvent(QMouseEvent *event){
    x = event->x();
    y = event->y();
    if(Porta::get_qtd_obj() > 0)
        clicouEmUmObjeto();

    if(criaF)
        criaObjeto(falso, &criaF);

    if(criaV)
        criaObjeto(verdade, &criaV);

    if(criaAND)
        criaObjeto(And, &criaAND);

    if(criaOR)
        criaObjeto(Or, &criaOR);

    if(criaNOT)
        criaObjeto(Not, &criaNOT);

    if(criaL)
        criaObjeto(led, &criaL);

    update();
}

void janelaPrincipal::clicouEmUmObjeto(){
    int flag = 0;
    for(int i = 0; i < Porta::get_qtd_obj(); i++){
        if((portas[i]->get_x() - 20 <= x and portas[i]->get_x() + 20>= x) and (portas[i]->get_y() - 20 <= y and portas[i]->get_y() + 20 >= y)){
            if(P1 == NULL)
                P1 = portas[i];
            else
                P2 = portas[i];

            if(portas[i]->get_click() == true){
                portas[i]->remover_porta();
                delete portas[i];
                portas.remove(i);

                P1 = P2 = NULL;
            }else{
                portas[i]->set_click(true);
                flag = 1;
            }
        }else{
            portas[i]->set_click(false);
        }
    }

    if(flag == 0)
        P1 = P2 = NULL;
    if((P1 != NULL) and (P2 != NULL)){
        criaLigacao();

        P2->set_click(false);
        P1->set_click(false);
        P1 = P2 = NULL;

    }
}

void janelaPrincipal::criaLigacao(){
    try {
        P1->teste(P2);
    }catch (int erro){
        if(erro == 1)
            QMessageBox::information(this, tr("ERROR"), tr("LED não deve ter saída!"));
        if(erro == 2)
            QMessageBox::information(this, tr("ERROR"), tr("Essa porta não suporta entradas"));
        if(erro == 3)
            QMessageBox::information(this, tr("ERROR"), tr("LED deve ter no máximo uma entrada!"));
        if(erro == 4)
            QMessageBox::information(this, tr("ERROR"), tr("Essa porta deve ter no máximo uma entrada"));
    }
}

void janelaPrincipal::paintEvent(QPaintEvent *event){

    QPainter *painter = new QPainter(this);

    for(int k = 0; k < Porta::get_qtd_obj(); k++){
        for(int i = 0; i < portas[k]->get_entrada_i(); i++){
            if(portas[k]->get_sinal() == 1){
                QPen pen(Qt::green);
                QBrush br(Qt::green);
                painter->setPen(pen);
                painter->setBrush(br);
                painter->drawRect(portas[k]->get_target());
             }
             if(portas[k]->get_sinal() == 3){
                QPen pen(Qt::red);
                QBrush br(Qt::red);
                painter->setPen(pen);
                painter->setBrush(br);
                painter->drawRect(portas[k]->get_target());
             }
             if(portas[k]->get_entradas(i)->get_sinal() == 1){
                QPen pen(Qt::green);
                painter->setPen(pen);
             }else if(portas[k]->get_entradas(i)->get_sinal() == 3){
                 QPen pen(Qt::red);
                 painter->setPen(pen);
             }else{
                 painter->setBrush(Qt::transparent);
                 painter->setPen(Qt::black);
             }
             painter->drawLine(portas[k]->get_ponto(), portas[k]->get_entradas(i)->get_ponto());
        }

        painter->drawImage(portas[k]->get_target(), portas[k]->get_image());

        if(portas[k]->get_click() == true){
            painter->setBrush(Qt::transparent);
            painter->setPen(Qt::black);
            painter->drawRect(portas[k]->get_target());
        }
    }
    delete painter;
}
