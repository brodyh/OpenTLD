#include <boost/python.hpp>
#include "TLD.h"

using tld::TLD;
using namespace boost::python;

BOOST_PYTHON_MODULE(pytld)
{
  class_<TLD>("TLD")
    .def_readwrite("trackerEnabled", &TLD::trackerEnabled)
    .def_readwrite("detectorEnabled", &TLD::detectorEnabled)
    .def_readwrite("learningEnabled", &TLD::learningEnabled)
    .def_readwrite("alternating", &TLD::alternating)
    .def_readwrite("valid", &TLD::valid)
    .def_readwrite("wasValid", &TLD::wasValid)
    .def_readwrite("currConf", &TLD::currConf)
    .def_readwrite("learning", &TLD::learning)
    .def("release", &TLD::release)
    .def("selectObject", &TLD::selectObject)
    .def("processImage", &TLD::processImage)
    .def("writeToFile", &TLD::writeToFile)
    .def("readFromFile", &TLD::readFromFile)
    ;
}
