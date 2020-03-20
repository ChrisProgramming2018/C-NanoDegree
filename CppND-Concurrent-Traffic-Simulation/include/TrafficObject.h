// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>


#ifndef CPPND_CONCURRENT_TRAFFIC_SIMULATION_INCLUDE_TRAFFICOBJECT_H_
#define CPPND_CONCURRENT_TRAFFIC_SIMULATION_INCLUDE_TRAFFICOBJECT_H_

#include <vector>
#include <thread>
#include <mutex>

enum ObjectType {
  noObject,
  objectVehicle,
  objectIntersection,
  objectStreet,
};

class TrafficObject {
 public:
  // constructor / desctructor
  TrafficObject();
  ~TrafficObject();

  // getter and setter
  int getID() { return _id; }
  void setPosition(double x, double y);
  void getPosition(const double &x, const double &y);
  ObjectType getType() { return _type; }

  // typical behaviour methods
  virtual void simulate() {}

 protected:
  ObjectType _type;                  // identifies the class type
  int _id;                           // every traffic object has its own unique id
  double _posX, _posY;               // vehicle position in pixels
  std::vector<std::thread> threads;  // holds all threads that have been launched within this object
  static std::mutex _mtx;            // mutex shared by all traffic objects for protecting cout

 private:
  static int _idCnt;  // global variable for counting object ids
};

#endif  // CPPND_CONCURRENT_TRAFFIC_SIMULATION_INCLUDE_TRAFFICOBJECT_H_
