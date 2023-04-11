

#include "Player.h"
DigitalIn jump(PC_10);


Player::Player() { }


void Player::init(int x, int y, SKIN Player_Skin, PLAYER_DIRECTION Player_Direction) {
    printf("Player: Init\n");
    _jumping = 0;
    _falling = 0;
    _stationary = 1;
    _height = 0;
    _x = x;
    _y = y;
    _Player_Direction = Player_Direction;
    _Player_Skin = Player_Skin;
}


void Player::draw(N5110 &lcd) {
    printf("Player: Draw\n");
    if(_Player_Skin == RIGHT1){
        lcd.drawSprite(_x,_y,16,10,(int *)Right1);      
    }
    else if(_Player_Skin == LEFT1){
        lcd.drawSprite(_x,_y,16,10,(int *)Left1);      
    }
    else if(_Player_Skin == RIGHT2){
        lcd.drawSprite(_x,_y,16,17,(int *)Right2);      
    }
    else if(_Player_Skin == LEFT2){
        lcd.drawSprite(_x,_y,16,17,(int *)Left2);      
    }


}


void Player::update(UserInput input) { //updates DIRECTION and JUMPING (if not already jumping)
    printf("Player: update\n");
   // if sw1.read==1{
   // jump(_x,_y,SKIN Player_Skin, PLAYER_DIRECTION Player_Direction)
  //  };
   // _speed = 3;
    if (input.d == E||input.d == NE||input.d == SE){
     //   _x+=_speed;
        _Player_Direction = RIGHT;
        _stationary = 0;
        //if (_Player_Skin == RIGHT1){
        //    _Player_Skin = RIGHT2;
       // }
       // else{_Player_Skin = RIGHT1;}
       // }
        }
    else if (input.d == W||input.d == NW||input.d == SW){//_x-=_speed;
            _Player_Direction = LEFT;
            _stationary = 0;
           // if (_Player_Skin == LEFT1){
           // _Player_Skin = LEFT2;
           // }
           // else{_Player_Skin = LEFT1;}
            }
    else if (input.d == CENTRE||input.d == N||input.d == S){//_x-=_speed;
            _stationary = 1;
           // if (_Player_Skin == LEFT1){
           // _Player_Skin = LEFT2;
           // }
           // else{_Player_Skin = LEFT1;}
            }
    if(_jumping == 0){
        _jumping = jump.read();
    }
    //if (_x<1) {_x = 1;}
    //if (_x>66) {_x = 66;}


}


Position2D Player::get_pos() { return {_x,_y}; }


int Player::get_x(){return _x;}
int Player::get_y(){return _y;}
int Player::get_height(){return _height;}


bool Player::get_jumping(){return _jumping;}
bool Player::get_falling(){return _falling;}
bool Player::get_stationary(){return _stationary;}




SKIN Player::get_skin(){return _Player_Skin;}
PLAYER_DIRECTION Player::get_direction(){return _Player_Direction;}


    //void set_pos(Position 2D player_pos){_}
    void Player::set_x(int x){_x=x;}
    void Player::set_y(int y){_y=y;}
    void Player::set_height(int h){_height=h;}
    void Player::set_jumping(bool jumping){_jumping=jumping;}
    void Player::set_falling(bool falling){_falling=falling;}
    void Player::set_skin(SKIN skin){_Player_Skin=skin;};


   



   

