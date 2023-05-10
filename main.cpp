#include "mbed.h"
#include "Joystick.h"
#include "N5110.h"  
#include "GameEngine.h"
#include "Player.h"
#include "Wyrm.h"
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
Wyrm _wyrm;
DigitalIn A(PC_10);
DigitalIn B(PC_11);
DigitalOut led1(PA_0);
DigitalOut led2(PA_1);
DigitalOut led3(PA_4);
DigitalOut led4(PB_0);
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
void level1b();
void level2b();
void level3b();
void welcome();
void game_over();
void death();
void got_treasure();
void game_complete();

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
    if(level==3){      
        const int treasure[5][5] = {
            {0,1,1,1,0},
            {0,1,0,1,0},
            {1,1,1,1,1},
            {1,0,1,0,1},
            {1,1,1,1,1}
        };
            lcd.drawSprite(70,32,5,5,(int *)treasure);
          /* if(_player.get_x()>=60&&_player.get_x()<=80
            &&_player.get_y()>=15 &&_player.get_y()<=25){
                //if(_player.get_x()>30){
            got_treasure();
        } */   
    }
    lcd.refresh();
}

void introlevel(){
    led1.write(1);
    led2.write(1);
    led3.write(1);
    led4.write(1);
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
    game.wyrms_init(50,84,RIGHT1,RIGHT,8,90,90,RIGHT1,RIGHT,8,90,90,RIGHT1,RIGHT,8);
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
    game.floors_init(20,45,50,
                     0,28,42,
                     46,25,40);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(28,29,90,90,90,90);
    game.doors_init(0,32,0,LEFT1,60,8,1,RIGHT1);
    game.wyrms_init(0,24,RIGHT1,RIGHT,15,
                    46,21,RIGHT1,RIGHT,10,
                    90,90,RIGHT1,RIGHT,8);
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
    game.player_init(0,0,RIGHT1,RIGHT); //void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
    game.floors_init(0,17,50,
                     16,34,84,
                     90,90,90);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(50,17,59,34,90,90);
    game.doors_init(0,0,0,LEFT1,0,34,1,RIGHT1);
    game.wyrms_init(50,30,LEFT1,LEFT,15,
                    50,30,RIGHT1,RIGHT,10,
                    90,90,RIGHT1,RIGHT,8);
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
    game.floors_init(41,37,60,
                     0,31,25,
                     10,17,63);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(25,32,
                      10,15,
                      75,19);
    game.doors_init(0,32,0,LEFT1,90,90,1,RIGHT1);
    game.wyrms_init(90,90,RIGHT1,RIGHT,12,
                    90,90,LEFT1,LEFT,6,
                    90,90,RIGHT1,RIGHT,8);
    game.dragon_init(39,16);
    for(int i=0;i<10000;i++){
   // while (lives > 0) {  // keep looping while lives remain
        // read the joystick input and store in a struct
        UserInput input = {joystick.get_direction(),joystick.get_mag()};
        //lives = pong.update(input);   // update the game engine based on input    
        game.update(input);
        render();
             
              // draw frame on screen
        ThisThread::sleep_for(300ms);
        if(game._got_treasure){got_treasure();}
        if(game._level_failed){death();}
        //if(game._level_done){level3();}
    }
}

void level3b(){
    level=4;
    lcd.clear();
    printf("LEVEL1");
    game._level_done=0;
    game.player_init(75,19,RIGHT1,RIGHT); //void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
    game.floors_init(41,37,60,
                     0,31,25,
                     10,17,63);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(25,32,
                      10,15,
                      75,19);
    game.doors_init(0,32,1,LEFT1,90,90,0,RIGHT1);
    game.wyrms_init(90,90,RIGHT1,RIGHT,12,
                    90,90,LEFT1,LEFT,6,
                    90,90,RIGHT1,RIGHT,8);
    game.dragon_init(39,16);
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
            level2b();
        }
    }
}

void level2b(){
    level=5;
    lcd.clear();
    printf("LEVEL1");
    game._level_done=0;
    game.player_init(0,34,RIGHT1,RIGHT); //void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
    game.floors_init(0,17,50,
                     16,34,84,
                     90,90,90);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(50,17,59,34,90,90);
    game.doors_init(0,0,1,LEFT1,0,34,0,RIGHT1);
    game.wyrms_init(50,30,LEFT1,LEFT,15,
                    50,30,RIGHT1,RIGHT,10,
                    90,90,RIGHT1,RIGHT,8);
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
            level1b();
        }
    }
}

void level1b(){
    level=6;
    lcd.clear();
    printf("LEVEL1");
    game._level_done=0;
    game.player_init(60,8,RIGHT1,RIGHT); //void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
    game.floors_init(20,45,50,
                     0,28,42,
                     46,25,40);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(28,29,90,90,90,90);
    game.doors_init(0,32,1,LEFT1,60,8,0,RIGHT1);
    game.wyrms_init(0,24,RIGHT1,RIGHT,15,
                    46,21,RIGHT1,RIGHT,10,
                    90,90,RIGHT1,RIGHT,8);
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
            game_complete();
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

void game_over() {
    led1.write(0);
    led2.write(0);
    led3.write(0);
    led4.write(0); // splash screen
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
    if(lives==3){
        led1.write(1);
        led2.write(1);
        led3.write(1);
        led4.write(0);
    }
    if(lives==2){
        led1.write(1);
        led2.write(1);
        led3.write(0);
        led4.write(0);
    }
    if(lives==1){
        led1.write(1);
        led2.write(0);
        led3.write(0);
        led4.write(0);
    }
    if(lives==0){
        led1.write(0);
        led2.write(0);
        led3.write(0);
        led4.write(0);
        game_over();}
    
    lcd.clear();
    lcd.printString("LEVEL FAILED!",0,0);
    lcd.printString("A= retry level",0,1);
    lcd.printString("B= exit game",0,2);
    lcd.refresh();
    ThisThread::sleep_for(500ms);
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

void got_treasure(){
    if(level==3){
        lcd.clear();
        lcd.printString("WELL DONE!",0,0);
        lcd.printString("You have the",0,1);
        lcd.printString("treasure.",0,2);
        lcd.printString("Now, escape",0,3);
        lcd.printString("the castle (A)",0,4);
        lcd.printString("B = exit game",0,5);
        lcd.refresh();
        ThisThread::sleep_for(300ms);
            while (!A.read()&&!B.read()){
            ThisThread::sleep_for(100ms);
            }
            if(A.read()){
                level3b();
            }
            else if(B.read()){
                welcome();
            }
    }
}

void game_complete(){
    lcd.clear();
    lcd.printString("Nice! You",0,0);
    lcd.printString("escaped with",0,1);
    lcd.printString("the treasure.",0,2);
    lcd.printString("A = play again",0,3);
    lcd.printString("B = exit game",0,4);
     lcd.refresh();
    while(!A.read()&&!B.read()){
        ThisThread::sleep_for(200ms);
    }
    while(1){
        if(A.read()){
            introlevel();
        }
        else if(B.read()){
            welcome();
        }
        ThisThread::sleep_for(100ms);
    }
}

