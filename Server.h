void initServer(){
  // ------------------------------------------------ Server Init
  server.on("/", SendWebsite);
  // server.on("/signal_0", handleSignal_0);
  // server.on("/signal_1", handleSignal_1);
  // server.on("/signal_2", handleSignal_2);
  // server.on("/signal_3", handleSignal_3);
  // server.on("/signal_4", handleSignal_4);
  // server.on("/signal_5", handleSignal_5);
  // server.on("/signal_6", handleSignal_6);
  // server.on("/signal_7", handleSignal_7);

  // Start Server
  server.begin();
  // Add your web page to the server
  Serial.println("Web server started");
}

void SendWebsite() {
  Serial.println("sending web page");
  server.send(200, "text/html", main_page);
}

void handleBtnMute() {
  Serial.println("Alarm Muted");
  server.send(200, "text/plain", "");  //Send web page
}