#include "GameEngine.h"


GameEngine::GameEngine() {}

//initialise player: position, skin, direction
void GameEngine::player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction){
    _player.init(player_x,player_y,player_skin,player_direction);
}
//initialise three floors with positions and widths
void GameEngine::floors_init(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width){
    _floor1.init(floor1_x, floor1_y, floor1_width);
    _floor2.init(floor2_x, floor2_y, floor2_width);
    _floor3.init(floor3_x, floor3_y, floor3_width);
}

//initialise three ladders with positions
void GameEngine::ladders_init(int ladder1_x,int ladder1_y, int ladder2_x,int ladder2_y, int ladder3_x,int ladder3_y){
    _ladder1.init(ladder1_x, ladder1_y);
    _ladder2.init(ladder2_x, ladder2_y);
    _ladder3.init(ladder3_x, ladder3_y);

}
//initialise 2 doors with positions, skins and exit statuses
void GameEngine::doors_init(int d1_x, int d1_y, bool d1_exit, SKIN d1_skin, int d2_x, int d2_y, bool d2_exit, SKIN d2_skin){
    _door1.init(d1_x,d1_y,d1_exit, d1_skin);
    _door2.init(d2_x,d2_y,d2_exit,d2_skin);
}

//initialise 3 worms with positions, skins, starting directions, and movement limits
void GameEngine::wyrms_init(int s1_x, int s1_y, SKIN Wyrm1_Skin, PLAYER_DIRECTION Wyrm1_Direction, int s1_limit,int s2_x, int s2_y, SKIN Wyrm2_Skin, PLAYER_DIRECTION Wyrm2_Direction, int s2_limit, int s3_x, int s3_y, SKIN Wyrm3_Skin, PLAYER_DIRECTION Wyrm3_Direction, int s3_limit){

    _wyrm1.init(s1_x,s1_y,Wyrm1_Skin,Wyrm1_Direction,s1_limit);
    _wyrm2.init(s2_x,s2_y,Wyrm2_Skin,Wyrm2_Direction,s2_limit);
    _wyrm3.init(s3_x,s3_y,Wyrm3_Skin,Wyrm3_Direction,s3_limit);
}
//iniitalise dragon with position
void GameEngine::dragon_init(int x, int y) {
    _dragon.init(x,y);
}

//updates all three wyrm positions
void GameEngine::wyrms_update(){
    _wyrm1.update();
    _wyrm2.update();
    _wyrm3.update();
}

//updates the moving parts: player, wyrms, dragon
void GameEngine::update(UserInput input) {
    _player.update(input); //update direction and jumping status from user inputs
    wyrms_update(); //updates position
    _dragon.update(); //updates skin and fireball position
    movement(); //update player position, as well as level failed and completed flags
}

