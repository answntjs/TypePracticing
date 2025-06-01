#include "std.h"

void key_checker() {
	system("cls");
	int ch1, ch2;
	while (1) {
		if (_kbhit()) {
			if (GetAsyncKeyState(VK_SHIFT) & 0x8000);//virtual keys checker
			if (GetAsyncKeyState(VK_CONTROL) & 0x8000);
			if (GetAsyncKeyState(VK_CAPITAL) & 0x8000);
			if (GetAsyncKeyState(VK_MENU) & 0x8000);

			ch1 = _getch();
			if (ch1 == 0 || ch1 == 224) {//function keys
				ch2 = _getch();
				
				printf("%d %d\n", ch2, ch1);
			}
			else if (ch1 == 8)printf("\b \b");//backspace
			else if (ch1 == 13)printf("\n");//enter
			else if (ch1 == 27)system("cls");//esc
			else printf("%c", ch1);
		}

	}
}