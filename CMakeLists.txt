cmake_minimum_required(VERSION 2.8.12)

project(FlowSoploCulc)

message ("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

#set(INSTALL_PREFIX_FOR_WINDOWS "E:/PRG/msys64/home/namatv/usr")


set(INSTALL_PREFIX_FOR_WINDOWS "${CMAKE_SOURCE_DIR}/../usr")
set(INSTALL_PREFIX_FOR_LINUX   "/home/namatv/usr")



set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Xml)
find_package(Qt5Widgets)
find_package(Qt5Designer)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
   set(CMAKE_INSTALL_PREFIX ${INSTALL_PREFIX_FOR_WINDOWS})

  message ("CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
  message ("CMAKE_INSTALL_PREFIX =  ${CMAKE_INSTALL_PREFIX}")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(CMAKE_INSTALL_PREFIX ${INSTALL_PREFIX_FOR_LINUX})
  
  message ("${BoldRed}CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}${ColourReset}")
  message ("${BoldGreen}CMAKE_INSTALL_PREFIX =  ${CMAKE_INSTALL_PREFIX}${ColourReset}")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

include_directories(
  ${Qt5Designer_INCLUDE_DIRS}
  src
#
  ${CMAKE_INSTALL_PREFIX}/include/EnterBoxPlugin
#
  ${CMAKE_INSTALL_PREFIX}/include/mnas
  ${CMAKE_INSTALL_PREFIX}/include/mnas/ns_MNAS_Error
  ${CMAKE_INSTALL_PREFIX}/include/mnas/ns_MNAS_CodePage  
  ${CMAKE_INSTALL_PREFIX}/include/mnas/ns_MNAS_Error
  ${CMAKE_INSTALL_PREFIX}/include/mnas/ns_MNAS_Gases 
  ${CMAKE_INSTALL_PREFIX}/include/mnas/ns_MNAS_HalfDiv
  ${CMAKE_INSTALL_PREFIX}/include/mnas/ns_MNAS_Matrix
  ${CMAKE_INSTALL_PREFIX}/include/mnas/ns_MNAS_MendeleevTbl
  ${CMAKE_INSTALL_PREFIX}/include/mnas/ns_MNAS_ValDimension
)


set(FlowSoploCulc_SRCS src/Flow.cpp  src/main.cpp)

add_executable (${CMAKE_PROJECT_NAME} ${FlowSoploCulc_SRCS} ${FlowSoploCulc_UIS_H} )


if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  find_library(mnas_lib mnas  ${CMAKE_INSTALL_PREFIX}/bin)
  find_library(EnterBoxPlugin_lib EnterBoxPlugin ${CMAKE_INSTALL_PREFIX}/bin)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  find_library(mnas_lib mnas  ${CMAKE_INSTALL_PREFIX}/lib)
  find_library(EnterBoxPlugin_lib EnterBoxPlugin ${CMAKE_INSTALL_PREFIX}/lib)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")


target_link_libraries(${CMAKE_PROJECT_NAME} 
  Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Designer
  ${mnas_lib}
  ${EnterBoxPlugin_lib}
)

install(
  TARGETS ${CMAKE_PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/static)
  
set(FlowSoploCulc_UIS src/Flow.ui)
