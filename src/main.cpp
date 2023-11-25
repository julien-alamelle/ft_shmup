#include <ncurses.h>

int main(void)
{
	initscr();

	printw("Hello World");
	move(LINES-1, COLS-1);
	addch('.');
	refresh();
	getch();
	endwin();

	return 0;
}
