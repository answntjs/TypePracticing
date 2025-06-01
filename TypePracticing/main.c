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

51. 과제요구사항 게임
52. 산성비?

	*/


#include "std.h"

#define MENU 7//메뉴의 수. 마지막 번호는 무조건 종료

unsigned char mode_selection_main();
drawUI_main();

unsigned char mode = 98;/**
모드 설정.
0=메인화면. 나머지 번호는 각 번호에 맞춤
*/


int main(void) {
    SetFixedConsoleSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
    DisableConsoleResize();

    Text words;
    words.reference = "words.txt";
    words.length = count_lines_of_file(words.reference);
    if (words.length == 0) {
        perror("파일이 비어있음.");
        return 1;
    }
    else if (words.length == -1) {
        perror("파일이 존재하지 않음.");
        return 1;
    }

    Text sentences;
    sentences.reference = "sentences.txt";
    sentences.length = count_lines_of_file(sentences.reference);
    if (sentences.length == 0) {
        perror("파일이 비어있음.");
        return 1;
    }
    else if (sentences.length == -1) {
        perror("파일이 존재하지 않음.");
        return 1;
    }
    
    words.arr = (char**)malloc(sizeof(char*) * words.length);
    sentences.arr = (char**)malloc(sizeof(char*) * sentences.length);
    if (!words.arr || !sentences.arr) {
        perror("메모리 할당 실패");
        return 1;
    }

    FILE* fp = fopen(words.reference, "r");
    if (!fp) {
        perror("메모리 할당 실패");
        free(words.arr);
        free(sentences.arr);
        return 1;
    }
    txt_to_arr(&words, &fp);
    fclose(fp);

    fp = fopen(sentences.reference, "r");
    if (!fp) {
        perror("메모리 할당 실패");
        free(words.arr);
        free(sentences.arr);
        return 1;
    }
    txt_to_arr(&sentences, &fp);
    fclose(fp);



    while (mode!=MENU) {
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
        case 6:mode = 0; break;
        case 7:
            break;
        case 98:
            txt_read_checker(&words, &sentences);
            system("pause");
            mode = 0;
            break;
        case 99:
            //key_checker();//키 입력 아스키코드 확인용, 입력기능 구현 확인용
        default:
            printf("메뉴를 불러오는 데 실패하였습니다! 게임을 종료합니다.\n\n");
            system("pause");
            mode = 7;
            break;
        }
        
    }



    return 0;
}

drawUI_main() {
    short x= WINDOWS_WIDTH / 2 - 7, y= WINDOWS_HEIGHT / 5;
    gotoxy(x,y);
    printf("TypePracticing");
    
    y += 5;
    
    char * menu[MENU] = {
        "1. 단어연습", "2. 낱말연습", "3. 짧은글연습", "4. 놀이", "5. 설정", "6. 크레딧", "7. 종료"
    };
    for(unsigned char i=0;i<MENU;i++,y+=2){
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
                if (n < MENU) { n++; y += 2; }
                else { n = MENU; }
            }
        default:;
        }
    }
}