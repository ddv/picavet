// Do not remove the include below
#include "PicavetFirmWare.h"
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include <Servo.h>
#include "utility/debug.h"
#include "utility/socket.h"
#include <string.h>
#include <avr/pgmspace.h> //PROGMEM
//#undef PROGMEM
//#define PROGMEM __attribute__(( section(".progmem.data") ))
//extern HardwareSerial Serial;




// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "JY-G5"   // cannot be longer than 32 characters!
#define WLAN_PASS       "1234567890"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define LISTEN_PORT           80      // What TCP port to listen on for connections.
                                      // The HTTP protocol uses port 80 by default.

#define MAX_ACTION            10      // Maximum length of the HTTP action that can be parsed.

#define MAX_PATH              100      // Maximum length of the HTTP request path that can be parsed.
                                      // There isn't much memory available so keep this short!

#define BUFFER_SIZE           MAX_ACTION + MAX_PATH + 20  // Size of buffer for incoming request data.
                                                          // Since only the first line is parsed this
                                                          // needs to be as large as the maximum action
                                                          // and path plus a little for whitespace and
                                                          // HTTP version.

#define TIMEOUT_MS            500    // Amount of time in milliseconds to wait for
                                     // an incoming request to finish.  Don't set this
                                     // too high or your server could be slow to respond.

Adafruit_CC3000_Server httpServer(LISTEN_PORT);
uint8_t buffer[BUFFER_SIZE+1];
int bufindex = 0;
char action[MAX_ACTION+1];
char path[MAX_PATH+1];

// Заголовок http-ответа text/html
const char HTTP_RESPONCE_HEADER_OK_0[] PROGMEM = "HTTP/1.1 200 OK\n";
const char HTTP_RESPONCE_HEADER_OK_1[] PROGMEM = "Content-Type: text/html\n";
const char HTTP_RESPONCE_HEADER_OK_2[] PROGMEM = "Connection: close\n\n";

const char* PROGMEM HTTP_RESPONCE_HEADER_OK[] PROGMEM = {
	HTTP_RESPONCE_HEADER_OK_0,
	HTTP_RESPONCE_HEADER_OK_1,
	HTTP_RESPONCE_HEADER_OK_2
};

// Заголовок http-ответа (text/plain)
const char HTTP_RESPONCE_HEADER_PLAIN_OK_0[] PROGMEM = "HTTP/1.1 200 OK\n";
const char HTTP_RESPONCE_HEADER_PLAIN_OK_1[] PROGMEM = "Content-Type: text/plain\n";
const char HTTP_RESPONCE_HEADER_PLAIN_OK_2[] PROGMEM = "Connection: close\n\n";

const char* PROGMEM HTTP_RESPONCE_HEADER_PLAIN_OK[] PROGMEM = {
	HTTP_RESPONCE_HEADER_PLAIN_OK_0,
	HTTP_RESPONCE_HEADER_PLAIN_OK_1,
	HTTP_RESPONCE_HEADER_PLAIN_OK_2
};

// HTML Форма для тестирования команд
const char HTTP_TEST_FORM_0[] PROGMEM = "<!DOCTYPE HTML>\n";
const char HTTP_TEST_FORM_1[] PROGMEM = "<html>\n";
const char HTTP_TEST_FORM_2[] PROGMEM = "<h1>TEST</h1>\n";
const char HTTP_TEST_FORM_3[] PROGMEM = "<form>";
const char HTTP_TEST_FORM_4[] PROGMEM = "<input type=text name='cmd' value='moveleft'>\n";
const char HTTP_TEST_FORM_5[] PROGMEM = "<input type=text name='degree' value='-160'>\n";
const char HTTP_TEST_FORM_6[] PROGMEM = "<input type='submit' value='Move left'>\n";
const char HTTP_TEST_FORM_7[] PROGMEM = "</form>";

const char HTTP_TEST_FORM_8[] PROGMEM = "<br>";

const char HTTP_TEST_FORM_9[] PROGMEM = "<form>";
const char HTTP_TEST_FORM_10[] PROGMEM = "<input type=text name='cmd' value='moveright'>\n";
const char HTTP_TEST_FORM_11[] PROGMEM = "<input type=text name='degree' value='120'>\n";
const char HTTP_TEST_FORM_12[] PROGMEM = "<input type='submit' value='Move right'>\n";
const char HTTP_TEST_FORM_13[] PROGMEM = "</form>";

const char HTTP_TEST_FORM_14[] PROGMEM = "<br>";

