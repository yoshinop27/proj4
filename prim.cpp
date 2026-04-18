/*
 * CSC-301
 * prim.cpp
 * Spring 2026
 *
 * Partner 1:
 * Partner 2:
 * Date:
 **/
#include "prim.hpp"
#include <cmath>
#include <limits>

using namespace std;

/*
 * getMin
 */
int getMin(vector<double> &cost, vector<bool> &visited) {
    int minCost = INFINITY;
    int minCostIdx = -1;
    // Find the unvisited vertex with the smallest cost
    for (int i = 0; i < cost.size(); i++) {
        if (!visited[i] && minCost > cost[i]) {
            minCost = cost[i];
            minCostIdx = i;
        }
    }
    return minCostIdx;
}

/*
 * isEmpty
 */
bool isEmpty(vector<bool> &visited) {
    for(int i = 0; i < visited.size(); i++) {
        if(visited[i] == false) {
            return false;
        }
    }
    return true;
}

/*
 * prim
 */
vector<Edge> prim(vector<Vertex> &adjList, vector<double> &adjMat) {
    // Initialize the empty MST.
    vector<Edge> mst;
    
    // For each vertex, we need a visited flag, a 'cost' for Prim's, and the
    // prev values to track the MST. Store these in seperate vectors.
    int n = adjList.size();
    vector<bool> visited(n, false);
    vector<double> cost(n, numeric_limits<double>::infinity());
    vector<int> prev(n, -1);

    // Set start vertex
    cost[0] = 0;
    prev[0] = 0;

    // Run while the mst is not size n-1
    for (int k=0; k<n-1; k++) {

        int vtxLabel = getMin(cost, visited);
        if (k != 0){
            Edge e = Edge(adjList[prev[vtxLabel]], adjList[vtxLabel], cost[vtxLabel]);
            printf("%f", e.weight);
            //mst.push_back(e);
        }
        visited[vtxLabel] = true;
        for (int i = 0; i<n; i++) {
            if (cost[i] > adjMat[vtxLabel*n+i]) {
                cost[i] = adjMat[vtxLabel*n+i]; 
                prev[i] = vtxLabel;
            }
        }
     }
    return mst;
}        
    
            
    