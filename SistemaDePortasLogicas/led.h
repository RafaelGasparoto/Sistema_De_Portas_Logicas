#ifndef LED_H
#define LED_H
#include "porta.h"

class LED : public Porta{
    void sinal();
public:
    LED(int x, int y);
    int get_tipo();
};

#endif // LED_H
