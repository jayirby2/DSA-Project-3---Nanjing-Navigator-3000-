# Nanjing Navigator 3000

### COP3530 - Project 3 - Jay Irby, Ben Lang, and David Zapata

## Background

There is a new AI-powered robotics company based in Nanjing, China that is attempting to create an autonomous car locksmith service. AI-powered robots will travel around the city
in small self-driving street vehicles, helping people get back into their vehicles after locking themselves out. The robots will need to travel quickly and efficiently from location 
to location, so we are testing their self-driving capabilitites by providing them a shortest path from their previous help-cite to their new help-cite. The self-driving robots drive at a
constant speed of 40mph on Nanjing roads, highways, and streets. Our problem: we want to minimize the distance these robots have to travel from point A to point B in order to help people get back
into their cars as efficiently as possible. Also, traveling the shortest distance also saved on fuel, so our robots can provide services for longer periods of time before a recharge/refuel. 


## Data 

We downloaded two files from this source that contains spatial datasets extracted from OpenStreetMap:  https://yzengal.github.io/datasets/

We downloaded Nanjing's distance graph and the verticies' corresponding coordinates. Nanjing's distance graph has 146,839 verticies, so this is a subtable dataset. The two files were in unusable
formats, so we had to write Python code to convert them to .csv files. We then uploaded the .csv's to this repository so they can be downloaded and used by any machine. 

Both the [Nanjing distances graph](https://github.com/jayirby2/DSA-Project-3---Nanjing-Navigator-3000-/blob/main/Nanjing_distances.csv) and the [coordinates](https://github.com/jayirby2/DSA-Project-3---Nanjing-Navigator-3000-/blob/main/coordinates.csv)
are in this repository. 

## The Data as Data Structures

Our distances graph is converted to an adjacency list: (node1 : (node2, distance), (node3, distance) ... (nodeN, distance). The adjacency list is a dictionary/map in Python. 
Basically, it contains all the edges in the graph, where each key represents a node, and its value is a list of tuples representing connected nodes and the distance (or weight) to each of them.

Our coordinates file is converted to a simple dictionary/map where each node/vertex is a key and the values is 1 tuple of their (latitude, longitude) coordinates.

## The Algorithms and Their Comparisons

We are using Dijkstra's Algorithm and the A* Algorithm to calculate the shortest path between two nodes. The starting and end locations are randomly generated nodes within our adjacency list's
keys (all of the unique verticies - locations in Nanjing). We randomly generate the points to test how our robot drives in the shortest path between 2 locations. We compare the 
algorithms by path, total distance, and runtime. Path and total distance should almost always be the same, so it is mostly runtime/efficiency we want to really look at.

## How To Run The Code

1.
Click the link to our [Google Colab](https://colab.research.google.com/drive/1r6pq1RWUnhrhGgxawIRa4uRkzXRJmTQE?usp=sharing), download into your own drive/make a copy, and click 'Run All'. 
Yes, it is literally that easy. All the cells will run, and you can scroll to the bottom of the file and click the 'Compare Algos' button to run as many simulations as you desire. 
You can also look through the detailed comments in our Notebook-style document. 

2.
### **Disclaimer**

Colab utilizes external GPUs, and we are suspcious that they mess with runtime, especially A*'s runtime. We prefer if users download the file as a .ipynb and run with their local machine, 
with intuitive notebook interfaces like Jupyter, VS Code notebooks, Deepnote, etc. 


So, you can download our [.ipynb file](https://github.com/jayirby2/DSA-Project-3---Nanjing-Navigator-3000-/blob/main/Nanjing_Navigator_3000.ipynb) and run on your own machine by - again -
clicking 'Run All'. We think this is pretty easy and effective.

## Output

Just for your interest, the comparative visualization looks like this. Click the button to get as many potential shortest path AI locksmith service deliveries as you desire. It is also interesting to
see how the runtime differs in Colab and on local machines. 

![image](https://github.com/user-attachments/assets/a3e24ab2-8450-4fb7-a6cb-20779dadd4e7)

