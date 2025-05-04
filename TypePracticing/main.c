/*

리소스 로딩...(텍스트파일, 사용자 정보 읽기)
메인화면
1. 자리연습 - 단일문자; Key Prac
2. 낱말연습 - 단어연습; Word Prac
3. 짧은글연습 - 단문장 연습; Sentence Prac
4. 긴글연습 - ; Essay Prac
5. 놀이
6. 환경설정
7. 크레딧
8. 종료



	*/


#include "std.h"
#define WINDOWS_WIDTH 96
#define WINDOWS_HEIGHT 30

void gotoxy(short x, short y);
void SetFixedConsoleSize(short width, short height);
void DisableConsoleResize();
unsigned char mode_selection_main();
drawUI_main();

typedef struct mode{
    unsigned char mode;
    char name[14];
    short default_x;
    short default_y;
}Mode;

unsigned char mode = 0;/**
모드 설정.
0=메인화면. 나머지 번호는 각 번호에 맞춤
*/

void main(void) {
    SetFixedConsoleSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
    DisableConsoleResize();
    
    Mode Key_prac = { 1,"자리연습", WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2 };
    Mode Word_prac = { 2,"낱말연습", WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2 };
    Mode Sentence_prac = { 3,"짧은글연습", WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2 };
    Mode Essay_prac = { 4,"긴글연습", WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2 };
    Mode Play = { 5,"놀이", WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2 };
    Mode Config = { 6,"환경설정", WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2 };
    Mode Credit = { 7,"크레딧", WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2 };
    Mode Quit = { 8,"종료", WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2 };

    while (mode!=8) {
        switch (mode) {
        case 0:
            drawUI_main();
            mode = mode_selection_main();
            system("cls");
            printf("%hhu\n",mode);
            system("pause");
            system("cls");
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:mode = 0;
        case 8:break;
        default:
            printf("메뉴를 불러오는 데 실패하였습니다! 게임을 종료합니다.\n\n");
            system("pause");
            goto end;
        }
        
    }


end:;
}



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
    // 크기 조절 불가 및 최대화 버튼 제거
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_THICKFRAME); // 최대화버튼, 크기조절 프레임 제거
    SetWindowLong(hwnd, GWL_STYLE, style);
}

drawUI_main() {
    short x= WINDOWS_WIDTH / 2 - 7, y= WINDOWS_HEIGHT / 5;
    gotoxy(x,y);
    printf("TypePracticing");
    
    y += 5;
    
    char menu[8][14] = {
        "1. 단어연습", "2. 낱말연습", "3. 짧은글연습", "4. 긴글연습", "5. 놀이", "6. 환경설정", "7. 크레딧", "8. 종료"
    };
    for(unsigned char i=0;i<8;i++,y+=2){
        gotoxy(x, y);
        printf("%s",menu[i]);
        x = WINDOWS_WIDTH / 2 - 7;
    }

    printf("\n");y = WINDOWS_HEIGHT;
    gotoxy(0, y);
    printf("v 0.0.1");
}

unsigned char mode_selection_main() {
    short x = WINDOWS_WIDTH / 2 - 7;
    short y = WINDOWS_HEIGHT / 5 + 5;
    
    unsigned char n = 1;
    unsigned char ch = 1;
    while (ch != '\n' && ch != ' ') {
        gotoxy(x, y);
        ch = getch();
        switch (ch) {
        case '\n':
        case 13:
        case ' ':
            return n;
            break;
        case 224://화살표
            ch = getch();
            switch (ch) {
            case 72://위
                if (n > 1) { n--; y -= 2; }
                else { n = 1; }
                break;
            case 80://아래
                if (n < 8) { n++; y += 2; }
                else { n = 8; }
            }
        default:;
        }
    }
}