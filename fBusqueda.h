#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
//funciones de busqueda y de impresion para los algoritmos
void DFS(vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost, char init, char goal);

void Greedy(vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost,
 unordered_map<char,int> &heuristicVal, char init, char goal);

void UCS(vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost, char init, char goal);

void Astar(vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost,
 unordered_map<char,int> &heuristicVal, char init, char goal);

bool recDFS(unordered_map<char, vector<char>> &graph, char element, char goal, unordered_map<char,int> &visited, unordered_map<char,char> &backTrack);


