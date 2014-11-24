
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/python/cmake-modules")

find_package(Boost COMPONENTS python REQUIRED)
find_package(PythonLibsNew REQUIRED)

include_directories(
  ../libopentld/imacq
  ../libopentld/mftracker
  ../libopentld/tld
  ../3rdparty/cvblobs
  ${OpenCV_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${PYTHON_INCLUDE_DIRS})

if(NOT USE_SYSTEM_LIBS)
    include_directories(../3rdparty/libconfig)
endif(NOT USE_SYSTEM_LIBS)

link_directories(${OpenCV_LIB_DIR} ${Boost_LIBRARY_DIRS})

add_library(pytld SHARED pytld.cpp)

target_link_libraries(pytld ${Boost_LIBRARIES} ${OpenCV_LIBS} ${PYTHON_LIBRARY} libopentld cvblobs config++)

set_target_properties(pytld PROPERTIES PREFIX "")
set_target_properties(pytld PROPERTIES SUFFIX .so)
