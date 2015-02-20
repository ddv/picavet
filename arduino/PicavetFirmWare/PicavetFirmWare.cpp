// Do not remove the include below
#include "PicavetFirmWare.h"
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include "utility/debug.h"
#include "utility/socket.h"
extern HardwareSerial Serial;

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

#define MAX_PATH              64      // Maximum length of the HTTP request path that can be parsed.
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



void setup(void)
{
  Serial.begin(115200);
  Serial.println(F("Hello, CC3000!\n"));

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
      Serial.print(F("Action: ")); Serial.println(action);
      Serial.print(F("Path: ")); Serial.println(path);
      // Check the action to see if it was a GET request.
      if (strcmp(action, "GET") == 0) {
        // Respond with the path that was accessed.
        // First send the success response code.
    	  client.fastrprintln(F("HTTP/1.1 200 OK"));
    	  client.fastrprintln(F("Content-Type: text/html"));
    	  client.fastrprintln(F("Connection: close")); // the connection will be closed after completion of the response
    	  client.println();
    	  client.fastrprintln(F("<!DOCTYPE HTML>"));
    	  client.fastrprintln(F("<html>"));

    	  client.fastrprintln(F("<h1>TEST</h1>"));
    	  client.fastrprintln(F("<form>"));
    	  client.fastrprintln(F("<input type=text name='cmd' value='moveleft'>"));
    	  client.fastrprintln(F("<input type=text name='time' value='1000'>"));
    	  client.fastrprintln(F("<input type='submit' value='Send data...'>"));
    	  client.fastrprintln(F("</form>"));
		client.fastrprint(F("You accessed path: "));
			client.fastrprintln(path);
			client.fastrprintln(F("</html>"));

			Serial.print(F(">>>PATH:"));
			if(String(path).startsWith("/?cmd=moveleft&time=")) {
				String p = String(path);
				String val = p.substring(20);
				int val_int = val.toInt();
				Serial.print(F(">>>CMD VAL=["));
				Serial.print(val_int);
				Serial.println(F("]"));
			}
			Serial.println(String(path));

      }
      else {
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






//void setup() {
//	Serial.begin(115200);
//
//	Serial.println(F("Hello, CC3000!\n"));
//
//	Serial.print("Free RAM: ");
//	Serial.println(getFreeRam(), DEC);
//
//	Serial.println(F("\nInitializing..."));
//	if (!cc3000.begin()) {
//		Serial.println(F("Couldn't begin()! Check your wiring?"));
//		while (1)
//			;
//	}
//
//	Serial.print(F("\nAttempting to connect to "));
//	Serial.println(WLAN_SSID);
//	if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
//		Serial.println(F("Failed!"));
//		while (1)
//			;
//	}
//
//	Serial.println(F("Connected!"));
//
//	Serial.println(F("Request DHCP"));
//	while (!cc3000.checkDHCP()) {
//		delay(100); // ToDo: Insert a DHCP timeout!
//	}
//
//	/* Display the IP address DNS, Gateway, etc. */
//	while (!displayConnectionDetails()) {
//		delay(1000);
//	}
//
//	chatServer.begin();
//
//	Serial.println(F("Listening for connections..."));
//
//}



//void loop() {
//
//	// Установка связи с клиентским сокетом
//	Adafruit_CC3000_ClientRef client = chatServer.available();
//
//	if (client) {
//
//		Serial.println("new client");
//		// an http request ends with a blank line
//		boolean currentLineIsBlank = true;
//
//		//Выделяем буфер для чтения строк
//		//char buffer[HTTP_GET_BUFFER_SIZE];
//		//int charIndex = 0;
//
//		// Строка, для получения данных из сокета
//		String readString = String();
//
//		while (client.connected()) {
//			if (client.available()) {
//				char c = client.read();
//
//
////				if (c == '\n') {
////					Serial.print("string [" + readString + "]\n");
////
////
////					//int i = readString.indexOf("GET ");
////
////						Serial.print("[GET LENGTH]=");
////						Serial.println(readString.length());
////
////						//if(readString.startsWith("GET ")) {
////							Serial.print("[GET COMMAND]");
////							//Serial.println(readString);
////						//}
////
////
////
////					readString = String();
////				} else if (readString.length() < HTTP_GET_BUFFER_SIZE) {
////					if (c != '\r') {
////						readString.concat(c);
////					}
////				}
////
//
//				Serial.write(c);
//				// if you've gotten to the end of the line (received a newline
//				// character) and the line is blank, the http request has ended,
//				// so you can send a reply
//				if (c == '\n' && currentLineIsBlank) {
//					// send a standard http response header
//					client.println("HTTP/1.1 200 OK");
//					client.println("Content-Type: text/html");
//					client.println("Connection: close"); // the connection will be closed after completion of the response
////					client.println("Refresh: 20"); // refresh the page automatically every 5 sec
//					client.println();
//					client.println("<!DOCTYPE HTML>");
//					client.println("<html>");
//
//					client.println("<h1>TEST</h1>");
//					client.println("<form>");
//					client.println("<input type=text name='cmd' value='moveleft'>");
//					client.println("<input type=text name='time' value='1000'>");
//					client.println("<input type='submit' value='Send data...'>");
//					client.println("</form>");
//					client.println("</html>");
//					break;
//				}
//				if (c == '\n') {
//					// you're starting a new line
//					currentLineIsBlank = true;
//				} else if (c != '\r') {
//					// you've gotten a character on the current line
//					currentLineIsBlank = false;
//				}
//			}
//		}
//		// give the web browser time to receive the data
//		delay(1);
//		// close the connection:
//		client.stop();
//		Serial.println("client disconnected");
//		Serial.print("Free RAM: ");
//		Serial.println(getFreeRam(), DEC);
//	}
//
////	MatchState ms;
//
////	for (int i = 0; i < 4; i++) {
////		Serial.println(test_http_headers[i]);
////		ParseRequestStr(test_http_headers[i]);
////	}
//
//
//}
//
//void ParseRequestStr(String reqStr) {
////	MatchState ms;
////	unsigned int index = 0;
////	char bufferReqStr[reqStr.length() + 1]; //Buf for Reg Ex
////	char bufferStr[reqStr.length() + 1]; // Buf for char array
////	reqStr.toCharArray(bufferStr, reqStr.length() + 1); // String to Char Array
////	ms.Target(bufferStr);
////
////	while (true) {
////
////		char result = ms.Match("GET /%?(.+)=(.+)&(.+)=(.+) .*", index);
//////		char result = ms.Match("%.+(%.+)=(%-?%a+)%.+", index);
////		if (result == REGEXP_MATCHED) {
////			Serial.print("Matched on: ");
////			Serial.println(ms.GetMatch(bufferReqStr));
////			Serial.println("Captures:");
////			for (int j = 0; j < ms.level; j++)
////				Serial.println(ms.GetCapture(bufferReqStr, j));
////			index = ms.MatchStart + ms.MatchLength;
////
////			Serial.print("GET COMMAND cmd=[");
////			Serial.print(ms.GetCapture(bufferReqStr, 1));
////			Serial.print("] time=[" );
////			Serial.print(ms.GetCapture(bufferReqStr, 3));
////			Serial.println("]" );
////
////		} else
////			break;
////	}
////
//
//}
//
///**************************************************************************/
///*!
// @brief  Tries to read the IP address and other connection details
// */
///**************************************************************************/
//bool displayConnectionDetails(void) {
//	uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
//
//	if (!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv,
//			&dnsserv)) {
//		Serial.println(F("Unable to retrieve the IP Address!\r\n"));
//		return false;
//	} else {
//		Serial.print(F("\nIP Addr: "));
//		cc3000.printIPdotsRev(ipAddress);
//		Serial.print(F("\nNetmask: "));
//		cc3000.printIPdotsRev(netmask);
//		Serial.print(F("\nGateway: "));
//		cc3000.printIPdotsRev(gateway);
//		Serial.print(F("\nDHCPsrv: "));
//		cc3000.printIPdotsRev(dhcpserv);
//		Serial.print(F("\nDNSserv: "));
//		cc3000.printIPdotsRev(dnsserv);
//		Serial.println();
//		return true;
//	}
//}
