#include "std.h"

void gotoxy(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetFixedConsoleSize(short width, short height) {
    HWND console = GetConsoleWindow();
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // 1단계: 커서 숨기기 (선택 사항)
    //CONSOLE_CURSOR_INFO cursorInfo;
    //GetConsoleCursorInfo(hOut, &cursorInfo);
    //cursorInfo.bVisible = FALSE;
    //SetConsoleCursorInfo(hOut, &cursorInfo);

    // 2단계: 콘솔 창 크기 제한을 위해 화면 버퍼 크기 조정
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(hOut, bufferSize);

    // 3단계: 콘솔 윈도우 크기 조정
    SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
}

void DisableConsoleResize() {
    HWND hwnd = GetConsoleWindow();
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_THICKFRAME); // 최대화버튼, 크기조절 프레임 제거
    SetWindowLong(hwnd, GWL_STYLE, style);
}

void bar(int length, double numerator, double denominator) {
    int i;
    for (i = 0; i < length * numerator / denominator; i++) printf("#");
    for (i; i < length; i++) printf("-");
}

int count_lines_of_file(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {//파일이 존재하지 않거나 비어있는 경우
        perror("파일 읽기 실패.");
        system("pause");
        return -1;
    }

    int count = 0;
    char buffer[WINDOWS_WIDTH];
    while (fgets(buffer, sizeof(buffer), fp)) count++;

    fclose(fp);
    return count;
}

void txt_to_arr(Text* text, FILE** fp) {
    char buffer[WINDOWS_WIDTH];
    for (int i = 0; i < (*text).length; i++) {
        if (!fgets(buffer, sizeof(buffer), *fp)) break;
        buffer[strcspn(buffer, "\r\n")] = '\0';

        (*text).arr[i] = (char*)malloc(strlen(buffer) + 1);
        if (!(*text).arr[i]) {
            perror("메모리 할당 실패");
            system("pause");
            break;
        }
        strcpy((*text).arr[i], buffer);
    }
}


void print_in_rectangle(short coord_x, short coord_y, short size_x, short size_y, char* str) {
    int i, j, l, k;
    k = 0, l = 0;
    for (i = 0; i < size_y; i++) {
        gotoxy(coord_x, coord_y + i);
        for (j = 0; j < size_x; j++) {
            if (str[k] == '\0') l = 1;
            if (str[k] == '\n') l++, k++;
            if (l)printf(" ");
            else {
                printf("%c", str[k]);
                k++;
            }
        }
        l--;
        if (l < 1)l = 0;
    }
    gotoxy(coord_x, coord_y);
    return;
}


void get_random_int_arr(int(*arr)[], int size, int max, int min) {
    for (int i = 0; i < size; i++) {
        (*arr)[i] = rand() % (max - min + 1) + min;
    }
}