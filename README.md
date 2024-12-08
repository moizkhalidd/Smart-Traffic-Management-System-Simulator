# Traffic Management System

## Introduction

The **Traffic Management System** is designed to optimize and manage traffic flow in a city’s road network by leveraging advanced algorithms, real-time data, and traffic control mechanisms. The system aims to reduce congestion, improve safety, and enhance the overall efficiency of urban transportation. By integrating real-time traffic updates, signal management, emergency vehicle handling, route optimization, and road blockage detection, this system is an essential tool for modern smart cities.

## Technology Stack

- **Data Structures**: The system relies on efficient data structures like **Graphs**, **Linked Lists**, **Heaps**, and **Queues** to store and manage traffic data, road networks, and vehicle information.
- **Algorithms**: For calculating the shortest path, the project makes use of methods like **Dijkstra's Algorithm**.
- **Real-time Updates**: The system simulates real-time traffic data, including vehicle counts, traffic congestion, signal timings, and road blockages, providing up-to-date information to users.
- **User Interface**: A simple and interactive user interface allows users to input intersections, manage traffic signals, track vehicles, and view real-time traffic status.

## Key Features

### 1. **Display City Traffic Network**

The **Display City Traffic Network** feature provides a visual representation of the city’s traffic network using an adjacency list format. This feature illustrates the connections between intersections and the associated weights, such as travel times or distances, enabling a clear understanding of the traffic flow across the city.

### 2. **Display Traffic Signal Status**

The **Display Traffic Signal Status** feature provides a comprehensive overview of the traffic signal timings at every intersection in the city. It shows the green time for each signal, indicating how long the signal remains green for vehicles at that intersection. This feature helps monitor and analyze signal timings to ensure smooth traffic flow.

### 3. **Display Congestion Status**

The **Display Congestion Status** feature provides real-time traffic congestion data for all roads in the city. It highlights roads with varying traffic densities by displaying the total number of vehicles currently on each road. This allows users and traffic authorities to identify slow-moving, high-traffic areas, as well as roads with minimal vehicle flow.

### 4. **Display Blocked Roads**

The **Display Blocked Roads** feature provides an organized list of roads currently unavailable for traffic. It includes roads that are fully blocked and those under repair. This helps drivers and traffic authorities to plan alternate routes and manage traffic more effectively.

### 5. **Emergency Vehicle Handling**

The **Emergency Vehicle Handling** feature prioritizes emergency vehicles (e.g., ambulances, fire trucks, or police vehicles) by dynamically adjusting traffic signals along the shortest path to ensure minimal delays. It temporarily increases green time at intersections on the emergency route, allowing the vehicle to pass quickly and safely. Once the emergency has cleared, traffic signals revert to their normal timings.

### 6. **Block Roads**

The **Block Roads** feature allows traffic authorities to temporarily or permanently block specific roads in the traffic network. This feature is useful for scenarios such as construction, accidents, or scheduled maintenance. It ensures the traffic system dynamically updates to account for the blocked road and provides alternative routes for vehicles.

### 7. **Vehicle Routing**

The **Vehicle Routing** feature allows for the calculation of all possible paths from a start intersection to a destination intersection, along with their respective travel times or "weights". This feature is useful for determining the best routes for vehicles and can also be used to assess congestion or optimize traffic flow by providing multiple route options.

### 8. **Add Vehicle**

The **Add Vehicle** feature allows users to simulate the addition of a vehicle to a specific road segment in the traffic network. By specifying a start and end intersection, the system updates the traffic conditions to reflect the new vehicle’s presence, which can affect congestion levels and travel times along the path.

### 9. **Manage Signal for Highest Priority**

The **Manage Signal for Highest Priority** feature adjusts the traffic signal timings at intersections to prioritize emergency vehicles. By dynamically adjusting the green time at each intersection, the system ensures that emergency vehicles can move through the traffic network with minimal delay. Once the emergency vehicle has passed, the system restores the normal signal timings to ensure smooth traffic flow for other vehicles.

### 10. **Add Priority Vehicle**

