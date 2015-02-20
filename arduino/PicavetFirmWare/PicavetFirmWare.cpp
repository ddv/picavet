// Do not remove the include below
#include "PicavetFirmWare.h"
//http://www.gammon.com.au/forum/?id=11063
#include <Regexp.h>
//http://forum.biicode.com/t/eclipse-unresolved-inclusion-arduino-h/195/6
extern HardwareSerial Serial;
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include "utility/debug.h"
#include "utility/socket.h"

// инициализация WI-FI шилда
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
#define WLAN_SSID "JY-G5"           // cannot be longer than 32 characters!
#define WLAN_SECURITY   WLAN_SEC_WPA2
#define WLAN_PASS "1234567890" // Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define LISTEN_PORT           80//23    // What TCP port to listen on for connections.

char* test_http_headers[] = {
		"GET /?cmd=moveleft&time=100 HTTP/1.1",
	"GET /index.html?aaa=1&bbb=2;ccc=3 HTTP/1.1",
	"Host: 192.168.43.47",
	"Connection: keep-alive",
	"Accept: text/html,application/wrap string"
	" [Accept: text/html,application/]xhtml+xml,application/xml;q=0.9wrap"
	" string [html+xml,application/xml;q=0.9],*/*;q=0.8"
};

// инициализируем WI-FI шилд
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS,
ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);

// Открываем серверный сокет
Adafruit_CC3000_Server chatServer(LISTEN_PORT);


// Размер входного буфера (HTTP)
#define HTTP_GET_BUFFER_SIZE 100

void setup() {
	Serial.begin(115200);

	Serial.println(F("Hello, CC3000!\n"));

	Serial.print("Free RAM: ");
	Serial.println(getFreeRam(), DEC);

	Serial.println(F("\nInitializing..."));
	if (!cc3000.begin()) {
		Serial.println(F("Couldn't begin()! Check your wiring?"));
		while (1)
			;
	}

	Serial.print(F("\nAttempting to connect to "));
	Serial.println(WLAN_SSID);
	if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
		Serial.println(F("Failed!"));
		while (1)
			;
	}

	Serial.println(F("Connected!"));

	Serial.println(F("Request DHCP"));
	while (!cc3000.checkDHCP()) {
		delay(100); // ToDo: Insert a DHCP timeout!
	}

	/* Display the IP address DNS, Gateway, etc. */
	while (!displayConnectionDetails()) {
		delay(1000);
	}

	chatServer.begin();

	Serial.println(F("Listening for connections..."));

}

void loop() {

	// Установка связи с клиентским сокетом
	Adafruit_CC3000_ClientRef client = chatServer.available();

	if (client) {

		Serial.println("new client");
		// an http request ends with a blank line
		boolean currentLineIsBlank = true;

		//Выделяем буфер для чтения строк
		//char buffer[HTTP_GET_BUFFER_SIZE];
		//int charIndex = 0;

		// Строка, для получения данных из сокета
		String readString = String();

		while (client.connected()) {
			if (client.available()) {
				char c = client.read();


				if (c == '\n') {
					Serial.print("string [" + readString + "]\n");


					//int i = readString.indexOf("GET ");

						Serial.print("[GET COMMAND]=");
						Serial.println(readString.length());
						//Serial.println(i);


					readString = String();
				} else if (readString.length() < HTTP_GET_BUFFER_SIZE) {
					if (c != '\r') {
						readString.concat(c);
					}
				}


				Serial.write(c);
				// if you've gotten to the end of the line (received a newline
				// character) and the line is blank, the http request has ended,
				// so you can send a reply
				if (c == '\n' && currentLineIsBlank) {
					// send a standard http response header
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println("Connection: close"); // the connection will be closed after completion of the response
//					client.println("Refresh: 20"); // refresh the page automatically every 5 sec
					client.println();
					client.println("<!DOCTYPE HTML>");
					client.println("<html>");

					client.println("<h1>TEST</h1>");
					client.println("<form>");
					client.println("<input type=text name='cmd' value='moveleft'>");
					client.println("<input type=text name='time' value='1000'>");
					client.println("<input type='submit' value='Send data...'>");
					client.println("</form>");
					client.println("</html>");
					break;
				}
				if (c == '\n') {
					// you're starting a new line
					currentLineIsBlank = true;
				} else if (c != '\r') {
					// you've gotten a character on the current line
					currentLineIsBlank = false;
				}
			}
		}
		// give the web browser time to receive the data
		delay(1);
		// close the connection:
		client.stop();
		Serial.println("client disconnected");
	}

	MatchState ms;

//	for (int i = 0; i < 4; i++) {
//		Serial.println(test_http_headers[i]);
//		ParseRequestStr(test_http_headers[i]);
//	}


}

void ParseRequestStr(String reqStr) {
	MatchState ms;
	unsigned int index = 0;
	char bufferReqStr[reqStr.length() + 1]; //Buf for Reg Ex
	char bufferStr[reqStr.length() + 1]; // Buf for char array
	reqStr.toCharArray(bufferStr, reqStr.length() + 1); // String to Char Array
	ms.Target(bufferStr);

	while (true) {

		char result = ms.Match("GET /%?(.+)=(.+)&(.+)=(.+) .*", index);
//		char result = ms.Match("%.+(%.+)=(%-?%a+)%.+", index);
		if (result == REGEXP_MATCHED) {
			Serial.print("Matched on: ");
			Serial.println(ms.GetMatch(bufferReqStr));
			Serial.println("Captures:");
			for (int j = 0; j < ms.level; j++)
				Serial.println(ms.GetCapture(bufferReqStr, j));
			index = ms.MatchStart + ms.MatchLength;

			Serial.print("GET COMMAND cmd=[");
			Serial.print(ms.GetCapture(bufferReqStr, 1));
			Serial.print("] time=[" );
			Serial.print(ms.GetCapture(bufferReqStr, 3));
			Serial.println("]" );

		} else
			break;
	}


}

/**************************************************************************/
/*!
 @brief  Tries to read the IP address and other connection details
 */
/**************************************************************************/
bool displayConnectionDetails(void) {
	uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

	if (!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv,
			&dnsserv)) {
		Serial.println(F("Unable to retrieve the IP Address!\r\n"));
		return false;
	} else {
		Serial.print(F("\nIP Addr: "));
		cc3000.printIPdotsRev(ipAddress);
		Serial.print(F("\nNetmask: "));
		cc3000.printIPdotsRev(netmask);
		Serial.print(F("\nGateway: "));
		cc3000.printIPdotsRev(gateway);
		Serial.print(F("\nDHCPsrv: "));
		cc3000.printIPdotsRev(dhcpserv);
		Serial.print(F("\nDNSserv: "));
		cc3000.printIPdotsRev(dnsserv);
		Serial.println();
		return true;
	}
}
