/*
 * csi.c
 *
 *  Created on: 2023/12/12
 *      Author: 幸子
 */

#include <stdio.h>
#include "csi.h"


void clear_screen(const enum clear_option option) {
	printf("\033[%dJ", option);
}

void move_cursor(int row, int col) {
	printf("\033[%d;%dH", row, col);
}
