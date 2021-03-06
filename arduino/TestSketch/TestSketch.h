// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _TestSketch_H_
#define _TestSketch_H_
#include "Arduino.h"
//add your includes for the project TestSketch here


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
bool parseRequest(uint8_t* buf, int bufSize, char* action, char* path);
void parseFirstLine(char* line, char* action, char* path);
bool displayConnectionDetails(void);
int runHttpCommand(char http_path[]);
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project TestSketch here




//Do not add code below this line
#endif /* _TestSketch_H_ */
