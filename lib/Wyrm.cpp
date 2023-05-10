#include "Wyrm.h"

Wyrm::Wyrm() { }


void Wyrm::init(int x, int y, SKIN Wyrm_Skin, PLAYER_DIRECTION Wyrm_Direction, int limit) {
    //initialise wyrm conditions
    printf("Wyrm: Init\n");
    _x = x;
    _y = y;
    _limit = limit;
    _steps = 0;
    _direction = Wyrm_Direction;
    _skin = Wyrm_Skin;
}

void Wyrm::draw(N5110 &lcd) { //draw wyrm
    if(_skin == RIGHT1){ 
        lcd.drawSprite(_x,_y,4,11,(int *)WyrmRight1);      
    }
    else if(_skin == LEFT1){
        lcd.drawSprite(_x,_y,4,11,(int *)WyrmLeft1);      
    }
    else if(_skin == RIGHT2){
        lcd.drawSprite(_x,_y,4,11,(int *)WyrmRight2);      
    }
    else if(_skin == LEFT2){
        lcd.drawSprite(_x,_y,4,11,(int *)WyrmLeft2);      
    }
    else if(_skin == RIGHT3){
        lcd.drawSprite(_x,_y,4,11,(int *)WyrmRight3);      
    }
    else if(_skin == LEFT3){
        lcd.drawSprite(_x,_y,4,11,(int *)WyrmLeft3);      
    }
}


void Wyrm::update() { //update wyrm position and skin
    if(_steps<=_limit){ // if hasn't reach step limit yet
        _steps++; // increment _steps which keeps track of how many steps taken
        if(_direction==RIGHT){ 
            _x+=2; //move right
            if(_skin==RIGHT1){_skin=RIGHT2;} //cycle through 3 skins for each direction
            else if(_skin==RIGHT2){_skin=RIGHT3;}
            else if(_skin==RIGHT3){_skin=RIGHT1;}
        }
        else if(_direction==LEFT){
            _x-=2;//go left
            if(_skin==LEFT1){_skin=LEFT2;} //cycle skin
            else if(_skin==LEFT2){_skin=LEFT3;}
            else if(_skin==LEFT3){_skin=LEFT1;}
        }
    }
    else if(_steps>_limit){ //if at step limit, reverse direction and update skin
        if(_direction==LEFT){
            _direction=RIGHT;
            _skin=RIGHT1;
        }
        else if(_direction==RIGHT){
            _direction=LEFT;
            _skin=LEFT1;
        }
        _steps=0; //reset step count
    }
    
}

//accessors:
Position2D Wyrm::get_pos() { return {_x,_y}; }
int Wyrm::get_x(){return _x;}
int Wyrm::get_y(){return _y;}





SKIN Wyrm::get_skin(){return _skin;}
PLAYER_DIRECTION Wyrm::get_direction(){return _direction;}


    void Wyrm::set_x(int x){_x=x;}
    void Wyrm::set_y(int y){_y=y;}

    void Wyrm::set_skin(SKIN skin){_skin=skin;};



   



   


