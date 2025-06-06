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

//커서를 움직여 모드를 선택하는 함수. 모드 숫자를 반환함.
unsigned char mode_selection_main(char*(*info)[MENU]);

//메인화면 ui를 그림
void drawUI_main(char*(*menu)[MENU]);

/**
모드 설정.
0=메인화면. 나머지 번호는 각 번호에 맞춤
*/


int main(void) {
    SetFixedConsoleSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
    DisableConsoleResize();
    srand(time(NULL));

    //dynamic 메모리 할당, 사실 잘은 몰라도됨
    Text words;
    words.reference = "words.txt";
    words.length = count_lines_of_file(words.reference);
    if (words.length == 0) {
        perror("파일이 비어있음");
        system("pause");
        return 1;
    }
    else if (words.length == -1) {
        perror("파일이 존재하지 않음");
        system("pause");
        return 1;
    }

    Text sentences;
    sentences.reference = "sentences.txt";
    sentences.length = count_lines_of_file(sentences.reference);
    if (sentences.length == 0) {
        perror("파일이 비어있음");
        system("pause");
        return 1;
    }
    else if (sentences.length == -1) {
        perror("파일이 존재하지 않음");
        system("pause");
        return 1;
    }
    
    words.arr = (char**)malloc(sizeof(char*) * words.length);
    sentences.arr = (char**)malloc(sizeof(char*) * sentences.length);
    if (!words.arr || !sentences.arr) {
        perror("메모리 할당 실패");
        system("pause");
        return 1;
    }

    FILE* fp = fopen(words.reference, "r");
    if (!fp) {
        perror("메모리 할당 실패");
        system("pause");
        free(words.arr);
        free(sentences.arr);
        return 1;
    }
    txt_to_arr(&words, &fp);
    fclose(fp);

    fp = fopen(sentences.reference, "r");
    if (!fp) {
        perror("메모리 할당 실패");
        system("pause");
        free(words.arr);
        free(sentences.arr);
        return 1;
    }
    txt_to_arr(&sentences, &fp);
    fclose(fp);

    unsigned char mode =0;

    char* menu[MENU] = {
        "1. 자리연습", "2. 낱말연습", "3. 짧은글연습", "4. 놀이", "5. 설정", "6. 크레딧", "7. 종료"
    };
    char* menu_info[MENU] = {
        "글자판의 위치를 익히는 곳입니다.\n\n숫자, 알파벳, 특수문자 등\n여러 문자들의 위치를 알 수 있습니다.",
        "낱말을 입력하며 글쓰기를 연습합니다.\n\n낱말을 입력하고 Enter 혹은 Space Bar\n글쇠를 눌러 다음 낱말을 입력합니다.",
        "짧은 글 10문으로 글쓰기를 연습합니다.\n\n빠르게 입력하는 것도 중요하지만,\n정확하게 입력하는 것이 더욱 중요합니다.",
        "게임을 통해 타자를 연습할 수 있습니다.",
        "설정은 제작중.\n\n유저 데이터 혹은 타자 데이터 통계,\n게임 설정 등 만들수도 있고 안만들 수도 있고",
        "Motivated by Hancom\n\nDeveloped in Konkuk University",
        "TypePracticing을 끝냅니다.",
    };

    while (mode!=MENU) {
        switch (mode) {
        case 0:
            system("cls");
            drawUI_main(&menu);
            mode = mode_selection_main(&menu_info);
            //system("cls");
            //printf("%hhu\n",mode);
            //system("pause");
            break;
        case 1:
            system("cls");
            key_prac();
            mode = 0;
            break;
        case 2:
            mode = 0;
            break;
        case 3:
            system("cls");
            sentence_prac(&sentences);
            mode = 0;
            break;
        case 4:
            system("cls");
            play_game(&words);
            mode = 0;
            break;
        case 5:
            mode = 0;
            break;
        case 6:mode = 0; break;
        case 7:
            break;
        case 98:
            //텍스트 읽기 테스트
            txt_read_checker(&words, &sentences);
            system("pause");
            mode = 0;
            break;
        case 99:
            key_checker();//키 입력 아스키코드 확인용, 입력기능 구현 확인용
        default:
            printf("메뉴를 불러오는 데 실패하였습니다! 게임을 종료합니다.\n\n");
            system("pause");
            mode = 7;
            break;
        }
        
    }

    //반드시 해제
    free(words.arr);
    free(sentences.arr);
    return 0;
}

void drawUI_main(char*(* menu)[MENU]) {
    short x= WINDOWS_WIDTH / 2 - 7, y= WINDOWS_HEIGHT / 7;
    gotoxy(x,y);
    printf("TypePracticing");
    
    y += 5;
    
    for(unsigned char i=0;i<MENU;i++,y+=2){
        x = WINDOWS_WIDTH / 2 - 28;
        gotoxy(x, y);
        printf("%s",(*menu)[i]);
    }

    printf("\n");y = WINDOWS_HEIGHT;
    gotoxy(0, y);
    printf("v 0.0.1");
}

unsigned char mode_selection_main(char* (*info)[MENU]) {
    short x = WINDOWS_WIDTH / 2 - 28;
    short y = WINDOWS_HEIGHT / 7 + 5;
    
    unsigned char n = 1;
    unsigned char ch = 1;
    print_in_rectangle(x + 21, WINDOWS_HEIGHT / 7 + 5, 40, 13, (*info)[n - 1]);
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
                else { n = 1; continue; }
                break;
            case 80://아래
                if (n < MENU) { n++; y += 2; }
                else { n = MENU; continue; }
                break;
            default:
                continue;
            }
            break;
        default:
            continue;
        }
        print_in_rectangle(x + 21, WINDOWS_HEIGHT / 7 + 5, 40, 13, (*info)[n - 1]);
    }
}