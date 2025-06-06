#define ROUND 5 // 게임 라운드 수
#include "std.h"

 struct GameState {
    int round;             // 현재 라운드 (1~5)
    char* p_target_word;  // 목표 단어 (예: "bad")
    int current_pos;       // 현재 입력 위치 (0부터 시작)
    int max_length;  // 최대 단어 길이
} ;

void make_ui(struct GameState* game) {

    gotoxy(WINDOWS_WIDTH / 2 - 5, WINDOWS_HEIGHT / 3 + 2);
    printf("라운드 %d/%d \n%s", game->round + 1, ROUND,game->p_target_word);
    gotoxy(0, WINDOWS_HEIGHT / 3 + 4);
    for (int i = 0; i < strlen(game->p_target_word); i++) {

        printf("="); 
    }
    printf(">");
    gotoxy(game->max_length + 1, WINDOWS_HEIGHT / 3 + 4);
    printf(">");

}




int random_word(Text* words, int *wordlen,int num) {
    int a[1024];// 오버플로우 방지
    int count = 0;
    for (int i = 0; i < words->length; i++)
    {
        //printf("%s\n", words->arr[i]);
        if (wordlen[i] == num)
        {
            a[count] = i;
            count++;
        } 
    }
    if (!count)
    {
        exit(1);
    }
    return a[rand() % count];
}


int select_difficulty() {
    char* menu[] = { "쉬움", "보통", "어려움" };
    char* info[] = {
        "단어가 느린 속도로 떨어집니다.",
        "보통 속도와 적당한 난이도입니다.",
        "빠른 속도로 많은 단어가 등장합니다."
    };

    int selected = 0;
    while (1) {

        gotoxy(WINDOWS_WIDTH / 2 - 10, WINDOWS_HEIGHT / 3);
        printf("난이도 선택 (↑/↓ 이동, Enter 선택)");

        for (int i = 0; i < 3; i++) {
            gotoxy(WINDOWS_WIDTH / 2 - 5, WINDOWS_HEIGHT / 3 + 2 + i * 2);
            if (i == selected) {
                printf("> %s", menu[i]); 
                print_in_rectangle(WINDOWS_WIDTH / 2 + 10, WINDOWS_HEIGHT / 3 + 2, 40, 3, info[i]);
            }
            else {
                printf("  %s", menu[i]);
            }
        }

        int ch = _getch();
        if (ch == 224) {
            ch = _getch();
            if (ch == 72 && selected > 0) selected--;  // ↑
            if (ch == 80 && selected < 2) selected++;   // ↓
        }
        else if (ch == '\n' || ch == ' ') {
            return selected;  // Enter 선택
        }
    }
}

void play_game(Text* words) {


    int difficulty = select_difficulty();

    struct GameState game;
    game.round = 0;  // 초기 라운드 설정
    game.p_target_word = NULL;  // 초기 목표 단어 설정
    game.current_pos = 0;  // 초기 입력 위치 설정
    game.max_length = 0;  // 초기 최대 단어 길이 설정


    int* wordlength;
    wordlength = (int*)malloc(sizeof(int) * words->length);

    for (int i = 0; i < words->length; i++)
    {
        wordlength[i] = strlen(words->arr[i]);
    }




    int result[ROUND];

    for (int i = 0; i < ROUND; i++)
    {
        switch (difficulty)
        {
        case 0:  // 쉬움
            result[i] = random_word(words, wordlength, 3 + i * 2);  // 첫 번째 단어 선택
            break;
        case 1:  // 보통
            result[i] = random_word(words, wordlength, 4 + i* 2);
            break;
        case 2:  // 어려움
            result[i] = random_word(words, wordlength, 5 + i * 3);  // 두 번째 단어 선택
            break;
        default:
            break;
        }
    }
	game.max_length = strlen(words->arr[result[ROUND - 1]]);
    printf("%s", game.p_target_word);
    system("cls");



    while (1) {

        game.p_target_word = words->arr[result[game.round]];
        int ch = 0;
        char* writtenWord = (char*)calloc(strlen(game.p_target_word) + 1,sizeof(char));
        make_ui(&game);
        gotoxy(game.current_pos, WINDOWS_HEIGHT / 3 + 4);
        while (ch != 13) {

            ch = _getch();

            if (ch == '\b') {//backspace
                writtenWord[game.current_pos] = '\0'; // 현재 위치의 문자를 제거
                game.current_pos = (game.current_pos > 0) ? --game.current_pos : 0;
                printf("\b=\b");
            }
            else if (ch == 13)game.current_pos = 0;//enter
            else if (ch == 27) return;//esc
            else if (ch == '\t');//tab
            else if(game.current_pos < strlen(game.p_target_word)){
                
                writtenWord[game.current_pos] = ch;
                game.current_pos++;
                printf("%c", ch);
            }

        }
        if (!strcmp(writtenWord,game.p_target_word))//맞으면 0
        {
            // 정답
            gotoxy(0,  4);
            printf("%d", strcmp(writtenWord, game.p_target_word));
        }
        else
        {
            //오답
        }

        game.round++;
        if (game.round == ROUND)
        {
            break;
        }
    }
    free(wordlength);
    getch();
}

