#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <stdio.h>
#include "cursecolor.h"

const int col_terminal = 1;
const int col_bg = 2;
const int col_border = 3;
const int col_tbar = 4;
const int col_wcont = 5;

const char lowerletters[26] = {
    'a','b','c','d','e','f','g','h','i','j',
    'k','l','m','n','o','p','q','r','s','t',
    'u','v','w','x','y','z'
};

std::string menu = "/";

typedef struct {
    int x;
    int y;
} Pos;

void draw_horizline_aty(int y){
    mvaddch(y,0, '+');
    mvaddch(y,78, '+');
    for(int i=1;i<78;i++) mvaddch(y,i, '-');
}

void draw_horizline2_aty(int y, int color){
    mvaddch(y,0, '|');
    mvaddch(y,78, '|');
    setcolor(color);
    for(int i=1;i<78;i++) mvaddch(y,i, ' ');
    setcolor(col_border);
}

void draw_tbar(std::string tbtext){
    setcolor(col_tbar);
    mvaddstr(1, 2, tbtext.c_str());
}

void draw_window(){
    setcolor(col_border);
    draw_horizline_aty(0);
    draw_horizline_aty(2);
    draw_horizline_aty(22);

    draw_horizline2_aty(1, col_tbar);
    for(int i=3;i<22;i++) draw_horizline2_aty(i, col_wcont);

    draw_tbar("[-] Program Manager");

    setcolor(col_terminal);
    for(int i=0;i<23;i++) mvaddch(i, 79, ' ');
    for(int i=0;i<80;i++) mvaddch(23, i, ' ');
    
    refresh();   
}

void draw_menu(){

}

int main(){
    char key = 0;
    Pos curpos = {0,0};

    initscr();
    start_color();
    noecho();
    
    move(0,0);

    init_pair(col_terminal, 10, 0);
    init_pair(col_bg, 15, 6);
    init_pair(col_border, 7, 8);
    init_pair(col_tbar, 15, 4);
    init_pair(col_wcont, 0, 15);

    fillwithcolor(col_bg);
    refresh();

    draw_window();
    
    while(key!=0x1b){
        key = getch();
    }
    
    //std::cout << '\n';
    endwin();
    return 0;
}