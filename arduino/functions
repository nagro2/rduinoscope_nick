#include <avr/dtostrf.h> //for dtostrf

bool isSummerTime() 
{
  bool summer_time = false;

    #define serial_debug_dst
    #ifdef serial_debug_dst
    Serial.print(day());
    Serial.print("/");
    Serial.print(month());
    Serial.print("/");
    Serial.print(year());
    Serial.print("  weekday: ");
    Serial.println(weekday());
    Serial.print(hour());
    Serial.print(":");
    Serial.println(minute());
  #endif
  
  if (DST_mode == 1) { // Europe DST mode
    //from Giacomo version
    //in Italy: Summer time ends the last sunday of october and begins the last of march


  // If I'm in October
    if (month() == 10)
    {
        // If it's Sunday
        if (weekday() == 1)
        {
            if (day() + 7 > 31 && hour() >= 3) summer_time = false;
            else summer_time = true;
        }
        else
        {
            // If last sunday has passed
            if ((day() + 7 - (weekday() - 1)) > 31) summer_time = false;
            else  summer_time = true;
        }
    }
    // If I'm in March
    else if (month() == 3)
    {
        // Se è domenica
        if (weekday() == 1)
        {
            // Se è l'ultima domenica
            if ((day() + 7) > 31 && hour() >= 2) summer_time = true;
            else summer_time = false;
        }
        else
        {
            // Se non è domenica, ma l'ultima è già passata
            if ((day() + 7 - (weekday() - 1)) > 31) summer_time = true;
            else  summer_time = false;
        }
    }
    // Se sono nel periodo dell'ora legale
    else if (month() >= 4 && month() <= 9) summer_time = true;
    // Se sono nel periodo dell'ora solare
    else if ((month() >= 1 && month() <= 2) || (month() >= 11 && month() <= 12)) summer_time = false;
  }
  
  else if (DST_mode == 2 ){  // USA DST mode
    //In USA DST begins on the 2nd Sunday in March and ends on the first Sunday in November
    //2nd Sunday of March range is 8-14 
    //1st Sunday of November range is 1-7

        // mostRecentSunday means the Sunday that began the current week, not last week's Sunday
        int mostRecentSunday = day() - (weekday() -1); // weekday for Sunday is reported as 1, but need week start at 0
        Serial.print("most recent Sunday= ");
        Serial.println(mostRecentSunday);
        //January, february, and december are out.
        //if (month < 3 || month > 11) { return false; } // don't need this explicitly
        //April to October are in
        if (month() > 3 && month() < 11) { summer_time = true; }
        //In march, we are DST if our previous sunday was on or after the 8th.
        else if (month() == 3 && mostRecentSunday >= 8) { summer_time = true; }
        //In november we must be before the first sunday to be dst.
        //That means the previous sunday must be before the 1st.
        else if (month() == 11 && mostRecentSunday <= 0) { summer_time = true; }

    Serial.print("from isSummerTime, summer_time= ");
    Serial.println(summer_time);
    return summer_time; 
    }
}

void storeOptions_SD()
{
  SD.remove("options.txt");
  File dataFile = SD.open("options.txt", FILE_WRITE);

  if (dataFile)
  {
    char charBuf[10]; //for dtostrf
    //String debugstring;
    
    String options =                       "(" +
      (String)TFT_Brightness             + ";" +
              TFT_Time                   + ";" + 
      (String)Tracking_type              + ";" + 
      (String)IS_MERIDIAN_FLIP_AUTOMATIC + ";" + 
              Fan1_State                 + ";" +
              Fan2_State                 + ";" +
      (String)IS_SOUND_ON                + ";" +
      (String)IS_STEPPERS_ON             + ";" +
              loaded_gps_from_SD         + ";" +
              dtostrf(OBSERVATION_LATTITUDE, 6, 4, charBuf)      + ";" +
              dtostrf(OBSERVATION_LONGITUDE, 6, 4, charBuf)      + ";" +
              Summer_Time  +               ")" ;
    dataFile.print(options);
    dataFile.close();

    #ifdef serial_debug 
      Serial.print("saved options to SD: ");
      Serial.println(options);
    #endif
  }
}

