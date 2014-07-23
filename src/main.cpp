#include "logmich.hpp"

int main()
{
  logmich::set_log_level(logmich::kInfo);
  log_info("hello world");
  //g_logger.append_format_unchecked(Logger::kInfo, "hello world %s %05d", "STRING", 5);
  log_info("hello world %s %05d", "STRING", 5);
  log_info("hello world");
  return 0;
}

/* EOF */
