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

using namespace std;

/*
 * find
 */
int find(int v, vector<int> &pi) {
    if (v == pi[v]) {
        return v;
    } else {
        int rep = find(pi[v], pi);
        pi[v] = rep;
        return rep;
    }
}

/*
 * union_by_rank
 */
void union_by_rank(int u, int v, vector<int> &rank, vector<int> &pi) {
    if(rank[u] == rank[v]) {
        rank[u]++;
        int rep_v = find(v, pi);
        int rep_u = find(u, pi);
        pi[rep_v] = rep_u;
    } else if (rank[u] < rank[v]){
        int rep_v = find(v, pi);
        int rep_u = find(u, pi);
        pi[rep_u] = rep_v;
    } else {
        int rep_v = find(v, pi);
        int rep_u = find(u, pi);
        pi[rep_v] = rep_u;
    }
}

/*
 * kruskal
 */
vector<Edge> kruskal(vector<Vertex> &adjList, vector<Edge> &edgeList) {
    // Initialize the empty MST.
    vector<Edge> mst;
    
    // For each vertex, we need rank values and pi pointers (ints) for the
    // Disjoint Sets. Initialize the rank to 0 and pi to be the vertex labels.
    int n = adjList.size();
    vector<int> rank(n, 0);
    vector<int> pi(n);
    int position = 0;
    for (int i=0; i<pi.size(); i++) {
        pi[i] = adjList[i].label;
    }
    for(int j = 0; j < edgeList.size(); j++)
    {
    Edge minEdge = edgeList[0];
    for(int i = 0; i < edgeList.size(); i++) {
        if((edgeList[i].weight < minEdge.weight) && (find(edgeList[i].first.label, pi) != find(edgeList[i].second.label, pi))) {
            minEdge.weight = edgeList[i].weight;
            position = i;
        }
    }
    
    union_by_rank(minEdge.first.label, minEdge.second.label, rank, pi);
    mst.push_back(minEdge);
    }

    return mst;
}