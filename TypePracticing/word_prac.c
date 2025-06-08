#include "std.h"
#define WORD_PRAC_NUM 20

void word_prac(Text* words) {
	gotoxy(WINDOWS_WIDTH / 16, WINDOWS_HEIGHT / 8);
	printf("단어연습");
	
	auto int index[WORD_PRAC_NUM + 1];
	get_random_int_arr(&index, WORD_PRAC_NUM, words->length - 1, 0);
	index[WORD_PRAC_NUM] = -1;

	int num; num = 0;
	char buffer[WINDOWS_WIDTH + 1] = {NULL};
	int ch1;
	int position; position = 0;

	Status Stat = { 0, 0, 0, 0, 0, 0, 1};
	
	time_t start_time;
	time_t now;
	start_time = time(NULL);
	for(num=0;num<WORD_PRAC_NUM;num++){
		//화면 지우기
		print_in_rectangle(0, WINDOWS_HEIGHT / 8 + 4, WINDOWS_WIDTH, 13, "");

		//5개 문장 표시, 더 없으면 안함
		for (int i = 0; i < 5; i++) {
			gotoxy(0, WINDOWS_HEIGHT / 8 + 4 + 3 * i);
			if (index[num + i] == -1) break;
			printf("%s", words->arr[index[num + i]]);
		}

		gotoxy(0, WINDOWS_HEIGHT / 8 + 5);
		
		//버퍼 초기화
		strcpy(buffer, "");
		ch1 = 0;
		while (ch1 != 13 && ch1 != ' ') {
			now = time(NULL);
			if (now == start_time)now++;

			drawUI_game(&Stat, num, WORD_PRAC_NUM);

			gotoxy(position, WINDOWS_HEIGHT / 8 + 5);
			ch1 = _getch();
			if (ch1 == 0 || ch1 == 224) {
				ch1 = _getch();

			}
			else if (ch1 == '\b') {//backspace
				position = (position > 0) ? --position : 0;
				buffer[position] = NULL;
				printf("\b \b");
			}
			else if (ch1 == 13 || ch1 == ' ')position = 0;//enter
			else if (ch1 == 27) break;//esc
			else if (ch1 == '\t');//tab
			else {
				buffer[position] = ch1;
				printf("%c", ch1);
				if (buffer[position] == words->arr[index[num]][position]) Stat.correct++;
				else {
					Stat.incorrect++;
					Beep(255, 1);
				}
				position = (position < WINDOWS_WIDTH - 1) ? ++position : WINDOWS_WIDTH - 1;
				Stat.type_count++;
			}

			Stat.type_speed = 60 * (double)Stat.type_count / (now - start_time);
			if (Stat.type_speed > Stat.type_peak) Stat.type_peak = Stat.type_speed;

			Stat.accuracy = 100*(double)Stat.correct / (Stat.correct + Stat.incorrect);
			if (Stat.accuracy > Stat.accuracy_peak) Stat.accuracy_peak = Stat.accuracy;

		}
		if (ch1 == 27) break;
	}

	print_result(&Stat);
}