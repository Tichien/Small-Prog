#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include <panel.h>
#include <menu.h>
#include <form.h>
#include <locale.h>


int main()
{
        /* Initialize curses */
		setlocale(LC_ALL, "");
        initscr();
        start_color();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        /* Initialize few color pairs */
        init_pair(1, COLOR_RED, COLOR_BLACK);

        attron(COLOR_PAIR(1));
		addstr("\u28FF");
		addstr("\u28FF");
		addstr("\u28FF");
		addstr("\u28FF");
		addstr("\u28FF");
		addstr("\n");
		addstr("\u28FF");
		addstr("\u28FF");
		addstr("\u28FF");
        attroff(COLOR_PAIR(1));
        refresh();
        getch();

        endwin();
        return 0;
}
