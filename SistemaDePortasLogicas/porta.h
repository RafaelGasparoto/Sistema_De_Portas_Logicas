#ifndef CLASSES_H
#define CLASSES_H
#include <QPoint>
#include <QImage>
#include <QVector>

class Porta{
private:
    int x, y;
    bool click;
    QRect target;
    int id;
    QVector<int> id_saida;
    QVector<int> id_entrada;
    static int qtObj;

protected:
    int saida_i;
    int entrada_i;
    QImage image;
    int sinal_emitido;
    QVector<Porta *> saidas;
    QVector<Porta *> entradas;

public:
    Porta(int , int);
    virtual ~Porta();

    void teste(Porta *);
    virtual int get_tipo() = 0;
    void remover_porta();

    void set_entrada(Porta *);
    void set_saida(Porta *);
    void set_click(bool);

    int get_id();
    static int get_qtd_obj();
    int get_id_saida(int);
    int get_id_entrada(int);
    int get_entrada_i();
    int get_saida_i();
    Porta* get_entradas(int);
    int get_x();
    int get_y();
    bool get_click();
    int get_sinal();
    QPoint get_ponto();
    QRect get_target();
    QImage get_image();

private:
    void sinais();
    void insere_ou_remove_ligacao(Porta *, Porta *);

protected:
    virtual void sinal();
};

#endif // CLASSES_H
