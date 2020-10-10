# LogMich - A Trivial Logging Library
# Copyright (C) 2020 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.6)
project(logmich-0.1)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/external/cmake-modules/)

include(ClangTidy)
include(MaximumWarnings)

find_package(fmt REQUIRED)

add_library(logmich STATIC src/logger.cpp src/log.cpp)
target_compile_options(logmich PUBLIC ${WARNINGS_CXX_FLAGS})
target_include_directories(logmich PUBLIC include/)
target_link_libraries(logmich fmt)

if(BUILD_TESTS)
  add_executable(test_logmich tests/main.cpp)
  target_link_libraries(test_logmich logmich)

  enable_testing()
  add_test(NAME windstille.appdata.xml
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND test_logmich)
endif()

# EOF #