void loadOptions_SD()
{
  File dataFile = SD.open("options.txt");

  if (dataFile)
  {
    char optionsBuffer[100] = {""};
    dataFile.read(optionsBuffer, 100);
    String receivedString = optionsBuffer;
    
    #ifdef serial_debug  
      Serial.print("options:");
      Serial.println(optionsBuffer);
    #endif

    int iniPac = receivedString.indexOf('(');
    int endPac = receivedString.indexOf(')');

    if (iniPac != -1 && endPac != -1 && endPac - iniPac > 1)
    {
      String packetIn = optionsBuffer;
      packetIn = packetIn.substring(1, endPac); //tolgo le parentesi
      String valoriIn[12] = {""}; //was 8

      #ifdef serial_debug
        Serial.print("packetIn:");
        Serial.println(packetIn);
      #endif

      for (int i=0; i<sizeof(valoriIn)/sizeof(valoriIn[0])-1; i++)  //genero le sottostringhe
      {
        int endVal  = packetIn.indexOf(";");
        valoriIn[i] = packetIn.substring(0, endVal);
        #ifdef serial_debug
          Serial.print("valoriIn[");
          Serial.print(i);
          Serial.print("] :");
          Serial.println(valoriIn[i]);
        #endif
        packetIn    = packetIn.substring(endVal+1, packetIn.length());
      }
      valoriIn[sizeof(valoriIn)/sizeof(valoriIn[0])-1] = packetIn;

      //aggiorno:
      TFT_Brightness             = valoriIn[0].toInt();          
      TFT_Time                   = valoriIn[1];
      Tracking_type              = valoriIn[2].toInt();
      IS_MERIDIAN_FLIP_AUTOMATIC = valoriIn[3].toInt(); 
      Fan1_State                 = valoriIn[4];
      Fan2_State                 = valoriIn[5];
      IS_SOUND_ON                = valoriIn[6].toInt();
      IS_STEPPERS_ON             = valoriIn[7].toInt();
      loaded_gps_from_SD         = valoriIn[8].toInt();

      if (loaded_gps_from_SD == 1){
        OBSERVATION_LATTITUDE    = valoriIn[9].toFloat();
        OBSERVATION_LONGITUDE    = valoriIn[10].toFloat();
        Summer_Time = valoriIn[11].toInt();
        #ifdef serial_debug
          Serial.println("loaded lat-lon from sd");
          Serial.print("loaded LAT= " );
          Serial.println(OBSERVATION_LATTITUDE, 4);
          Serial.print("loaded LON= " );
          Serial.println(OBSERVATION_LONGITUDE, 4);
        #endif
      }

      analogWrite(TFTBright, TFT_Brightness);

      if (Tracking_type == 0) Tracking_Mode = "Lunar";
      else if (Tracking_type == 2) Tracking_Mode = "Solar";
      else
      {
        Tracking_type = 1;
        Tracking_Mode = "Celest";
      }

      if      (TFT_Time.equals("30 s"  )) TFT_timeout = 30000;
      else if (TFT_Time.equals("60 s"  )) TFT_timeout = 60000;
      else if (TFT_Time.equals("2 min" )) TFT_timeout = 120000;
      else if (TFT_Time.equals("5 min" )) TFT_timeout = 300000;
      else if (TFT_Time.equals("10 min")) TFT_timeout = 600000;
      else
      {
        TFT_Time = "AL-ON";
        TFT_timeout = 0;
      }

      #ifdef serial_debug
        Serial.print("TFT_timeout = ");
        Serial.println(TFT_timeout);
      #endif

      if (IS_MERIDIAN_FLIP_AUTOMATIC) Mer_Flip_State = "AUTO";
      else
      {
        IS_MERIDIAN_FLIP_AUTOMATIC = false;
        Mer_Flip_State = "OFF";
      }

      if(Fan1_State.equals("OFF"))
        IS_FAN1_ON = false;
      else
      {
        Fan1_State = "ON";
        IS_FAN1_ON = true;
      }
      if(Fan2_State.equals("OFF"))
        IS_FAN2_ON = false;
      else
      {
        Fan2_State = "ON";
        IS_FAN2_ON = true;
      }

      if(IS_SOUND_ON)
      {
        Sound_State = "ON";
      }
      else  
      {
        IS_SOUND_ON = false;
        Sound_State = "OFF";
      }   
                              
      if(IS_STEPPERS_ON)
        Stepper_State = "ON";
      else  
      {
        IS_STEPPERS_ON = false;
        Stepper_State = "OFF";
      }
    }
    
    dataFile.close();
  }
}

