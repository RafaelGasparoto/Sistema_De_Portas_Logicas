#ifndef AND_H
#define AND_H
#include "porta.h"

class AND : public Porta{
    void sinal();
public:
    AND(int, int);
    int get_tipo();
};

#endif // AND_H
