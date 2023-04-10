
#include "Floor.h"


Floor::Floor() {}


void Floor::init(int x, int y, int width){
printf("Floor: Init\n");
_x = x;
_y = y;
_width = width;
}


void Floor::draw(N5110 &lcd) {
    printf("Floor:Draw\n");
    lcd.drawRect(_x,_y,_width,1,FILL_BLACK);    
}


int Floor::get_y() {return _y;}
int Floor::get_x() {return _x;}
int Floor::get_width() {return _width;}
