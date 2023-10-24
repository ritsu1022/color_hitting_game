/*
 ============================================================================
 Name        : color_hitting_game.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char q1 = 'R';
	char q2 = 'G';
	char q3 = 'B';
	char q4 = 'Y';

	puts("【色当てゲーム】");
	puts("ゲームをはじめてください");
	puts("コンピュータが問題を出しました。");
	puts("予想を入力してください。");

	char t1 = getchar();
	char t2 = getchar();
	char t3 = getchar();
	char t4 = getchar();

	putchar(t1);
	putchar(t2);
	putchar(t3);
	putchar(t4);

	return EXIT_SUCCESS;
}
