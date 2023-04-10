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
//DigitalIn sw1(PC_10);
DigitalIn sw2(PC_11);
GameEngine game;


///////////// prototypes ///////////////
void init();
void render();
void introlevel();
void level1();
void welcome();
void game_over();
////////////////////////////////////////




int main() {
    init();      // initialise devices and objects
    welcome();   // waiting for the user to start
    //render();    // first draw the initial frame
    int fps = 10;
    thread_sleep_for(1000/fps);  // and wait for one frame period - millseconds
    int lives = 4;   // display lives on LEDs
    introlevel();
    //level1();      
   // game_over();
   
}


void init() {
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
    game._level_done=0;
    game.player_init(0,32,RIGHT1,RIGHT); //void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
    game.floors_init(30,32,40,
                     0,26,20,
                     50,17,65);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(28,32,50,17,90,90);
    game.doors_init(0,32,0,LEFT1,69,0,1,RIGHT1);
    for(int i=0;i<10000;i++){
   // while (lives > 0) {  // keep looping while lives remain
        // read the joystick input and store in a struct
        UserInput input = {joystick.get_direction(),joystick.get_mag()};
        //lives = pong.update(input);   // update the game engine based on input    
        game.update(input);
        render();

        if(game._level_done){
            game_over();
        }                   // draw frame on screen
        ThisThread::sleep_for(300ms);
        
    }
};

void level1(){
    welcome();
    game._level_done=0;
    game.player_init(0,32,RIGHT1,RIGHT); //void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
    game.floors_init(0,0,0,
                     0,0,0,
                     0,0,0);//(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width)
    game.ladders_init(0,0,0,0,0,0);
    game.doors_init(0,32,0,LEFT1,69,0,1,RIGHT1);
    _snake.init(20,  44, RIGHT1, RIGHT,  6);
    for(int i=0;i<10000;i++){
   // while (lives > 0) {  // keep looping while lives remain
        // read the joystick input and store in a struct
        UserInput input = {joystick.get_direction(),joystick.get_mag()};
        //lives = pong.update(input);   // update the game engine based on input    
        game.update(input);
        render();                     // draw frame on screen
        ThisThread::sleep_for(300ms);
        if(game._level_failed){
            lcd.printString("Ooops!",0,4);
            lcd.refresh();
            ThisThread::sleep_for(2000ms);
            level1();
        }
        if(game._level_done){
            ThisThread::sleep_for(300ms);
            level1();
        }
    }
}

void welcome() { // splash screen
    lcd.printString("          ",0,1);  
    lcd.printString("Press Nucleo",0,3);
    lcd.printString("Blue button",0,4);
    lcd.refresh();


        while (buttonA.read() == 1){


         ThisThread::sleep_for(100ms);
     
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

