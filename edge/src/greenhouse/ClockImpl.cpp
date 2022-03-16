#include <DS1307RTC.h>
#include "ClockImpl.h"

bool ClockImpl::isWired() {
  return RTC.chipPresent();
}

time_t ClockImpl::getTime() {
  return RTC.get();
}

void ClockImpl::setTime(time_t time) {
  RTC.set(time);
}

void ClockImpl::setTime(int hour, int minute) {
  tmElements_t tm;
  time_t now = RTC.get();
  breakTime(now, tm);
  tm.Hour = hour;
  tm.Minute = minute;
  RTC.write(tm);
}
