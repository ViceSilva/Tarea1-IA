#include <iostream>
#include <fstream>
#include <string>

using namespace std;
//funciones de utilidad
bool parse(string fileName, vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost, unordered_map<char,int> &heuristicVal, char &init, char &goal);
void printParsedData(vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost, unordered_map<char,int> &heuristicVal, char &init, char &goal);
void printResult(vector<char> &nodes, unordered_map<char,unordered_map<char,int>> &cost, unordered_map<char,int> &visited, unordered_map<char,char> &backTrack, char init, char goal);
void printResult2(vector<char> &nodes, unordered_map<char,unordered_map<char,int>> &cost, unordered_map<char,int> &visited, vector<char> route);
