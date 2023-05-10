#ifndef PLAYER_H
#define PLAYER_H
#include "mbed.h"
#include "N5110.h"
#include "Utils.h"



class Player
{
public:
    Player();
    void init(int x, int y, SKIN Player_Skin, PLAYER_DIRECTION Player_direction);
    void draw(N5110 &lcd);
    void update(UserInput input);
    Position2D get_pos();
    int get_x();
    int get_y();
    int get_height();
    bool get_jumping();
    bool get_falling();
    bool get_stationary();
    SKIN get_skin();
    PLAYER_DIRECTION get_direction();
 
    //void set_pos(Position 2D player_pos);
    void set_x(int x);
    void set_y(int y);
    void set_jumping(bool jumping);
    void set_falling(bool falling);
    void set_skin(SKIN skin);
    void set_height(int height);

private:

    int _x;
    int _y;
    int _height;
    int _speed;
    bool _jumping;
    bool _falling;
    bool _stationary;
    PLAYER_DIRECTION _Player_Direction;
    SKIN _Player_Skin;
    //Direction player_direction;
};

const int Right1[16][10] = {
    {0,0,1,1,1,0,0,0,0,0},
    {0,0,1,0,1,0,0,0,0,0},
    {0,0,1,1,1,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0},
    {0,1,1,1,1,0,0,0,0,1},
    {1,1,1,1,1,1,0,0,1,0},
    {1,1,1,1,1,1,0,1,0,0},
    {1,0,0,0,1,1,1,0,0,0},
    {1,0,1,0,1,1,0,1,0,0},
    {1,0,0,0,1,0,0,0,0,0},
    {0,1,1,1,1,0,0,0,0,0},
    {0,0,1,1,1,1,0,0,0,0},
    {0,1,1,0,1,1,0,0,0,0},
    {0,1,1,0,0,1,0,0,0,0},
    {0,1,0,0,0,1,0,0,0,0},
    {0,1,1,0,0,1,1,0,0,0}
};
const int Right2[16][17] = {
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,0,1,0,1,0,0},
    {0,1,1,1,0,0,1,1,1,0,1,1,0,0,0,0,0},
    {1,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0},
    {1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,0,0},
    {1,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}
};


const int Left1[16][10] = {
    {0,0,0,0,0,1,1,1,0,0},
    {0,0,0,0,0,1,0,1,0,0},
    {0,0,0,0,0,1,1,1,0,0},
    {0,0,0,0,0,0,1,0,0,0},
    {1,0,0,0,0,1,1,1,1,0},
    {0,1,0,0,1,1,1,1,1,1},
    {0,0,1,0,1,1,1,1,1,1},
    {0,0,0,1,1,1,0,0,0,1},
    {0,0,1,0,1,1,0,1,0,1},
    {0,0,0,0,0,1,0,0,0,1},
    {0,0,0,0,0,1,1,1,1,0},
    {0,0,0,0,1,1,1,1,0,0},
    {0,0,0,0,1,1,0,1,1,0},
    {0,0,0,0,1,0,0,1,1,0},
    {0,0,0,0,1,0,0,0,1,0},
    {0,0,0,1,1,0,0,1,1,0}
};


const int Left2[16][17] = {
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,1,0,1,0,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,0,1,1,0,1,1,1,0,0,1,1,1,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,1},
    {0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,0,1},
    {0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,1},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,0},
    {0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,1,0,1,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0}
};
#endif

