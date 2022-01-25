#ifndef NOT_H
#define NOT_H
#include "porta.h"

class NOT : public Porta{
    void sinal();
public:
    NOT(int, int);
    int get_tipo();
};

#endif // NOT_H
