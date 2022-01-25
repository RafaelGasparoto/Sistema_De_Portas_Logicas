#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H
#include "porta.h"
#include "led.h"
#include "or.h"
#include "and.h"
#include "not.h"
#include "falso.h"
#include "verdade.h"
#include <QVector>
#include <QMainWindow>
#include <QImage>

using namespace std;

class janelaPrincipal : public QMainWindow {

private:
    Q_OBJECT
    int x, y;
    QMenuBar *bar;
    QMenu *arquivo, *inserir;
    QAction *acaoNovo, *acaoAbrir, *acaoSalvar, *acaoSair;
    QAction *acaoVerdade, *acaoFalso, *acaoLED, *acaoNOT, *acaoAND, *acaoOR;
    bool criaF = false;
    bool criaV = false;
    bool criaL = false;
    bool criaAND = false;
    bool criaOR = false;
    bool criaNOT = false;
    Porta *P1, *P2;
    OR *Or;
    NOT *Not;
    AND *And;
    Verdade *verdade;
    Falso *falso;
    LED *led;
    QVector<Porta *> portas;
    static janelaPrincipal *instancia;

    janelaPrincipal(QWidget *parent = nullptr);
    janelaPrincipal(const janelaPrincipal &ins);
    janelaPrincipal operator=(janelaPrincipal &ins);

    template <class T>
    void criaObjeto(T*, bool*);
    void clicouEmUmObjeto();
    void criaLigacao();
    void barraMenu();
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void limpaMemoria();

public:
    static janelaPrincipal *get_instancia();

private slots:
    void selecionaNovo();
    void selecionaAbrir();
    void selecionaSalvar();
    void selecionaSair();

    void selecionaVerdade();
    void selecionaFalso();
    void selecionaAND();
    void selecionaOR();
    void selecionaNOT();
    void selecionaLED();

};


#endif // JANELAPRINCIPAL_H
