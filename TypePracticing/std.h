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

typedef struct text {
    char* reference;
    char** arr;
    int length;
}Text;


void key_checker(void);

void txt_read_checker(Text*, Text*);

//지정된 좌표로 콘솔 언더바 이동
void gotoxy(short, short);

//콘솔 크기 조정
void SetFixedConsoleSize(short, short);

// 크기 조절 불가 및 최대화 버튼 제거
void DisableConsoleResize(void);

//바를 콘솔창에 그림. 시작 좌표(왼쪽)를 지정하여 정해진 길이만큼 비율을 그림
void loading_bar(short start_x, short start_y, int length, double numerator, double denominator);

//파일을 읽고 줄 수를 반환함. 오류시 -1 반환
int count_lines_of_file(const char* filename);


void txt_to_arr(Text*, FILE**);