/** ==================================================================================== 
 * @file EE_API.h                                                             
 * @author K.vijlbrief                                     
 * @date 13-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief EE API VGA driver header file, contains all function and data prototypes for layer 1 and 2 
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */

#include "main.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_tim1_up;



#define VGA_BLUE0_Pin GPIO_PIN_8
#define VGA_BLUE0_GPIO_Port GPIOE
#define VGA_BLUE1_Pin GPIO_PIN_9
#define VGA_BLUE1_GPIO_Port GPIOE
#define VGA_GREEN0_Pin GPIO_PIN_10
#define VGA_GREEN0_GPIO_Port GPIOE
#define VGA_GREEN1_Pin GPIO_PIN_11
#define VGA_GREEN1_GPIO_Port GPIOE
#define VGA_GREEN2_Pin GPIO_PIN_12
#define VGA_GREEN2_GPIO_Port GPIOE
#define VGA_RED0_Pin GPIO_PIN_13
#define VGA_RED0_GPIO_Port GPIOE
#define VGA_RED1_Pin GPIO_PIN_14
#define VGA_RED1_GPIO_Port GPIOE
#define VGA_RED2_Pin GPIO_PIN_15
#define VGA_RED2_GPIO_Port GPIOE
#define VGA_HSYNC_Pin GPIO_PIN_11
#define VGA_HSYNC_GPIO_Port GPIOB
#define VGA_VSYNC_Pin GPIO_PIN_12
#define VGA_VSYNC_GPIO_Port GPIOB


 /* function prototypes */

/**
 * @brief Draws customizable text on the VGA screen
 *
 * @param x_lup x position to start writing the text
 * @param y_lup y position to start writing the text
 * @param color colour of the text to be written
 * @param text pointer to the text that needs to be written
 * @param fontname pointer to the name of the font that was selected
 * @param fontsize the size of the font
 * @param fontstyle style of the chosen font, i.e. bold, italic, etc.
 * @param reserved reserved bit, is currently being ignored
 * @return Returns the variable err_code, 0 if the function executed correctly, between 300 and 399 if there was an error during execution
 */
int API_draw_text(int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved);

/**
    @brief Draws a line from coordinate 1 (x,y) to coordinate 2 (x,y) 
    @param x_1 position 1, x-coordinate
    @param y_1 position 1, y-coordinate
    @param x_2 position 2, x-coordinate
    @param y_2 position 2, y-coordinate
    @param color colour of the line to be drawn
    @param weight not sure what line weight is, maybe thickness of the line
    @param reserved reserved bit, is currently being ignored
    @return Returns the variable err_code, 0 if the function executed correctly, between 300 and 399 if there was an error during execution 
 */
 int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved);

 /**
    @brief Draws a customizable rectangle on the VGA screen
    @param x start 
    @return de variabele err_code, 0 als de functie correct is uitgevoerd, iets anders als er een fout is opgetreden tijdens het uitvoeren
 */
 int API_draw_rectangle(int x, int y, int width, int height, int color, int filled, int reserved, int reserved2);

 /**
    @brief Schrijft text op het scherm via een aantal parameters
    @param 
    @return de variabele err_code, 0 als de functie correct is uitgevoerd, iets anders als er een fout is opgetreden tijdens het uitvoeren
 */
 int API_draw_bitmap(int x_lup, int y_lup, int bm_nr);

 /**
    @brief Schrijft text op het scherm via een aantal parameters
    @param 
    @return de variabele err_code, 0 als de functie correct is uitgevoerd, iets anders als er een fout is opgetreden tijdens het uitvoeren
 */
 int API_clearscreen(int color);


 /* Optional function prototypes */

 /**
    @brief Schrijft text op het scherm via een aantal parameters
    @param 
    @return de variabele err_code, 0 als de functie correct is uitgevoerd, iets anders als er een fout is opgetreden tijdens het uitvoeren
 */
 int API_wait(int msecs);

 /**
    @brief Schrijft text op het scherm via een aantal parameters
    @param 
    @return de variabele err_code, 0 als de functie correct is uitgevoerd, iets anders als er een fout is opgetreden tijdens het uitvoeren
 */
 int API_repeat_commands(int nr_previous_commands, int iterations, int reserved);

 /**
    @brief Schrijft text op het scherm via een aantal parameters
    @param 
    @return de variabele err_code, 0 als de functie correct is uitgevoerd, iets anders als er een fout is opgetreden tijdens het uitvoeren
 */
 int API_draw_circle(int x, int y, int radius, int color, int reserved);

 /**
    @brief Schrijft text op het scherm via een aantal parameters
    @param 
    @return de variabele err_code, 0 als de functie correct is uitgevoerd, iets anders als er een fout is opgetreden tijdens het uitvoeren
 */
 int API_draw_figure(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x_4, int y_4, int x_5, int y_5, int color, int reserved);


