/*
 * ST7735.h
 *
 *  Created on: 12 июн. 2023 г.
 *      Author: Spectator
 */

#ifndef ST7735_ST7735_H_
#define ST7735_ST7735_H_

#include "stm32f4xx.h"
#include "main.h"

//-------------------------------------Commands-------------------------------------------------

#define NOP			0x00		//No operation
#define SWRESET		0x01		//Software reset
#define RDDID		0x04		//Read display ID
#define RDDST		0x09		//Read display status
#define RDDPM		0x0A		//Read display power mode
#define RDDMADCTL   0x0B		//Read display MADCTL
#define RDDCOLMOD   0x0C		//Read display pixel format
#define RDDIM		0x0D		//Read display image mode
#define RDDSM		0x0E		//Read display signal mode
#define SLPIN		0x10		//Sleep In
#define SLPOUT		0x11		//Sleep Out
#define PTLON		0x12		//Partial display mode on
#define NORON 		0x13		//Normal display mode on
#define INVOFF		0x20		//Display Inversion off
#define INVON		0x21		//Display Inversion on
#define GAMSET		0x26		//Gamma set
#define DISPOFF		0x28		//Display off
#define DISPON 		0x29		//Display on
#define CASET		0x2A		//Column address set
#define RASET		0x2B		//Raw address set
#define RAMWR		0x2C		//Memory write
#define RAMRD		0x2E		//Memory read
#define PTLAR		0x30		//Partial area
#define TEOFF		0x34		//Tearing effect line off
#define TEON		0x35		//Tearing effect line on
#define MADCTL		0x36		//Memory data access control
#define IDMOFF		0x38		//Idle mode off
#define IDMON		0x38		//Idle mode on
#define COLMOD		0x3A		//Interface Pixel Format
#define INVCTR		0xB4		//Display inversion control

#define PIC_SIZE	0xF000		//Amount of pixels
#define COLUMN		0x80
#define RAW			0xA0

#define RGB_666     0x06        //RGB setcode
#define RGB_565     0x05
#define RGB_444     0x03

#define CS_H()				( HAL_GPIO_WritePin(GPIOC, CS_Pin, GPIO_PIN_SET) )
#define CS_L()				( HAL_GPIO_WritePin(GPIOC, CS_Pin, GPIO_PIN_RESET) )
#define RESET_ON()			( HAL_GPIO_WritePin(GPIOC, RESET_Pin, GPIO_PIN_RESET) )
#define RESET_OFF()			( HAL_GPIO_WritePin(GPIOC, RESET_Pin, GPIO_PIN_SET) )
#define DATA_MODE() 		( HAL_GPIO_WritePin(CMD_GPIO_Port, CMD_Pin, GPIO_PIN_SET) )
#define CMD_MODE()			( HAL_GPIO_WritePin(CMD_GPIO_Port, CMD_Pin, GPIO_PIN_RESET) )
#define BCKGND_ON()			( HAL_GPIO_WritePin(GPIOB, BACK_LIGHT_Pin, GPIO_PIN_SET) )
#define BCKGND_OFF()		( HAL_GPIO_WritePin(GPIOB, BACK_LIGHT_Pin, GPIO_PIN_RESET) )

extern SPI_HandleTypeDef hspi1;

void hwReset(void);
void swReset(void);
void display_init(void);
void send_command(SPI_HandleTypeDef* spi,uint8_t cmd);
void send_byte(SPI_HandleTypeDef* spi,uint8_t* data);
void send_image(SPI_HandleTypeDef* spi,uint8_t* image);
void read_data(SPI_HandleTypeDef* spi,uint8_t cmd,uint8_t* data,uint16_t bytes_amount);
void set_red_background(uint8_t* color);
void set_green_background(uint8_t* color);
void set_blue_background(uint8_t* color);
void set_yellow_background(uint8_t* color);

#endif /* ST7735_ST7735_H_ */