const char HTTP_TEST_FORM_15[] PROGMEM = "<form>";
const char HTTP_TEST_FORM_16[] PROGMEM = "<input type=text name='cmd' value='moveup'>\n";
const char HTTP_TEST_FORM_17[] PROGMEM = "<input type=text name='degree' value='30'>\n";
const char HTTP_TEST_FORM_18[] PROGMEM = "<input type='submit' value='Move UP'>\n";
const char HTTP_TEST_FORM_19[] PROGMEM = "</form>";

const char HTTP_TEST_FORM_20[] PROGMEM = "<br>";

const char HTTP_TEST_FORM_21[] PROGMEM = "<form>";
const char HTTP_TEST_FORM_22[] PROGMEM = "<input type=text name='cmd' value='movedown'>\n";
const char HTTP_TEST_FORM_23[] PROGMEM = "<input type=text name='degree' value='-30'>\n";
const char HTTP_TEST_FORM_24[] PROGMEM = "<input type='submit' value='Move DOWN'>\n";
const char HTTP_TEST_FORM_25[] PROGMEM = "</form>";

const char* HTTP_TEST_FORM[] PROGMEM = {
	HTTP_TEST_FORM_0,
	HTTP_TEST_FORM_1,
	HTTP_TEST_FORM_2,
	HTTP_TEST_FORM_3,
	HTTP_TEST_FORM_4,
	HTTP_TEST_FORM_5,
	HTTP_TEST_FORM_6,
	HTTP_TEST_FORM_7,
	HTTP_TEST_FORM_8,
	HTTP_TEST_FORM_9,
	HTTP_TEST_FORM_10,
	HTTP_TEST_FORM_11,
	HTTP_TEST_FORM_12,
	HTTP_TEST_FORM_13,
	HTTP_TEST_FORM_14,
	HTTP_TEST_FORM_15,
	HTTP_TEST_FORM_16,
	HTTP_TEST_FORM_17,
	HTTP_TEST_FORM_18,
	HTTP_TEST_FORM_19,
	HTTP_TEST_FORM_20,
	HTTP_TEST_FORM_21,
	HTTP_TEST_FORM_22,
	HTTP_TEST_FORM_23,
	HTTP_TEST_FORM_24,
	HTTP_TEST_FORM_25
};

// Команды приходящие через HTTP GET
const char CMD_MOVE_LEFT[] PROGMEM = "moveleft";
const char CMD_MOVE_RIGHT[] PROGMEM = "moveright";
const char CMD_MOVE_UP[] PROGMEM = "moveup";
const char CMD_MOVE_DOWN[] PROGMEM = "movedown";

#define SERVO_VERTICAL_PIN 12
#define SERVO_HORIZONTAL_PIN 9
#define SERVO_VERTICAL_NULL_POS 90
// Пин определения центрального положения подвеса
#define SERVO_FRONT_IRQ_PIN 7

Servo myservoH;
Servo myservoV;

