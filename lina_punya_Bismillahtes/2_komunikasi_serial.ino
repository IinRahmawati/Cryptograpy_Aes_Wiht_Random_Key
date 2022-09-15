void komunikasiSerial(void) {
  if (Serial2.available())
  {
    int i = 0;
    while (Serial2.available() && i < 63)
    {
      serialbuffer[i] = (char)Serial2.read();
      i++;
    }
    serialbuffer[i] = '\0';
    if (serialbuffer[0])
    {
      Serial.print("data diterima dari Lora ");
      Serial.println(serialbuffer);
      //buka kunci sebelum data diproses
      prosesData();
    }
  }
}
