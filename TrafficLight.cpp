// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>



#include <iostream>
#include <random>
#include <thread>
#include <thread>
#include <chrono>
#include <future>
#include "../include/TrafficLight.h"

/* Implementation of class "MessageQueue" */

// __________________________________________________________________________________________________________________________________________________
template <typename T>
T MessageQueue<T>::receive() {
  // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait()
  // to wait for and receive new messages and pull them from the queue using move semantics.
  // The received object should then be returned by the receive function.
  std::unique_lock<std::mutex> uLock(_mutex);
  _cond.wait(uLock, [this] { return !_messages.empty(); });  // pass unique lock to condition variable
  // remove last vector element from queue
  T msg = std::move(_messages.back());
  _messages.pop_back();
  return msg;
}

// __________________________________________________________________________________________________________________________________________________
template <typename T>
void MessageQueue<T>::send(T &&msg) {
  // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex>
  // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
  // simulate some work

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  // perform vector modification under the lock
  std::lock_guard<std::mutex> uLock(_mutex);
  // add vector to queue
  std::cout << "   Message " << msg << " has been sent to the queue" << std::endl;
  _messages.push_back(std::move(msg));
  _cond.notify_one();  // notify client after pushing new Vehicle into vector
}

/* Implementation of class "TrafficLight" */

// __________________________________________________________________________________________________________________________________________________
TrafficLight::TrafficLight() {
  _currentPhase = TrafficLightPhase::red;
}

// __________________________________________________________________________________________________________________________________________________
void TrafficLight::waitForGreen() {
  // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop
  // runs and repeatedly calls the receive function on the message queue.
  // Once it receives TrafficLightPhase::green, the method returns.
  std::cout << "wait for green " << getID()  << std::endl;
  auto currentPhase = _messages.receive();
  while (currentPhase == red) {
    currentPhase = _messages.receive();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  std::cout << " Green for " << getID()  << std::endl;
  return;
}

// __________________________________________________________________________________________________________________________________________________
TrafficLightPhase TrafficLight::getCurrentPhase() {
    return _currentPhase;
}

// __________________________________________________________________________________________________________________________________________________
void TrafficLight::simulate() {
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called.
    // To do this, use the thread queue in the base class.
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// __________________________________________________________________________________________________________________________________________________
// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases() {
  // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles
  // and toggles the current phase of the traffic light between red and green and sends an update method
  // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds.
  // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles.

  // generate different light phase by using random variables
  std::default_random_engine generator;
  generator.seed(getID());
  std::uniform_int_distribution<int> distribution(4, 7);
  double switchTime = distribution(generator);


  std::cout << " Car has to wait for "  << switchTime  << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  while (true) {
    // time to switch light
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    // std::cout << "time passed" << elapsed.count() << std::endl;

    if (elapsed.count() >= switchTime) {
      switchTime = distribution(generator);
      if (_currentPhase == green) {
        _currentPhase = red;
      } else {
        _currentPhase = green;
      }
      auto switchLight = std::async(std::launch::async, &MessageQueue<TrafficLightPhase>::send, &_messages, std::move(_currentPhase));
      switchLight.wait();
      start = std::chrono::high_resolution_clock::now();
      std::cout << "time until change " << switchTime << std::endl;
    }
    // wait a second
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}
