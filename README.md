# Kinematics

## Overview
This is an object-oriented programming project that showcases the 2D movement of an robotic arm
in a 3D environment. Using the `threpp` library as a dependency, this project creates a 
scene where a robotic arm composed of multiple segments demonstrates inverse kinematics (IK)
principles, allowing the arm to reach a specified target represented as a green sphere. 

![](data/RobotArmDemo.gif)

## Features
* **3D Robotic Arm Simulation:** Simulates a robotic arm with desired number of segments
* **Inverse Kinematics Solver:** Implements an IK solver to move the arm 
towards target point using the [Cyclic Coordinates Descent](http://rodolphe-vaillant.fr/entry/114/cyclic-coordonate-descent-inverse-kynematic-ccd-ik)
approach (CCD)

## Installation and Setup
### 1. **Clone the repository:**
   ``` 
    git clone https://github.com/HermanGran/MappeEksamen_.git
   ```
### 2. **Install Threepp:**

#### Threepp
`Threpp` is a library which implements the [three.js](https://threejs.org) library from JavaScript
inside the C++ environment. 

#### Using threepp
As `vcpkg` is used, you need to tell CMake about it in order for dependency resolution to work:

`-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`

###### Building under MinGW

Under MinGW you'll need to specify the vcpkg triplet:
```shell
-DVCPKG_TARGET_TRIPLET=x64-mingw-[static|dynamic]  # choose either `static` or `dynamic`.
-DVCPKG_HOST_TRIPLET=x64-mingw-[static|dynamic]    # <-- needed only if MSVC cannot be found. 
```

In order to update `threepp`, replace the baseline value in [vcpkg-configuration.json](vcpkg-configuration.json).
The baseline should point to a [commit](https://github.com/Ecos-platform/vcpkg-registry/commits/main)
from the [custom vcpkg registry](https://github.com/Ecos-platform/vcpkg-registry) that hosts the port.

## Usage
* **Launching the Robot Arm:** Run the Robot executable
* **Controlling the Arm:** Top left corner has the control for the target point and number of segments in the arm

<p align="center">
  <img src="data/RobotArmControls.gif" />
</p>

## Further improvement
* The CCD Algorithm i have created only works in the 2D plane. Going forward, the plan is to improve the algorithm to work
in three dimensions using quaternions. 
* Implement a draggable object as the target point
* Using boids as target objects for the robot arm, so when the arm touches the boids, they vanish