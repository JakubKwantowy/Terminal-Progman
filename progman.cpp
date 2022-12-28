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

bool dgb = 0;

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

Pos curpos = {0,0};

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
    setcolor(col_border);
    attron(A_BOLD);
    mvaddstr(1, 2, "[-]");
    setcolor(col_tbar);
    attron(A_BOLD);
    mvaddstr(1, 6, tbtext.c_str());
    attroff(A_BOLD);
}

void draw_window(){
    setcolor(col_border);
    draw_horizline_aty(0);
    draw_horizline_aty(2);
    draw_horizline_aty(22);

    draw_horizline2_aty(1, col_tbar);
    for(int i=3;i<22;i++) draw_horizline2_aty(i, col_wcont);

    setcolor(col_wcont);
    attron(A_BOLD);
    mvaddstr(3, 3, "File ");
    attroff(A_BOLD);

    /*
    3- File Menu
    */

    if(!menu.compare("/")){
        
    }else if(!menu.compare("/file/")){
        setcolor(col_border);
                       // 00
                       // 567
        mvaddstr(4, 3, "+-----+");
        mvaddstr(5, 3, "| Run |");
        mvaddstr(6, 3, "+-----+");
    }

    draw_tbar("Program Manager");

    setcolor(col_terminal);
    for(int i=0;i<23;i++) mvaddch(i, 79, ' ');
    for(int i=0;i<80;i++) mvaddch(23, i, ' ');
    
    refresh();  
}

void menu_draw(std::string newmenu){
    menu = newmenu;

    draw_window();
    move(curpos.y, curpos.x); 
}

int main(){
    char key = 0;
    char mych = 0;

    WINDOW *currwindow = initscr();
    start_color();
    noecho();
    keypad(currwindow, true);
    
    move(0,0);

    init_pair(col_terminal, 10, 0);
    init_pair(col_bg, 15, 6);
    init_pair(col_border, 7, 8);
    init_pair(col_tbar, 15, 4);
    init_pair(col_wcont, 0, 7);

    fillwithcolor(col_bg);
    refresh();

    draw_window();
    mych = mvinch(0,0);
    
    while(key!=0x1b){
        key = getch();
        if(dgb) printf("\n%02X", key);
        switch(key){
            case 0x3:
                curpos.y--;
                move(curpos.y,curpos.x);
            break;
            case 0x2:
                curpos.y++;
                move(curpos.y,curpos.x);
            break;
            case 0x4:
                curpos.x--;
                move(curpos.y,curpos.x);
            break;
            case 0x5:
                curpos.x++;
                move(curpos.y,curpos.x);
            break;
            case 0xa:
                if(curpos.x == 3 && curpos.y == 1) key = 0x1b;
                else if(curpos.y == 3){
                     if(curpos.x > 2 && curpos.x < 7) menu_draw("/file/");
                }

                if(!menu.compare("/file/")){
                    if(curpos.x > 4 && curpos.x < 8){
                        if(curpos.y == 5) key = 0x1b;
                    }
                }
            break;
            case 65:
                dgb = !dgb;
            break;
        }
    }
    
    endwin();
    return 0;
}