void API_Init(void);
void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void UB_VGA_FillScreen(uint8_t color);
void UB_VGA_SetPixel(uint16_t xp, uint16_t yp, uint8_t color);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);





 // Defines for GPIO pins 
#define VGA_GPIOE_BASE_ADR     ((uint32_t)0x40021000) // ADR from Port-E
#define VGA_GPIO_ODR_OFFSET    ((uint32_t)0x00000014) // ADR from Register ODR
#define VGA_GPIO_BYTE_OFFSET   ((uint32_t)0x00000001) // Data for 8bit
#define VGA_GPIOE_ODR_ADDRESS   (VGA_GPIOE_BASE_ADR | VGA_GPIO_ODR_OFFSET | VGA_GPIO_BYTE_OFFSET)

//--------------------------------------------------------------
// Define for black on PE8 - PE15
//--------------------------------------------------------------
#define VGA_GPIO_HINIBBLE  ((uint16_t)0xFF00) // GPIO_Pin_8 to GPIO_Pin_15

// 16 different colours, maybe an opportunity to save RAM?
// 8 bit -> 4 bit, and then masking to get 8-bit again?
#define VGA_COLOR_BLACK 0xFF
#define VGA_COLOR_BLUE
#define VGA_COLOR_LIGHTBLUE
#define VGA_COLOR_GREEN
#define VGA_COLOR_LIGHTGREEN
#define VGA_COLOR_CYAN
#define VGA_COLOR_LIGHTCYAN
#define VGA_COLOR_RED
#define VGA_COLOR_LIGHTRED
#define VGA_COLOR_MAGENTA
#define VGA_COLOR_LIGHTMAGENTA
#define VGA_COLOR_BROWN
#define VGA_COLOR_YELLOW
#define VGA_COLOR_GRAY
#define VGA_COLOR_WHITE
#define VGA_COLOR_RESERVED

// Boundaries of the vga display /2, because of the available RAM and oscilator options
#define VGA_DISPLAY_X   320
#define VGA_DISPLAY_Y   240

/* Every define needed to configure the timers for pixelclock and vertical timing */


// Defines for timer 1
// Because it is not possible to generate a 25.2 or 25MHz clock, a 14MHz clock is generated instead
// This is done through: 
// APB2 base clock = 168MHz
// Division factor for the clock = 11 (+1)
// Generated clock = 168 / 11 (+1) = 14MHz
// With a horizontal resolution of 320, we achieve a video-on time of 22,85 us, which is close enough to the 25,42 us specified timing
#define VGA_TIM1_PERIOD         11
#define VGA_TIM1_PRESCALE       0


// Defines for timer 2
// This timer is still set to 31.48kHz to achieve 60Hz
// This is done through: 
// APB1 base clock = 84MHz
// Division factor for the clock = 2667 (+1)
// Generated clock = 84 / 2667 (+1) = 31,48kHz
// With a vertical resolution of 240, we achieve a video-on time of 22,85 us, which is close enough to the 25,42 us specified timing
#define VGA_TIM2_HSYNC_PERIOD   2667
#define VGA_TIM2_HSYNC_PRESCALE 0

#define VGA_TIM2_HSYNC_IMP      320 // Prev 320
#define VGA_TIM2_HTRIGGER_START 480 // Prev 480
#define VGA_TIM2_DMA_DELAY      37 // Prev 37
// #define  VGA_TIM2_DMA_DELAY         30  // ease the delay when DMA START (Optimization = -O1)


// Defines for the VSync-signal
#define VGA_VSYNC_PERIODE        525 
#define VGA_VSYNC_IMP            2
#define VGA_VSYNC_BILD_START     36 // Prev 36
#define VGA_VSYNC_BILD_STOP      514   // (16,38ms)


/* Structure definition for VGA */
typedef struct {
  uint16_t hsync_cnt;   // counter
  uint32_t start_adr;   // start_adres
}VGA_t;
extern VGA_t VGA;


extern uint8_t VGA_RAM1[(VGA_DISPLAY_X+1)*VGA_DISPLAY_Y];