#include "mbed.h"
#include "Joystick.h"
#include "N5110.h"  
#include "GameEngine.h"
#include "Player.h"
#include "Snake.h"
#include "Utils.h"


///////////// defines /////////////////////
//#define PADDLE_WIDTH 2
//#define PADDLE_HEIGHT 8
//#define BALL_SIZE 2
//#define BALL_SPEED 3


///////////// objects ///////////////////
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_1, PC_0);
DigitalIn buttonA(BUTTON1); //onboard user button
Player _player;
Snake _snake;
DigitalIn A(PC_10);
DigitalIn B(PC_11);
GameEngine game;
int level;
int lives;


///////////// prototypes ///////////////
void init();
void render();
void tutorial();
void introlevel();
void level1();
void level2();
void level3();
void welcome();
void game_over();
void death();
////////////////////////////////////////




int main(){
    init();
    lives=4;      // initialise devices and objects
    welcome();   // waiting for the user to start
    //render();    // first draw the initial frame
    int fps = 10;
    thread_sleep_for(1000/fps);  // and wait for one frame period - millseconds
    //lives = 4;
    //introlevel();
    //level1();      
   // game_over();
   
}


void init(){
    lcd.init(LPH7366_1);
    lcd.setContrast(0.5);
    joystick.init();
   // game.init(0,32,RIGHT1,RIGHT,48,31,14);     // (int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction,int floor1_y, int floor2_y, int floor3_y);
}
void render() {  // clear screen, re-draw and refresh
    lcd.clear();  
    game.draw(lcd);
    lcd.refresh();
}

void introlevel(){
    level=0;
    lcd.clear();
    printf("INTRO LEVEL");
    game._level_done=0;
    game.player_init(0,32,RIGHT1,RIGHT); //void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
    game.floors_init(30,32,40,
                     0,26,20,
                     50,17,65);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(28,32,50,17,90,90);
    game.doors_init(0,32,0,LEFT1,69,0,1,RIGHT1);
    game.snake_init(30,44,RIGHT1,RIGHT,8);
    game.dragon_init(90,90);
    while(!game._level_done&&!game._level_failed){
   // while (lives > 0) {  // keep looping while lives remain
        // read the joystick input and store in a struct
        UserInput input = {joystick.get_direction(),joystick.get_mag()};
        //lives = pong.update(input);   // update the game engine based on input    
        game.update(input);
        render();
        ThisThread::sleep_for(200ms);
        
    }
    if(game._level_failed){death();}
    if(game._level_done){level1();}

};

void level1(){
    level=1;
    lcd.clear();
    printf("LEVEL1");
    game._level_done=0;
    game.player_init(0,32,RIGHT1,RIGHT); //void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
    game.floors_init(0,0,0,
                     0,0,0,
                     0,0,0);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(0,0,0,0,0,0);
    game.doors_init(0,32,0,LEFT1,69,32,1,RIGHT1);
    game.snake_init(50,84,RIGHT1,RIGHT,8);
    game.dragon_init(90,90);
    for(int i=0;i<10000;i++){
   // while (lives > 0) {  // keep looping while lives remain
        // read the joystick input and store in a struct
        UserInput input = {joystick.get_direction(),joystick.get_mag()};
        //lives = pong.update(input);   // update the game engine based on input    
        game.update(input);
        render();                     // draw frame on screen
        ThisThread::sleep_for(300ms);
        if(game._level_failed){death();}
        if(game._level_done){
            level2();
        }
    }
}

void level2(){
    level=2;
    lcd.clear();
    printf("LEVEL1");
    game._level_done=0;
    game.player_init(0,32,RIGHT1,RIGHT); //void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
    game.floors_init(0,0,0,
                     0,0,0,
                     0,0,0);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(0,0,0,0,0,0);
    game.doors_init(0,32,0,LEFT1,69,32,1,RIGHT1);
    game.snake_init(50,84,RIGHT1,RIGHT,8);
    game.dragon_init(90,90);
    for(int i=0;i<10000;i++){
   // while (lives > 0) {  // keep looping while lives remain
        // read the joystick input and store in a struct
        UserInput input = {joystick.get_direction(),joystick.get_mag()};
        //lives = pong.update(input);   // update the game engine based on input    
        game.update(input);
        render();                     // draw frame on screen
        ThisThread::sleep_for(300ms);
        if(game._level_failed){death();}
        if(game._level_done){
            level3();
        }
    }
}

