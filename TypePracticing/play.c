#define ROUND 5 // 게임 라운드 수
#include "std.h"

 struct GameState {
    int round;             // 현재 라운드 (1~5)
    char* p_target_word;  // 목표 단어 (예: "bad")
    int current_pos;       // 현재 입력 위치 (0부터 시작)
    int max_length;  // 최대 단어 길이
    double limit_time;
    char correct[ROUND];
} ;

 int select_difficulty() {
     char* menu[] = { "1. 쉬움", "2. 보통", "3. 어려움" };
     char* info[] = {
         "쉬움.",
         "적당한 난이도입니다.",
         "어려움."
     };

     int selected = 0;
     while (1) {

         gotoxy(WINDOWS_WIDTH / 2 - 3, WINDOWS_HEIGHT / 4);
         printf("난이도");

         for (int i = 0; i < 3; i++) {
             gotoxy(WINDOWS_WIDTH / 2 - 28, WINDOWS_HEIGHT / 3 + 2 + i * 2);
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
         else if (ch == 27) {
             return -1;
         }
     }
 }

void make_ui(struct GameState* game, char* dif) {
    gotoxy(WINDOWS_WIDTH / 2 - strlen(game->correct)/2 -1, WINDOWS_HEIGHT / 3 + 1);
    printf("%s", game->correct);
    gotoxy(WINDOWS_WIDTH / 2 - 14, WINDOWS_HEIGHT / 3 + 2);
    printf("난이도:%s   라운드 %d/%d \n%s", dif,game->round + 1, ROUND,game->p_target_word);
    gotoxy(0, WINDOWS_HEIGHT / 3 + 4);
    for (int i = 0; i < strlen(game->p_target_word); i++) {

        printf("="); 
    }
    printf(">");
    gotoxy(game->max_length + 1, WINDOWS_HEIGHT / 3 + 4);
    printf(">");

}

void time_ui(double limit_time, ULONGLONG t) {

    gotoxy(WINDOWS_WIDTH / 2 - 5, WINDOWS_HEIGHT / 3);
    printf("시간 %.2lf/%.2lf  ", limit_time - (double)t / 1000, limit_time);
}

int random_word(Text* words, int* wordlen, int num, int min, int max) {
    int a[1024];// 오버플로우 방지
    int count = 0;
    short ran = rand() % 3;

    for (int i = 0; i <= rand() % 2; i++)
    {
        if (ran == 0) {
            if (num > min)
                num--;
        }
        else if (ran == 1)
        {
            if (num < max)
                num++;
        }
    }


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
        printf("no word %d", num);
        exit(1);
    }
    return a[rand() % count];
}

void play_game(Text* words,int di) {
    gotoxy(WINDOWS_WIDTH / 16, WINDOWS_HEIGHT / 8);
	printf("짧은글쓰기");

    int difficulty = di;
    if (difficulty == -1)
    {
        difficulty = select_difficulty();
    }
    if (difficulty == -1) return;

    char* dif[3];
    double tasu, plusTime; //난이도 설정에 따른 보정치
    struct GameState game;
    game.round = 0;  // 초기 라운드 설정
    game.p_target_word = NULL;  // 초기 목표 단어 설정
    game.current_pos = 0;  // 초기 입력 위치 설정
    game.max_length = 0;  // 초기 최대 단어 길이 설정
    strcpy(game.correct,"    ");//초기화

    int* wordlength;
    wordlength = (int*)malloc(sizeof(int) * words->length);
    int max_len = 0, min_len = WINDOWS_WIDTH;
    for (int i = 0; i < words->length; i++)
    {
        wordlength[i] = strlen(words->arr[i]);
        max_len = (max_len < wordlength[i]) ? wordlength[i] : max_len;
        min_len = (min_len > wordlength[i]) ? wordlength[i] : min_len;
    }

    int result[ROUND];

    for (int i = 0; i < ROUND; i++)
    {
        switch (difficulty)
        {
        case 0:  // 쉬움
            //printf("%d,", (max_len * i + (4 - i) * min_len) / 4);// 첫 번째 단어 선택
            result[i] = random_word(words, wordlength, (int)(max_len * i + (ROUND - 1 -i) * min_len)/ (ROUND - 1),min_len,max_len);
            strcpy(dif, "쉬움");
            plusTime = 3;
            tasu = 60;
            break;
        case 1:  // 보통
            result[i] = random_word(words, wordlength, (int)(max_len * i + (ROUND - 1 - i) * min_len) / (ROUND - 1), min_len, max_len);
            strcpy(dif, "보통");
            plusTime = 2;
            tasu = 120;
            break;
        case 2:  // 어려움
            result[i] = random_word(words, wordlength, (int)(max_len * i + (ROUND - 1 - i) * min_len) / (ROUND - 1), min_len, max_len);
            strcpy(dif, "어려움");
            plusTime = 1;
            tasu = 240;
            break;
        default:
            break;
        }
    }
	game.max_length = strlen(words->arr[result[ROUND - 1]]);
    printf("%s", game.p_target_word);
    system("cls");

    while (1) {
        ULONGLONG start_time = GetTickCount64();
        ULONGLONG now;


        game.p_target_word = words->arr[result[game.round]];
        game.limit_time = plusTime / (game.round+1) + strlen(game.p_target_word) / (tasu / 60);
        int ch = 0;
        char* writtenWord = (char*)calloc(strlen(game.p_target_word) + 1,sizeof(char));
        make_ui(&game, dif);
        ULONGLONG time_gap = 0;
        time_ui(game.limit_time, time_gap);
        while (ch != 13) {
            if (game.limit_time*1000 - time_gap <= 0) break;
            if (!_kbhit())
            {
                now = GetTickCount64();

                if (time_gap != now - start_time){
                    time_gap = now - start_time;
                    time_ui(game.limit_time, time_gap);
                }
                continue;
            }

            gotoxy(game.current_pos, WINDOWS_HEIGHT / 3 + 4);
            ch = _getch();

            if (ch == '\b') {//backspace
                writtenWord[game.current_pos] = '\0'; // 현재 위치의 문자를 제거
                game.current_pos = (game.current_pos > 0) ? --game.current_pos : 0;
                printf("\b=\b");
            }
            else if (ch == 13) {
                game.current_pos = 0;
                break;
            }//enter
            else if (ch == 27) {
                free(writtenWord);
                return;//esc
            }
            else if (ch == '\t');//tab
            else if(game.current_pos < strlen(game.p_target_word)){
                
                writtenWord[game.current_pos] = ch;
                game.current_pos++;
                printf("%c", ch);
            }

        }
        if (!strcmp(writtenWord,game.p_target_word))//맞으면 0
        {
            game.correct[game.round] = 'O';//정답;
        }
        else
        {
            game.correct[game.round] = 'X';
            //오답
        }

        game.round++;
        if (game.round == ROUND)
        {
            break;
        }
    }
    int co = 0;
    for (int i = 0; i < ROUND; i++)
    {
        if (game.correct[i] == 'O')
        {
            if (co >= ROUND / 2)
            {
                co = -1;
                break;
            }
            co++;
        }
    }
    system("cls");
    if (co == -1 && difficulty != 2)
    {
        printf("과반수 이상 맞춰서 다음레벨로");
        _getch();
        free(wordlength);
        play_game(words,difficulty + 1);
        return;
    }
    else
    {
        printf("연습하세요!");
        _getch();
        free(wordlength);
        return;
    }
}

