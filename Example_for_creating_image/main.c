
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Fonts_SSD1306.h"

/* display size -------------------------------------------------- */ 
#define GDDRAM_SEG					128U		// X [pixels]
#define GDDRAM_COM     				32U			// Y [pixels]	
#define GDDRAM_SIZE 				512U		// [bytes]	(GDDRAM_SEG * GDDRAM_COM) / 8 

// Enumeration for screen colors
typedef enum {
	Black = 0x00, 
	White = 0x01  
} SSD1306_COLOR_t;

// Struct to store transformations
struct SSD1306_t {
	uint16_t CurrentX;
	uint16_t CurrentY;
};

/* prototypes ----------------------------------------------------- */ 
void drawPixel_SSD1306(uint8_t, uint8_t, SSD1306_COLOR_t); 
char ssd1306_WriteChar(char, SSD1306_Font_t, SSD1306_COLOR_t); 
char ssd1306_WriteString(char*, SSD1306_Font_t, SSD1306_COLOR_t); 

// image storage buffer
uint8_t DisplayBuffer[GDDRAM_SIZE]; 

// default coordinates
struct SSD1306_t SSD1306 = {0, 0};


int main(void){
	
	// open file
	FILE *image_save_file = fopen("TestImage.txt", "wb");
	
	/* create image ------------------------------------------------ */ 
	ssd1306_WriteString((char*)"   123456789", Font_6x8, White);
	SSD1306.CurrentX = 0; 
	SSD1306.CurrentY = 10; 
	ssd1306_WriteString((char*)"0010001110", Font_6x8, White);
	SSD1306.CurrentX = 10; 
	SSD1306.CurrentY = 20; 
	ssd1306_WriteString((char*)"!!! HELLO !!!", Font_6x8, White);
	/* ------------------------------------------------------------- */ 
	
	// write data to file
	fwrite((uint8_t*)DisplayBuffer , 1 , GDDRAM_SIZE, image_save_file); 
	
	// close file
	fclose(image_save_file);
			
	return 0;
	
}


/*!
 * @brief:	Function to set a pixel to a coordinate
 * @param: 	x, y - coordinates; color - White or Black color of pixel. 
*/
void 
drawPixel_SSD1306(uint8_t x, uint8_t y, SSD1306_COLOR_t color){
	
	if( x >= GDDRAM_SEG || y >= GDDRAM_COM )
		return;															 															
   
	if( color == White )
		DisplayBuffer[x + (y / 8) * GDDRAM_SEG] |= 1 << (y % 8);
	else 
		DisplayBuffer[x + (y / 8) * GDDRAM_SEG] &= ~(1 << (y % 8));
}

/*!
* @brief:	Function for drawing a symbol
* @param: 	ch - symbol for drawing; 
*			Font - structure for storing font parameter; 
*			color - White or Black color of symbol. 
*/
char 
ssd1306_WriteChar(char ch, SSD1306_Font_t Font, SSD1306_COLOR_t color) {
	
	uint32_t i, b, j;
    
	if( ch < 32 || ch > 126 )
		return 0;
	
	if( GDDRAM_SEG < (SSD1306.CurrentX + Font.width ) || GDDRAM_COM < (SSD1306.CurrentY + Font.height) )
		return 0;

	for(i = 0; i < Font.height; ++i){
		b = Font.data[(ch - 32) * Font.height + i];
		for(j = 0; j < Font.width; ++j){		
			if( (b << j) & 0x8000 )
				drawPixel_SSD1306(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t)color);
			else
				drawPixel_SSD1306(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t)!color);	
		}
	}
	
	SSD1306.CurrentX += Font.width;
	return ch;
}

/*!
* @brief:	Function for drawing a string
* @param: 	*str - pointer to string; 
*			Font - structure for storing font parameter; 
*			color - White or Black color of symbol. 
*/
char 
ssd1306_WriteString(char *str, SSD1306_Font_t Font, SSD1306_COLOR_t color) {

	while(*str){
		if( ssd1306_WriteChar(*str, Font, color) != *str )
			return *str;
		str++;
	}
 
	return *str;
}

