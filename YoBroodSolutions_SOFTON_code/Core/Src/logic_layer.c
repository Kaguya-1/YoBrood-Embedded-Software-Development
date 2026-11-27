/*
 logic_layer.c
 By C.Fletcher

 I get a 2d array of chars from front layer.
 I need to validate the data has the correct number of parameters.
 I find the datatype of the parameters and store them in a struct.
 I call the API func
 */


 #include "logic_layer.h"
 #include "main.h"

ValidationLUT_t validationLUT[] = 
{
    {"lijn", LINE_PARAM_COUNT, 201, LOGIC_APIcommand_line},
    {"rechthoek", RECT_PARAM_COUNT, 202, LOGIC_APIcommand_rect},
    {"tekst", TEXT_PARAM_COUNT, 203, LOGIC_APIcommand_text},
    {"bitmap", BITMAP_PARAM_COUNT, 204, LOGIC_APIcommand_bitmap},
    {"clearscreen", CLEARSCREEN_PARAM_COUNT, 205, LOGIC_APIcommand_clearscreen},
    {"wacht", WAIT_PARAM_COUNT, 206, LOGIC_APIcommand_wait},
    {"herhaal", REPEAT_PARAM_COUNT, 207, LOGIC_APIcommand_repeat},
    {"cirkel", CIRCLE_PARAM_COUNT, 208, LOGIC_APIcommand_circle},
    {"figuur", FIGURE_PARAM_COUNT, 209, LOGIC_APIcommand_figure}
};

const int validationLUT_size = sizeof(validationLUT) / sizeof(validationLUT[0]);    //define size of the LUT for readability later

// Validate the data received from the front layer
int LOGIC_data_validation(const char data[][MAX_STR_PARAM_LENGTH], int parameter_count)
{
    for(int i = 0; i < validationLUT_size; i++)
    {
        if(strcmp(data[0], validationLUT[i].command_name) == 0)
        {
            if(parameter_count != validationLUT[i].expected_param_count)
                return validationLUT[i].error_code; //return error code for incorrect parameter count of specific command
            
            else
                return validationLUT[i].callAPI_function(data); //call the API function for the specific command
        }
    }
    return 200; // Unknown command
}