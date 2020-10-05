#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wrong number of input parameters\n");
        return -1;
    }
	
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Wrong file name\n");
        return -1;
    }

    int ch = 0;
    int linesNum = 0;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '\n') {
            linesNum += 1;
        }
    }
    fseek(f, 0, SEEK_SET);

    char *lines[linesNum];
    memset(lines, 0, linesNum * sizeof(char *));
    int i = 0;
    size_t lineLen;
    int maxLen = 0;
    while (getline(&lines[i], &lineLen, f) != -1) {
        if (strlen(lines[i]) > maxLen) {
            maxLen = strlen(lines[i]);
        }
        i += 1;
    }
    fclose(f);

    WINDOW *win;
    int currentLine = 0;

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    printw("File: %s", argv[1]);
    refresh();

    int linesWin = LINES - 2 * DX - 2;
    int colsWin = COLS - 2 * DX - 2;
    win = newwin(linesWin + 2, colsWin + 2, DX, DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);

    int firstRow = 0;
    int firstColumn = 0;
    ch = 0;    
    do {
        switch (ch) {
            case ' ':
            case KEY_NPAGE:
                if (firstRow + linesWin < linesNum) {
                    firstRow += linesWin;
                }
                else {
                    firstRow = linesNum - 1;
                }
                break;
            case KEY_PPAGE:
                if (firstRow - linesWin >= 0) {
                    firstRow -= linesWin;
                }
                else {
                    firstRow = 0;
                }
                break;
            case KEY_RIGHT:
                if (firstColumn < maxLen - 1) {
                    firstColumn += 1;
                }
                break;
            case KEY_LEFT:
                if (firstColumn > 0) {
                    firstColumn -= 1;
                }
                break;
            case KEY_UP:
                if (firstRow > 0) {
                    firstRow -= 1;
                }
                break;
            case KEY_DOWN:
                if (firstRow < linesNum - 1) {
                    firstRow += 1;
                }
                break;
        }

        werase(win);
        wmove(win, 1, 0);
        for (int i = firstRow; i < firstRow + linesWin && i < linesNum; ++i) {
            if (firstColumn < strlen(lines[i])) {
                wprintw(win, " %4d >>> %.*s", i + 1, (firstColumn + colsWin > strlen(lines[i])) ? strlen(lines[i]) : colsWin, lines[i] + firstColumn);
            }
            else {
                wprintw(win, " %4d >>>\n", i + 1);
            }
        }
        box(win, 0, 0);
        wrefresh(win);
    } while((ch = wgetch(win)) != 27);

    endwin();
    for (int i = 0; i < linesNum; ++i) {
        free(lines[i]);
    }

    return 0;
}
