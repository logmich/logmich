/*
**  LogMich - A Trivial Logging Library
**  Copyright (C) 2014 Ingo Ruhnke <grumbel@gmail.com>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_LOGMICH_LOG_HPP
#define HEADER_LOGMICH_LOG_HPP

#include <string>
#include <sstream>
#include <boost/format.hpp>

namespace logmich {
namespace detail {

inline void unpack_fmt(boost::format& fmt)
{
}

template<typename Head, typename ...Rest>
inline void unpack_fmt(boost::format& fmt, const Head& head, Rest&&... rest)
{
  unpack_fmt(fmt % head, std::forward<Rest>(rest)...);
}

/** Takes __PRETTY_FUNCTION__ and tries to shorten it to the form:
    Classname::function() */
std::string log_pretty_print(const std::string& str);

} // namespace detail

enum LogLevel
{
  /** things that shouldn't happen (i.e. a catched exceptions) */
  kError,

  /** messages that indicate an recoverable error (i.e. a catched
      exceptions) */
  kWarning,

  /** informal status messages that don't indicate a fault in the
      program */
  kInfo,

  /** extra verbose debugging messages */
  kDebug,

  /** temporary extra verbose debugging messages */
  kTemp
};

class Logger
{
private:
  LogLevel m_log_level;

public:
  Logger();
  void incr_log_level(LogLevel level);
  void set_log_level(LogLevel level);
  LogLevel get_log_level() const;

  void append(std::ostream& out, LogLevel level, const std::string& file, int line, const std::string& str);
  void append(LogLevel level, const std::string& file, int line, const std::string& str);

  void append_format(LogLevel level, const std::string& file, int line, const std::string& msg)
  {
    append(level, file, line, msg);
  }

  template<typename ...Args>
  void append_format(LogLevel level, const std::string& file, int line, const std::string& fmt, Args&&... args)
  {
    boost::format format(fmt);
    detail::unpack_fmt(format, args...);
    append(level, file, line, format.str());
  }
};

extern Logger g_logger;

inline void incr_log_level(LogLevel level)
{
  g_logger.incr_log_level(level);
}

inline void set_log_level(LogLevel level)
{
  g_logger.set_log_level(level);
}

inline LogLevel get_log_level()
{
  return g_logger.get_log_level();
}

} // namespace logmich

#define log_info(...) do {                                              \
    if (logmich::g_logger.get_log_level() >= logmich::kInfo)                      \
    {                                                                   \
      logmich::g_logger.append_format(logmich::kInfo, __FILE__, __LINE__, __VA_ARGS__); \
    }                                                                   \
  } while(false)

#define log_debug(...) do {                                             \
    if (logmich::g_logger.get_log_level() >= logmich::kDebug)                     \
    {                                                                   \
      logmich::g_logger.append_format(logmich::kDebug, __FILE__, __LINE__, __VA_ARGS__); \
    }                                                                   \
  } while(false)

#define log_warn(...) do {                                              \
    if (logmich::g_logger.get_log_level() >= logmich::kWarn)                      \
    {                                                                   \
      logmich::g_logger.append_format(logmich::kWarn, __FILE__, __LINE__, __VA_ARGS__); \
    }                                                                   \
  } while(false)

#define log_error(...) do {                                             \
    if (logmich::g_logger.get_log_level() >= logmich::kError)                     \
    {                                                                   \
      logmich::g_logger.append_format(logmich::kError, __FILE__, __LINE__, __VA_ARGS__); \
    }                                                                   \
  } while(false)

/** Write an debug message, while ignoring the log level. Use for
    temporary messages in development that should not be part of final
    release. */
#define log_tmp(...) do {                                               \
    if (logmich::g_logger.get_log_level() >= logmich::kTemp)                      \
    {                                                                   \
      logmich::g_logger.append_format(logmich::kTemp, __FILE__, __LINE__, __VA_ARGS__); \
    }                                                                   \
  } while(false)

#endif

/* EOF */
