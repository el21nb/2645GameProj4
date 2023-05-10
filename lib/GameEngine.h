#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include "mbed.h"
#include "N5110.h"
#include "Ladder.h"
#include "Floor.h"
#include "Door.h"
#include "Wyrm.h"
#include "Utils.h"
#include "Player.h"
#include "Dragon.h"

class GameEngine {
    public:
        GameEngine();  // pass in the lcd object from the main file

        //initialisations
        void player_init(int player_x,int player_y,SKIN player_skin,PLAYER_DIRECTION player_direction);
        void floors_init(int floor1_x, int floor1_y, int floor1_width, int floor2_x, int floor2_y, int floor2_width, int floor3_x, int floor3_y, int floor3_width);
        void ladders_init(int ladder1_x,int ladder1_y, int ladder2_x,int ladder2_y, int ladder3_x,int ladder3_y);
        void doors_init(int d1_x, int d1_y, bool d1_exit, SKIN d1_skin, int d2_x, int d2_y, bool d2_exit, SKIN d2_skin);
        void wyrms_init(int s1_x, int s1_y, SKIN Wyrm1_Skin, PLAYER_DIRECTION Wyrm1_Direction, int s1_limit,int s2_x, int s2_y, SKIN Wyrm2_Skin, PLAYER_DIRECTION Wyrm2_Direction, int s2_limit, int s3_x, int s3_y, SKIN Wyrm3_Skin, PLAYER_DIRECTION Wyrm3_Direction, int s3_limit);
        void dragon_init(int x, int y);

        void wyrms_update(); //update all 3 wyrm positions
        void update(UserInput input); //update player based on user inputs, update dragon and wyrms
        void draw(N5110 &lcd); //draw everything on lcd
        void movement();        //moving object and game status updates:
        //object interaction checks:
        bool check_ceiling_collision();
        bool check_floor_collision();
        bool check_ladder();
        bool check_exit();
        bool check_wyrm();
        bool check_fireball();
        bool check_treasure();
        //flags to tell main() to exit levels
        bool _level_done;
        bool _level_failed;
        bool _got_treasure;

    private: //all the objects in the game:
        Floor _floor1;
        Floor _floor2;
        Floor _floor3;
        Player _player;
        Ladder _ladder1;
        Ladder _ladder2;
        Ladder _ladder3;
        Door _door1;
        Door _door2;
        Wyrm _wyrm1;
        Wyrm _wyrm2;
        Wyrm _wyrm3;
        Dragon _dragon;
};


#endif



