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

void chg_display_title(void) {
	puts("【色当てゲーム】");
	puts("ゲームをはじめてください");
}

static char q1;
static char q2;
static char q3;
static char q4;

void chg_make_question(void) {
	q1 = 'R';
	q2 = 'G';
	q3 = 'B';
	q4 = 'Y';
	puts ("コンピュータが問題を出しました。");
}

int chg_play_turn(void) {
	int matched = 0;

	char t1 = get_trial_char();
	char t2 = get_trial_char();
	char t3 = get_trial_char();
	char t4 = get_trial_char();
	discard_inputs();

	putchar(t1);
	putchar(t2);
	putchar(t3);
	putchar(t4);

	if (q1 == t1) { matched += 1; }
	if (q2 == t2) { matched += 1; }
	if (q3 == t3) { matched += 1; }
	if (q4 == t4) { matched += 1; }

	return matched;
}

void color_hitting_game(void) {
	int player_win = 0;

	chg_display_title();
	chg_make_question();
	const int max_turns = 10;
	for(int turn = 0; turn < max_turns; turn++) {
		printf("予想を入力してください。%d 回目\n", turn + 1);

		int matched = 0;
		matched = chg_play_turn();

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
	return;
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	color_hitting_game();
	return EXIT_SUCCESS;
}

