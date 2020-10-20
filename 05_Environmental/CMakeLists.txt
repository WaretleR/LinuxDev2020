cmake_minimum_required(VERSION 3.10)
set(BIN_NAME pcreshow)
project(${BIN_NAME} VERSION 1.0)
set(KEYPAD 1)

add_custom_target(allclean 
    COMMAND rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake config.h Makefile ${BIN_NAME}
)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)
find_path(PCRE_INCLUDE_DIR pcre2.h REQUIRED)
find_library(PCRE_LIBRARY pcre2-8 REQUIRED)
if (NOT PCRE_INCLUDE_DIR OR NOT CURSES_INCLUDE_DIR)
    message(FATAL_ERROR " No include file found ")  
endif()
if (NOT PCRE_LIBRARY OR NOT CURSES_LIBRARY)
    message(FATAL_ERROR " No library found ")
endif()
include_directories(${CURSES_INCLUDE_DIR} ${PCRE_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_executable(${BIN_NAME} pcreshow.c)
target_link_libraries(${BIN_NAME} ${CURSES_LIBRARY} ${PCRE_LIBRARY})

configure_file(CMakeconfig.h.in config.h)