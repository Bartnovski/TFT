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
uint8_t caset[] = {0,0,0,162};
uint8_t raset[] = {0,0,0,132};
uint8_t cas = CASET;
uint8_t ras = RASET;
uint8_t madctl = 0x3E; 	//	RGB -> BGR
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
	// send_command(spi, MADCTL);
	// send_bytes(spi,&madctl,1);
}

void send_command(SPI_HandleTypeDef* spi,uint8_t cmd) {
	CS_L();
	CMD_MODE();
	HAL_SPI_Transmit(spi, &cmd, 1, 100);
	CS_H();
}

void send_bytes(SPI_HandleTypeDef* spi,uint8_t* data,uint16_t bytes_amount) {
	CS_L();
	DATA_MODE();
	HAL_SPI_Transmit(spi, data, bytes_amount, 100);
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


void set_pixel(uint32_t x,uint32_t y,uint8_t *color_p) {
	send_command(&hspi1, CASET);
	caset[1] = x;
	send_bytes(&hspi1,caset,2);
	send_command(&hspi1, RASET);
	raset[1] = y;
	send_bytes(&hspi1,raset,2);
	send_command(&hspi1, RAMWR);
	send_bytes(&hspi1,(uint8_t*)color_p,3);
}















