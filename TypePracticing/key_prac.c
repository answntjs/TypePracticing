#include "std.h"

#define KEY_PRACTICE_LENGTH 30

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
        drawUI_game(&Stat, current, KEY_PRACTICE_LENGTH);

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
        if (input == 27) break;

        Stat.type_speed = 60 * (double)Stat.type_count / (now_time - start_time);
        if (Stat.type_speed > Stat.type_peak) Stat.type_peak = Stat.type_speed;

        Stat.accuracy = 100 * (double)Stat.correct / (Stat.correct + Stat.incorrect);
        if (Stat.accuracy > Stat.accuracy_peak) Stat.accuracy_peak = Stat.accuracy;
        
    }
    
    print_result(&Stat);
}
