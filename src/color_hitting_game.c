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
#include <time.h>

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

static char qx[QSIZE];

void chg_make_question(void) {
	qx[0] = 'R';
	qx[1] = 'G';
	qx[2] = 'B';
	qx[3] = 'Y';
	puts ("コンピュータが問題を出しました。");
}

int chg_play_turn(void) {
	int matched = 0;

	char tx[QSIZE];
	for(int i = 0; i < QSIZE; i++) {
		tx[i] = get_trial_char();
	}
	discard_inputs();

	for(int i = 0; i < QSIZE; i++) {
		putchar(tx[i]);
	}

	for(int i = 0; i < QSIZE; i++) {
		if (qx[i] == tx[i]) {
			matched += 1;
		}
	}

	return matched;
}

int chg_check_result(int matched) {
	puts("結果");
	printf("%d コ合っています。\n", matched );
	if (matched == QSIZE) {
		return 1;
	} else {
		return 0;
	}
}

void chg_display_win_or_lose(int player_win) {
	if(player_win) {
		puts("あなたの勝ちです。");
	} else {
		puts("残念！出題者の勝ちです。");
	}
}

void color_hitting_game(void) {
	int player_win = 0;

	srand((unsigned)time(NULL));
	chg_display_title();
	chg_make_question();
	const int max_turns = 10;
	for(int turn = 0; turn < max_turns; turn++) {
		printf("予想を入力してください。%d 回目\n", turn + 1);

		int matched = 0;
		matched = chg_play_turn();

		player_win = chg_check_result(matched);
		if(player_win) {
			break;
		}
	}

	chg_display_win_or_lose(player_win);
	return;
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	color_hitting_game();
	return EXIT_SUCCESS;
}

