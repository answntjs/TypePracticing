#include "std.h"
#define SENTENCE_PRAC_NUM 10

void sentence_prac(Text* sentences) {
	gotoxy(WINDOWS_WIDTH / 16, WINDOWS_HEIGHT / 8);
	printf("짧은글쓰기");
	
	auto int index[SENTENCE_PRAC_NUM + 1];
	get_random_int_arr(&index, SENTENCE_PRAC_NUM, sentences->length - 1, 0);
	index[SENTENCE_PRAC_NUM] = -1;

	int num; num = 0;
	char buffer[WINDOWS_WIDTH + 1] = {NULL};
	int ch1, ch2;
	int position; position = 0;

	Status Stat = { 0, 0, 0, 0, 0, 0, 1};
	
	
	time_t start_time;
	time_t now;
	start_time = time(NULL);
	for(num=0;num<SENTENCE_PRAC_NUM;num++){
		//화면 지우기
		print_in_rectangle(0, WINDOWS_HEIGHT / 8 + 4, WINDOWS_WIDTH, 13, "");

		//5개 문장 표시, 더 없으면 안함
		for (int i = 0; i < 5; i++) {
			gotoxy(0, WINDOWS_HEIGHT / 8 + 4 + 3 * i);
			if (index[num + i] == -1) break;
			printf("%s", sentences->arr[index[num+i]]);
		}

		//버퍼 초기화
		strcpy(buffer, "");
		ch1 = 0;
		while (ch1 != 13) {
			now = time(NULL);
			if (now == start_time)now++;

			//UI 갱신
			gotoxy(WINDOWS_WIDTH / 16, WINDOWS_HEIGHT / 8 + 1);
			printf("%-8s%2d/%-20d%-11s%4.0f/%-9s %-8s%3.0f/100", "진행도:", (num + 1), SENTENCE_PRAC_NUM, "분당 타수:", Stat.type_speed, "분", "정확도:", Stat.accuracy);
			gotoxy(WINDOWS_WIDTH / 16, WINDOWS_HEIGHT / 8 + 2);
			bar(30, num, SENTENCE_PRAC_NUM); printf(" "); bar(25, Stat.type_speed, Stat.type_peak); printf(" "); bar(20, Stat.accuracy, 100);

			gotoxy(position, WINDOWS_HEIGHT / 8 + 5);
			ch1 = _getch();
			//좌우 화살표로 이동하는건 일단 보류;;;; 머리아프고 일단 구현이 급합
			if (ch1 == 0 || ch1 == 224) {//function keys
				/*ch2 = _getch();
				if (ch1 == 224 && ch2 == 75) {
					if (position <= 0) position = 0;
					else position--;
				}
				else if (ch1 == 224 && ch2 == 77) {
					if (position >= WINDOWS_WIDTH) position = WINDOWS_WIDTH;
					else position++;
				}*/
				ch1 = _getch();

			}
			else if (ch1 == '\b') {//backspace
				//memmove(buffer + position, buffer + position + 1, WINDOWS_WIDTH - position + 1);
				position = (position > 0) ? --position : 0;
				buffer[position] = NULL;
				printf("\b \b");
			}
			else if (ch1 == 13)position = 0;//enter
			else if (ch1 == 27) break;//esc
			else if (ch1 == '\t');//tab
			else {
				//memmove(buffer + position + 1, buffer + position, WINDOWS_WIDTH - position);
				//buffer[WINDOWS_WIDTH] = NULL;
				buffer[position] = ch1;
				printf("%c", ch1);
				//if (!strncmp(buffer+position, sentences->arr[index[num]]+position, 1))Stat.correct++;
				if (buffer[position] == sentences->arr[index[num]][position]) Stat.correct++;
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

	gotoxy(WINDOWS_WIDTH / 2 - 2, WINDOWS_HEIGHT / 2);
	printf("결과");
	gotoxy(WINDOWS_WIDTH / 2 - 11, WINDOWS_HEIGHT / 2 + 2);
	printf("분당 타수:    %8.3lf", Stat.type_speed);
	gotoxy(WINDOWS_WIDTH / 2 - 11, WINDOWS_HEIGHT / 2 + 3);
	printf("최고 타수:    %8.3lf", Stat.type_peak);
	gotoxy(WINDOWS_WIDTH / 2 - 11, WINDOWS_HEIGHT / 2 + 4);
	printf("정확도:       %8.3lf", Stat.accuracy);
	gotoxy(WINDOWS_WIDTH / 2 - 13, WINDOWS_HEIGHT / 2 + 6);
	printf("Press any key to continue.");
	_getch();
}