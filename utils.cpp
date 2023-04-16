#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "utils.h"

using namespace std;

bool parse(string fileName, vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost, unordered_map<char,int> &heuristicVal, char &init, char &goal){
	//se abree el archivo
	ifstream file(fileName);
	if (file.is_open()) {
        string line;
        //se obtiene el nodo inicial y objetivo
        if(getline(file, line)){
        	stringstream ss(line);
        	string trash;
        	ss >> trash >> init;
        }
        if(getline(file, line)){
        	stringstream ss(line);
        	string trash;
        	ss >> trash >> goal;
        }
        //se obtienen los valores heuristicos de los nodos
        while (getline(file, line)) {
        	int count = 0;
        	for (int i = 0; i < line.size()-1; ++i)
        		if(line[i] == ' ')
        			count++;
        	if(count > 1)
        		break;
        	char node;
        	int h;
        	stringstream ss(line);
        	ss >> node >> h;
        	nodes.push_back(node);
        	heuristicVal[node] = h;
        }
        //se obtienen los valores de los caminos de los nodos
        stringstream ss(line);
        char node1, node2;
        int c;
        ss >> node1 >> node2 >> c;
        graph[node1].push_back(node2);
        cost[node1][node2] = c;
        while (getline(file, line)){
        	stringstream ss(line);
	        char node1, node2;
	        int c;
	        ss >> node1 >> node2 >> c;
	        graph[node1].push_back(node2);
	        cost[node1][node2] = c;
        }
        file.close(); // Close the file
        return true;
    }
    else cout<<"unable to open file"<<endl;
    return false;
}
//funcion para imprimir la data obtenida, para testear parser
void printParsedData(vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost, unordered_map<char,int> &heuristicVal, char &init, char &goal){
	cout<<"--------------------------------------------------"<<endl;
	cout<<init<<" "<<goal<<endl;
	for(auto it = heuristicVal.begin(); it != heuristicVal.end(); it++){
		cout<<it->first<<" : "<<it->second<<endl;
	}

	for(auto it = graph.begin(); it != graph.end(); it++){
		cout<<it->first<<" : "<<endl;
		for (int i = 0; i < it->second.size(); ++i)
		{
			cout<<it->second[i]<<" cost:"<<cost[it->first][it->second[i]]<<endl;
		}
	}
	cout<<"--------------------------------------------------"<<endl;
}
//impresion de resultados

//impresion para cuando se tiene el backtrack
void printResult(vector<char> &nodes, unordered_map<char,unordered_map<char,int>> &cost, unordered_map<char,int> &visited, unordered_map<char,char> &backTrack, char init, char goal){
	//se imprimen resultados
	vector<char> reversePath;
	reversePath.push_back(goal);
	char node = goal;
	while(node != init){
		node = backTrack[node];
		reversePath.push_back(node);
	}
	//comienza impresion
	int sumCost = 0;
	for (int i = reversePath.size()-1; i > 0; --i){
		sumCost += cost[reversePath[i]][reversePath[i-1]];
		cout<<reversePath[i]<<"->";
	}
	cout<<reversePath[0]<<endl;
	cout<<"Costo: "<<sumCost<<endl;
	for (int i = 0; i < nodes.size(); ++i){
		cout<<nodes[i]<<": "<<visited[nodes[i]]<<endl;
	}
}
//impresion para cuando se tiene la ruta
void printResult2(vector<char> &nodes, unordered_map<char,unordered_map<char,int>> &cost, unordered_map<char,int> &visited, vector<char> route){
	//comienza impresion
	int sumCost = 0;
	for (int i = 0; i < route.size()-1; ++i)
	{
		sumCost += cost[route[i]][route[i+1]];
		cout<<route[i]<<"->";
	}
	cout<<route[route.size()-1]<<endl;
	cout<<"Costo: "<<sumCost<<endl;
	for (int i = 0; i < nodes.size(); ++i){
		cout<<nodes[i]<<": "<<visited[nodes[i]]<<endl;
	}
}