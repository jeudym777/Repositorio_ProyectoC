cmake_minimum_required(VERSION 3.16)
project(ProyectoLenguajes C)

set(CMAKE_C_STANDARD 99)

#Set your directories.  The dot representes the root application folder.
#Thus my the path to my domain folder:
set(APP_DOMAIN ./domain)
set(APP_CALC ./calc)

#Include the directories and now your cpp files will recognize your headers
include_directories(${APP_DOMAIN})
include_directories(${APP_CALC})

set(
   SOURCE_FILES
        ProyectoLenguajes.cpp
       ${APP_DOMAIN}/person.h
       ${APP_DOMAIN}/person.cpp
       ${APP_CALC}/add.h
       ${APP_CALC}/add.cpp
)
add_executable(ProyectoLenguajes main.c)

#CHEARS!




