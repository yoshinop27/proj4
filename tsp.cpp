/*
 * CSC-301
 * tsp.cpp
 * Spring 2026
 *
 * Partner 1:
 * Partner 2:
 * Date:
 */

#include "tsp.hpp"
#include <stack>

using namespace std;

/*
 * tsp
 * Input: adjacency list, start vertex
 * Return: Vector of vertices denoting tour
 * Use DFS to traverse our tree building a vector of unique vertices in order of how we visited them,
 * adding the start vertice at the end to complete the cycle.
 */
vector<int> tsp(vector<Vertex> &adjList, Vertex &start) {
    // Create the empty tour.
    vector<int> tour;
    
    // Create the vector for tracking visited during the DFS.
    int n = adjList.size();
    vector<bool> visited(n, false); 
    // perform DFS
    stack<Vertex> st;
    // Initialize our stack with start 
    st.push(start);
    visited[start.label] = true;
    // Run while our stack is non empty and DFS is going
    while (!st.empty()) {
        Vertex cur = st.top();
        st.pop();
        // Add all unviisted neighbors to the stack
        for (int i=0; i<cur.mstNeighbors.size(); i++){
            int neighborIdx = cur.mstNeighbors[i];
            if (!visited[neighborIdx]){
                st.push(adjList[neighborIdx]);
                visited[neighborIdx] = true;
            }
        }
        tour.push_back(cur.label);
    }
    tour.push_back(start.label);

    return tour;
}