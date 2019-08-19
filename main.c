#include <gb/gb.h>
#include <stdio.h>
#include "simplepittsburgh.c"
#include "pittsburghmap.c"
#include <gb/font.h>
#include "windowmap.c"

void main(){
    font_t min_font;

    font_init();
    min_font = font_load(font_min); // 36 tile
    font_set(min_font);

    set_bkg_data(27,22,pittsburghtiles);
    set_bkg_tiles(0,0,40,18, pittsburghmap);

    set_win_tiles(0,0, 5,1, windowmap);
    move_win(7,135);
    SHOW_BKG;
    SHOW_WIN;
    DISPLAY_ON;
   

   while(1){
        scroll_bkg(1,0);
        delay(100);
   }

}