void setup(void)
{
	Serial.begin(115200);
	Serial.println(F("Picavet WiFi CC3000"));

	//myservoV.attach(SERVO_VERTICAL_PIN);
	//myservoH.attach(SERVO_HORIZONTAL_PIN);

	return;
//
//	myservo.attach(SERVO_VERTICAL_PIN); // attaches the servo on pin 9 to the servo object
//	Serial.print(F("Servo [V] POS 90"));
//	myservo.write(90);
//
//	delay(1000);
//	Serial.print(F(" POS 0"));
//	myservo.write(0);
//	delay(1000);
//
//	delay(1000);
//	Serial.println(F(" POS 180"));
//	myservo.write(180);
//	delay(1000);
//
//	myservo.detach();
//
//	//
//
//	myservo.attach(SERVO_HORIZONTAL_PIN); // attaches the servo on pin 9 to the servo object
//	Serial.print(F("Servo [H]"));
//
//	int i = 50;
//	Serial.print(F("["));
//	Serial.print(i);
//	Serial.print(F("]"));
//
//	delay(1000);
//
//	i = 120;
//	Serial.print(F("["));
//	Serial.print(i);
//	Serial.print(F("]"));
//
//	delay(1000);
//
//	myservo.detach();

//	for (int i = -360; i <= 360; i+=50) {
//
//		Serial.print(F("["));
//		Serial.print(i);
//		Serial.print(F("]"));
//		myservo.write(i);
//
//		delay(1000);
//
//	}
//	myservo.detach();

	//return;

//	for (unsigned int i = 0; i < sizeof(HTTP_RESPONCE_HEADER_OK) / 2; i++) {
//			strcpy_P(path, (char*) pgm_read_word(&(HTTP_RESPONCE_HEADER_OK[i]))); // Necessary casts and dereferencing, just copy.
//			Serial.println(path);
//		}
//
//	for (unsigned int i = 0; i < sizeof(HTTP_TEST_FORM) / 2; i++) {
//		strcpy_P(path, (char*) pgm_read_word(&(HTTP_TEST_FORM[i]))); // Necessary casts and dereferencing, just copy.
//		Serial.println(path);
//	}

	int action = false;

	char s1[] = "/?cmd=moveleft&degree=90";
	action = runHttpCommand(s1);
	Serial.print(F("ACTION="));
	Serial.println(action);

	delay(2000);

	char s2[] = "/?cmd=moveright&degree=120";
	action = runHttpCommand(s2);
	Serial.print(F("ACTION="));
	Serial.println(action);

	delay(2000);

	return;

//	char s3[] = "/?cmd=moveup&degree=-30";
//	action = runHttpCommand(s3);
//	Serial.print(F("ACTION="));
//	Serial.println(action);
//
//	char s4[] = "/?cmd=movedown&degree=-45";
//	action = runHttpCommand(s4);
//	Serial.print(F("ACTION="));
//	Serial.println(action);
//
//	char s5[] = "/?cmd=center";
//	action = runHttpCommand(s5);
//	Serial.print(F("ACTION="));
//	Serial.println(action);



//	memset(&path,   0, sizeof(path)); // Забиваем нулями
//
//	Serial.print("path=[");
//	Serial.print(sizeof(path));
//	Serial.println("]");


//	char s[] = "/?cmd=moveleft&degree=-160";
//
//
//	Serial.print("char path=[");
//	Serial.print(sizeof(s));
//	Serial.println("]");
//
//	String ss = String(s);
//
//	Serial.print("String ss length=[");
//	Serial.print(ss.length());
//	Serial.println("]");
//
//	Serial.print("String=[");
//	Serial.print(ss);
//	Serial.println("]");
//
//	Serial.println("] str=");
//	 for (unsigned int i = 0; i < sizeof(s) - 1; i++){
//	    Serial.print(i, DEC);
//	    Serial.print(" = ");
//	    Serial.write(s[i]);
//	    Serial.println();
//
//	  }






  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);

  // Initialise the module
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }

  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }

  Serial.println(F("Connected!"));

  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }

  // Display the IP address DNS, Gateway, etc.
  while (! displayConnectionDetails()) {
    delay(1000);
  }

  // ******************************************************
  // You can safely remove this to save some flash memory!
  // ******************************************************
  Serial.println(F("\r\nNOTE: This sketch may cause problems with other sketches"));
  Serial.println(F("since the .disconnect() function is never called, so the"));
  Serial.println(F("AP may refuse connection requests from the CC3000 until a"));
  Serial.println(F("timeout period passes.  This is normal behaviour since"));
  Serial.println(F("there isn't an obvious moment to disconnect with a server.\r\n"));

  // Start listening for connections
  httpServer.begin();

  Serial.println(F("Listening for connections..."));
}

void loop(void)
{

	char s1[] = "/?cmd=moveleft&degree=90";
	int a = runHttpCommand(s1);
	Serial.print(F("ACTION="));
	Serial.println(a);

	delay(2000);

	while(true) {}


  // Try to get a client which is connected.
  Adafruit_CC3000_ClientRef client = httpServer.available();
  if (client) {
    Serial.println(F("Client connected."));
    // Process this request until it completes or times out.
    // Note that this is explicitly limited to handling one request at a time!

    // Clear the incoming data buffer and point to the beginning of it.
    bufindex = 0;
    memset(&buffer, 0, sizeof(buffer));

    // Clear action and path strings.
    memset(&action, 0, sizeof(action));
    memset(&path,   0, sizeof(path));

    // Set a timeout for reading all the incoming data.
    unsigned long endtime = millis() + TIMEOUT_MS;

    // Read all the incoming data until it can be parsed or the timeout expires.
    bool parsed = false;
    while (!parsed && (millis() < endtime) && (bufindex < BUFFER_SIZE)) {
      if (client.available()) {
        buffer[bufindex++] = client.read();
      }
      parsed = parseRequest(buffer, bufindex, action, path);
    }

    // Handle the request if it was parsed.
		if (parsed) {
			Serial.println(F("Processing request"));
			Serial.print(F("Action: "));
			Serial.println(action);
			Serial.print(F("Path: "));
			Serial.println(path);
			// Check the action to see if it was a GET request.
			if (strcmp(action, "GET") == 0) {
				// Respond with the path that was accessed.
				// First send the success response code.


				// Обрабатываем GET-запрос. Ищем факт передачи комманды
				int command_status =  runHttpCommand(path);

				// Выдаем HTTP-заголовоки
				for (unsigned int i = 0; i < sizeof(HTTP_RESPONCE_HEADER_OK) / 2; i++) {
					strcpy_P(path, (char*) pgm_read_word(&(HTTP_RESPONCE_HEADER_OK[i])));
					client.fastrprint(path);
				}

				// Выдаем тестовую HTML-форму
				for (unsigned int i = 0; i < sizeof(HTTP_TEST_FORM) / 2; i++) {
					strcpy_P(path, (char*) pgm_read_word(&(HTTP_TEST_FORM[i])));
					client.fastrprint(path);
				}


				client.fastrprint(F("<hr><h2> RESULT "));

				char buf [4];
				sprintf (buf, "%d", command_status);
				client.fastrprint(buf);
				client.fastrprint(F("</h2> "));


				client.fastrprintln(F("</html>"));








			} else {
				// Unsupported action, respond with an HTTP 405 method not allowed error.
				client.fastrprintln(F("HTTP/1.1 405 Method Not Allowed"));
				client.fastrprintln(F(""));
			}
		}

    // Wait a short period to make sure the response had time to send before
    // the connection is closed (the CC3000 sends data asyncronously).
    delay(100);

    Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);

    // Close the connection when done.
    Serial.println(F("Client disconnected"));

    client.close();
  }
}


