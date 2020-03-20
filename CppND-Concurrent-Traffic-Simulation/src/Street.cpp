// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>

#include <iostream>
#include "../include/Vehicle.h"
#include "../include/Intersection.h"
#include "../include/Street.h"


// __________________________________________________________________________________________________________________________________________________
Street::Street() {
  _type = ObjectType::objectStreet;
  _length = 1000.0;  // in m
}

// __________________________________________________________________________________________________________________________________________________
void Street::setInIntersection(std::shared_ptr<Intersection> in) {
  _interIn = in;
  in->addStreet(get_shared_this());  // add this street to list of streets connected to the intersection
}
// __________________________________________________________________________________________________________________________________________________
void Street::setOutIntersection(std::shared_ptr<Intersection> out) {
  _interOut = out;
  out->addStreet(get_shared_this());  // add this street to list of streets connected to the intersection
}
