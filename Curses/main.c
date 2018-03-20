#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include <panel.h>
#include <menu.h>
#include <form.h>


int main()
{
        /* Initialize curses */
        initscr();
        start_color();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        /* Initialize few color pairs */
        init_pair(1, COLOR_RED, COLOR_BLACK);

        attron(COLOR_PAIR(1));
        addstr(":::"); 
        addstr(".::"); 
        addstr(" ::"); 
        addstr(".:."); 
        addstr(".: "); 
        addstr(" : "); 
        addstr("..."); 
        addstr(".. "); 
        addstr(" . ");
        attroff(COLOR_PAIR(1));
        refresh();
        getch();

        endwin();
        return 0;
}