cmake_minimum_required(VERSION 2.6)

project(FlowSoploCulc)
# set(CMAKE_INSTALL_PREFIX /home/namatv)
execute_process(COMMAND uname -m OUTPUT_VARIABLE arch)

find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtDesigner REQUIRED )

# add_subdirectory(ns_MNAS_lib)
# add_subdirectory(EnterBoxPlugin)

include(${QT_USE_FILE})

include_directories(
  ${QT_INCLUDES} 
  ${CMAKE_CURRENT_BINARY_DIR} 
# 
  /usr/local/include/EnterBoxPlugin
  /usr/local/include/MNAS_lib
#
  ../EnterBoxPlugin/src
#
  ../ns_MNAS_lib/ns_MNAS_CodePage
  ../ns_MNAS_lib/ns_MNAS_Error
  ../ns_MNAS_lib/ns_MNAS_Gases
  ../ns_MNAS_lib/ns_MNAS_HalfDiv
  ../ns_MNAS_lib/ns_MNAS_Matrix
  ../ns_MNAS_lib/ns_MNAS_MendeleevTbl
  ../ns_MNAS_lib/ns_MNAS_ValDimension
)

set(FlowSoploCulc_SRCS
  src/Flow.cpp  
  src/main.cpp
)

set(FlowSoploCulc_UIS 
  ./src/Flow.ui 
  ../EnterBoxPlugin/forms/EnterBox.ui
)

QT4_WRAP_UI(FlowSoploCulc_UIS_H ${FlowSoploCulc_UIS})

qt4_automoc(${FlowSoploCulc_SRCS})

add_executable (FlowSoploCulc ${FlowSoploCulc_SRCS} ${FlowSoploCulc_UIS_H} )

find_library(ns_MNAS_lib ns_MNAS_lib /usr/local/lib64 ../ns_MNAS_lib/build )
find_library(EnterBoxPlugin EnterBoxPlugin /usr/local/lib64 ../EnterBoxPlugin/build )

target_link_libraries(FlowSoploCulc
  ${QT_QTCORE_LIBRARY} 
  ${QT_QTGUI_LIBRARY} 
  ${QT_QTDESIGNER_LIBRARY} 
  ${ns_MNAS_lib}
  ${EnterBoxPlugin}
)

if (${arch} MATCHES "x86_64")
  message ("FlowSoploCulc ${arch}")
  install(
    TARGETS FlowSoploCulc
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib64
    ARCHIVE DESTINATION lib64/static
  )
else(True)
  message ("FlowSoploCulc ${arch}")
  install(
    TARGETS FlowSoploCulc
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
  )
endif (${arch} MATCHES "x86_64")

