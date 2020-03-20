// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>


#ifndef CPPND_CONCURRENT_TRAFFIC_SIMULATION_INCLUDE_VEHICLE_H_
#define CPPND_CONCURRENT_TRAFFIC_SIMULATION_INCLUDE_VEHICLE_H_

#include "../include/TrafficObject.h"

// forward declarations to avoid include cycle
class Street;
class Intersection;

class Vehicle : public TrafficObject, public std::enable_shared_from_this<Vehicle> {
 public:
  // constructor / desctructor
  Vehicle();

  // getters / setters
  void setCurrentStreet(std::shared_ptr<Street> street) { _currStreet = street; }
  void setCurrentDestination(std::shared_ptr<Intersection> destination);

  // typical behaviour methods
  void simulate();

  // miscellaneous
  std::shared_ptr<Vehicle> get_shared_this() { return shared_from_this(); }

 private:
  // typical behaviour methods
  void drive();

  std::shared_ptr<Street> _currStreet;             // street on which the vehicle is currently on
  std::shared_ptr<Intersection> _currDestination;  // destination to which the vehicle is currently driving
  double _posStreet;                               // position on current street
  double _speed;                                   // ego speed in m/s
};

#endif  // CPPND_CONCURRENT_TRAFFIC_SIMULATION_INCLUDE_VEHICLE_H_
