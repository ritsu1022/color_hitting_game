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

enum clear_option {
	AFTER_CURSOR = 0, BEFORE_CURSOR = 1, FULL_SCREEN = 2
};

void clear_screen(const enum clear_option option) {
	printf("\033[%dJ", option);
}

void move_cursor(int row, int col) {
	printf("\033[%d;%dH", row, col);
}

void chg_display_title(void) {
	clear_screen(FULL_SCREEN);
	move_cursor(1, 1);
	puts("【色当てゲーム】");
	puts("ゲームをはじめてください");
}

void chg_display_question(void) {
	for (int i = 0; i < QSIZE; i++) {
			putchar(qx[i]);
	}
	putchar('\n');
}

const char* CHG_HIT_CHAR = "\033[30;47mH\033[0m";
const char* CHG_BLOW_CHAR = "\033[37;40mB\033[0m";

void chg_display_hit_pin(void) {
	printf("%s ", CHG_HIT_CHAR);
}

void chg_display_blow_pin(void) {
	printf("%s ", CHG_BLOW_CHAR);
}

const char* CHG_RED_MARK        = "\033[41m R \033[0m";
const char* CHG_GREEN_MARK      = "\033[42m G \033[0m";
const char* CHG_YELLOW_MARK     = "\033[43m Y \033[0m";
const char* CHG_BLUE_MARK       = "\033[44m B \033[0m";
const char* CHG_MAGENTA_MARK    = "\033[45m M \033[0m";
const char* CHG_CYAN_MARK       = "\033[46m C \033[0m";
const char* CHG_OTHER_MARK      = "\033[47m _ \033[0m";

const char* chg_color_to_mark(const char color) {
	const char* mark;
	switch (color) {
	case 'R':
		mark = CHG_RED_MARK;
		break;
	case 'G':
		mark = CHG_GREEN_MARK;
		break;
	case 'Y':
		mark = CHG_YELLOW_MARK;
		break;
	case 'B':
		mark = CHG_BLUE_MARK;
		break;
	case 'M':
		mark = CHG_MAGENTA_MARK;
		break;
	case 'C':
		mark = CHG_CYAN_MARK;
		break;
	default:
		mark = CHG_OTHER_MARK;
		break;
	}
	return mark;
}

void chg_display_trial(const char tx[]) {
	for(int i = 0; i < QSIZE; i++) {
		printf("%s ", chg_color_to_mark(toupper(tx[i])));
	}
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

void chg_get_line(char buf[], int size) {
	char* cr;

	fgets(buf, size, stdin);
	cr = strchr(buf, '\n');
	if(cr != NULL) {
		*cr = '\0';
	}
}

enum chg_game_state {
	chg_state_PLAYING, chg_state_PLAYER_WIN, chg_state_PLAYER_LOSE
};

enum chg_game_state chg_check_result(const char tx[]) {
	int hit = 0;
	int blow = 0;

	for (int i = 0; i < QSIZE; i++) {
		char txc = toupper(tx[i]);
		if (qx[i] == txc) {
			hit += 1;
		} else {
			if(memchr(qx, txc, QSIZE) != NULL) {
				blow += 1;
			}
		}
	}

	for (int i = 0; i < hit; i++) {
		chg_display_hit_pin();
	}
	for (int i = 0; i < blow; i++) {
		chg_display_blow_pin();
	}
	putchar( '\n' );

	if (hit == QSIZE) {
		return chg_state_PLAYER_WIN;
	} else {
		return chg_state_PLAYING;
	}
}

enum chg_game_state chg_play_turn(const int turn) {
	char tx[QSIZE+10];
	const int size = sizeof(tx);
	while(true) {
		chg_get_line(tx, size);

		if (chg_input_is_quit(tx)) {
			return chg_state_PLAYER_LOSE;
		}

		if (chg_input_length_is_valid(tx)
			&& chg_input_chars_is_valid(tx)
			&& chg_input_chars_is_no_dup(tx)) {
			break;
		} else {
			puts("再入力してください");
		}
	}
	move_cursor(turn + 2, 1);
	clear_screen(AFTER_CURSOR);
	printf("%2d回: ", turn + 1);
	chg_display_trial(tx);
	return chg_check_result(tx);
}

void chg_display_win_or_lose(enum chg_game_state game_state) {
	if(game_state == chg_state_PLAYER_WIN) {
		puts("あなたの勝ちです。");
	} else {
		puts("残念！出題者の勝ちです。");
	}
	fputs("問題: ", stdout);
	chg_display_trial(qx);
}

void color_hitting_game(void) {
	enum chg_game_state game_state = chg_state_PLAYING;

	srand((unsigned)time(NULL));
	chg_display_title();
	chg_make_question();
	const int max_turns = 10;
	for(int turn = 0; turn < max_turns; turn++) {
		printf("予想を入力してください。\n%2d 回目>>", turn + 1);

		game_state = chg_play_turn(turn);
		if(game_state == chg_state_PLAYER_WIN
			|| game_state == chg_state_PLAYER_LOSE) {
			break;
		}
	}

	chg_display_win_or_lose(game_state);
	return;
}

void chg_display_operation_menu(void) {
	puts("(N) 新しいゲームを始める");
	puts("(Q) 終了");
	printf("操作を選んでください：");
}

void chg_select_operation(void) {
	char opx[4];
	const int size = sizeof(opx);
	while (true) {
		chg_display_title();
		chg_display_operation_menu();
		chg_get_line(opx, size);
		const char op = toupper(opx[0]);
		if( op == 'Q') {
			puts("ゲームを終了しました。");
			return;
		} else if ( op == 'N') {
			color_hitting_game();
		}
	}
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	chg_select_operation();
	return EXIT_SUCCESS;
}