//draw everything:
void GameEngine::draw(N5110 &lcd) { 
    _dragon.draw(lcd);
    _floor1.draw(lcd);
    _floor2.draw(lcd);
    _floor3.draw(lcd);
    _ladder1.draw(lcd);
    _ladder2.draw(lcd);
    _ladder3.draw(lcd);
    _door1.draw(lcd);
    _door2.draw(lcd);
    _wyrm1.draw(lcd);
    _wyrm2.draw(lcd);
    _wyrm3.draw(lcd);
    _player.draw(lcd);

}
void GameEngine::movement(){
    //use accessors to get player data: jumping, falling and stationary statuses & height
    Position2D player_pos = _player.get_pos(); //player 2D position
    bool player_jumping = _player.get_jumping();//if sw1 held, and player not falling
    bool player_falling = _player.get_falling();//if player has been jumping but has reached height limit or sw1 released
    bool player_stationary = _player.get_stationary(); //1 if joystick in centre, north or south
    int height = _player.get_height(); //used to limit jump height
    int ladder_height;

    if(player_falling){height=0;} //if player is falling, reset height
    
    if(check_ladder()){ //climbing ladder
        if(player_jumping){ //if jump being held, ascend the ladder, reset the jump flag
            player_pos.y-=2;
            player_jumping=0;
        }
        else{
        player_pos.y+=2; //if jump not being held, and player not at floor, descend the ladder
            if(check_floor_collision()){
                player_pos.y--;
            }   
        }
    }

    if(!player_jumping&&!player_stationary&&!player_falling){ //normal walking

            if(_player.get_direction() == RIGHT){  //move to the right
                player_pos.x+=3;
                if(_player.get_skin() == RIGHT1){ //toggle skin
                    _player.set_skin(RIGHT2);
                    }
                else{
                    _player.set_skin(RIGHT1);
                    }
            }
            if(_player.get_direction() == LEFT){ //move to the left
                player_pos.x-=3;
                    if(_player.get_skin() == LEFT1){ //toggle skin
                        _player.set_skin(LEFT2);
                    }
                    else{
                        _player.set_skin(LEFT1);
                        }
                    }
           
    }
    else if(player_jumping&&player_stationary&&!player_falling){//jumping straight up
        player_pos.y--; //go up
        height++; //increment height flag
        if(height==4){ //if height is at its limit, player begins falling
            player_falling=1;
        }
        if(check_ceiling_collision()){ //if player hits ceiling, begins falling
            player_falling=1;
            player_pos.y++;
        }
    }
    else if(player_jumping&&!player_stationary&&!player_falling){ //jumping left or right        
        if(_player.get_direction()==LEFT){ //jump up and left
            player_pos.x-=2;
            player_pos.y--;
            height++; //increment height
        }
        else if(_player.get_direction()==RIGHT){ //jump up and right
            player_pos.x+=2;
            player_pos.y--;
            height++; //increment height
        }
        if(height==4){ //if at height limit, begin falling
            player_falling=1;
        }
        if(check_ceiling_collision()){ //if player hits ceiling, begins falling
            player_falling=1;
            player_pos.y++;

        }
    }
    else if(player_falling&&player_stationary){ //falling straight down
        player_pos.y++; //go down
        height--; //decrement height
        if(check_floor_collision()){ //stop falling if hit floor
            player_falling=0;
            player_jumping=0;
            //player_pos.y--;

        }
    }
    else if(player_falling&&!player_stationary){ //falling left or right
        player_pos.y++; //go down
        height--; //decrement height
        if(_player.get_direction()==LEFT){ //go left
            player_pos.x-=2;
        }
        else if(_player.get_direction()==RIGHT){ //go right
            player_pos.x+=2;
        }
        if(check_floor_collision()){ //stop falling if hit floor
            player_falling=0;
            player_jumping=0;
            //player_pos.y--;

        }


    }
    //limit player position to within the lcd screen
    if(player_pos.x<1) {player_pos.x = 1;}
    if(player_pos.x>74) {player_pos.x = 74;}
    if(player_pos.y<1) {player_pos.y=1;}

    //update the player conditions to the newly determined ones using the mutators
    _player.set_x(player_pos.x);
    _player.set_y(player_pos.y);
    _player.set_falling(player_falling);
    _player.set_jumping(player_jumping);
    _player.set_height(height);

    //if at exit, _level_done
    _level_done=check_exit();
    //if player touched a fireball or syrm, _level_failed
    if(check_wyrm()||check_fireball()){
        _level_failed = 1;
    }
    //if player touched treasure, _got_treasure
    _got_treasure=check_treasure();
}

