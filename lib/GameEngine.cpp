#include "GameEngine.h"


GameEngine::GameEngine() {}


void GameEngine::player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction){
    _player.init(player_x,player_y,player_skin,player_direction);
}
void GameEngine::floors_init(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width){
    _floor1.init(floor1_x, floor1_y, floor1_width);
    _floor2.init(floor2_x, floor2_y, floor2_width);
    _floor3.init(floor3_x, floor3_y, floor3_width);
}
void GameEngine::ladders_init(int ladder1_x,int ladder1_y, int ladder2_x,int ladder2_y, int ladder3_x,int ladder3_y){
    _ladder1.init(ladder1_x, ladder1_y);
    _ladder2.init(ladder2_x, ladder2_y);
    _ladder3.init(ladder3_x, ladder3_y);

}
void GameEngine::doors_init(int d1_x, int d1_y, bool d1_exit, SKIN d1_skin, int d2_x, int d2_y, bool d2_exit, SKIN d2_skin){
    _door1.init(d1_x,d1_y,d1_exit, d1_skin);
    _door2.init(d2_x,d2_y,d2_exit,d2_skin);
}

void GameEngine::update(UserInput input) {
    _player.update(input); //update direction and jumping status from user inputs
    movement(); //update position
}


void GameEngine::draw(N5110 &lcd) {
    _floor1.draw(lcd);
    _floor2.draw(lcd);
    _floor3.draw(lcd);
    _ladder1.draw(lcd);
    _ladder2.draw(lcd);
    _ladder3.draw(lcd);
    _door1.draw(lcd);
    _door2.draw(lcd);
    _player.draw(lcd);

}
void GameEngine::movement(){
    Position2D player_pos = _player.get_pos();
    bool player_jumping = _player.get_jumping();
    bool player_falling = _player.get_falling();
    bool player_stationary = _player.get_stationary();
    int height = _player.get_height();
    int ladder_height;
   
    if(player_falling){height=0;} //reset height
    
    if(check_ladder()){ //climbing ladder
        if(player_jumping){
            player_pos.y--;//
            player_jumping=0;
        }
        else{
        player_pos.y++;
            if(check_floor_collision()){
                player_pos.y--;
            }   
        }
    }

    if(!player_jumping&&!player_stationary&&!player_falling){ //normal walking
            if(_player.get_direction() == RIGHT){
                player_pos.x+=3;
                if(_player.get_skin() == RIGHT1){
                    _player.set_skin(RIGHT2);
                    }
                else{
                    _player.set_skin(RIGHT1);
                    }
            }
            if(_player.get_direction() == LEFT){
                player_pos.x-=3;
                    if(_player.get_skin() == LEFT1){
                        _player.set_skin(LEFT2);
                    }
                    else{
                        _player.set_skin(LEFT1);
                        }
                    }
           
    }
    else if(player_jumping&&player_stationary&&!player_falling){//jumping straight up
        player_pos.y--;
        height++;
        if(height==4){
            player_falling=1;
        }
        if(check_ceiling_collision()){
            player_falling=1;
            player_pos.y++;
        }
    }
    else if(player_jumping&&!player_stationary&&!player_falling){ //jumping left or right        
        if(_player.get_direction()==LEFT){
            player_pos.x-=2;
            player_pos.y--;
            height++;
        }
        else if(_player.get_direction()==RIGHT){
            player_pos.x+=2;
            player_pos.y--;
            height++;
        }
        if(height==4){
            player_falling=1;
        }
        if(check_ceiling_collision()){
            player_falling=1;
            player_pos.y++;

        }
    }
    else if(player_falling&&player_stationary){ //falling straight down
        player_pos.y++;
        height--;
        if(height==0||check_floor_collision()){
            player_falling=0;
            player_jumping=0;
            player_pos.y--;

        }
    }
    else if(player_falling&&!player_stationary){ //falling left or right
        player_pos.y++;
        height--;
        if(_player.get_direction()==LEFT){
            player_pos.x-=2;
        }
        else if(_player.get_direction()==RIGHT){
            player_pos.x+=2;
        }
        if(height==0||check_floor_collision()){
            player_falling=0;
            player_jumping=0;
            player_pos.y--;

        }


    }
    if(player_pos.x<1) {player_pos.x = 1;}
    if(player_pos.x>74) {player_pos.x = 74;}
    if(player_pos.y<1) {player_pos.y=1;}
    _player.set_x(player_pos.x);
    _player.set_y(player_pos.y);
    _player.set_falling(player_falling);
    _player.set_jumping(player_jumping);
    _player.set_height(height);
    _level_done=check_exit();

}


