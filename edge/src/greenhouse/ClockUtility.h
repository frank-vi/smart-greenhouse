#ifndef __CLOCK_UTILITY__
#define __CLOCK_UTILITY__

#include <TimeLib.h>
#include "Arduino.h"

#define HOUR_IN_SECONDS 3600L
#define MINUTE_IN_SECONDS 60

class ClockUtility {
public:
  static long hoursAndMinutesAsSeconds() {
    return (hour() * HOUR_IN_SECONDS) + (minute() * MINUTE_IN_SECONDS);
  }

  static long convertToSeconds(int hourToConvert, int minuteToConvert) {
    long hourConverted = HOUR_IN_SECONDS * hourToConvert;
    int minuteConverted = MINUTE_IN_SECONDS * minuteToConvert;
    return hourConverted + minuteConverted;
  }

  static int getHour(long timeToAnalize) {
    float hourDecimal = (float) timeToAnalize / 3600;
    return (int) hourDecimal;
  }

  static int getMinute(long timeToAnalize) {
    float hourDecimal = (float) timeToAnalize / 3600;
    int hour = (int) hourDecimal;
    int minute = (hourDecimal - hour) * 60;
    return minute;
  }

  static long getTime(const String& timeString) {
    int separatorIndex = timeString.indexOf(':');
    if(separatorIndex != -1) {
      int hourToConvert = (int)timeString.substring(0, separatorIndex).toInt();
      int minuteToConvert = (int)timeString.substring(separatorIndex+1).toInt();
      return ClockUtility::convertToSeconds(hourToConvert, minuteToConvert);
    }
    return ClockUtility::convertToSeconds((int)timeString.toInt(), 0);
  }
};

#endif
