#include <ncurses.h>

#ifndef __cursecolor_h
#define __cursecolor_h

typedef unsigned char byte;

void setcolor(int color){
    attron(COLOR_PAIR(color));
}

void unsetcolor(int color){
    attroff(COLOR_PAIR(color));
}

void fillwithcolor(int color){
    bkgd(COLOR_PAIR(color));
}

#endif