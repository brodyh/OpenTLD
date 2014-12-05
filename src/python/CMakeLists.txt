
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

# Create the conversion numpy <=> cv::Mat library
add_library(np_opencv_converter SHARED np_opencv_converter.cpp utils/conversion.cpp)
target_link_libraries(np_opencv_converter ${Boost_LIBRARIES} ${PYTHON_LIBRARY} ${OpenCV_LIBS})
set_target_properties(np_opencv_converter PROPERTIES PREFIX "")
set_target_properties(np_opencv_converter PROPERTIES SUFFIX .so)

# Create the TLD Wrapper
add_library(pytld SHARED pytld.cpp)
target_link_libraries(pytld ${Boost_LIBRARIES} ${OpenCV_LIBS} ${PYTHON_LIBRARY} libopentld cvblobs config++ np_opencv_converter)
set_target_properties(pytld PROPERTIES PREFIX "")
set_target_properties(pytld PROPERTIES SUFFIX .so)

# for debuggin
add_executable(dbg dbg.cpp)
target_link_libraries(dbg ${OpenCV_LIBS} ${Boost_LIBRARIES} ${PYTHON_LIBRARY})