// Парсер GET-запроса
// возвращает статус выполнения команды
int runHttpCommand(char http_path[]) {

	Serial.println(F("runCommand"));

	Serial.print("http_path=[");
	Serial.print(http_path);
	Serial.println("]");

	char cmd[10];
	int value;

	int i = sscanf(http_path, "/?cmd=%[^'&']&degree=%d", cmd, &value);

	Serial.print(F("cmd=["));
	Serial.print(cmd);
	Serial.print(F("] value=["));
	Serial.print(value);
	Serial.print(F("]["));
	Serial.print(i);
	Serial.println(F("]"));



	if (strcmp_P(cmd, CMD_MOVE_LEFT) == 0) {
		Serial.print(F("!!! MOVE LEFT !!!! angle="));
		myservoH.attach(SERVO_HORIZONTAL_PIN);
		myservoH.write(value);
		Serial.println(myservoH.read());
		delay(1000);
		myservoH.write(SERVO_VERTICAL_NULL_POS);
		myservoH.detach();
		return 0;
	}

	if (strcmp_P(cmd, CMD_MOVE_RIGHT) == 0) {
		Serial.print(F("!!! MOVE RIGHT !!!! angle="));
		myservoH.write(value);
		Serial.println(myservoH.read());
		delay(1000);
		myservoH.write(SERVO_VERTICAL_NULL_POS);
		return 0;
	}

	if (strcmp_P(cmd, CMD_MOVE_UP) == 0) {
		Serial.println(F("!!! MOVE UP !!!!"));
		return 0;
	}
	if (strcmp_P(cmd, CMD_MOVE_DOWN) == 0) {
		Serial.println(F("!!! MOVE DOWN !!!!"));
		return 0;
	}


	return -1;
}

// Return true if the buffer contains an HTTP request.  Also returns the request
// path and action strings if the request was parsed.  This does not attempt to
// parse any HTTP headers because there really isn't enough memory to process
// them all.
// HTTP request looks like:
//  [method] [path] [version] \r\n
//  Header_key_1: Header_value_1 \r\n
//  ...
//  Header_key_n: Header_value_n \r\n
//  \r\n
bool parseRequest(uint8_t* buf, int bufSize, char* action, char* path) {
  // Check if the request ends with \r\n to signal end of first line.
  if (bufSize < 2)
    return false;
  if (buf[bufSize-2] == '\r' && buf[bufSize-1] == '\n') {
    parseFirstLine((char*)buf, action, path);
    return true;
  }
  return false;
}

// Parse the action and path from the first line of an HTTP request.
void parseFirstLine(char* line, char* action, char* path) {
  // Parse first word up to whitespace as action.bool displayConnectionDetails(void)
  char* lineaction = strtok(line, " ");
  if (lineaction != NULL)
    strncpy(action, lineaction, MAX_ACTION);
  // Parse second word up to whitespace as path.
  char* linepath = strtok(NULL, " ");
  if (linepath != NULL)
    strncpy(path, linepath, MAX_PATH);
}

// Tries to read the IP address and other connection details
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}


