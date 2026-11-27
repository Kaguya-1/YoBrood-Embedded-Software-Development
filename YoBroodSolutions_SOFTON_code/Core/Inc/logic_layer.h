/** ==================================================================================== 
 * @file logic_layer.h                                                             
 * @author C.Fletcher                                  
 * @date 23-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief header for the logic layer, contains all of the logic functions for the program
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */

 //define for debugging
#define DEBUG_LOGIC_LAYER 0

//define for the expected parameter count for each command
#define LINE_PARAM_COUNT 7
#define RECT_PARAM_COUNT 7
#define TEXT_PARAM_COUNT 8
#define BITMAP_PARAM_COUNT 4
#define CLEARSCREEN_PARAM_COUNT 2
#define WAIT_PARAM_COUNT 2
#define REPEAT_PARAM_COUNT 3
#define CIRCLE_PARAM_COUNT 5
#define FIGURE_PARAM_COUNT 12

//function prototypes for logic layer
int LOGIC_data_validation(const char [][MAX_STR_PARAM_LENGTH], int parameter_count);
int LOGIC_APIcommand_line(const char [][MAX_STR_PARAM_LENGTH]);
int LOGIC_APIcommand_rect(const char [][MAX_STR_PARAM_LENGTH]);
int LOGIC_APIcommand_text(const char [][MAX_STR_PARAM_LENGTH]);
int LOGIC_APIcommand_bitmap(const char [][MAX_STR_PARAM_LENGTH]);
int LOGIC_APIcommand_clearscreen(const char [][MAX_STR_PARAM_LENGTH]);
int LOGIC_APIcommand_wait(const char [][MAX_STR_PARAM_LENGTH]);
int LOGIC_APIcommand_repeat(const char [][MAX_STR_PARAM_LENGTH]);
int LOGIC_APIcommand_circle(const char [][MAX_STR_PARAM_LENGTH]);
int LOGIC_APIcommand_figure(const char [][MAX_STR_PARAM_LENGTH]);

//typedefs
typedef struct
{
    const char* command_name;
    int expected_param_count;
    int error_code;
    int (*callAPI_function)(const char [][MAX_STR_PARAM_LENGTH]);
} ValidationLUT_t;