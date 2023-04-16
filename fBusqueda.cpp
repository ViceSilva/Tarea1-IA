#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <tuple>
#include "fBusqueda.h"
#include "utils.h"
#include <queue>

using namespace std;

void DFS(vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost, char init, char goal){
	//estructuras utiles
	unordered_map<char,int> visited;
	unordered_map<char,char> backTrack;
	srand(time(0));
	//comienza DFS recursivo
	backTrack[init]=init;
	if(!recDFS(graph,init,goal,visited,backTrack)){
		cout<<"NO SE ENCONTRO RUTA"<<endl;
		return;
	}
	printResult(nodes, cost, visited, backTrack, init, goal);

}

bool recDFS(unordered_map<char, vector<char>> &graph, char element, char goal, unordered_map<char,int> &visited, unordered_map<char,char> &backTrack){
	//se agrega el nodo como visitado y se revisa si es el nodo objetivo
	if(element == goal)
		return true;
	visited[element] = 1;
	//se obtienen los nodos hijos
	vector<int> childrenIndexes;
	for(int i = 0; i < graph[element].size(); i++){
		childrenIndexes.push_back(i);
	}
	//se toma un nodo aleatorio en cada iteracion y se revisa si ya fue visitado en caso contario se llama recursivamente a recDFS
	//si encuentra el objetivo termina la ejecucion
	while(!childrenIndexes.empty()){
		int Ind = rand()%childrenIndexes.size();
		int childInd = childrenIndexes[Ind];
		childrenIndexes.erase(childrenIndexes.begin()+Ind);
		char child = graph[element][childInd];
		if(visited[child])
			continue;
		//se registra camino en backtrack
		backTrack[child] = element;
		if(recDFS(graph,child,goal,visited,backTrack))
			return true;
	}
	//no se encontro el objetivo en esta rama
	return false;
}


void Greedy(vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost,
 unordered_map<char,int> &heuristicVal, char init, char goal){
 	//se definen estructuras de datos utiles
	unordered_map<char,char> backTrack;
	unordered_map<char,int> visited;
	priority_queue<pair<int, pair<char,char>>> nextN;
	//se inicializa nodo inicial
	backTrack[init]=init;
	visited[init]++;
	bool found = false;
	if(init==goal){
		printResult(nodes, cost, visited, backTrack, init, goal);
	}
	//se agregan todos los nodos hijos a una priorityqueue que retorna el elemento con menor valor en la heuristica
	for (int i = 0; i < graph[init].size(); ++i)
	{
		char childNode = graph[init][i];
		nextN.push({-heuristicVal[childNode], {childNode, init}});
	}
	//tomamos el siguiente valor en la priorityqueue y si no ha sido visitado revisamos si es el nodo objetivo en caso de serlo sale del ciclo
	//en caso contrario ingresa todos sus nodos hijos a la priorityqueue y lo considera expandido
	while(!nextN.empty()){
		pair<char,char> processedNode = nextN.top().second;
		nextN.pop();
		char expandedNode = processedNode.first;
		char parentNode = processedNode.second;
		if(visited[expandedNode] > 0){
			continue;
		}
		//se registra camino en backtrack
		backTrack[expandedNode] = parentNode;
		if(expandedNode == goal){
			found = true;
			break;
		}
		visited[expandedNode]++;
		//se agregan todos los nodos hijos a una priorityqueue que retorna el elemento con menor valor en la heuristica
		for (int i = 0; i < graph[expandedNode].size(); ++i){
			char childNode = graph[expandedNode][i];
			nextN.push({-heuristicVal[childNode], {childNode, expandedNode}});
		}
	}
	if(!found){
		cout<<"NO SE ENCONTRO RUTA"<<endl;
		return;
	}
	printResult(nodes, cost, visited, backTrack, init, goal);

}

void UCS(vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost, char init, char goal){
	//se definen estructuras utiles
	unordered_map<char,char> backTrack;
	unordered_map<char,int> visited;
	unordered_map<char,int> pathCost;
	priority_queue<pair<int, pair<char,char>>> nextN;
	bool found = false;
	//se establece nodo inicial
	backTrack[init]=init;
	visited[init]++;
	pathCost[init] = 0;
	if(init==goal){
		printResult(nodes, cost, visited, backTrack, init, goal);
	}
	//se agregan todos los nodos incluyendo el coste de la ruta a una priority queue, luego se obtendran primero los nodos con menor coste de ruta
	for (int i = 0; i < graph[init].size(); ++i)
	{
		char childNode = graph[init][i];
		nextN.push({-cost[init][childNode],{childNode, init}});
	}
	//ejecutara mientras queden elementos en la priorityqueue o haya encontrado el objetivo
	while(!nextN.empty()){
		//se obtienen datos del nodo
		int thisPathCost = -nextN.top().first;
		pair<char,char> processedNode = nextN.top().second;
		nextN.pop();
		char expandedNode = processedNode.first;
		char parentNode = processedNode.second;
		if(visited[expandedNode] > 0){
			continue;
		}
		//se registra el backtrack y el costo de la ruta
		pathCost[expandedNode] = thisPathCost;
		backTrack[expandedNode] = parentNode;
		if(expandedNode == goal){
			found = true;
			break;
		}
		visited[expandedNode]++;
		//se agregan todos los nodos incluyendo el coste de la ruta a una priority queue, luego se obtendran primero los nodos con menor coste de ruta
		for (int i = 0; i < graph[expandedNode].size(); ++i){
			char childNode = graph[expandedNode][i];
			nextN.push({-(pathCost[expandedNode] + cost[expandedNode][childNode]), {childNode, expandedNode}});
		}
	}
	if(!found){
		cout<<"NO SE ENCONTRO RUTA"<<endl;
		return;
	}
	printResult(nodes, cost, visited, backTrack, init, goal);

}

void Astar(vector<char> &nodes, unordered_map<char, vector<char>> &graph, unordered_map<char,unordered_map<char,int>> &cost,
 unordered_map<char,int> &heuristicVal, char init, char goal){
	unordered_map<char,int> visited;
	unordered_map<char,int> aStarScore;
	priority_queue<pair<int, tuple<char, vector<char>,int>>> nextN;
	bool found = false;
	aStarScore[init] = heuristicVal[init];
	vector<char> finalRoute;
	vector<char> route;
	route.push_back(init);
	nextN.push({-heuristicVal[init],{init, route, 0}});
	while(!nextN.empty()){
		int score = -nextN.top().first;
		tuple<char, vector<char>,int> nodeData = nextN.top().second;
		nextN.pop();
		char expandedNode = get<0>(nodeData);
		cout<<expandedNode<<" "<<score<<endl;
		if(visited[expandedNode] > 0 and !(score < aStarScore[expandedNode])){
			continue;
		}
		aStarScore[expandedNode] = score;
		vector<char> route = get<1>(nodeData);
		int pathCost = get<2>(nodeData);
		if(expandedNode == goal){
			found = true;
			finalRoute = route;
			break;
		}
		visited[expandedNode]++;
		for (int i = 0; i < graph[expandedNode].size(); ++i){
			char childNode = graph[expandedNode][i];
			vector<char> extendedRoute = route;
			extendedRoute.push_back(childNode);
			nextN.push({-(pathCost + cost[expandedNode][childNode] + heuristicVal[childNode]), {childNode, extendedRoute, pathCost + cost[expandedNode][childNode]}});
		}
	}
	if(!found){
		cout<<"NO SE ENCONTRO RUTA"<<endl;
		return;
	}
	printResult2(nodes, cost, visited, finalRoute);

}


