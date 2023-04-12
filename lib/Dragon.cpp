#include "Dragon.h"

Dragon::Dragon() { }


void Dragon::init(int x, int y) {
    printf("Dragon: Init\n");
    _skin = LEFT1;
    _x = x;
    _y = y;
    _fire_x=x;
}

void Dragon::draw(N5110 &lcd) {
    printf("Dragon: Draw\n");
    if(_skin==LEFT1){
    lcd.drawSprite(_x,_y,21,32,(int *)_dragon_L1);
    }
    else if(_skin==LEFT2){
    lcd.drawSprite(_x,_y,21,32,(int *)_dragon_L2);
    }
    lcd.drawRect(_fire_x,_y+14,2,2,FILL_BLACK);
}

void Dragon::update(){
    _fire_x-=3;
    if(_fire_x<=0){
        _fire_x=_x;
    }
    if(_skin==LEFT1){
        _skin=LEFT2;
    }
    else(_skin=LEFT1);
}


Position2D Dragon::get_pos(){ return {_x,_y}; }


int Dragon::get_x(){return _x;}
int Dragon::get_y(){return _y;}
int Dragon::get_fire_x(){return _fire_x;}


void Dragon::set_x(int x){_x=x;}
void Dragon::set_y(int y){_y=y;}


   
