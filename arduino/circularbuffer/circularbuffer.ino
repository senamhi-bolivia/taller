/**********************************************************************
Copyright (C) 2019  Paolo Paruno <p.patruno@iperbole.bologna.it>
authors:
Paolo Patruno <p.patruno@iperbole.bologna.it>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of 
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
#include <ArduinoLog.h>
#include "FloatBuffer.h"
#include <Time.h>
#include <TimeAlarms.h>

#define NSAMPLE 60

// global variables for sensors measure
FloatBuffer t;
float tmean=NAN;
float tsample=0.;

void measure()
{
  tsample++;

  t.autoput(tsample);
  LOGN(F("T sample %F" CR),tsample);
  
  if (t.getSize() == t.getCapacity()){
    tmean=0;
    for ( uint8_t i=0 ; i < t.getCapacity() ; i++)  {
      LOGN(F("T ele %d %F" CR),i,t.peek(i));
      tmean += (t.peek(i) - tmean) / (i+1);
    }
	      Serial.println(round(tmean*10.)/10.,1);	    	    
  } else{
    Serial.println("wait");	    	    
  }

}

void setup()
{

  // start up the serial interface
  Serial.begin(115200);
  // Pass log level, whether to show log level, and print interface.
  // Available levels are:
  // LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_NOTICE, LOG_LEVEL_VERBOSE
  // Note: if you want to fully remove all logging code, change #define LOG_LEVEL ....
  //       this will significantly reduce your project size

  // set runtime log level to the same of compile time
  Log.begin(LOG_LEVEL, &Serial);
  LOGN(F("Started" CR));

  t.init(NSAMPLE);

  // setup alarms
  Alarm.timerRepeat(1, measure);    // timer for every second    
  
  LOGN(F("setup done." CR));

}

void loop()
{
  Alarm.delay(0);
}
