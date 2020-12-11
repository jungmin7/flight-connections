# Weekly Development Log 

Jaywoo Jo, 
Hemank Kohli, 
Holly Lee


# End of Week of 11/16/20 #
<!-- Week of 11/16/20 -->

Our team has submitted the project goals and committed the team contract individually this week.
We have roughly set what datasets we will be using for the project. We are interested in using a BFS Traversal, and Dijkstra’s Algorithm. However, this could be changed as we are working on it.
Our team has also set the group work guidelines in the contract including the time commitment and work distribution.
This will be helpful for us in splitting tasks and efficiently working on the project.


# End of Week of 11/23/20 #
<!-- Week of 11/23/20 -->

This week was Thanksgiving break. While we continued to discuss goals and split roles, we did not do much work during the break.

# End of Week of 11/30/20 # 
<!-- Week of 11/30/20 -->

This week we had a mid-project check in meeting with our mentor, Zijie Lu. We only created class files and make files, so we were only able to dicuss about the kinds of algorithms we were interested in implementing. We also discussed with our mentor about how we decided that the Stanford SNAP dataset we were looking at seemed difficult to parse, and we found the OpenFlights data set more interesting. So he said it was alright to change our dataset and he said to just make sure to update our project goals.

Additionally, during the meeting we asked important questions such as how to create test cases and structure our code. In the next few days after that meeting, we finished creating code that pulls data from the flight data sets. One data set we parsed is a data set that includes a list of all the airports and its respective longitude/latitude points; the other data set we parsed was one that details flight paths from one airport to another (for ex: SIN --> ICN). As an overview of our graph structure, using the longitude/latitude data from the airports, we calculated the distance between two airports using Haversine's distance formula. With this, the nodes represented airports, the directed edges represented flight paths between airports, and the edge weights represented the distance. In the next week, we will be working on creating test cases and implementing the algorithms.

# Mid-Week of 12/07/20 #
<!-- Week of 11/07/20 -->
As a team, with the discord server and facebook messenger group chat we created, we have been communicating via chat and call on a near daily basis since the mid-project check in meeting. 

After a few days, after a lot of challenges, we successfully read the data and pulled what we needed to create the graph. For the airports file, we used substring methods to map each airport onto a pair of longitude and latitude points (for example, key of "SIN" would map to (1.36, 103.99)). Then, we read the routes file to 
find the paths between airports, and used the map of longitude/latitude points we created earlier to calculate the Haversine distance between two airports so we could create edge weights representing the distance between the airports.

We also implemented our algorithms, but we are still working to revise our Djikstra's algorithm. As we approach the deadline on Friday, we will be wrapping up our test cases. Then, we will work on the other aspects of the project like the README, 1 to 2 page report, and presentation.

# End of 12/07/20 #
<!-- Week of 11/07/20 -->
We wrapped up all of our test cases and made important design decisions on the best way to output the results of these test cases. As you can see if you run the tests, we outputted the results of the traversal, path, etc., along with an expected vs. actual output for debugging purposes. As seen in our test cases, we created thorough test cases that test important functions that can be run all at once (./test), individually (such as ./test test_integerEasy_BFS), or in groups (such as ./test [BFS]). 

We also finished writing a report that describes the goals, development, and closing thoughts for our project. We explained specific design decisions and why they proved to be successful. Lastly, we will be finishing up our README and submitting our presentation.





