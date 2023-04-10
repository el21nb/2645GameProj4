#include "Door.h"


Door::Door() {}

void Door::init(int x, int y, bool exit, SKIN skin){
printf("Door: Init\n");
_x = x;
_y = y;
_exit = exit;
_skin = skin;
}


void Door::draw(N5110 &lcd, SKIN skin) {
    printf("Door:Draw\n");
    if(_skin == LEFT1){
    lcd.drawSprite(_x,_y,17,15,(int *)DoorLeft);
    }
    else if(_skin == RIGHT1){
        lcd.drawSprite(_x,_y,17,15,(int *)DoorRight);
    }
}

int Door::get_y() {return _y;}
int Door::get_x() {return _x;}
bool Door::get_exit(){return _exit;}
SKIN Door::get_skin(){return _skin;}
