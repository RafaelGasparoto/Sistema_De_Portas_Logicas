#ifndef FALSO_H
#define FALSO_H
#include "porta.h"

class Falso : public Porta{
public:
    Falso(int, int);
    int get_tipo();
};

#endif // FALSO_H
