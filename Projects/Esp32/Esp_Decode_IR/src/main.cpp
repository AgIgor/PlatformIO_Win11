#if defined(ESP8266)
#include "ESP8266WiFi.h"
#elif defined(ESP32)
#include "WiFi.h"
#else
#error "This ain't a ESP8266 or ESP32"
#endif

#include "Arduino.h"
#include "IRremoteESP8266.h"  // ESP32 and ESP8266
#include "IRac.h"
#include "IRutils.h"


const int irPin = 2;
const char* ssid = "VIVOFIBRA-79D0";
const char* password = "58331BB245";

const char* html = R""""(
HTTP/1.1 200 OK
Content-type:text/html

&lt;!DOCTYPE html&gt;
&lt;html&gt;
&lt;head&gt;
  &lt;title&gt;Aircon&lt;/title&gt;
  &lt;style&gt;
    body { text-align: center; font-family: Arial, sans-serif; }    
    button { background-color: slateblue; color: white; border: none; width: 50px; height: 30px; }
    button:hover { background-color: darkslateblue; }    
    button:active { background-color: mediumslateblue; }    
  &lt;/style&gt;  
&lt;/head&gt;
&lt;body&gt;
  &lt;h1&gt;Aircon&lt;/h1&gt;
  &lt;p&gt;Power:
    &lt;a href=&quot;/power/on&quot;&gt;&lt;button&gt;ON&lt;/button&gt;&lt;/a&gt;
    &lt;a href=&quot;/power/off&quot;&gt;&lt;button&gt;OFF&lt;/button&gt;&lt;/a&gt;
  &lt;/p&gt;
&lt;/body&gt;
&lt;/html&gt;
)"""";


WiFiServer server(80);
IRac ac(irPin);


void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void setup_ac() {
  pinMode(irPin, OUTPUT);

  ac.next.protocol = decode_type_t::MITSUBISHI;       // Set a protocol to use. Here a DAIKIN Aircon
  ac.next.model = 1;                              // Some A/Cs have different models. Try just the first.
  ac.next.mode = stdAc::opmode_t::kCool;          // Run in cool mode initially.
  ac.next.celsius = true;                         // Use Celsius for temp units. False = Fahrenheit
  ac.next.degrees = 25;                           // 25 degrees.
  ac.next.fanspeed = stdAc::fanspeed_t::kMedium;  // Start the fan at medium.
  ac.next.swingv = stdAc::swingv_t::kOff;         // Don't swing the fan up or down.
  ac.next.swingh = stdAc::swingh_t::kOff;         // Don't swing the fan left or right.
  ac.next.light = false;                          // Turn off any LED/Lights/Display that we can.
  ac.next.beep = false;                           // Turn off any beep from the A/C if we can.
  ac.next.econo = false;                          // Turn off any economy modes if we can.
  ac.next.filter = false;                         // Turn off any Ion/Mold/Health filters if we can.
  ac.next.turbo = false;                          // Don't use any turbo/powerful/etc modes.
  ac.next.quiet = false;                          // Don't use any quiet/silent/etc modes.
  ac.next.sleep = -1;                             // Don't set any sleep time or modes.
  ac.next.clean = false;                          // Turn off any Cleaning options if we can.
  ac.next.clock = -1;                             // Don't set any current time if we can avoid it.
  ac.next.power = false;                          // Initially start with the unit off.
}

void ac_power(bool isOn) {
  ac.next.power = isOn;
  ac.sendAc();
}

void execute(String& command) {
  if (command.endsWith("GET /power/on")) {
    ac_power(true);
  }
  if (command.endsWith("GET /power/off")) {
    ac_power(false);
  }
}

void run_server() {
  WiFiClient client = server.accept();
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println(html);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        execute(currentLine);
      }
    }
    client.stop();
  }
}

void setup() {
  Serial.begin(9600);
  setup_ac();
  setup_wifi();
}

void loop() {
  run_server();
}