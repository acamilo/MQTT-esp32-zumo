#include <Preferences.h>
#include <WiFi.h>
#include <Esp32WifiManager.h>
#include "EspMQTTClient.h"


EspMQTTClient client(
  "robomqtt.cs.wpi.edu",  // MQTT Broker server ip
  "test",   // Can be omitted if not needed
  "",   // Can be omitted if not needed
  "ZumoBot"      // Client name that uniquely identify your device
);


//Create a wifi manager
WifiManager manager;
// modify the preferences
void setup() {
	//manager.erase();// This will erase the stored passwords
	manager.setup();
}

void loop() {
	// read the serial port for new passwords and maintain connections
	manager.loop();
	client.loop();
	if (manager.getState() == Connected) {
		// use the Wifi Stack now connected
	}
}


void onConnectionEstablished() {

  client.subscribe("mytopic/test", [] (const String &payload)  {
    Serial.println(payload);
  });

  client.publish("mytopic/test", "This is a message");
}
