/*
 * main.c
 *
 *  Created on: 2023/12/13
 *      Author: 幸子
 */

#include <stdlib.h>
#include <stdio.h>
#include "color_hitting_game.h"

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	chg_select_operation();
	return EXIT_SUCCESS;
}
