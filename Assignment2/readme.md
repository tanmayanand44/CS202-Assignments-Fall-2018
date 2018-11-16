# ASSIGNMENT 2 - SAT SOLVER Using SEMANTIC TABLEAU
### by Umang Malik (170765) and Tanmay Anand(170751)

## Instructions
1.) Compile sat.cpp ( ```g++ -std=c++17 -o sat sat.cpp```)
2.) Execute using ```./sat```
3.) Enter input in the format:
Num_Of_Variable Num_of_Clauses
Corresponding Clauses ending with 0

Ex: 
2 1
1 -2 0

##Heuristics
1.)Recursively decomposing on the first disjunction of first conjunction 
2.) Using unit propagation
