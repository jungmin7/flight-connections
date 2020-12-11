
<!-- FINAL PROJECT EXPLANATION -->
## Final Project Explanation
We used the OpenFlights (https://openflights.org/data.html) data set for our project, where we read the data and used it to create a graph to run algorithms of interest. We decided to use the airports.dat and routes.dat files listed on the OpenFlights website. The airports.dat file contains a list of over 10,000 airports with data items such as the airport name and country, the 3-digit IATA code, and longitude and latitude values. The routes.dat file contains flight paths from one airport to another (for example, ICN to SIN). 

Our project is based on analyzing and performing three algorithms based on OpenFlights data set.
The three algorithm are: BFS Traversal, Shortest Path between given vertices (Dijkstra's algorithm), and Strongly Connected Components (Kosaraju's algorithm).
The OpenFlight data set we used includes flight paths (routes) and information on each airport, such as the 3-letter code, and coordinates of the airport.
For the purpose of testing, a subset of the data files have been provided called routes_test.txt and airports_test.txt.

Please refer to the **final report** that thoroughly explains our goals and development:
https://docs.google.com/document/d/1_GpP6_4v_8IB3rl-n2YTE-Yo4ImPJpFXvOClcXQZB0w/edit

Please also refer to our **presentation video** and **presentation slides**:
(insert youtube link here)
https://docs.google.com/presentation/d/1X7W19w8QKExFXof0ubq4bdCS15rI1YQYrRCc_uVZVHg/edit#slide=id.gb0bf1a33ca_2_0


<!-- USAGE -->
## Usage
To run the code, head to the project_files directory using ```cd project_files``` and once there use ```make clean```.
Main.cpp has commented parts for each algorithms so please remove the comments for whichever algorithm you would like to run.
Once main.cpp is ready, run ```make && ./main``` to run the code.
Further instructions on how to change variables and file names are provided in main.cpp.
The testing data set has also been provided and can be used by replacing the string names as instructed in main.cpp.


<!-- CONTACT -->
## Contact
Jaywoo Jo (jrjo2@illinois.edu)

Hemank Kohli (hkohli2@illinois.edu)

Holly Lee (jungmin3@illinois.edu)


