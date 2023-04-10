#ifndef FLOOR_H
#define FLOOR_H
#include "mbed.h"
#include "N5110.h"
#include "Utils.h"


class Floor
{
public:
    Floor();
    void init(int x,int y,int width);
    void draw(N5110 &lcd);
    int get_y();
    int get_x();
    int get_width();


private:
    int _y;
    int _x;
    int _width;
};
#endif
