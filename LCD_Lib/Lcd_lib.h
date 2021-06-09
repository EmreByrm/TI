/*
 * Lcd_lib.h
 *
 *  Created on: 7 Kas 2020
 *      Author: Emre
 */

#ifndef LCD_LIB_H_
#define LCD_LIB_H_

#define LCD_PORT_BASE   GPIO_PORTA_BASE
#define RS              GPIO_PIN_2
#define E               GPIO_PIN_3
#define D4              GPIO_PIN_4
#define D5              GPIO_PIN_5
#define D6              GPIO_PIN_6
#define D7              GPIO_PIN_7

void LcdSettings(void);
void LcdClear(void);
void LcdCommand(unsigned char komut);
void LcdWrite(unsigned char write);
void Lcdxy(unsigned char a, unsigned char b);
void LcdFunction(unsigned char DL, unsigned char N, unsigned char F);
void LcdWordSend(unsigned char *dizi, unsigned int uzunluk);

#endif /* LCD_LIB_H_ */
