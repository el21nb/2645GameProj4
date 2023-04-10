#include "Ladder.h"


Ladder::Ladder() {}

void Ladder::init(int x, int y){
printf("Floor: Init\n");
_x = x;
_y = y;
}


void Ladder::draw(N5110 &lcd) {
    printf("Floor:Draw\n");
    lcd.drawSprite(_x,_y,16,5,(int *)ladder);    
}

int Ladder::get_y() {return _y;}
int Ladder::get_x() {return _x;}
