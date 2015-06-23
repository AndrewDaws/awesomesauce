#include "Parser.h"
#include "MK20DX256.h"

#ifndef TEST
#define STATIC static
#else
#define STATIC
#endif

#define PARSER_BUFFER_LENGTH_MAX (23)

STATIC PARSER_STATE_T state = PARSER_LOOKING_FOR_START;

static char buffer[PARSER_BUFFER_LENGTH_MAX];

char* Parser_AddChar(char NewChar) {
    
    if (NewChar == '[') {
        state = PARSER_LOOKING_FOR_CMD;
        buffer[0] = NewChar;
        return 0;
    }
    
    switch(state) {
        case PARSER_LOOKING_FOR_CMD:
            if ((NewChar >= 'A') && (NewChar <= 'Z')) {
                state = PARSER_LOOKING_FOR_LEN;
                buffer[1] = NewChar;
            }
            else
                state = PARSER_LOOKING_FOR_START;
            break;
            
        case PARSER_LOOKING_FOR_LEN:
            if (NewChar == '0') {
                state = PARSER_LOOKING_FOR_END;
                buffer[2] = NewChar;
            }
            else
                state = PARSER_LOOKING_FOR_START;
            break;

        case PARSER_LOOKING_FOR_END:
            if (NewChar == ']') {
                buffer[3] = NewChar;
                buffer[4] = 0; //NULL TERMINATE
                return buffer;
            }
            state = PARSER_LOOKING_FOR_START;
            break;

        default:  
            break;
    }

    return 0;
}