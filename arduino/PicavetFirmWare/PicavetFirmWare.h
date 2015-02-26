// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef PicavetFirmWare_H_
#define PicavetFirmWare_H_
#include "Arduino.h"
//add your includes for the project PicavetFirmWare here


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
//void ParseRequestStr(String);
//bool displayConnectionDetails(void);
//void parseFirstLine(char* line, char* action, char* path);
//bool parseRequest(uint8_t* buf, int bufSize, char* action, char* path) {

#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project PicavetFirmWare here




//Do not add code below this line
#endif /* PicavetFirmWare_H_ */