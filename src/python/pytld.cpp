#include <boost/python.hpp>
#include "TLD.h"
#include "np_opencv_converter.hpp"

#include <iostream>

using tld::TLD;
namespace py = boost::python;

static py::object rect2py(const cv::Rect *rect) {
  if (!rect)
    return py::object();

  py::tuple arr = py::make_tuple(rect->x, rect->y, rect->width, rect->height);
  return py::numeric::array(arr);
}

namespace tld {

  class PyTLD: public TLD {
  public:
    void pySelectObject(const cv::Mat &img, py::numeric::array pybb)
    {
      int x = py::extract<int>(pybb[0]);
      int y = py::extract<int>(pybb[1]);
      int width = py::extract<int>(pybb[2]);
      int height = py::extract<int>(pybb[3]);
      cv::Rect bb = cv::Rect(x, y, width, height);
      selectObject(img, &bb);
    }

    py::object getCurrBB() { return rect2py(currBB); }
    py::object getPrevBB() { return rect2py(prevBB); }
  };

}

BOOST_PYTHON_MODULE(pytld)
{
  using tld::PyTLD;
  fs::python::init_and_export_converters();
  py::numeric::array::set_module_and_type("numpy", "ndarray");
  py::class_<PyTLD>("TLD")
    .def_readwrite("trackerEnabled", &PyTLD::trackerEnabled)
    .def_readwrite("detectorEnabled", &PyTLD::detectorEnabled)
    .def_readwrite("learningEnabled", &PyTLD::learningEnabled)
    .def_readwrite("alternating", &PyTLD::alternating)
    .def_readwrite("valid", &PyTLD::valid)
    .def_readwrite("wasValid", &PyTLD::wasValid)
    .def_readwrite("currConf", &PyTLD::currConf)
    .def_readwrite("learning", &PyTLD::learning)
    .def("release", &PyTLD::release)
    .def("selectObject", &PyTLD::pySelectObject)
    .def("processImage", &PyTLD::processImage)
    .def("writeToFile", &PyTLD::writeToFile)
    .def("readFromFile", &PyTLD::readFromFile)
    .add_property("currBB", &PyTLD::getCurrBB)
    .add_property("prevBB", &PyTLD::getPrevBB)
    ;
}
