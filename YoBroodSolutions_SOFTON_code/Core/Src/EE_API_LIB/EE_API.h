/** ==================================================================================== 
 * @file EE_API.h                                                             
 * @author K.vijlbrief                                     
 * @date 13-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief EE API VGA driver header file, contains all function and data prototypes for layer 1 and 2 
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */





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