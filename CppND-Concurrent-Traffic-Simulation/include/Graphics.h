// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>

#ifndef CPPND_CONCURRENT_TRAFFIC_SIMULATION_INCLUDE_GRAPHICS_H_
#define CPPND_CONCURRENT_TRAFFIC_SIMULATION_INCLUDE_GRAPHICS_H_

#include <opencv2/core.hpp>
#include <string>
#include <vector>
#include "../include/TrafficObject.h"

class Graphics {
 public:
  // constructor / desctructor
  // getters / setters
  void setBgFilename(std::string filename) { _bgFilename = filename; }
  void setTrafficObjects(const std::vector<std::shared_ptr<TrafficObject>> &trafficObjects) { _trafficObjects = trafficObjects; }
  // typical behaviour methods
  void simulate();

 private:
  // typical behaviour methods
  void loadBackgroundImg();
  void drawTrafficObjects();

  // member variables
  std::vector<std::shared_ptr<TrafficObject>> _trafficObjects;
  std::string _bgFilename;
  std::string _windowName;
  std::vector<cv::Mat> _images;
};

#endif  // CPPND_CONCURRENT_TRAFFIC_SIMULATION_INCLUDE_GRAPHICS_H_
