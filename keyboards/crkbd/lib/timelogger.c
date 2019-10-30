#include <stdio.h>
#include "crkbd.h"

char timelog_str[24] = {};
unsigned int last_time = 0;
unsigned int elapsed_time = 0;

void set_timelog(void) {
  elapsed_time = timer_elapsed(last_time);
  last_time = timer_read();
  snprintf(timelog_str, sizeof(timelog_str), "lt:%5u, et:%5u", last_time, elapsed_time);
}

const char *read_timelog(void) {
  return timelog_str;
}

// my funcs
char totaltime_str[24] = {};
unsigned int reset_count_lt = 0;
unsigned int reset_count = 0;
unsigned long total_time = 0;

void check_timer_reset(void) {
  unsigned int tmp_int = timer_read();
  if (tmp_int < reset_count_lt) {
    reset_count++;
  }
  reset_count_lt = tmp_int;
}

void set_totaltime(void) {
  total_time = (unsigned long)0xffff * reset_count + last_time;
  unsigned int hour = total_time / 3600000;
  unsigned int min = (total_time / 60000) % 60;
  unsigned int sec = (total_time / 1000) % 60;
  snprintf(totaltime_str, sizeof(totaltime_str), "%4uh %2um %2us,%6lu", hour, min, sec, total_time / 1000);
}
const char *read_totaltime(void) {
  check_timer_reset();
  return totaltime_str;
}
