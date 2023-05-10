#ifndef WYRM_H
#define WYRM_H
#include "mbed.h"
#include "N5110.h"
#include "Utils.h"

/*enum SKIN{
    LEFT1,
    LEFT2,
    RIGHT1,
    RIGHT2
};


enum PLAYER_DIRECTION{
    LEFT,
    RIGHT
};*/

class Wyrm
{
public:
    Wyrm();
    void init(int x, int y, SKIN Wyrm_Skin, PLAYER_DIRECTION Wyrm_Direction, int limit);
    void draw(N5110 &lcd);
    void update();
    Position2D get_pos();
    int get_x();
    int get_y();
    SKIN get_skin();
    PLAYER_DIRECTION get_direction();
 
    //void set_pos(Position 2D player_pos);
    void set_x(int x);
    void set_y(int y);
    void set_skin(SKIN skin);

private:
    int _limit;
    int _steps;
    int _x;
    int _y;
    PLAYER_DIRECTION _direction;
    SKIN _skin;
    //Direction player_direction;
};

const int WyrmRight1[4][11] = {
    {0,0,0,1,1,0,0,0,0,0,0},
    {0,0,1,1,1,1,0,0,1,1,1},
    {0,1,1,0,0,1,1,0,1,1,1},
    {1,1,0,0,0,0,1,1,1,0,0},

};
const int WyrmRight2[4][11] = {
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,1,1,1},
    {0,0,1,1,1,1,1,0,1,1,1},
    {1,1,1,0,0,0,1,1,1,0,0},

};
const int WyrmRight3[4][11] = {
    {0,0,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,1,1,0,0,0,0,0},
    {1,1,0,1,1,1,1,0,1,1,1},
    {0,1,1,1,0,0,1,1,1,1,1},

};
const int WyrmLeft1[4][11] = {
    {0,0,0,0,0,0,1,1,0,0,0},
    {1,1,1,0,0,1,1,1,1,0,0},
    {1,1,1,0,1,1,0,0,1,1,0},
    {0,0,1,1,1,0,0,0,0,1,1},

};
const int WyrmLeft2[4][11] = {
    {0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,0,0,1,1,0,0,0},
    {1,1,1,0,1,1,1,1,1,0,0},
    {0,0,1,1,1,0,0,0,1,1,1},

};
const int WyrmLeft3[4][11] = {
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,0,1},
    {1,1,1,0,1,1,1,1,0,1,1},
    {1,1,1,1,1,0,0,1,1,1,0},

};
#endif


