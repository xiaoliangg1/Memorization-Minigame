/*
 * Project5.c
 *
 * Created: 3/5/2021 5:49:58 PM
 * Author : Hengxi
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "avr.h"
#include "lcd.h"

int is_pressed(int r, int c){
	DDRC = 0;
	PORTC = 0;
	SET_BIT(DDRC, r);
	CLR_BIT(PORTC, r);
	SET_BIT(PORTC, c + 4);
	avr_wait(1);
	if (GET_BIT(PINC, c + 4)){
		return 0;
	}
	return 1;
}

int get_key(){
	for (int r = 0; r < 4; r++){
		for (int c = 0; c < 4; c++){
			if (is_pressed(r, c)){
				return 4 * r + c + 1;
			}
		}
	}
	return 0;
}

void display(int side) {
	char buf1[17];
	sprintf(buf1, "%d", side);
	lcd_pos(0, 0);
	lcd_puts(buf1);
}

void display_text(int c) {
	char buf1[17];
	if (c == 0){
		sprintf(buf1, "start");
		lcd_pos(0, 0);
		lcd_puts(buf1);
	}else{
		sprintf(buf1, "OVER");
		lcd_pos(0, 0);
		lcd_puts(buf1);
	}
}

int num_gen(){
	int r = rand();
	int num = r % 10;
	
	return num;
}

int main(void)
{
	lcd_init();
	
    /* Replace with your application code */
    while (1) 
    {	
		int nums[50];
		int index = 0;
		int done = 0;
		unsigned int seed = 0;
		display_text(0);
		while(get_key() == 0){
			seed++;
		}
		srand(seed);
		avr_wait(1000);
		lcd_clr();
		while (done == 0)
		{
			nums[index] = num_gen();
/*			int num = nums[index];*/
			index++;
				
				
// 			display(num);
// 			avr_wait(500);
// 			lcd_clr();
				
				
			for (int i = 0; i < index; i++){
				display(nums[i]);
				avr_wait(500);
				lcd_clr();
				avr_wait(100);
			}
				
			for (int i = 0; i < index; i++) {
				while (done == 0) {
					int key = get_key();
					int num;
					if (key > 0 && key < 4){
						num = key;
					}else if (key > 4 && key < 8){
						num = key - 1;
					}else if (key > 8 && key < 12){
						num = key - 2;
					}else{
						num = 0;
					}
					if (key != 0){
						if (num == nums[i]){
							avr_wait(500);
							break;
						}else{
							display_text(1);
							avr_wait(2000);
							lcd_clr();
							done = 1;
						}
					}
				}
			}	
			lcd_clr();
		}
    }
}

