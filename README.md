Social Network Graph Simulator 

A C-based application that models a social network using graph theory. It reads user data and relationships from text files, builds an adjacency matrix, and allows interaction through a command-line interface.

This project demonstrates core Data Structures and Algorithms (DSA) concepts, including dynamic memory allocation, graph traversals, and file I/O operations.

Technical Highlights:

-Graph Representation: Uses a dynamically allocated adjacency matrix to map user relationships (friendships).
-Breadth-First Search (BFS): Implements a custom queue-based BFS algorithm to simulate how a "post" spreads through the network from one user to their extended connections.
-Roy-Warshall Algorithm: Calculates the transitive closure of the graph to determine if an indirect connection path exists between any two users in the network.
-Dynamic Memory Management: Strictly manages memory using malloc and free to prevent memory leaks when handling matrices and arrays.
-Persistent State: Modifications to the network (adding or removing friendships) are dynamically written back to the retea.txt file.

Features:

-The interactive CLI menu includes the following functionalities:
-Direct Friendship Check: Verifies if two specific users are directly connected.
-Friend Count: Calculates the total degree (number of friends) of a specific node.
-Isolated Users: Identifies users with zero connections (nodes with a degree of 0).
-Indirect Connection Check: Uses Roy-Warshall to see if a path exists between two distant users.
-Add/Remove Friendships: Updates the adjacency matrix in memory and rewrites the edge list to the data file.
-Post Distribution (BFS): Simulates a feed algorithm, showing exactly who sees a post originating from a specific user.

Project Structure:

source_code.c: The main source code containing the logic and graph algorithms.
network.txt: The network data file. First line contains [number_of_nodes] [number_of_edges], followed by the edges (connections).
users.txt: Maps integer IDs to User string names.

How to Run:

You can compile and run this project using any standard C compiler (like gcc). Ensure all three files are in the same directory.
