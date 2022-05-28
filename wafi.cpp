// Wait All F*cking Input
// Copyright (C) 2022  Yury Moskov
//
// Licensed under GPL 3.0
// See LICENSE or https://www.gnu.org/licenses/gpl-3.0.txt
//

#include <termios.h>
#include <iostream>
#include <unistd.h>

// Terminal stuff
struct termios old_attr;

void disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_attr);
}

void enable_raw_mode() {
	tcgetattr(STDIN_FILENO, &old_attr);
	atexit(disable_raw_mode);

	struct termios new_attr = old_attr;
	new_attr.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_attr);
}

/*
1) Enter non-cannonical input mode
2) Handle it properly
3) Read all input
4) Exit non-cannonical input mode
5) Print input

It's simple as that.
*/

#define BACKSPACE_CHAR 127
#define CTRL_D_CHAR 4

#include "buffer.h"
#include <cstring>

int main(int argc, char* argv[]) {
	bool debug = false;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
			debug = true;
		}

		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			printf("Use: %s [options]\n"
			"Options:\n"
			"\t--debug - enable debug mode\n"
			"\t--help - show this message\n", argv[0]);
			return 0;
		}
	}

	enable_raw_mode();
	EditableBuffer buffer;
	char ch;

	do {
		std::cin.read(&ch, 1);

		if (ch == BACKSPACE_CHAR) {
			buffer.pop();
		} else if (ch == CTRL_D_CHAR) {
			// End of File
		} else {
			buffer.put(ch);
		}

		// clear stdout
		printf("\033[H\033[J");
		std::flush(std::cout);

		if (debug) {
			printf("%d,%d\n", buffer.getIndex(), buffer.length());
		}
		printf("%s", buffer.str().c_str());
	} while(!std::cin.eof() && ch != CTRL_D_CHAR);

	if (debug) {
		// clear stdout
		printf("\033[H\033[J");
		std::flush(std::cout);

		// printf("%d\n", buf.pos);
		printf("%s", buffer.str().c_str());
	}
	return 0;
}

