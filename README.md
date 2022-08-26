# Autonomous car using ROS


![GitHub Repo stars](https://img.shields.io/github/stars/bhavikmk/self-driving-car-ros?color=FFE333)
![GitHub Repo forks](https://img.shields.io/github/forks/bhavikmk/self-driving-car-ros?color=FFE333)

![Ubuntu 20.04](https://img.shields.io/badge/OS-Ubuntu-informational?style=flat&logo=ubuntu&logoColor=white&color=2bbc8a)
![ROS](https://img.shields.io/badge/Tools-ROS-informational?style=flat&logo=ROS&logoColor=white&color=2bbc8a)
![C++](https://img.shields.io/badge/Code-C++-informational?style=flat&logo=c%2B%2B&logoColor=white&color=2bbc8a)
![Python](https://img.shields.io/badge/Code-Python-informational?style=flat&logo=c%2B%2B&logoColor=white&color=2bbc8a)


## Description

My customised implementation of autonomous car using Robot Operating System (ROS). Also applicable for autonomous trucking system. 

> **Levels of autonomy:**

> * Level 0 - Complete manual mode (no automation)
> * Level 1 - hands on/shared control
> * Level 2 - hands off 
> * Level 3 - eyes off
> * Level 4 - mind off 
> * Level 5 - steering wheel optional


ADAS that are considered From level 3 to 5, the amount of control the vehicle has increases.

level 5 being where the vehicle is fully autonomous.

## Self driving car architecture

![](https://github.com/bhavikmk/self-driving-car-ros/blob/main/assets/ros-architecture-car.png)


## **Sensors**
  - Camera, Lidar, Radar, Sonar, IMU, GPS, Odometry

> **Sensor Selection Criteria**
>   * Range
>   * Resolution
>   * Robustness in different environments
>   * Perception of environment
>   * Speed
>   * Cost
>   * Size
>   * Computational requirements

## Perception

**2d object detector**:
> * I/P: Image
> * O/P: Detections msg

**3d object detector**:
> * I/P: LaserScan
> * O/P: 3D_Detections msg

**free space detector**:
> * I/P: LaserScan
> * O/P: FreeSpace msg

**lane detector**:
> * I/P: Image
> * O/P: Lane msg

**sign detector and classifier**:
> * I/P: Image
> * O/P: Sign msg

## Localization & Mapping

**Implementation**
> * Extended kalman filter
> * Uncented kalman filter
> * Monte carlo localization
> * Occupancy grid mapping
> * GraphSLAM & FastSLAM 

## Planning

**Route planning**: 
> * I/P: Road Network Data, User destination, Online traffic information; 
> * O/P: Waypoints

**Behaviour planning**:
> * I/P: Waypoints from *route_planning_node*, Road topology, Static and dynamic objects from *object_tracker_node*, traffic sign from *traffic_sign_detector_node*, Traffic rules
> * O/P: Strategy

**Motion planning**:
> * I/P: Strategy from *behaviour_planning_node*, Estimated pose from *localizer_node*, collision free space from *free_space_detector_node*
> * O/P: Trajectory

> * Deep reinforcement learning based path planning

## Control

**Local Feedback Control**:
> * I/P: Trajectory from *motion_planning_node*
> * O/P: Steering angle, throttle and brake commands

**PID controller**:
> * I/P: Commands from local feedback controller, Sensor data 
> * O/P: Actuator control commands
---------------

### Visual and environmental monitoring

* **Automotive head-up display (auto-HUD)**  safely displays essential system information to a driver at a vantage point that does not require the driver to look down or away from the road.

* **Automotive navigation system** use digital mapping tools, such as the global positioning system (GPS) and traffic message channel (TMC), to provide drivers with up to date traffic and navigation information.

* **Automotive night vision systems** enable the vehicle to detect obstacles, including pedestrians, in a nighttime setting or heavy weather situation when the driver has low visibility. These systems can various technologies, including infrared sensors, GPS, Lidar, and Radar, to detect pedestrians and non-human obstacles.

* **Glare-free high beam** use Light Emitting Diodes, more commonly known as LEDs, to cut two or more cars from the light distribution. This allows oncoming vehicles coming in the opposite direction not to be affected by the light of the  high-beams. 
  
* **Omniview technology** improves a driver's visibility by offering a 360-degree viewing system. This system can accurately provide 3D peripheral images of the car's surroundings through video display outputted to the driver. Omniview technology uses the input of four cameras and a bird's eye technology to provide a composite 3D model of the surroundings.

* **Traffic sign recognition (TSR)** systems can recognize common traffic signs, such as a “stop” sign or a “turn ahead” sign, through image processing techniques. This system takes into account the sign's shape, such as hexagons and rectangles, and the color to classify what the sign is communicating to the driver. 

* **Vehicular communication systems** come in three forms: vehicle-to-vehicle (V2V), vehicle-to-infrastructure (V2I), and vehicle-to-everything (V2X). V2V systems allow vehicles to exchange information with each other about their current position and upcoming hazards. V2I systems occur when the vehicle exchanges information with nearby infrastructure elements, such as street signs. V2X systems occur when the vehicle monitors its environment and takes in information about possible obstacles or pedestrians in its path.


---------------

# Notes

Self driving car is widely developed technology and large toolbox and state of the art ideas available, Need to make right decisions according to needs. 

Below are some of the features of car with ADAS. I will try to also implement this in the project.

- [ ] Parking sensors 
- [ ] Surround-view 
- [ ] Traffic sign recognition 
- [ ] Lane departure warning 
- [ ] Night vision
- [ ] Blind spot information system
- [ ] Rear-cross traffic alert
- [ ] Forward-collision warning
- [ ] Adaptive cruise control 
- [ ] Emergency brake assist
- [ ] Automatic emergency brake assist
- [ ] Lane-keeping
- [ ] Lane centering
- [ ] Highway assist
- [ ] Autonomous obstacle avoidance
- [ ] Autonomous parking.

--------------
