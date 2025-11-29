# Report
Fill out these report questions. 


1. What is the difference between a directed and undirected graph?

A directed graph is a graph where edges can exist from source vertexes to destination vertexes, 
without necessarily having that destination vertex have an edge that points back to the source vertex. 
This gives a one-sided path from the source vertex to a destination vertex.
Undirected graphs are the opposite. In an undirected graph, if vertex a points to vertex b, 
it is guaranteed that vertex b has an edge that points back to vertex a. 

2. What is the Big O of Dijkstra's algorithm.... 
   * Assuming you used an array (or list) to store the vertices.
   Time complexity: O(V^2)
   This is because you have to loop through the vertices (and their edges), 
   and at each vertex you also would need to make a loop to find the minimum distance you have stored.
   Space complexity: O(V)
   This is because you have to store information for all vertices, 
   such as the minimum distance and the previous vertex. 
   * Assuming you used a heap / priority queue to store the vertices.
   O((V + E)log V)
   This is because you have to loop through the vertices and their edges,
   and for each iteration you find the minimum distance using the heap, 
   which takes O(log V) time. 
   You also need to do heap insertions, which take O(log V) time.
   Space complexity: O(V) - same as list implementation
   

3. Explain in your own words what that means for larger graphs when trying to find the shortest distance. 
This algorithm can be slow for large graphs, as the time complexities of its implementations are relatively high.
The efficienty of the different implementations in terms of time complexity also varies between dense and sparse graphs.
For dense graphs, the heap/priority queue might actually be slower than the list implementation,
as it takes more time to insert into a heap than to a list, 
and you would have to do many insertions if you have many edges. 
For sparse graphs, however, the heap implementation is more optimal. 



## Deeper Thinking
4. For this assignment, you didn't need the most "efficient" set of data structures (for example, a heap wasn't required). However, think on the scale of google/apple maps - they have to deal with millions of vertices and edges. What data structures would you use to store the graph? Why? Somethings to consider - would you be able to store the entire graph at a time? Could you break it up into smaller pieces? How would you do that? Would there be advantages to caching/memoization of paths? You are free to explore your thoughts on this subject/reflect on various ideas. Other than a realization of some scalability of problems, there isn't a wrong answer. 

A real life map would be relatively sparse, as a road itself has few destinations. 
An adjacency list would be a memory efficient structure for this case rather than a matrix. 
As an entire map already uses a ton of memory, it is best to use a data structure that saves memory. 
However, such a large graph still would not be able to be stored in a single adjacency list.
It could be partitioned into different sections based on location.
This could be done with a technique called 'sharding'.

We would also need ways to save runtime. 
Since there are relatively few edges in comparison with the amount of vertices,
I think a heap would be wise to implement.
With a heap we would avoid having to loop O(n) to find the minimum of the stored distances for every vertex,
and although while visiting every edge we'd have to insert to the heap with O(log V) time, as we have
few edges in comparison to the vertices, a heap would still be more efficient.

In this scenario of google-maps, users would often be searching for the same route as other users,
and also the same route as they have previously looked up.
A cache would be necessary and beneficial to not always have to re-calculate the same paths. 
The cache can store commonly used routes, and also a user's previous routes that they have taken. 

Also, we might need to often insert more locations into the structure as well as delete locations.
A hashmap could be used to store the vertices instead of an array to avoid O(n) insertion and deletion time.



## Future Understanding
5. Related to shortest distance, is a problem called the "messenger" or "traveling sales person" problem commonly abbreviated to TSP. This problem is to find the shortest path that visits **every** vertex in a graph. Another way to look at it, is you are an delivery driver, and you have a series of packages to deliver. Can you find an optimal path for your deliveries that minimizes the total distance traveled? Imagine if you had 5 stops. How many different paths are there?  There are 120 possible paths to look at! (assuming fully connected routes). 
   * How many possible paths are there if you have 6 stops?
   There are 720 possible paths for 6 stops (6 * 5 * 4 * 3 * 2 * 1).
   * How many possible paths are there if you have 10 stops?
   There are 3628800 possible paths for 10 stops (10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1).
