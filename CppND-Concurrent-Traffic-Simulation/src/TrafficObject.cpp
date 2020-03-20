// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>

#include <algorithm>
#include <iostream>
#include <chrono>
#include "../include/TrafficObject.h"

// init static variable
int TrafficObject::_idCnt = 0;

std::mutex TrafficObject::_mtx;
// ________________________________________________________________________________________________
void TrafficObject::setPosition(double x, double y) {
  _posX = x;
  _posY = y;
}

// ________________________________________________________________________________________________
void TrafficObject::getPosition(double &x, double &y) {
  x = _posX;
  y = _posY;
}

TrafficObject::TrafficObject() {
  _type = ObjectType::noObject;
  _id = _idCnt++;
}

// ________________________________________________________________________________________________
TrafficObject::~TrafficObject() {
  // set up thread barrier before this object is destroyed
  std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
      t.join();
      });
}
