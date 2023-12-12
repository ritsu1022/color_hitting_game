/*
 * csi.h
 *
 *  Created on: 2023/12/12
 *      Author: 幸子
 */

#ifndef CSI_H_
#define CSI_H_

enum clear_option {
	AFTER_CURSOR = 0, BEFORE_CURSOR = 1, FULL_SCREEN = 2
};;

void clear_screen(const enum clear_option option);
void move_cursor(int row, int col);

#endif /* CSI_H_ */