6. What type of growth is this problem? 
This problem is O(n!), which is called factorial growth. 
7. Take some time to research TSP problems. It falls under a certain classification of problems? What is it? 

This problem is a combinatorial optimization problem and is considered to be NP-hard. [source]

A combinatorial optimization problem is a problem where the goal is to find the most optimal solution
within a finite number of solutions. Often this finite number of solutions is still very large.

NP means that this problem cannot be solved in polynomial time, but cannot be verified in polynomial time.
Polynomial means in proportion to n. For example, O(n), O(n^2), O(n^3), O(log n), and O(n log n) all count as polynomial time.
However, you would not be able to verify that your solution is the shortest path in polynomial time. 
You can only verify that it is a valid path, meets requirements, and meets a certain threshold in polynomial time.
NP-hard means that it is at least as hard as the hardest NP problems. 

The TSP problem can be brute forced. A brute force solution is to calculate all the possible paths,
store the existing minimum path, and every time you find a shorter path, reset the minimum to the newly found path.
This accurately finds the minimum path, but it is computationally expensive.

Another way is to use a greedy algorithm. To solve this TSP with greedy,
you can find the location that is closest to the current location, and continue until you visit all the locations.
This solution is much faster, but it is only approximate. It is not 100% accurate. 

There are 'heuristic' approaches to provide a decent but not exact solution to this algorithm,
as well as the 'approximation' approach.

I think this problem is quite interesting as it is so practical and yet an optimal solution for it hasn't been found.

8. Provide some examples of fields / problems that use TSP.

A school bus route uses TSP, as it needs to stop at certain locations before arriving at the school 
and has to follow an efficient path so that route doesn't take too much time.

TSP is also used in DNA sequencing, to figure out how to sequence overlapping fragments to recreate a genome. [source]

TSP is used in network design - telecommunications companies need to find a short route to connect their network nodes,
so that they minimize signal loss. 


> [!TIP]
> We are having you explore TSP, so you can see the terms used for problem classification that are often the foundation of computer science theory. You will not be asked to know about TSP outside of this assignment or even problem classification. Computer Science is often about dealing with problems considered "too hard" or "impossible", and finding ways to make them possible! As such, knowing topics such as N, NP, NP-Complete, etc. is important to understand the limits (to break).


## Technical Interview Practice Questions
For both these questions, are you are free to use what you did as the last section on the team activities/answered as a group, or you can use a different question.

1. Select one technical interview question (this module or previous) from the [technical interview list](https://github.com/CS5008-khoury/Resources/blob/main/TechInterviewQuestions.md) below and answer it in a few sentences. You can use any resource you like to answer the question.

What are some scenarios when you wouldn't want to apply a greedy algorithm?

You wouldn't want to use a greedy algorithm for a problem where continuously picking the local optimal solution
won't lead to a globally optimal solution. An example is the coin change problem.
If you need to give 12 cents, and have coins of 8, 6, and 1 (let's imagine you're in an alternate universe with these kinds of coins),
grabbing the 8 and then having to take 4 1s won't be the solution that uses fewer coins.

Another example is when there are lots of different constraints and it is unclear
what the local most optimal solution is at each step.

There could also be global context that greedy solutions don't consider. 
For example, if you can take either 2 dollars or 1 dollar, following the greedy approach
you would take 2 dollars, but that doesn't work if the context is that if you take 1 dollar 
you receive another 100 dollar bill.


2. Select one coding question (this module or previous) from the [coding practice repository](https://github.com/CS5008-khoury/Resources/blob/main/LeetCodePractice.md) and include a c file with that code with your submission. Make sure to add comments on what you learned, and if you compared your solution with others. 