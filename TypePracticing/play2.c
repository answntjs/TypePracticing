#include "std.h"
#define LIFE 5
#define ROUND 5 // 게임 라운드 수

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
    int* a = (int*)malloc(sizeof(int) * words->length);
    if (!a) {
        perror("메모리 할당 실패");
        system("pause");
        exit(1);
    }
    int count = 0, i, r;

    for (i = 0; i < words->length; i++){
        //printf("%s\n", words->arr[i]);
        if (wordlen[i] == num)
        {
            a[count] = i;
            count++;
        } 
    }

    if (!count){
        exit(1);
    }

    r = a[rand() % count];
    free(a);
    return r;
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
            return selected;  // Enter or Space bar선택
        }
    }
}

void play_game(Text* words) {


    int difficulty = select_difficulty();
    printf("난이도선택완료\n");
    struct GameState game;
    game.round = 0;  // 초기 라운드 설정
    game.p_target_word = NULL;  // 초기 목표 단어 설정
    game.current_pos = 0;  // 초기 입력 위치 설정
    game.max_length = 0;  // 초기 최대 단어 길이 설정


    int* wordlength;
    wordlength = (int*)malloc(sizeof(int) * words->length);
    int max, min;
    max = 0, min = strlen(words->arr[0]);

    for (int i = 0; i < words->length; i++)
    {
        wordlength[i] = strlen(words->arr[i]);
        max = (max > wordlength[i]) ? max : wordlength[i];
        min = (min < wordlength[i]) ? min : wordlength[i];
    }
    printf("%d %d\n",max,min);

    //a 와 b의 i:round-i 내분점

    int result[ROUND];
    for (int i = 0; i < ROUND; i++){
        switch (difficulty){
        case 0:  // 쉬움
            result[i] = random_word(words, wordlength, (int)((min * (ROUND - i + 3) + max * i) / (ROUND + 3)));  //min, max의 0:8, 1:7,... 내분점
            break;
        case 1:  // 보통
            result[i] = random_word(words, wordlength, (int)((min * (ROUND - i + 1) + max * i) / (ROUND + 1)));//0:6, ...
            break;
        case 2:  // 어려움
            result[i] = random_word(words, wordlength, (int)((min * (ROUND - i - 1) + max * i) / (ROUND - 1)));//0:4, ...
            break;
        default:
            break;
        }
    }
	game.max_length = strlen(words->arr[result[ROUND - 1]]);
    system("cls");

    printf("%s", game.p_target_word);
    char* writtenWord = (char*)calloc(strlen(game.max_length) + 1, sizeof(char));
    if (!writtenWord) {
        perror("메모리 할당 실패");
        system("cls");
        exit(1);
    }
    int ch; ch = 0;
    int life; life = LIFE;
    while (life > 0) {
        ch = 0;
        game.p_target_word = words->arr[result[game.round]];
        make_ui(&game);
        gotoxy(game.current_pos, WINDOWS_HEIGHT / 3 + 4);
        while (ch != '\n' && ch != 27) {
            if (_kbhit()) {
                if (GetAsyncKeyState(VK_SHIFT) & 0x8000);//virtual keys checker
                if (GetAsyncKeyState(VK_CONTROL) & 0x8000);
                if (GetAsyncKeyState(VK_CAPITAL) & 0x8000);
                if (GetAsyncKeyState(VK_MENU) & 0x8000);

                ch = _getch();
                if (ch == 0 || ch == 224) { ch = _getch(); }
                else if (ch == 8) {
                    game.current_pos = (game.current_pos > 0) ? --game.current_pos : 0;
                    writtenWord[game.current_pos] = NULL;
                    printf("\b \b");
                }
                else if (ch == '\n')game.current_pos = 0;//enter
                else if (ch == 27)break;//esc
                else if (ch == '\t');
                else if (game.current_pos < game.max_length - 1) {
                    writtenWord[game.current_pos] = ch;
                    game.current_pos++;
                    printf("%c", ch);
                }
            }
        }
        if (!strcmp(writtenWord, game.p_target_word)) {
            // 정답
            gotoxy(0, 4);
            printf("%d", strcmp(writtenWord, game.p_target_word));
        }
        else {
            life--;
        }

        game.round++;
        if (game.round == ROUND) {
            break;
        }
    }
    free(wordlength);
    _getch();
}

