
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include<string.h>
//#define UART_BAUD_RATE 9600
SoftwareSerial espSerial(3,1);  // RX, TX pins
// Update these with values suitable for your network.

const char* ssid = "Hackathon";
const char* password = "h@ckA1h0n";
const char* mqtt_server = "broker.hivemq.com";
const char* mqttTopic = "360_coders";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(1)
char msg[MSG_BUFFER_SIZE];
int value = 0;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '0') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("ON");
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
    Serial.print("OFF");
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("device/temp", "MQTT Connect");
      // ... and resubscribe
      client.subscribe("360_coders");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  //Serial.begin(115200);
  
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
    Serial.println("WELCOME");
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  /*unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    //Serial.println(analogRead(A0));
    value=analogRead(A0)*0.32;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world ", value);
    //Serial.print("Publish message: ");
    //Serial.println(msg);
    client.publish("device/temp", msg);
    */
   // Serial.println("Device booted to loop");
#if 1
if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
     if (client.publish(mqttTopic, inputString.c_str())) {
      Serial.println("Data published successfully");
    } else {
      Serial.println("Failed to publish data");
  }
    stringComplete = false;
  }
#else
  if (espSerial.available()) {
    String data = espSerial.readString();
      Serial.println("Recieved data");
      Serial.println(data);

   // data.trim();

    // Publish data to MQTT topic
    if (client.publish(mqttTopic, data.c_str())) {
      Serial.println("Data published successfully");
    } else {
      Serial.println("Failed to publish data");
  }
}
#endif
}
