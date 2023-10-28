#include "InitNode.h"

#pragma region test
#ifdef ALARM
void SendWebsite() {
  Serial.println("sending web page");
  server.send(200, "text/html", main_page);
}

void ProcessButton_0() {
  Serial.println("Alarm Muted");

  // option 1 -- keep page live but dont send any thing
  // here i don't need to send and immediate status, any status
  // like the illumination status will be send in the main XML page update
  // code
  server.send(200, "text/plain", ""); //Send web page

  // option 2 -- keep page live AND send a status
  // if you want to send feed back immediataly
  // note you must have reading code in the java script
  /*
    if (LED0) {
    server.send(200, "text/plain", "1"); //Send web page
    }
    else {
    server.send(200, "text/plain", "0"); //Send web page
    }
  */
}

void SendXML() {
  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  strcat(XML, "<Sensor>\n");

  strcat(XML, "<Wifi>\n");
  sprintf(buf, "<Hostname>%s</Hostname>\n", fb_GetString(SENSOR_NODE_WIFI_HOSTNAME_PATH));
  strcat(XML, buf);
  sprintf(buf, "<Local_IP>%s</Local_IP>\n", fb_GetString(SENSOR_NODE_WIFI_LOCAL_IP_PATH));
  strcat(XML, buf);
  sprintf(buf, "<Signal_Strength>%s</Signal_Strength>\n", fb_GetString(SENSOR_NODE_WIFI_SIGNAL_STRENGTH_PATH));
  strcat(XML, buf);
  strcat(XML, "</Wifi>\n");

  strcat(XML, "</Sensor>\n");

  strcat(XML, "</Data>\n");

  Serial.println(XML);
  // Send XML
  server.send(200, "text/xml", XML);
}
#endif
#pragma endregion test

void setup() {

  initNode();
  
#ifdef ALARM
  server.on("/", SendWebsite);
  // server.on("/xml", SendXML);
  server.on("/TEMPread", handleTEMP);
  server.on("/BUTTON_0", ProcessButton_0);

  // Start Server
  server.begin();
  // Add your web page to the server
  Serial.println("Web server started");
#endif

}

void loop() {

  server.handleClient();
}


