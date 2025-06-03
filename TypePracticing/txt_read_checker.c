#include "std.h"

void txt_read_checker(Text* words, Text* sentences){
	for (int i = 0; i < words->length; i++) {
		printf("%s ", words->arr[i]);
	}
	printf("\n");
	for (int i = 0; i < sentences->length; i++) {
		printf("%s\n", sentences->arr[i]);
	}
}