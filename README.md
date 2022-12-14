# README

## File Details

1. AVL.cpp                #class defn for derived avl class from searchtree
2. BST.cpp                #class defn for derived bst class from searchtree
3. Node.h                 #class defn for node class
4. Red_Black.cpp          #class defn for derived redblack class from searchtree
5. SearchTree.cpp         #source code for searchtree class
6. SearchTree.h           #class declaration for generic searchtree class
7. Splay.cpp              #class defn for derived splay class from searchtree

## Description

1. This repo is to implement different types of 2-node search trees namely binary search tree(bst), AVL tree, Splay tree, and Red_Black Trees.
2. This is done by defining a generic parent class called searchtree and deriving each specialized search tree type.
3. Three major methods implemented are search(), insert(), and remove().
4. An additional method display() is provided to visualize the tree.

## Running the code
1. To tinker with any of the trees, add a main() function below the class definition in the file. For example see Red_Black.cpp
2. To run, cd to repo folder and run the following command : "g++ SearchTree.cpp <filename.cpp> -o exec;./exec.exe" (without quotes ofc XD :) )
3. replace <filename.cpp> with appropriate name. For Eg: "g++ SearchTree.cpp Red_Black.cpp -o exec; ./exec.exe"
