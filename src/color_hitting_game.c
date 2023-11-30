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
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define QSIZE 4
static char qx[QSIZE];

static const char qseeds[] = { 'R', 'G', 'B', 'Y', 'M', 'C' };
static const int num_of_colors = sizeof(qseeds)/ sizeof(qseeds[0]);

char get_trial_char(void) {
	char ch;
	for (;;) {
		ch = getchar();
		for (int i = 0; i < num_of_colors; i++) {
			if(ch == qseeds[i]) {
				return ch;
			}
		}
	}
	return ch;
}

void discard_inputs(void) {
	for(; getchar() != '\n';) {
		/* do nothing */
	}
}

void chg_display_title(void) {
	puts("【色当てゲーム】");
	puts("ゲームをはじめてください");
}

void chg_display_question(void) {
	for (int i = 0; i < QSIZE; i++) {
			putchar(qx[i]);
	}
	putchar('\n');
}

void chg_make_question(void) {
	char wk_qseeds[num_of_colors];
	memcpy(wk_qseeds, qseeds, sizeof(qseeds));
	for (int i = 0, len = num_of_colors;  i < QSIZE; i++, len--) {
		unsigned int r = rand() % len;
		qx[i] = wk_qseeds[r];
		wk_qseeds[r] = wk_qseeds[len - 1];
	}

	puts ("コンピュータが問題を出しました。");

#ifdef DEBUG
	chg_display_question();
#endif // DEBUG
}

bool chg_input_chars_is_no_dup(const char* buf) {
	size_t length = strlen(buf);

	int freq[num_of_colors];
	memset(freq, 0, sizeof(int) * num_of_colors);

	for (size_t i = 0; i < length; i++) {
		char* offset = memchr(qseeds, toupper(buf[i]), num_of_colors);
		if (offset != NULL) {
			int idx = offset - qseeds;
			freq[idx]++;
		}
	}

	bool ret = true;
	for (int i = 0; i < num_of_colors; i++) {
		if (freq[i] >= 2) {
			printf("同じ文字\"%c\"が%d回使われています\n", qseeds[i], freq[i]);
			ret = false;
		}
	}
	return ret;
}

bool chg_input_chars_is_valid(const char* buf) {
	size_t length = strlen(buf);

	char illegal_chars[QSIZE] = { '\0' };
	int j = 0;
	for (size_t i = 0; i < length; i++) {
		char ch = toupper(buf[i]);
		if (memchr(qseeds, ch, num_of_colors) == NULL) {
			if (memchr(illegal_chars, buf[i],QSIZE) == NULL) {
				illegal_chars[j++] = buf[i];
			}
		}
	}
	if (strlen(illegal_chars) > 0) {
		printf("使えない文字\"%s\"が含まれています。\n", illegal_chars);
		return false;
	}
	return true;
}

bool chg_input_length_is_valid(const char* buf) {
	size_t length = strlen(buf);

	if (length < QSIZE) {
		puts("入力が短すぎます");
		return false;
	}
	if (length > QSIZE) {
		puts("入力が長すぎます");
		return false;
	}
	return true;
}

bool chg_input_is_quit(const char* buf) {
	if(toupper(buf[0]) == 'Q') {
		return true;
	} else {
		return false;
	}
}

void chg_input_answer(char buf[], int size) {
	char* cr;

	fgets(buf, size, stdin);
	cr = strchr(buf, '\n');
	if(cr != NULL) {
		*cr = '\0';
	}
}

int chg_play_turn(void) {
	int matched = 0;

	char tx[QSIZE+10];
	const int size = sizeof(tx);
	while(true) {
		chg_input_answer(tx, size);

		if (chg_input_length_is_valid(tx)
			&& chg_input_chars_is_valid(tx)
			&& chg_input_chars_is_no_dup(tx)) {
			break;
		} else {
			puts("再入力してください");
		}
	}

	for(int i = 0; i < QSIZE; i++) {
		if (qx[i] == toupper(tx[i])) {
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

