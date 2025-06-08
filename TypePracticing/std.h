#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <string.h>

#define WINDOWS_WIDTH 96
#define WINDOWS_HEIGHT 32

#define WORD_PRAC_NUM 30

//txt 데이터를 저장할 struct. reference=원본 txt파일명, arr=텍스트 내용 저장공간, length=배열 길이
typedef struct text {
    char* reference;//text 출처
    char** arr;//파일에서 읽어온 데이터 저장
    unsigned int length;//arr의 길이
}Text;

typedef struct status {
    unsigned int correct;//맞은 글자 수
    unsigned int incorrect;//틀린 글자 수
    double accuracy;//정확도 백분율
    double accuracy_peak;//정확도 고점
    unsigned int type_count;//타수
    double type_speed;//분당 타수
    double type_peak;//분당 타수 고점
}Status;

//키입력 테스트 함수
void key_checker(void);

//텍스트 읽기 테스트 함수
void txt_read_checker(Text*, Text*);

//지정된 좌표로 콘솔 언더바 이동
void gotoxy(short, short);

//콘솔 크기 조정
void SetFixedConsoleSize(short, short);

// 크기 조절 불가 및 최대화 버튼 제거
void DisableConsoleResize(void);

//바를 콘솔창에 그림. 정해진 길이만큼 비율을 그림
void bar(int, double, double);

//파일을 읽고 줄 수를 반환함. 오류시 -1 반환
int count_lines_of_file(const char*);

//txt 파일을 줄 단위로 읽어 문자열 배열로 변환하여 Text에 저장하는 함수
void txt_to_arr(Text*, FILE**);

//특정 좌표로 이동하여 정해진 크기의 가상의 상자 안에 문자열을 출력하는 함수.
void print_in_rectangle(short, short, short, short, char*);

//자리연습
void key_prac(void);

//단어연습
void word_prac(Text*);

//짧은글쓰기
void sentence_prac(Text*);

//놀이
void play_game(Text*, int, int);

//정수 배열 arr의 element를 size 수만큼 난수로 채우는 함수
void get_random_int_arr(int**, int, int, int);

//게임 기본 UI
void drawUI_game(Status*, int, int);

//게임의 결과 표시
void print_result(Status*);

