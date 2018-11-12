# APS_Project

How to use the Set data structure created in this project:

Add as header file "Set.cpp" or "avl_Set.cpp" in your code.

To make an instance of set data structure write
Set<T>  s;  //T being any primitive data type
This will create an empty Set s on which you can perform the following operations:
1) s.insert(x)
      Insert element x into s.
2) s.erase(x)
      Remove element x from s, if x is persent in the set.
3) s.begin()
      Access the first element of the set s.
4) s.empty()
      Check if set s is empty or not.
5) print(s)   //Only For "Set.cpp"
      For printing set implemented using Red-black tree.
6) s.printSet()   //Only For "avl_Set.cpp"
      For printing set implemented using avl tree.
