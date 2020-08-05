# CPPND: Project use Pytorch API and QT5 to predict next word 
<img src="images/Image-1.png" width="600" height="450" />

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

* libtorch >= 1.6.0
  * Linux: use downloadlink  https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-1.6.0%2Bcpu.zip

## Basic Build Instructions

1. Clone this repo.
2. create a new folder third `mkdir third`
3. Unzip the pytorch download there
4. make sure qt5 is installed https://www.qt.io/
5. create a new folder model `mkdir model`
5. Make a build directory in the top level directory: `mkdir build && cd build`
6. Compile: `cmake .. && make`
7. Run it: `./gui-app`.
 

# How to use the app
<img src="images/Image-2.png" width="600" height="450" />
1. Choose the path for the word file ( words avaiable for the network)
<img src="images/Image-3.png" width="600" height="450" />
2. Load the saved weights to the model
 <img src="images/Image-4.png" width="600" height="450" />
3. Add word in text window
<img src="images/Image-5.png" width="600" height="450" />
4. Click to predict the 4 next most likly to the model
<img src="images/Image-6.png" width="600" height="450" />
5. Click on the button with the word that fits for you 
6. The program adds the word to your input and displaies the outputs  



# credit

- The pytorch model is inspirered from https://github.com/prabhuomkar/pytorch-cpp
- cmake understanding  CMake Tutorial For Beginners  and  https://stackoverflow.com/
- C++ in general (if you understand german) https://ad-wiki.informatik.uni-freiburg.de/teaching/ProgrammierenCplusplusSS2020
