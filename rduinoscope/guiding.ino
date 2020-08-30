#ifdef AUTOGUIDING

// This code is derived from Arduino ST4.
//
// Arduino ST4 is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Arduino ST4 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Arduino ST4.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright Kevin Ferrare 2014

/*
 * Led indicates whether the software requested connection, it is shut off when the software disconnects
 */

/**
 * An axis has a pin per direction.
 * Both pins cannot be up at the same time.
 */
//#define autoguide_diagnostics
void consider_autoguide()
{
    //if (SerialUSB.available() > 0) {
    //Received something
    String opcode = SerialUSB.readStringUntil('#');
    boolean validOpcode=true;
    //Parse opcode
    if(opcode=="CONNECT"){
      digitalWrite(pinLED, HIGH);
      Serial.println("received CONNECT");
      //resetPins();
    }
    else if (opcode=="DISCONNECT"){
      digitalWrite(pinLED, LOW);
      Serial.println("received DISCONNECT");
      //resetPins();
    }
    else if(opcode=="RA0"){
      //rightAscension.reset();
      #ifdef autoguide_diagnostics
      Serial.println("received RA0");
      #endif
    }
    else if(opcode=="RA+"){
      //rightAscension.plus();
      #ifdef autoguide_diagnostics
      Serial.println("received RA+");
      #endif
      consider_Manual_Move(151,500);
    }
    else if(opcode=="RA-"){
      //rightAscension.minus();
      #ifdef autoguide_diagnostics
      Serial.println("received RA-");
      #endif
      consider_Manual_Move(771,500);
    }
    else if(opcode=="DEC0"){
      //declination.reset();
      #ifdef autoguide_diagnostics
      Serial.println("received DEC0");
      #endif
    }
    else if(opcode=="DEC+"){
      //declination.plus();
      #ifdef autoguide_diagnostics
      Serial.println("received DEC+");
      #endif
      consider_Manual_Move(500,151);
    }
    else if(opcode=="DEC-"){
      //declination.minus();
      #ifdef autoguide_diagnostics
      Serial.println("received DEC-");
      #endif
      consider_Manual_Move(500,771);
    }
    else{
      validOpcode=false;
    }
    if(validOpcode){
      //Acknowledge valid command
      SerialUSB.println("OK#");
      #ifdef autoguide_diagnostics
      Serial.println("sent OK");
      #endif
    }
  //} 
}


#endif
