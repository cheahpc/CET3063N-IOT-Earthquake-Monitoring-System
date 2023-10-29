void SendWebsite() {
  Serial.println("sending web page");
  server.send(200, "text/html", main_page);
}

void handleBtnMute() {
  Serial.println("Alarm Muted");
  server.send(200, "text/plain", "");  //Send web page
}

void SendSensorXML() {
  String xml = "<?xml version = '1.0'?>\n<Data>\n";
  xml += "<Sensor>\n";
  xml += "<Accelerator>\n";
  xml += "<X>" + fb_Get(SENSOR_NODE_ACCEL_X_PATH) + "</X>\n";
  xml += "<Y>" + fb_Get(SENSOR_NODE_ACCEL_Y_PATH) + "</Y>\n";
  xml += "<Z>" + fb_Get(SENSOR_NODE_ACCEL_Z_PATH) + "</Z>\n";
  xml += "</Accelerator>\n";
  xml += "<Gyroscope>\n";
  xml += "<X>" + fb_Get(SENSOR_NODE_GYRO_X_PATH) + "</X>\n";
  xml += "<Y>" + fb_Get(SENSOR_NODE_GYRO_Y_PATH) + "</Y>\n";
  xml += "<Z>" + fb_Get(SENSOR_NODE_GYRO_Z_PATH) + "</Z>\n";
  xml += "</Gyroscope>\n";
  xml += "<Magnetometer>\n";
  xml += "<X>" + fb_Get(SENSOR_NODE_MAG_X_PATH) + "</X>\n";
  xml += "<Y>" + fb_Get(SENSOR_NODE_MAG_Y_PATH) + "</Y>\n";
  xml += "<Z>" + fb_Get(SENSOR_NODE_MAG_Z_PATH) + "</Z>\n";
  xml += "</Magnetometer>\n";
  xml += "<Temperature>\n";
  xml += "<Celsius>" + fb_Get(SENSOR_NODE_TEMP_PATH) + "</Celsius>\n";
  xml += "</Temperature>\n";
  xml += "</Sensor>\n";

  xml += "<Earthquake>\n";
  xml += "<Magnitude>" + fb_Get(EARTHQUAKE_MAGNITUDE_PATH) + "</Magnitude>\n";
  xml += "<Level>" + fb_Get(EARTHQUAKE_LEVEL_PATH) + "</Level>\n";
  xml += "</Earthquake>\n";

  xml += "</Data>\n";

  // Serial.println(xml);
  // Send XML
  server.send(200, "text/xml", xml);
}

void SendConnectionXML() {
  String xml = "<?xml version = '1.0'?>\n<Data>\n";
  xml += "<Sensor>\n";
  xml += "<Wifi>\n";
  xml += "<Hostname>" + fb_Get(SENSOR_NODE_WIFI_HOSTNAME_PATH) + "</Hostname>\n";
  xml += "<Local_IP>" + fb_Get(SENSOR_NODE_WIFI_LOCAL_IP_PATH) + "</Local_IP>\n";
  xml += "<Signal_Strength>" + fb_Get(SENSOR_NODE_WIFI_SIGNAL_STRENGTH_PATH) + "</Signal_Strength>\n";
  xml += "</Wifi>\n";
  xml += "</Sensor>\n";

  xml += "<Alarm>\n";
  xml += "<Wifi>\n";
  xml += "<Hostname>" + fb_Get(ALARM_NODE_WIFI_HOSTNAME_PATH) + "</Hostname>\n";
  xml += "<Local_IP>" + fb_Get(ALARM_NODE_WIFI_LOCAL_IP_PATH) + "</Local_IP>\n";
  xml += "<Signal_Strength>" + fb_Get(ALARM_NODE_WIFI_SIGNAL_STRENGTH_PATH) + "</Signal_Strength>\n";
  xml += "</Wifi>\n";
  xml += "</Alarm>\n";
  xml += "</Data>\n";

  // Serial.println(xml);
  // Send XML
  server.send(200, "text/xml", xml);
}