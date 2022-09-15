void prosesData ( void ) {
  if (serialbuffer[0] == '1') {
    stat = 1;
    if (serialbuffer[2] == '1') {
      if (serialbuffer[4] == '1') {
        SendDataSensor1();
      }
      else if (serialbuffer[4] == '2') {
        SendDataSensor2();
      }
      else if (serialbuffer[4] == '3') {
        SendDataSensor3();
      }
    }
    else if (serialbuffer[2] == '2') {
      SendMeteranON();
    }
    else if (serialbuffer[2] == '3') {
      SendMeteranOFF();
    }
  }
}
