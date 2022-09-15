
//data per Jam
void SendDataSensor1(void) {

  char DtJam;
  for (int i1 = 0; i1 <= 23; i1++) {
    DtJam + (char(DataJamEpprom[i1]) + ";" );
  };

  //chipertext
  encrypt(&DtJam, key, cipherTextOutput);
  for (int i = 0; i < 16; i++) {
      char str[3];
      sprintf(str, "%02x", (char)cipherTextOutput[i]);
      Serial.print(str);
    }
  
  Serial.println(DtJam);
  stat = 0;
}

//Data per Hari
void SendDataSensor2(void) {
  char DtHari;
  for (int i2 = 1; i2 <= 31; i2++) {
    DtHari + (char (DataHariEpprom[i2]) + ";" );
  } ;
  
  //chipertext
  encrypt(&DtHari, key, cipherTextOutput);
  for (int i = 0; i < 16; i++) {
      char str[3];
      sprintf(str, "%02x", (char)cipherTextOutput[i]);
      Serial.print(str);
    }
  Serial.println(DtHari);
  stat = 0;
}

//data per Bulan
void SendDataSensor3 (void) {
  char DtBulan;
  for (int i3 = 1; i3 <= 12; i3++) {
    DtBulan + (char(DataBulanEpprom[i3]) + ";" );
  };
  
  //chipertext
  encrypt(&DtBulan, key, cipherTextOutput);
  for (int i = 0; i < 16; i++) {
      char str[3];
      sprintf(str, "%02x", (char)cipherTextOutput[i]);
      Serial.print(str);
    }
  Serial.println(DtBulan);
  stat = 0;
}

//kirim feedback
void  SendMeteranON(void) {
  String ON = "1,2;";
  Serial.println(ON);
  Serial2.println(ON);
  stat = 0;
}


//kirim feedback
void  SendMeteranOFF ( void ) {
  String OFF = "1,3;";
  //  digitalWrite(14, )
  Serial.println(OFF);
  Serial2.println(OFF);
  stat = 0;
}
