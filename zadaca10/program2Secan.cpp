#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int findShortestPath(vector<vector<int>>& graph, int start, int end) {      

    int numVertices = graph.size();   
    vector<int> distance(numVertices, 1e9);  
    distance[start] = 0; 

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
    pq.push(make_pair(0, start)); 

    while (!pq.empty()) { 
        int u = pq.top().second; 
        pq.pop(); 
        for (int v = 0; v < numVertices; ++v) { 
            if (graph[u][v] != -1 && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) { 
                distance[v] = distance[u]+ graph[u][v];
                pq.push(make_pair(distance[v], v));
            }
        }
    }

    return distance[end]; 
}

int main(){
    int N, R, S, F;
    cin >> N >> R >> S >> F;
    vector<vector<int>> matrica(R, vector<int>(3));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> matrica[i][j];
        }
    }

    // Matrica susjedstva
    vector<vector<int>> adjMatrix(N + 1, vector<int>(N + 1, -1));
    for (int i = 0; i < R; i++) {
        adjMatrix[matrica[i][0]][matrica[i][1]] = matrica[i][2]+12;
        adjMatrix[matrica[i][1]][matrica[i][0]] = matrica[i][2]+12;
    }

    int totalCost = findShortestPath(adjMatrix, S, F);
    
    cout << totalCost << endl;

    return 0;
}


