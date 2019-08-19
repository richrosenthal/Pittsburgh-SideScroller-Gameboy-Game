#include <gb/gb.h>
#include <stdio.h>
#include "simplepittsburgh.c"
#include "pittsburghmap.c"
#include <gb/font.h>
#include "windowmap.c"

INT8 playerLocation[2]; //An array to store our player location
BYTE jumping;
UINT8 gravity = -2;
UINT8 currentspeedY;
UINT8 floorYposition = 100;


unsigned char StickMan[] =
{
  0x7C,0x00,0x7C,0x38,0x6C,0x38,0x7C,0x38,
  0x54,0x10,0x10,0x10,0x38,0x38,0x28,0x28, //Tile 1 of an 8x8 sprite

  0x7C,0x00,0x7C,0x38,0x6C,0x38,0x7C,0x38, // Tile 2 of an 8x8 sprite
  0x54,0x10,0x10,0x10,0x7C,0x7C,0x00,0x00
};


void performantDelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}

INT8 wouldhitsurface(UINT8 projectedYPosition){
    if(projectedYPosition >= floorYposition){
        return floorYposition;
    }
    return -1;

}

void jump(){
    INT8 possiblesurfaceY; 

    if(jumping == 0){
        jumping = 1;
        currentspeedY = 10;
    }

    currentspeedY = currentspeedY + gravity;

    playerLocation[1] = playerLocation[1] - currentspeedY;

    possiblesurfaceY = wouldhitsurface(playerLocation[1]);

    if(possiblesurfaceY > -1){
       jumping = 0;
       move_sprite(0, playerLocation[0], possiblesurfaceY); //setting the first move sprite parameter to 1 will leave an after image
    }

    
    else{
       move_sprite(0, playerLocation[0], playerLocation[1]); //setting the first move sprite parameter to 1 will leave an after image
    }
}
     




void main(){
     font_t min_font;

    font_init();
    min_font = font_load(font_min); // 36 tile
    font_set(min_font);

    set_bkg_data(27,22,pittsburghtiles);
    set_bkg_tiles(0,0,40,18, pittsburghmap);

    set_win_tiles(0,0, 5,1, windowmap);
    move_win(7,135);



    set_sprite_data(0, 8, StickMan); //Defines the sprite data

    set_sprite_tile(0,0);            //defines the number of tiles

    playerLocation[0] = 10;
    playerLocation[1] = floorYposition;
    jumping = 0;

    move_sprite(0, playerLocation[0], playerLocation[1]);

    DISPLAY_ON; //Turns on display
    SHOW_BKG; // Must be in order 
    SHOW_WIN;
    SHOW_SPRITES; //Will show the sprites......completely forgot this when compiling the first time.

    while(1){
        if((joypad() & J_A) || jumping == 1){
            jump();
            
        }
        if(joypad() & J_RIGHT){
            playerLocation[0] = playerLocation[0] + 2;
            move_sprite(0, playerLocation[0], playerLocation[1]);
            
        }
        if(joypad() & J_LEFT){
            playerLocation[0] = playerLocation[0]  -2;
            move_sprite(0, playerLocation[0], playerLocation[1]);
            
        }
        if(joypad() & J_DOWN){
            playerLocation[1] = playerLocation[1]  + 2;
            move_sprite(0, playerLocation[0], playerLocation[1]);
            
        }
        scroll_bkg(1,0);
        performantDelay(4);

    }
}