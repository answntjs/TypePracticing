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
#define WINDOWS_HEIGHT 30
#define SENTENCE_PRAC_NUM 10
#define WORD_PRAC_NUM 30

typedef struct text {
    char* reference;//text 출처
    char** arr;//파일에서 읽어온 데이터 저장
    int length;//인덱스
}Text;

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

//바를 콘솔창에 그림. 시작 좌표(왼쪽)를 지정하여 정해진 길이만큼 비율을 그림
void bar(short, short, int, double, double);

//파일을 읽고 줄 수를 반환함. 오류시 -1 반환
int count_lines_of_file(const char*);

//txt 파일을 문자열 배열로 변환하여 Text에 넣어주는 함수
void txt_to_arr(Text*, FILE**);

//특정 좌표로 이동하여 정해진 크기의 가상의 상자 안에 문자열을 출력하는 함수.
void print_in_rectangle(short, short, short, short, char*);

//짧은글쓰기
void sentence_prac(Text*);