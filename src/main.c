#include <ncurses.h>
#include <stdio.h>

int rulare(int joc) {
    while (joc == 1) {
        clear();
        initscr();
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_GREEN);

        // ゲームボード描画
        int x, y;
        getmaxyx(stdscr, x, y);
        move(0, y / 2);
        printw("Wordle Game (Developing!)\n");
        refresh();

        // ゲームボード作成
        int h = 5, w = 10, sty = 5, stx = x / 2, i, j;
        int pozx[6][6], pozy[6][6];

        for (i = 0; i < 6; i++) {
            for (j = 0; j < 5; j++) {
                WINDOW* win = newwin(h, w, sty, stx);
                refresh();
                box(win, 0, 0);
                wrefresh(win);
                pozx[i][j] = sty + h / 2;
                pozy[i][j] = stx + w / 2;
                stx = stx + 10;
            }
            stx = x / 2;
            sty = sty + 5;
        }

        joc = 0;
    }
    return 0;
}

int main() {
    int joc = 1;
    clear();
    rulare(joc);
    return 0;
}

