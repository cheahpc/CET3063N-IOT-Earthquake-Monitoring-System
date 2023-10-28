#include "InitNode.h"


void setup() {
  // Initialize sensor, wifi, etc
  initNode();
}

WiFiClient client;
void loop() {
  // check if the server is established
  if (server.available()) {
    while (!client.available()) delay(1);

    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // landing page for the controller
    client.println("HTTP/1.1 200 ok");
    client.println("Content-Type: text/html");
    client.println("");

    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<meta charset='utf-8'/>");
    client.println("<title>ESP8266</title>");
    client.println("</head>");
    client.println("<body>");
    client.println("<p>Welcome to ESP8266</p><br/>");
    client.println("Accelerator X: ");
    client.println(getAccel(1), 6);
    client.println("<br/>");
    client.println("Accelerator Y: ");
    client.println(getAccel(2), 6);
    client.println("<br/>");
    client.println("Accelerator Z: ");
    client.println(getAccel(3), 6);
    client.println("<br/>");
    client.println("</body>");
    client.println("</html>");
  } else {
    Serial.println("Server not connected");
  }
  // wait until the client sends the data
}
