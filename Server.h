void SendWebsite() {
  Serial.println("sending web page");
  server.send(200, "text/html", main_page);
}

void handleBtnMute() {
  Serial.println("Alarm Muted");
  server.send(200, "text/plain", "");  //Send web page
}