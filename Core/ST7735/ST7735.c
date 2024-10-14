/*
 * ST7735.c
 *
 *  Created on: 12 июн. 2023 г.
 *      Author: Spectator
 */

/*
 *  Перед отправкой изображение уменьшить до размеров диспдея и использовать bin2c.exe
 *  для конвертации в массив
 */

#include "ST7735.h"

SPI_HandleTypeDef* spi = &hspi1;
uint8_t nop = 0x00;
uint8_t caset[] = {0,60,0,80};
uint8_t raset[] = {0,80,0,100};
uint8_t cas = CASET;
uint8_t ras = RASET;
void hwReset() {

}

void swReset() {

}

void display_init() {
	RESET_OFF();
	HAL_Delay(120);
	send_command(spi, DISPON);
	HAL_Delay(120);
	send_command(spi, SLPOUT);
}

void send_command(SPI_HandleTypeDef* spi,uint8_t cmd) {
	CS_L();
	CMD_MODE();
	HAL_SPI_Transmit(spi, &cmd, 1, 100);
	CS_H();
}

void send_byte(SPI_HandleTypeDef* spi,uint8_t* data) {
	CS_L();
	DATA_MODE();
	HAL_SPI_Transmit(spi, data, 1, 100);
	CS_H();
}

void send_image(SPI_HandleTypeDef* spi,uint8_t* image) {
	send_command(&hspi1, RAMWR);
	// for(uint16_t i = 0;i < PIC_SIZE;i++)
	// 	//for(uint8_t k = 0;k < 3;k++)
	// 		send_byte(spi, image + i);
	CS_L();
	DATA_MODE();
	HAL_SPI_Transmit(spi, image, PIC_SIZE, 100);
	CS_H();
}

void read_data(SPI_HandleTypeDef* spi,uint8_t cmd,uint8_t* data,uint16_t bytes_amount) {
	CS_L();
	CMD_MODE();
	HAL_SPI_Transmit(spi, &cmd, 1, 100);
	DATA_MODE();
	HAL_SPI_Receive(spi, data ,bytes_amount, 100);
	CS_H();
}

void set_red_background(uint8_t* color) {

	 for(uint16_t i = 0;i < PIC_SIZE;i += 3) {
		 color[i] = 0xFF;
		 color[i + 1] = 0x00;
		 color[i + 2] = 0x00;
	 }
}

void set_green_background(uint8_t* color) {

	 for(uint16_t i = 0;i < PIC_SIZE;i += 3) {
		 color[i] = 0x00;
		 color[i + 1] = 0xFF;
		 color[i + 2] = 0x00;
	 }
}

void set_blue_background(uint8_t* color) {

	 for(uint16_t i = 0;i < PIC_SIZE;i += 3) {
		 color[i] = 0x00;
		 color[i + 1] = 0x00;
		 color[i + 2] = 0xFF;
	 }
}


void set_yellow_background(uint8_t* color) {

	 for(uint16_t i = 0;i < PIC_SIZE;i += 3) {
		 color[i] = 0xFF;
		 color[i + 1] = 0xFF;
		 color[i + 2] = 0x00;
	 }
}





















