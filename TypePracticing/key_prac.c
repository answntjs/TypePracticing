#include "std.h"

#define KEY_PRACTICE_LENGTH 20

void key_prac(void) {
    Status status = { 0 };
    char generated[KEY_PRACTICE_LENGTH + 1];
    char input;
    int i, current = 0;

    // 난수로 문자 생성 (영문 대소문자 + 숫자)
    for (i = 0; i < KEY_PRACTICE_LENGTH; i++) {
        int r = rand() % 62;//숫자 10+소문자 26+대문자 26
        if (r < 10) generated[i] = '0' + r;
        else if (r < 36) generated[i] = 'A' + (r - 10);
        else generated[i] = 'a' + (r - 36);
    }
    generated[KEY_PRACTICE_LENGTH] = '\0';

    printf("자리 연습: 다음 문자를 입력하세요.\n\n");

    clock_t start = clock();
    while (current < KEY_PRACTICE_LENGTH) {
        // 줄 처음부터 출력
        printf("\r");
        for (i = current; i < KEY_PRACTICE_LENGTH; i++) {
            if (i == current) printf("[%c]", generated[i]);
            else printf(" %c ", generated[i]);
        }
        for (i = 0; i < current; i++) printf("   "); // 지워진 자리만큼 공백
        fflush(stdout);

        input = _getch();

        if (input == generated[current]) {
            printf("\r");
            current++;
            status.correct++;
        }
        else {
            Beep(255, 1);
            status.incorrect++;
        }
        status.type_count++;
    }
    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    status.type_speed = (status.type_count / duration) * 60.0;
    status.accuracy = 100.0 * status.correct / status.type_count;

    printf("\n\n[결과]\n");
    printf("정확도: %.2f%%\n", status.accuracy);
    printf("타자 속도: %.2f 타/분\n", status.type_speed);
    printf("맞은 수: %d, 틀린 수: %d\n", status.correct, status.incorrect);

    system("pause");
}
