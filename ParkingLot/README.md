### Parking Lot System - Singleton Design Pattern

#### Introduction
The parking lot system presented here is designed to handle multiple levels and various types of vehicles, such as cars, trucks, and motorcycles. The system is implemented using the Singleton design pattern, which ensures that there is only one instance of the `ParkingLot` class throughout the application. This design pattern is particularly well-suited for this project as it guarantees centralized management of parking operations across multiple entry and exit points, providing consistent real-time information and maintaining data integrity in a concurrent environment.

#### Why Singleton Design Pattern?
The Singleton pattern is ideal for scenarios where a single point of coordination is required across different components or threads of an application. In this parking lot system, the Singleton pattern ensures that only one instance of the `ParkingLot` class is used to manage all levels, parking spots, and vehicle operations. This prevents inconsistencies and conflicts that could arise from having multiple instances of the parking lot managing the same set of resources. Additionally, by using a mutex for thread safety, the Singleton pattern helps manage concurrent access to parking operations, ensuring that only one thread can modify the state of the parking lot at any given time.

#### Class Structure Overview
- **Vehicle**: Represents a vehicle that can be parked in the parking lot. It includes the vehicle's number plate and type (e.g., car, truck, motorcycle).
  
- **ParkingSpot**: Represents a single parking spot in the parking lot. It keeps track of whether the spot is occupied and which type of vehicle it can accommodate.

- **Level**: Represents a level in the parking lot. It contains a collection of parking spots and provides methods to park and unpark vehicles.

- **ParkingLot**: This is the core class that follows the Singleton pattern. It manages all levels in the parking lot and handles parking and unparking operations. It also provides real-time availability information for all parking spots.

#### Class Interactions
- **Vehicle and ParkingSpot**: The `ParkingSpot` class interacts with the `Vehicle` class to determine if a vehicle can be parked in a particular spot based on the vehicle type. It also manages the state of whether a parking spot is occupied.

- **Level and ParkingSpot**: The `Level` class contains multiple `ParkingSpot` objects and manages the parking operations within a specific level. It checks for available spots and assigns them to vehicles as they enter the parking lot.

- **ParkingLot and Level**: The `ParkingLot` class manages multiple `Level` objects, ensuring that vehicles are parked across different levels. It interacts with each level to find an available spot and park the vehicle. It also handles unparking operations and provides real-time availability information for all levels.

#### Singleton Implementation
The `ParkingLot` class is implemented as a Singleton using the following key features:
- **Private Constructor**: The constructor of the `ParkingLot` class is private, preventing direct instantiation.
- **Deleted Copy Constructor and Assignment Operator**: The copy constructor and assignment operator are deleted to ensure that the `ParkingLot` class cannot be copied or assigned.
- **Static Instance**: A static instance of the `ParkingLot` class is created within the class itself. This instance is accessed through the `getInstance()` method.
- **Mutex for Thread Safety**: A mutex (`std::mutex`) is used to ensure that all parking and unparking operations are thread-safe, preventing race conditions in a concurrent environment.

This structured approach ensures that the parking lot system is scalable, easy to maintain, and thread-safe, making it suitable for real-world applications where consistent and reliable operation is critical.