//check if player touches a ceiling
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
//check if player touches a floor
    bool floor_collision = 0;
    int feet = _player.get_y()+16; //y position of the players feet
    if(feet>=48){ //if player at bottom edge of lcd, floor collision is true
        floor_collision = 1;
    }
    //3 checks, one for each floor, for when player direction is left:
    if(_player.get_direction()==LEFT){
        if(feet == _floor1.get_y() && _player.get_x() >= _floor1.get_x() && _player.get_x() <= _floor1.get_x() + _floor1.get_width()){
            floor_collision = 1;
        }
        else if(feet == _floor2.get_y() && _player.get_x() >= _floor2.get_x() && _player.get_x() <= _floor2.get_x() + _floor2.get_width()){
            floor_collision = 1;
        }
        else if(feet == _floor3.get_y() && _player.get_x() >= _floor3.get_x() && _player.get_x() <= _floor3.get_x() + _floor3.get_width()){
            floor_collision = 1;
        }
    }
    //3 checks, one for each floor, for when player direction is right:
    else{
        if(feet == _floor1.get_y() && _player.get_x()+11 >= _floor1.get_x() && _player.get_x()+11<= _floor1.get_x()+ _floor1.get_width()){
            floor_collision = 1;
        }
        else if(feet == _floor2.get_y() && _player.get_x()+11 >= _floor2.get_x() && _player.get_x()+11 <= _floor2.get_x() + _floor2.get_width()){
            floor_collision = 1;
        }
        else if(feet == _floor3.get_y() && _player.get_x()+11 >= _floor3.get_x() && _player.get_x()+11 <= _floor3.get_x() + _floor3.get_width()){
            floor_collision = 1;
        }
        if(floor_collision){
            _player.set_height(0);
        }
    }
        return floor_collision; //return bool: 1 if collided with floor
    

}


bool GameEngine::check_ladder(){ //check if player is on a ladder
    bool climbing_ladder=0;
    //x and y positions for player and 3 ladders:
    int px=_player.get_x();
    int py=_player.get_y();
    int l1x=_ladder1.get_x();
    int l1y=_ladder1.get_y();
    int l2x=_ladder2.get_x();
    int l2y=_ladder2.get_y();
    int l3x=_ladder3.get_x();
    int l3y=_ladder3.get_y();
//3 checks: one for each ladder
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
    return climbing_ladder; //return true if player is on ladder
}

bool GameEngine::check_exit(){ //check if player is on the exit (_door2)
    bool exiting = 0;
    int px= _player.get_x();
    int py= _player.get_y();
    int d2_x = _door2.get_x();
    int d2_y= _door2.get_y();

    if(px>=d2_x&&px+10<=d2_x+15){
        if(py>=d2_y&&py+16<=d2_y+18){
             printf("Player exiting\n");
            exiting =1;
    }

    }
    return exiting; //true if the player is on the exit
    }

bool GameEngine::check_wyrm(){ //check for collision with a wyrm
    bool wyrmd = 0;
    int px= _player.get_x();
    int py= _player.get_y();
    //arrays of x and y positions for the 3 wyrms
    int sx[3]= {_wyrm1.get_x(),_wyrm2.get_x(),_wyrm3.get_x()}; 
    int sy[3]= {_wyrm1.get_y(),_wyrm2.get_y(),_wyrm3.get_y()};
    //iterate through the arrays, to check for collisions with each wyrm
    for(int i=0;i<3;i++){
    if(py<=sy[i]+4&&py+16>=sy[i]){
        if(sx[i]<=px&& sx[i]+10>=px){
            wyrmd=1;
        }
        else if(sx[i]>=px&& sx[i]<=px+11){
            wyrmd=1;
        }
    }
    }
    return wyrmd;    //true if colllided with wyrm
    printf("wyrmd");
}

bool GameEngine::check_fireball(){ //check if player hit by a fireball
    bool fireballed = 0;
    int px= _player.get_x();
    int py= _player.get_y();
    int fy= _dragon.get_y()+14; //fire y position is 14 below top of dragon
    int fx = _dragon.get_fire_x(); //fire x position obtained by accessor
    if(fy>=py&&fy<=py+16){
        if(fx>=px&&fx<=px+7){
            fireballed=1;
        }
    }

    return fireballed; //true if player hit by fireball
    printf("fireballed");
}

bool GameEngine::check_treasure(){ //check if player is on the treasure
    int px= _player.get_x();
    int py= _player.get_y();
    int _got_treasure=0;
    if(px>=70){
        if(py>=19&& py <=37){
            _got_treasure=1;
        }
    
    }
    return _got_treasure; //true if the player is on the treasure
}
    int py= _player.get_y();
    int _got_treasure=0;
    if(px>=70){
        if(py>=19&& py <=37){
            _got_treasure=1;
        }
    
   // if(75<=px&&px<=84&&16<=py&&py<=23){
  //      _got_treasure=1;
   // }}
    }
    return _got_treasure;
}
