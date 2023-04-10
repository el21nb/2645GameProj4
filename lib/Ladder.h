
#ifndef LADDER_H
#define LADDER_H

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"

class Ladder
{
public:
    Ladder();
    void init(int x,int y);
    void draw(N5110 &lcd);
    int get_y();
    int get_x();


private:
    int _y;
    int _x;
};
const int ladder[16][5] = {
    {1,0,0,0,1},
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
};
#endif
