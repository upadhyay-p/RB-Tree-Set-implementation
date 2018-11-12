# APS_Project

**How to use the Set data structure created in this project:

Add as header file "Set.cpp" or "avl_Set.cpp" in your code.

To make an instance of set data structure write:

T is any primitive data type.
Set<T>  s;  
This will create an empty Set s on which you can perform the following operations:
1) s.insert(x):
      Insert element x into s.
2) s.erase(x):
      Remove element x from s, if x is persent in the set.
3) s.begin():
      Access the first element of the set s.
4) s.empty():
      Check if set s is empty or not.
5) For "Set.cpp":
      print(s).
      Prints set implemented using Red-black tree.
6) For "avl_Set.cpp":
      s.printSet().
      Prints set implemented using avl tree.


**How to give input to "avl_application.cpp" and "application.cpp" :

First line should contain two space separated integers N and E representing Number of nodes and edges in the graph.
Then E lines follow, each line has 3 space separated integers x, y , z representing that from vertex x to vertex y an edge is there of weight z.



**Output format of  "avl_application.cpp" and "application.cpp":

Considering the first vertex to be source vertex.
The shortest distances from the source vertex (vertex number 1) to all other vertices are printed.
Leaving a space between any 2 printed numbers. 
