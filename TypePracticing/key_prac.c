#include "std.h"

#define KEY_PRACTICE_LENGTH 20

void key_prac(void) {
    Status Stat = { 0, 0, 0, 0, 0, 0, 1 };
    char generated[KEY_PRACTICE_LENGTH];
    char input;
    int i, current = 0;

    // 난수로 문자 생성 (영문 대소문자 + 숫자)
    for (i = 0; i < KEY_PRACTICE_LENGTH; i++) {
        int r = rand() % 62;//숫자 10+소문자 26+대문자 26
        if (r < 10) generated[i] = '0' + r;
        else if (r < 36) generated[i] = 'A' + (r - 10);
        else generated[i] = 'a' + (r - 36);
    }


    gotoxy(WINDOWS_WIDTH / 16, WINDOWS_HEIGHT / 8);
    printf("자리연습");

    time_t start_time = time(NULL);
    time_t now_time;
    while (current < KEY_PRACTICE_LENGTH) {
        gotoxy(WINDOWS_WIDTH / 16, WINDOWS_HEIGHT / 8 + 1);
        printf("%-8s%2d/%-20d%-11s%4.0f/%-9s %-8s%3.0f/100", "진행도:", (current + 1), KEY_PRACTICE_LENGTH, "분당 타수:", Stat.type_speed, "분", "정확도:", Stat.accuracy);
        gotoxy(WINDOWS_WIDTH / 16, WINDOWS_HEIGHT / 8 + 2);
        bar(30, current, KEY_PRACTICE_LENGTH); printf(" "); bar(25, Stat.type_speed, Stat.type_peak); printf(" "); bar(20, Stat.accuracy, 100);

        print_in_rectangle(WINDOWS_WIDTH / 2 - 5 * 4 - 3, WINDOWS_HEIGHT / 2 - 2, 5*9, 1, "");
        for (i = current-4; i <= current+4; i++) {
            if (i < 0)printf("     ");
            else if (i == current) {
                printf(" [%c] ", generated[i]);
            }
            else if (i > KEY_PRACTICE_LENGTH - 1);
            else{
                printf("  %c  ", generated[i]);
            }
        }
        gotoxy(WINDOWS_WIDTH / 2 -1, WINDOWS_HEIGHT / 2-2);

        fflush(stdout);
        input = _getch();
        now_time = time(NULL);
        if (now_time == start_time)now_time++;

        switch (input) {
        case 0:
        case 224:
            _getch();
            break;
        case '\n':
        case '\t':
        case 27:
        case '\b':
            break;
        default:
            Stat.type_count++;
            if (input == generated[current]) {
                current++;
                Stat.correct++;
            }
            else {
                Beep(255, 1);
                Stat.incorrect++;
            }
            break;
        }
        Stat.type_speed = 60 * (double)Stat.type_count / (now_time - start_time);
        if (Stat.type_speed > Stat.type_peak) Stat.type_peak = Stat.type_speed;

        Stat.accuracy = 100 * (double)Stat.correct / (Stat.correct + Stat.incorrect);
        if (Stat.accuracy > Stat.accuracy_peak) Stat.accuracy_peak = Stat.accuracy;
        
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
