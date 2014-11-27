#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <iostream>
#include <boost/python.hpp>

#include "TLD.h"
#include "np_opencv_converter.hpp"

namespace py = boost::python;

static py::object rect2py(const cv::Rect *rect) {
  if (!rect)
    return py::object();

  py::tuple arr = py::make_tuple(rect->x, rect->y, rect->width, rect->height);
  return py::numeric::array(arr);
}

namespace tld {

  class PyTLD: public tld::TLD {
  public:
    void pySelectObject(const cv::Mat &img, py::numeric::array pybb)
    {
      int x = py::extract<int>(pybb[0]);
      int y = py::extract<int>(pybb[1]);
      int width = py::extract<int>(pybb[2]);
      int height = py::extract<int>(pybb[3]);
      cv::Rect bb = cv::Rect(x, y, width, height);
      cv::Mat grey;
      if (img.channels() == 3)
	cvtColor(img, grey, CV_BGR2GRAY);
      else
	grey = img;
      selectObject(grey, &bb);
    }

    py::object getCurrBB() { return rect2py(currBB); }
    py::object getPrevBB() { return rect2py(prevBB); }

    // Should be called before select object
    // imgSize = [width, height]
    void setImgSize(py::object imgSize) {
      detectorCascade->imgWidth = py::extract<int>(imgSize[0]);
      // this is the number of bytes in a row for grey scale
      detectorCascade->imgWidthStep = py::extract<int>(imgSize[0]);
      detectorCascade->imgHeight = py::extract<int>(imgSize[1]);
    }

    bool getUseShift() { return detectorCascade->useShift; }
    void setUseShift(bool useShift) { detectorCascade->useShift = useShift; }
    float getShift() { return detectorCascade->shift; }
    void setShift(float shift) { detectorCascade->shift = shift; }
    int getMinScale() { return detectorCascade->minScale; }
    void setMinScale(int minScale) { detectorCascade->minScale = minScale; }
    int getMaxScale() { return detectorCascade->maxScale; }
    void setMaxScale(int maxScale) { detectorCascade->maxScale = maxScale; }
    int getNumTrees() {return detectorCascade->numTrees; }
    void setNumTrees(int numTrees) { detectorCascade->numTrees = numTrees; }
    int getMinSize() { return detectorCascade->minSize; }
    void setMinSize(int minSize) { detectorCascade->minSize = minSize; }
    float getThetaTP() { return detectorCascade->nnClassifier->thetaTP; }
    void setThetaTP(float thetaTP) { detectorCascade->nnClassifier->thetaTP = thetaTP; }
    float getThetaFP() { return detectorCascade->nnClassifier->thetaFP; }
    void setThetaFP(float thetaFP) { detectorCascade->nnClassifier->thetaFP = thetaFP; }
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
    .def("setImgSize", &PyTLD::setImgSize)
    .add_property("currBB", &PyTLD::getCurrBB)
    .add_property("prevBB", &PyTLD::getPrevBB)
    .add_property("useShift", &PyTLD::getUseShift, &PyTLD::setUseShift)
    .add_property("shift", &PyTLD::getShift, &PyTLD::setShift)
    .add_property("minScale", &PyTLD::getMinScale, &PyTLD::setMinScale)
    .add_property("maxScale", &PyTLD::getMaxScale, &PyTLD::setMaxScale)
    .add_property("numTrees", &PyTLD::getNumTrees, &PyTLD::setNumTrees)
    .add_property("minSize", &PyTLD::getMinSize, &PyTLD::setMinSize)
    .add_property("thetaTP", &PyTLD::getThetaTP, &PyTLD::setThetaTP)
    .add_property("thetaFP", &PyTLD::getThetaFP, &PyTLD::setThetaFP)
    ;
}
