void water_flow(void) {
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    pulse1Sec = pulseCount;
    pulseCount = 0;

    flowRate = ((100.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();

    flowMilliLitres = (flowRate / 60) * 100;
    flowLitres = flowMilliLitres / 100;

    totalMilliLitres += flowMilliLitres;
//    totalLitres =  totalMilliLitres / 1000;
    totalLitres = 10;
    Serial.print("Flow rate: ");
    Serial.print(float(flowRate));
    Serial.print("L/min");
    Serial.print("\t");

    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalLitres);
    Serial.println("L");
  }
  if (totalLitres > 0) {
    EEPROM.put(addressTotal, int(totalLitres));
    EEPROM.commit();
  }
}
