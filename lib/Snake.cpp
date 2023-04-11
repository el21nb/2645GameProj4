#include "Snake.h"

Snake::Snake() { }


void Snake::init(int x, int y, SKIN Snake_Skin, PLAYER_DIRECTION Snake_Direction, int limit) {
    printf("Snake: Init\n");
    _x = x;
    _y = y;
    _limit = limit;
    _steps = 0;
    _direction = Snake_Direction;
    _skin = Snake_Skin;
}

void Snake::draw(N5110 &lcd) {
    printf("Snake: Draw\n");
    if(_skin == RIGHT1){
        lcd.drawSprite(_x,_y,4,11,(int *)SnakeRight1);      
    }
    else if(_skin == LEFT1){
        lcd.drawSprite(_x,_y,4,11,(int *)SnakeLeft1);      
    }
    else if(_skin == RIGHT2){
        lcd.drawSprite(_x,_y,4,11,(int *)SnakeRight2);      
    }
    else if(_skin == LEFT2){
        lcd.drawSprite(_x,_y,4,11,(int *)SnakeLeft2);      
    }
    else if(_skin == RIGHT3){
        lcd.drawSprite(_x,_y,4,11,(int *)SnakeRight3);      
    }
    else if(_skin == LEFT3){
        lcd.drawSprite(_x,_y,4,11,(int *)SnakeLeft3);      
    }
}


void Snake::update() {
    printf("snake: update");
    if(_steps<=_limit){
        _steps++;
        if(_direction==RIGHT){
            _x+=2;
            if(_skin==RIGHT1){_skin=RIGHT2;}
            else if(_skin==RIGHT2){_skin=RIGHT3;}
            else if(_skin==RIGHT3){_skin=RIGHT1;}
        }
        else if(_direction==LEFT){
            _x-=2;
            if(_skin==LEFT1){_skin=LEFT2;}
            else if(_skin==LEFT2){_skin=LEFT3;}
            else if(_skin==LEFT3){_skin=LEFT1;}
        }
    }
    else if(_steps>_limit){
        if(_direction==LEFT){
            _direction=RIGHT;
            _skin=RIGHT1;
        }
        else if(_direction==RIGHT){
            _direction=LEFT;
            _skin=LEFT1;
        }
        _steps=0;
    }
    
}


Position2D Snake::get_pos() { return {_x,_y}; }


int Snake::get_x(){return _x;}
int Snake::get_y(){return _y;}





SKIN Snake::get_skin(){return _skin;}
PLAYER_DIRECTION Snake::get_direction(){return _direction;}


    //void set_pos(Position 2D player_pos){_}
    void Snake::set_x(int x){_x=x;}
    void Snake::set_y(int y){_y=y;}

    void Snake::set_skin(SKIN skin){_skin=skin;};


   


