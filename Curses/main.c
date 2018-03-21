#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include <panel.h>
#include <menu.h>
#include <form.h>
#include <locale.h>

int braille_char_offset = 0x2800;

int pixel_map[4][2] = { {0x01, 0x08}, 
                        {0x02, 0x10},
                        {0x04, 0x20},
                        {0x40, 0x80} };


wint_t getcell(WINDOW* win, int col, int row){
        wchar_t wc[2] = {0};
        mvwinnwstr(win, row, col, wc, 1);
        return wc[0];
}

void setcell(WINDOW* win, int col, int row, wint_t c){
        wchar_t wc[2] = {0}; wc[0] = c;
        mvwaddnwstr(win, row, col, wc, 1);
}

int main()
{
        /*
        int k = 0;
        scanf("%d", &k);

        int data[k][2];

        for(int i = 0 ; i < k ; i++){
                data[i][0] = -1;
                data[i][1] = -1;
        }

        for(int i = 0 ; i < k ; i++){
                scanf("%d%d", &data[i][0], &data[i][1]);
        }

        int braille = 0x2800;
        */
        /* Initialize curses */
        setlocale(LC_ALL, "");

        initscr();
        start_color();
        //cbreak();
        noecho();
        keypad(stdscr, TRUE);

        init_pair(1, COLOR_GREEN, COLOR_RED);

        refresh();
        
        WINDOW* pad = newpad(10, 10);
        wborder(pad, '*', '*', '*', '*', '*', '*', '*', '*');
        
        wbkgd(pad, COLOR_PAIR(1));

        wint_t wi = 0;
        wchar_t wc[2] = {0};

        //winwstr(pad, wc);
        //mvwinnwstr(pad, 0, 0, wc, 1);
        //inwstr()
        setcell(pad, 0, 0, braille_char_offset + 0x01);
        wi = getcell(pad, 0, 0);

        //waddnwstr(pad, L"€", 1);
        //mvwinnwstr(pad, 0, 0, wc, 1);
       // mvaddstr(1, 0, L"\x2713");


        mvprintw(11, 0, "Wide char : %lc", wi);
        
        //refresh();
        prefresh(pad, 0, 0, 0, 0, 10, 10);
        //wrefresh(pad);
        /* Initialize few color pairs */

        //attron(COLOR_PAIR(1));

        /*
        for (int i = 0; i < k; ++i){
                int x = data[i][0], y = data[i][1];

                if(x != -1 && y != -1){
                        // operation binaire union ajoute les bits si ceux ci ne sont pas présent
                        braille |= pixel_map[y][x];
                }


        }
        printw("%lc\n", braille);
        */


       // attroff(COLOR_PAIR(1));
       

        int c = 0;

        while((c = getch()) != KEY_F(1)){
               /* int y = 0, x = 0;
                
                getmaxyx(stdscr, y, x);

                printw("LINES : %d\n", y);
                printw("COLS : %d\n", x);
                */
               prefresh(pad, 0, 0, 0, 0, 10, 10);
               //wrefresh(pad);
        }

        endwin();
        return 0;
}


