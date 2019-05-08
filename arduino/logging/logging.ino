#include <ArduinoLog.h>

/*!
* This example sketch shows most of the features of the ArduinoLog library
*
*/

void setup() {
    // Set up serial port and wait until connected
    Serial.begin(115200);

    // Pass log level, whether to show log level, and print interface.
    // Available levels are:
    // LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_NOTICE, LOG_LEVEL_TRACE, LOG_LEVEL_VERBOSE
    // Note: if you want to fully remove all logging code, uncomment #define DISABLE_LOGGING in Logging.h
    //       this will significantly reduce your project size

    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    Log.setPrefix(printTimestamp); // Uncomment to get timestamps as prefix
    //Log.setSuffix(printNewline); // Uncomment to get newline as suffix

    //Start logging

    Log.notice(F(CR "******************************************" CR));                     // Info string with Newline
    Log.notice(  "***          Logging example                " CR);                       // Info string in flash memory
    Log.notice(F("******************* ")); Log.notice("*********************** " CR);      // two info strings without newline
}

void loop() {

    Log.notice   (  "Log as Info with integer values : %d, %d" CR                  , 100,  1000);
    Log.notice   (F("Log as Info with hex values     : %x, %X" CR                 ), 100,  1000);
    Log.notice   (  "Log as Info with hex values     : %x, %X" CR                  , 1000, 1000);
    Log.notice   (F("Log as Info with binary values  : %b, %B" CR                 ), 100,   100);
    Log.notice   (  "Log as Info with binary values  : %b, %B" CR                  , 1000,  1000);
    Log.notice   (F("Log as Info with long values    : %l, %l" CR                 ), 1000000, 1000000);
    Log.notice   (  "Log as Info with bool values    : %t, %T" CR                  , true, false);
    Log.notice   (F("Log as Info with string value   : %s" CR                     ), "Senamhi");
    Log.notice   (F("Log as Info with float value   : %F" CR                      ), 15.17);
    Log.notice   (  "Log as Info with float value   : %F" CR                       , 15.18);
    Log.notice   (F("Log as Info with double value   : %D" CR                     ), 1234.56789);
    Log.notice   (  "Log as Info with double value   : %D" CR                      , 1234.56789);
    Log.notice   (F("Log as Debug with mixed values  : %d, %d, %l, %l, %t, %T" CR ), 100 , 1000,
                10000, 100000, true, false);
    Log.trace    (  "Log as Trace with bool value    : %T" CR                      , true);
    Log.warning  (  "Log as Warning with bool value  : %T" CR                      , false);
    Log.error    (  "Log as Error with bool value    : %T" CR                      , true);
    Log.fatal    (  "Log as Fatal with bool value    : %T" CR                      , false);
    Log.verbose  (F("Log as Verbose with bool value   : %T" CR CR CR               ), true);
    delay(5000);
}

void printTimestamp(Print* _logOutput) {
  char c[12];
  int m = sprintf(c, "%10lu ", millis());
  _logOutput->print(c);
}

void printNewline(Print* _logOutput) {
  _logOutput->print('\n');
}

