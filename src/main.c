#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ゲームのメイン実行関数
int rulare(int joc) {
    while (joc == 1) {
        // 画面の初期化
        clear();
        initscr();

        // 色の初期化
        start_color();

        // 色ペアの定義
        init_pair(1, COLOR_BLACK, COLOR_GREEN);
        init_pair(2, COLOR_BLACK, COLOR_YELLOW);

        // 画面のサイズを決定
        int x, y;
        getmaxyx(stdscr, x, y);
        move(0, y / 2);
        printw("Wordle\n");
        refresh();

        int h = 5, w = 10, sty = 5, stx = x / 2, i, j;
        int pozx[6][6], pozy[6][6];

        // ゲームボードの作成
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 5; j++) {
                WINDOW* win = newwin(h, w, sty, stx);
                refresh();
                box(win, 0, 0);
                wrefresh(win);
                // 位置の保存
                pozx[i][j] = sty + h / 2;
                pozy[i][j] = stx + w / 2;
                stx = stx + 10;
            }
            stx = x / 2;
            sty = sty + 5;
        }
        // カーソルの移動
        move(pozx[0][0], pozy[0][0]);
        i = 0;
        j = 0;
        int c = 0, event = 0, guess_nr, k, l, ap, final = 0;
        char temp;
        char cuvant[5];
        curs_set(0);
        noecho();
        // 辞書の定義
        char dict[29][6] = {
            "apple", "beach", "chair", "dance", "eagle", "flame", "grass",
            "honey", "inked", "joint", "kingy", "lemon", "magic", "nesty",
            "opale", "pathy", "quiet", "rosey", "snowy", "tanky", "unity",
            "water", "youth", "titan", "zebra", "vapor", "crave", "block"};
        int ver[29][6] = {0};
        char guess[5];

        // ランダムに単語を選択
        srand(time(NULL));
        guess_nr = rand() % (27 + 1 - 0);
        move(pozx[0][0], pozy[0][0]);

        // 入力のリスニング
        while ((i != 6) && (final != 1)) {
            int menu = 0;
            if ((j >= 0) && (j < 5)) {
                temp = getch();
                // 単語の削除
                if (temp == 127) {
                    if (j > 0) {
                        j--;
                    }
                    move(pozx[i][j], pozy[i][j]);
                    printw(" ");
                    move(pozx[i][j], pozy[i][j]);

                } else {
                    // 文字のみ入力を制限
                    if ((temp >= 65) && (temp <= 90)) {
                        temp = temp + 32;
                    }
                    // 大文字を小文字に変換
                    if ((temp >= 97) && (temp <= 122)) {
                        cuvant[j] = temp;
                        j++;
                        printw("%c", temp);
                        move(pozx[i][j], pozy[i][j]);
                    }
                    // 警告メッセージの表示
                    if (event == 1) {
                        move(1, 1);
                        printw("                                 ");
                        move(pozx[i][j], pozy[i][j]);
                        event = 0;
                    }
                    if (temp == '\n') {
                        WINDOW* win = newwin(10, 10, 0, 0);
                        box(win, 0, 0);
                        move(1, 1);
                        printw("Enter 5 letters word");
                        event = 1;
                        move(pozx[i][j], pozy[i][j]);
                    }
                    // メニューの表示
                    if (temp == ':') {
                        menu = 1;
                        move(40, 0);
                        printw(
                            "Game Menu\n[n] to new game.\n[x] to close.\n[:] to back game.");
                    }
                    while (menu == 1) {
                        char verf;
                        verf = getch();
                        if (verf == ':') {
                            menu = 0;
                            move(40, 0);
                            printw(
                                "                                           \n "
                                "                            \n                "
                                "                      \n                      "
                                "                            ");
                            move(pozx[i][j], pozy[i][j]);
                        }
                        // ゲーム終了
                        if (verf == 'x') {
                            joc = 0;
                            clear();
                            endwin();
                            return 1;
                        }
                        // ゲームのリセット
                        if (verf == 'n') {
                            menu = 0;
                            move(40, 0);
                            printw(
                                "                                           \n "
                                "                            \n                "
                                "                      \n                      "
                                "                            ");
                            move(pozx[i][j], pozy[i][j]);
                            joc = 1;
                            return 0;
                        }
                    }
                }
                // 色付けの実行
            } else if (j == 5) {
                move(pozx[i][j], pozy[i][j]);
                temp = getch();
                int ver[29][6] = {0};
                if (temp == '\n') {
                    j = 0;
                    for (k = 0; k < 5; k++) {
                        // 文字を対応する位置で確認
                        if (cuvant[k] == dict[guess_nr][k]) {
                            // 緑のボックスの表示
                            WINDOW* win = newwin(h, w, pozx[i][k] - h / 2,
                                                 pozy[i][k] - w / 2);
                            refresh();
                            wattron(win, COLOR_PAIR(1));
                            box(win, 0, 0);
                            redrawwin(win);
                            ver[guess_nr][k] = 1;
                            move(pozx[i][k], pozy[i][k]);
                            printw("%c", cuvant[k]);
                            wrefresh(win);
                        } else {
                            int ok = 1, ap = 0;
                            for (l = 0; l < 5; l++) {
                                // 単語内で文字を検索
                                if ((cuvant[k] == dict[guess_nr][l]) &&
                                    (ok == 1) && (ver[guess_nr][l] == 0)) {
                                    ver[guess_nr][l] = 1;
                                    int m = 0;
                                    // 重複する文字があるか確認
                                    for (m = 0; m < 5; m++) {
                                        if (cuvant[k] == dict[guess_nr][m]) {
                                            ap++;
                                        }
                                        if ((cuvant[m] == dict[guess_nr][m]) &&
                                            (cuvant[k] == cuvant[m])) {
                                            ap--;
                                        }
                                    }
                                    // 黄色のボックスの表示
                                    if (ap != 0) {
                                        WINDOW* win =
                                            newwin(h, w, pozx[i][k] - h / 2,
                                                   pozy[i][k] - w / 2);
                                        refresh();
                                        wattron(win, COLOR_PAIR(2));
                                        box(win, 0, 0);
                                        redrawwin(win);
                                        move(pozx[i][k], pozy[i][k]);
                                        printw("%c", cuvant[k]);
                                        wrefresh(win);
                                    }
                                }
                            }
                        }
                    }
                    i++;
                    move(pozx[i][j], pozy[i][j]);
                } else if (temp == 127) {
                    if (j > 0) {
                        j--;
                    }
                    move(pozx[i][j], pozy[i][j]);
                    printw(" ");
                    move(pozx[i][j], pozy[i][j]);
                }
                // 最終的な単語の確認
                if (strcmp(cuvant, dict[guess_nr]) == 0) {
                    final = 1;
                }
            }
        }
        move(40 , 10);
        if (final == 1) {
            printw(
                "You Win!\n[Y] to new game");
        } else {
            printw(
                "You Lose...\nAns: %s\n[Y] to new game",
                dict[guess_nr]);
        }
        // 新しいゲームを開始
        if (getch() == 'y') {
            joc = 1;
        } else {
            joc = 0;
        }
    }

    return 0;
}

int main() {
    int joc = 1, n;
    // 初期化
    clear();
    n = rulare(joc);
    // 再プレイの確認
    if (n == 0) {
        joc = 1;
        rulare(joc);
    }
    // 画面の終了
    endwin();
    return 0;
}