void level3(){
    level=3;
    lcd.clear();
    printf("LEVEL1");
    game._level_done=0;
    game.player_init(0,32,RIGHT1,RIGHT); //void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
    game.floors_init(0,0,0,
                     0,0,0,
                     0,0,0);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(0,0,0,0,0,0);
    game.doors_init(0,32,0,LEFT1,69,32,1,RIGHT1);
    game.snake_init(50,84,RIGHT1,RIGHT,8);
    game.dragon_init(50,20);
    for(int i=0;i<10000;i++){
   // while (lives > 0) {  // keep looping while lives remain
        // read the joystick input and store in a struct
        UserInput input = {joystick.get_direction(),joystick.get_mag()};
        //lives = pong.update(input);   // update the game engine based on input    
        game.update(input);
        render();                     // draw frame on screen
        ThisThread::sleep_for(300ms);
        if(game._level_failed){death();}
        if(game._level_done){
            level3();
        }
    }
}

void welcome() {
    lcd.clear();
    lcd.printString("CASTLE CRAWLER",0,1);  
    lcd.printString("A = tutorial",0,3);
    lcd.printString("B = play",0,4);
    lcd.refresh();
    ThisThread::sleep_for(300ms);
        while (!A.read()&&!B.read()){
        ThisThread::sleep_for(100ms);
        }
        if(A.read()){
            tutorial();
        }
        else if(B.read()){
            introlevel();
        }
}


void game_over() { // splash screen
    while (1) {
        lcd.clear();
        lcd.printString("  Game Over ",0,2);  
        lcd.refresh();
        ThisThread::sleep_for(250ms);
        lcd.clear();
        lcd.refresh();
        ThisThread::sleep_for(250ms);
    }
}

void tutorial(){
    while(!B.read()){
    lcd.clear();
    lcd.printString("WELCOME PLAYER",0,1);
    lcd.printString("to Castle",0,2);
    lcd.printString("Ravenloft!",0,3);
    lcd.printString("(Press B)",0,5);
    lcd.refresh();
    }
    while(B.read()){
    ThisThread::sleep_for(200ms);
    }
    while(!B.read()){
    lcd.clear();
    lcd.printString("This castle &",0,1);
    lcd.printString("its wealth has",0,2);
    lcd.printString("been captured",0,3);
    lcd.printString("by a DRAGON",0,4);
    lcd.printString("(Press B)",0,5);
    lcd.refresh();
    }
    while(B.read()){
    ThisThread::sleep_for(200ms);
    }
    while(!B.read()){
    lcd.clear();
    lcd.printString("Your task is",0,0);
    lcd.printString("to steal some",0,1);
    lcd.printString("TREASURE from",0,2);
    lcd.printString("the DRAGON and",0,3);
    lcd.printString("return it to",0,4);
    lcd.printString("town (Press B)",0,5);
    lcd.refresh();
    }
    while(B.read()){
    ThisThread::sleep_for(200ms);
    }
    while(!B.read()){
    lcd.clear();
    lcd.printString("Use Joystick",0,0);
    lcd.printString("to WALK. Use A",0,1);
    lcd.printString("to JUMP/CLIMB.",0,2);
    lcd.printString("AVOID wyrms,",0,3);
    lcd.printString("spikes, fire",0,4);
    lcd.printString("(Press B)",0,5);
    lcd.refresh();
    }
        while(B.read()){
    ThisThread::sleep_for(200ms);
    }
    while(!B.read()){
    lcd.clear();
    lcd.printString("Press B",0,1);
    lcd.printString("to exit game",0,2);
    lcd.printString("during play.",0,3);
    lcd.printString("(Press B)",0,5);
    lcd.refresh();
    }
        while(B.read()){
    ThisThread::sleep_for(200ms);
    }
    while(!A.read()){
    lcd.clear();
    lcd.printString("Are you ready?",0,1);
    lcd.printString("Press A",0,3);
    lcd.refresh();
    }
    while(A.read()){
    ThisThread::sleep_for(200ms);
    }
    lcd.clear();
    lcd.printString("Good luck...",0,3);
    lcd.refresh();
    ThisThread::sleep_for(1500ms);
    introlevel();
}

void death(){
    game._level_failed=0;
    lives--;
    if(lives==0){game_over();}
    lcd.clear();
    lcd.printString("LEVEL FAILED!",0,0);
    lcd.printString("A= retry level",0,1);
    lcd.printString("B= exit game",0,2);
    lcd.refresh();
    while(!A.read()&&!B.read()){
        ThisThread::sleep_for(200ms);
    }
    while(1){
        if(A.read()){
            if(level==0){
                introlevel();
            }
            else if(level==1){
                level1();
            }
            else if(level==2){
                level2();
            }
            else if(level==3){
                level3();
            }
        }
        else if(B.read()){
            welcome();
        }
        ThisThread::sleep_for(100ms);
    }
}

