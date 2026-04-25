/*
 * CSC-301
 * kruskal.cpp
 * Spring 2026
 *
 * Partner 1:
 * Partner 2:
 * Date:
 */

#include "kruskal.hpp"
#include "algorithm"

using namespace std;

/*
 * find
 * Input: vertex label, parent vector
 * Return: int representing parent vertex label
 * Search the parent vector recursively until we find a vertex that is their own parent. 
 * This is the reprsentative of the component that v is in. Once the representative is found, 
 * assign that as the parent to each searched vertex (path compression)
 */
int find(int v, vector<int> &pi) {
    // It's a representative immediately return
    if (v == pi[v]) {
        return v;
    } else {
        // Find the representative of the parent
        int rep = find(pi[v], pi);
        // Assign the representative of it's component as the parent
        pi[v] = rep;
        return rep;
    }
}

/*
 * union_by_rank
 * Input: vertices from components being unioned, vector of ranks, vector of parents
 * Depending on the ranks of components being added, union the components and update the ranks if needed. 
 */
void union_by_rank(int u, int v, vector<int> &rank, vector<int> &pi) {
    // Find representatives of vertexes being unioned
    int rep_v = find(v, pi);
    int rep_u = find(u, pi);
    // Cases based on ranks of representatives
    if(rank[rep_u] == rank[rep_v]) {
        rank[rep_u]++;
        pi[rep_v] = rep_u;
    } else if (rank[rep_u] < rank[rep_v]){
        pi[rep_u] = rep_v;
    } else {
        pi[rep_v] = rep_u;
    }
}

/*
 * kruskal
 * Input: adjacency list, edge list
 * Return: Minimum spanning tree
 * Starts with all vertices as seperate forests. Select the minimum edge that lies in seperate components. Adds that edge
 * then unions the components. Repeats until we have a spanning tree
 */
vector<Edge> kruskal(vector<Vertex> &adjList, vector<Edge> &edgeList) {
    // Initialize the empty MST.
    vector<Edge> mst;
    
    // For each vertex, we need rank values and pi pointers (ints) for the
    // Disjoint Sets. Initialize the rank to 0 and pi to be the vertex labels.
    int n = adjList.size();
    vector<int> rank(n, 0);
    vector<int> pi(n);
    // fill in parent array with vertex labels
    for (int i=0; i<pi.size(); i++) {
        pi[i] = adjList[i].label;
    }
    // Find the minimum edge that's not contained in the same component
    for(int j = 0; j < pi.size()-1; j++) {
        double minWeight = INFINITY;
        int minIdx = -1;    
        // Search all edges
        for(int i = 0; i < edgeList.size(); i++) {
            if(edgeList[i].weight < minWeight && (find(edgeList[i].first.label, pi) != find(edgeList[i].second.label, pi))) {
                minIdx = i;
                minWeight = edgeList[i].weight;
            }
        }
        Edge minEdge = edgeList[minIdx];
        // Union components
        union_by_rank(minEdge.first.label, minEdge.second.label, rank, pi);
        mst.push_back(minEdge);
        // Add to mstNeighbors
        adjList[minEdge.first.label].mstNeighbors.push_back(minEdge.second.label);
        adjList[minEdge.second.label].mstNeighbors.push_back(minEdge.first.label);
    }

    return mst;
}