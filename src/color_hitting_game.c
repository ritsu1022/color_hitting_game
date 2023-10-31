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

void discard_inputs(void) {
	for(;getchar() != '\n';) {
		/* do nothing */
	}
}
int main(void) {
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

		char t1 = getchar();
		char t2 = getchar();
		char t3 = getchar();
		char t4 = getchar();
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
	}
	return EXIT_SUCCESS;
}
