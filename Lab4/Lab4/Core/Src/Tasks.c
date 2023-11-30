/*
 * Tasks.c
 *
 *  Created on: Nov 30, 2023
 *      Author: M S I
 */

#include "Tasks.h"
#include "main.h"

void InitLED(void){
	HAL_GPIO_WritePin(red_GPIO_Port, red_Pin, 1);
	HAL_GPIO_WritePin(yellow_GPIO_Port, yellow_Pin, 1);
	HAL_GPIO_WritePin(green_GPIO_Port, green_Pin, 1);
	HAL_GPIO_WritePin(blue_GPIO_Port,blue_Pin, 1);
	HAL_GPIO_WritePin(purple_GPIO_Port,purple_Pin, 1);
}

void Task1(void){
	HAL_GPIO_TogglePin(red_GPIO_Port, red_Pin);
}

void Task2(void){
	HAL_GPIO_TogglePin(yellow_GPIO_Port, yellow_Pin);
}

void Task3(void){
	HAL_GPIO_TogglePin(green_GPIO_Port, green_Pin);
}

void Task4(void){
	HAL_GPIO_TogglePin(blue_GPIO_Port, blue_Pin);
}

void Task5(void){
	HAL_GPIO_TogglePin(purple_GPIO_Port, purple_Pin);
}