bool GameEngine::check_ceiling_collision(){
    bool ceiling_collision = 0;
    if(_player.get_y()<=0){ceiling_collision=1;}
    else if(_player.get_y() == _floor1.get_y() && _player.get_x() >= _floor1.get_x() && _player.get_x() <= _floor1.get_x() + _floor1.get_width()){
        ceiling_collision = 1;
    }
    else if(_player.get_y() == _floor2.get_y() && _player.get_x() >= _floor2.get_x() && _player.get_x() <= _floor2.get_x() + _floor2.get_width()){
        ceiling_collision = 1;


    }
    else if(_player.get_y() == _floor3.get_y() && _player.get_x() >= _floor3.get_x() && _player.get_x() <= _floor3.get_x() + _floor1.get_width()){
        ceiling_collision = 1;


    }
    return ceiling_collision;
}

bool GameEngine::check_floor_collision(){

    bool floor_collision = 0;
    int feet = _player.get_y()+16;
    if(feet>=48){
        floor_collision = 1;
    }
    if(_player.get_direction()==LEFT){
        if(feet == _floor1.get_y() && _player.get_x() >= _floor1.get_x() && _player.get_x() <= _floor1.get_x() + _floor1.get_width()){
            floor_collision = 1;
        }
        else if(feet == _floor2.get_y() && _player.get_x() >= _floor2.get_x() && _player.get_x() <= _floor2.get_x() + _floor2.get_width()){
            floor_collision = 1;
        }
        else if(feet == _floor3.get_y() && _player.get_x() >= _floor3.get_x() && _player.get_x() <= _floor3.get_x() + _floor1.get_width()){
            floor_collision = 1;
        }
    }
    else{
        if(feet == _floor1.get_y() && _player.get_x()+11 >= _floor1.get_x() && _player.get_x()+11<= _floor1.get_x()+ _floor1.get_width()){
            floor_collision = 1;
        }
        else if(feet == _floor2.get_y() && _player.get_x()+11 >= _floor2.get_x() && _player.get_x()+11 <= _floor2.get_x() + _floor2.get_width()){
            floor_collision = 1;
        }
        else if(feet == _floor3.get_y() && _player.get_x()+11 >= _floor3.get_x() && _player.get_x()+11 <= _floor3.get_x() + _floor1.get_width()){
            floor_collision = 1;
        }
        if(floor_collision){
            _player.set_height(0);
        }
    }
        return floor_collision;
    

}

bool GameEngine::check_ladder(){
    bool climbing_ladder=0;
    int px=_player.get_x();
    int py=_player.get_y();
    int l1x=_ladder1.get_x();
    int l1y=_ladder1.get_y();
    int l2x=_ladder2.get_x();
    int l2y=_ladder2.get_y();
    int l3x=_ladder3.get_x();
    int l3y=_ladder3.get_y();

    if(px+7>=l1x && px <=l1x +7 ){
        if(py+16<=l1y+16 && py+16>=l1y){
       climbing_ladder =1;
        }
    }
    else if(px+7>=l2x && px <=l2x +7 ){
        if(py+16<=l2y+16 && py+16>=l2y){
       climbing_ladder =1;
        }
    }
    else if(px+7>=l3x && px <=l3x +7 ){
        if(py+16<=l3y+16 && py+16>=l3y){
       climbing_ladder =1;
        }
    }
    return climbing_ladder;
}

bool GameEngine::check_exit(){
    bool exiting = 0;
    int px= _player.get_x();
    int py= _player.get_y();
    int d2_x = _door2.get_x();
    int d2_y= _door2.get_y();
    if(px+7>=d2_x && px <=d2_x+15 ){
        if(py+16<=d2_y+17 && py+16>=d2_y){
            printf("Player exiting\n");
            exiting =1;
        }
    }
    return exiting;
    }
