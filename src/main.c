/*
 * main.c
 *
 *  Created on: 2023/12/13
 *      Author: 幸子
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "color_hitting_game.h"

int main(int argc, char* argv[]) {
	int filename_length;
	setvbuf(stdout, NULL, _IONBF, 0);
	if (argc <= 1) {
		filename_length = strlen(DEFAULT_SCORE_FILE);
		memcpy(score_file, DEFAULT_SCORE_FILE, filename_length);
	} else {
		filename_length = strlen(argv[1]);
		if(filename_length > FNAME_MAX) {
			fputs("ファイル名が長すぎます。", stderr);
			exit(EXIT_FAILURE);
		}
		memcpy(score_file, argv[1], filename_length);
	}

	chg_select_operation();
	return EXIT_SUCCESS;
}
