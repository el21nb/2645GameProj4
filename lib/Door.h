#ifndef DOOR_H
#define DOOR_H
#include "mbed.h"
#include "N5110.h"
#include "Utils.h"

class Door
{
public:
    Door();
    void init(int x, int y, bool exit, SKIN skin);
    void draw(N5110 &lcd);
    SKIN get_skin();
    int get_y();
    int get_x();
    bool get_exit();


private:
    SKIN _skin;
    int _y;
    int _x;
    bool _exit;

};
//door skins:
const int DoorLeft[17][15] = {

  {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},      
  {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
  {1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0},    
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1}, 
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1}, 
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1}

};

const int DoorRight[17][15] = {
  {0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0},
  {0,  0,  1,  1,  1,  0,  1,  1,  1,  1,  1,  0,  0,  0,  0}, 
  {0,  1,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  0,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}, 
  {1,  0,  1,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1}
};

#endif
