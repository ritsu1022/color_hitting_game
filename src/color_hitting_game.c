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

#define QSIZE 4

char get_trial_char(void) {
	char ch;
	for (;;) {
		ch = getchar();
		if (ch == 'R' || ch == 'G'|| ch == 'B'
				|| ch == 'Y' || ch == 'M'|| ch == 'C') {
			return ch;
		}
	}
	return ch;
}
void discard_inputs(void) {
	for(;getchar() != '\n';) {
		/* do nothing */
	}
}
int main(void) {
	int player_win = 0;
	setvbuf(stdout, NULL, _IONBF, 0);

	char q1 = 'R';
	char q2 = 'G';
	char q3 = 'B';
	char q4 = 'Y';

	puts("【色当てゲーム】");
	puts("ゲームをはじめてください");
	puts("コンピュータが問題を出しました。");
	for(int i = 0; i < 10; i++) {
		printf("予想を入力してください。%d 回目\n", i + 1);

		char t1 = get_trial_char();
		char t2 = get_trial_char();
		char t3 = get_trial_char();
		char t4 = get_trial_char();
		discard_inputs();

		putchar(t1);
		putchar(t2);
		putchar(t3);
		putchar(t4);

		int matched = 0;
		if(q1 == t1) { matched += 1; }
		if(q2 == t2) { matched += 1; }
		if(q3 == t3) { matched += 1; }
		if(q4 == t4) { matched += 1; }
		puts("結果");
		printf("%d コ合っています。\n", matched );
		if (matched == QSIZE) {
			player_win = 1;
			break;
		}
	}
	if (player_win) {
		puts("あなたの勝ちです。");
	} else {
		puts ("残念！出題者の勝ちです。");
	}
	return EXIT_SUCCESS;
}