The **Add Priority Vehicle** feature allows the user to add a vehicle to the traffic network with a specified priority level. This priority status determines how the vehicle will interact with the traffic management system, including adjustments to traffic signal timings. By giving vehicles different priority levels (High, Medium, Low), the system ensures that high-priority vehicles, such as emergency response vehicles, can pass through intersections more efficiently.

### 11. **Shortest Path (Dijkstra's Algorithm)**

The **Shortest Path** feature utilizes **Dijkstra's Algorithm** to find the most efficient route between two intersections within the city's traffic network. The algorithm evaluates the shortest possible path based on the travel time (or weight), ensuring quick and optimal routing for vehicles.

---

## Conclusion

The **Traffic Management System** provides a comprehensive solution for optimizing traffic flow in smart cities. By utilizing real-time data, advanced algorithms, and dynamic control mechanisms, the system helps improve safety, reduce congestion, and enhance overall efficiency in urban transportation. This system is scalable and adaptable to handle the complexities of modern cities, making it a critical tool for managing urban mobility effectively.

## Simulation Dashboard

![image](https://github.com/user-attachments/assets/d1d0b459-c922-40c5-aea5-6f84e2908ff5)

## Display City Traffic Network

![image](https://github.com/user-attachments/assets/ba45a818-05fe-46e6-acae-f818dabfd503)

## Display Traffic Signal Status

![image](https://github.com/user-attachments/assets/2fbc7efb-3eee-4262-a21b-6ed94a2b7b36)

## Display Congestion Status

![image](https://github.com/user-attachments/assets/67c48e16-b716-41c7-b517-187717a7febf)

## Display Blocked Roads

![image](https://github.com/user-attachments/assets/99696717-7271-4716-8cb8-4fd8811b2504)

## Emergency Vehicle Handling

![image](https://github.com/user-attachments/assets/0355a6f7-3df5-4cbd-951f-00c551bfbb71)

![image](https://github.com/user-attachments/assets/a979a0df-36f6-4f4a-9327-500533bcf406)

## Block Roads

![image](https://github.com/user-attachments/assets/9fb23a3f-c8b9-49ca-90a2-c70907d03bb3)

**Displaying block roads**

![image](https://github.com/user-attachments/assets/30ca2793-4f22-4027-b9b5-c9e2b21f56d2)

## Vehicle Routing (all posible routes)

![image](https://github.com/user-attachments/assets/bfcb6301-0437-44cb-a0a2-5537c3664f7f)

## Add Vehicle

![image](https://github.com/user-attachments/assets/c4d0b5da-2717-4abd-842d-d415cb6b73f5)

**Diplaying addition of vehicle** 

![image](https://github.com/user-attachments/assets/32df13d2-a493-4098-ae77-978297402ab5)

## Manage Signals 

![image](https://github.com/user-attachments/assets/cc0fae43-3130-4293-9494-3b888e5c7a42)

![image](https://github.com/user-attachments/assets/cbb7bb37-c1ca-41fc-a297-f72392af9067)

## Add Priority Vehicle

![image](https://github.com/user-attachments/assets/955fdc43-db6f-4f3a-b7bb-481e6d8cc47c)


## Add Road

![image](https://github.com/user-attachments/assets/cbf7fe2a-c2c5-4fa8-8c59-6f57a3c5d414)


**After road addition**

![image](https://github.com/user-attachments/assets/77505b31-469a-4e87-90af-f253a9314bb2)

## Remove Intersection

![image](https://github.com/user-attachments/assets/19657cb7-a12c-4c07-8748-b7070ce9bedd)

**Display after removal**

![image](https://github.com/user-attachments/assets/3c0a0362-6af3-4d31-9845-77a0522d196a)

## Road Removal

![image](https://github.com/user-attachments/assets/b3474864-492e-42df-9bf3-c05793fd5c41)

**Display After Removal**

![image](https://github.com/user-attachments/assets/1b06631d-15ab-4d2c-a331-080f7d026854)

## Display Shortest Path

![image](https://github.com/user-attachments/assets/44323f9f-b1f1-4b90-ad7f-59c1fcf3889e)

## Exiting Simulation

![image](https://github.com/user-attachments/assets/deb50472-f569-4218-a506-d0de58164f71)



