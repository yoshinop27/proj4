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
 * Input: Cost vector, Visited vector
 * Return: Minimum vertex index
 * Scan the vector and select the minimum cost vertice that hasnt been visited yet
 */
int getMin(vector<double> &cost, vector<bool> &visited) {
  double minCost = INFINITY;
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
 * Input: visited vector
 * Return: boolean if empty or not
 * Scan the vector to see if there are any unvisited
 */
bool isEmpty(vector<bool> &visited) {
  for (int i = 0; i < visited.size(); i++) {
    if (visited[i] == false) {
      return false;
    }
  }
  return true;
}

/*
 * prim
 * Input: Adjacency List, Adjacency Matrix
 * Return: vector of edges denoting MST
 * Start with a vertex, denote this as our tree. We then add the minimum edge that branches outwards from our tree. 
 * Repeat this process until we have a spanning tree.
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
  for (int k = 0; k < n; k++) {
    // Get closest unvisited vertice
    int vtxLabel = getMin(cost, visited);
    // Create edges and add to tree
    if (k != 0) {
      auto i1 = prev[vtxLabel];
      auto v1 = adjList[vtxLabel];
      auto c1 = cost[vtxLabel];
      auto v2 = adjList[i1];
      Edge e = Edge(adjList[prev[vtxLabel]], adjList[vtxLabel], cost[vtxLabel]);
      mst.push_back(e);
      adjList[vtxLabel].mstNeighbors.push_back(prev[vtxLabel]);
      adjList[prev[vtxLabel]].mstNeighbors.push_back(vtxLabel);
    }
    visited[vtxLabel] = true;
    // Determine if there's any vertices on the other side of the cut with a lower cost from current vertex
    for (int i = 0; i < n; i++) {
      if (cost[i] > adjMat[vtxLabel * n + i]) {
        cost[i] = adjMat[vtxLabel * n + i];
        prev[i] = vtxLabel;
      }
    }
  }
  return mst;
}
