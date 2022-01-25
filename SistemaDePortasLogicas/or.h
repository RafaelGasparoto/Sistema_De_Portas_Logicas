#ifndef OR_H
#define OR_H
#include "porta.h"

class OR : public Porta{
    void sinal();
public:
    OR(int x, int y);
    int get_tipo();
};

#endif // OR_H
