#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "utils.h"
#include "fBusqueda.h"

using namespace std;

int main(int argc, char const *argv[])
{
	//preparacion de datos
	string searchAlg = argv[1];
	string inputS = argv[2];
	unordered_map<char, vector<char>> graph;
	unordered_map<char,unordered_map<char,int>> cost;
	unordered_map<char,int> heuristicVal;
	vector<char> nodes;
	char init, goal;
	//se obtienen los datos desde el archivo definido
	if(!parse(inputS,nodes ,graph, cost, heuristicVal, init, goal))
		return 0;
	//printParsedData(nodes, graph, cost, heuristicVal, init, goal);
	//se imprime el resultado
	if(searchAlg == "DFS")
		DFS(nodes, graph, cost, init, goal);
	else if(searchAlg == "G")
		Greedy(nodes, graph, cost, heuristicVal, init, goal);
	else if(searchAlg == "UCS")
		UCS(nodes, graph, cost, init, goal);
	else if(searchAlg == "AS")
		Astar(nodes, graph, cost, heuristicVal, init, goal);
	else
		cout<<"no se ingreso un algoritmo valido"<<endl;
	return 0;
}