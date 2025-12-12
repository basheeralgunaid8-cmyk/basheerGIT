#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int source;
    int destination;
    int weight;
};

class DisjointSetUnion
{

private:

    vector<int> parent;
    vector<int> rank;

public:

    DisjointSetUnion(int numberOfVertices) 
    {
        parent.resize(numberOfVertices);
        rank.resize(numberOfVertices);
        for (int vertex = 0; vertex < numberOfVertices; vertex++) 
        {
            parent[vertex] = vertex;
            rank[vertex] = 1;
        }
    }

    int findRoot(int vertex)
    {
        return (parent[vertex] == vertex) ? vertex : (parent[vertex] = findRoot(parent[vertex]));
    }

    void unionSets(int vertex1, int vertex2) 
    {
        int root1 = findRoot(vertex1);
        int root2 = findRoot(vertex2);
        if (root1 != root2) //If they're in different sets, merge them
        {
            if (rank[root1] < rank[root2])
            {

                parent[root1] = root2;// Attach smaller tree under larger tree
            }
            else if (rank[root1] > rank[root2]) 
            {
                parent[root2] = root1;// Attach smaller tree under larger tree
            }
            else 
            {
                parent[root2] = root1;// Trees are same height, attach either way
                rank[root1]++;// But increase rank since tree grew taller
            }
        }
    }
};

bool compareEdgesByWeight( Edge& firstEdge,  Edge& secondEdge)
{
    return firstEdge.weight < secondEdge.weight;
}

int kruskalsMinimumSpanningTree(int numberOfVertices, int adjacencyMatrix[][10]) 
{
    // Extract all edges from adjacency 
    vector<Edge> allEdges;

    for (int sourceVertex = 0; sourceVertex < numberOfVertices; sourceVertex++) 
    {
        for (int destinationVertex = sourceVertex + 1; destinationVertex < numberOfVertices; destinationVertex++)
        {
            if (adjacencyMatrix[sourceVertex][destinationVertex] != 0) 
            {
                Edge newEdge;
                newEdge.source = sourceVertex;
                newEdge.destination = destinationVertex;
                newEdge.weight = adjacencyMatrix[sourceVertex][destinationVertex];
                allEdges.push_back(newEdge);
            }
        }
    }

    // Sort edges by weight in ascending order "built in function iside algorithm 
    // to sort by ascending order
    sort(allEdges.begin(), allEdges.end(), compareEdgesByWeight);

    // Apply Kruskal's algorithm
    DisjointSetUnion dsu(numberOfVertices);
    int totalCost = 0;
    int edgesInMST = 0;

    cout << "Edges in Minimum Spanning Tree:\n";
    for (Edge& currentEdge : allEdges)
    {
        int root1 = dsu.findRoot(currentEdge.source);
        int root2 = dsu.findRoot(currentEdge.destination);
        cout << "Considering edge " << currentEdge.source << "-" << currentEdge.destination
            << " (weight " << currentEdge.weight << "): ";
        cout << "Root(" << currentEdge.source << ")= " << root1 << " , Root(" << 
            currentEdge.destination << ")= " << root2<<" ";

        if (dsu.findRoot(currentEdge.source) != dsu.findRoot(currentEdge.destination)) 
        {
            dsu.unionSets(currentEdge.source, currentEdge.destination);
            totalCost += currentEdge.weight;
            cout << "Vertex " << currentEdge.source << " - Vertex " << currentEdge.destination
                << " : Weight " << currentEdge.weight << endl;
            edgesInMST++;
            if (edgesInMST == numberOfVertices - 1)
                break;
        }
        else
        {
            cout << " -> REJECTED (creates cycle)" << endl;
        }
    }
    return totalCost;
}

int main() {
    int numberOfVertices = 10;

    // Adjacency matrix for the undirected graph (only MST edges shown)
    int adjacencyMatrix[10][10] =
    {
        // 0  1  2  3  4  5  6  7  8  
    { 0, 4, 0, 0, 0, 0, 0, 8, 0, 0},  // Vertex 0
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // Vertex 1
    { 0, 0, 0, 7, 0, 4, 0, 0, 2, 0},  // Vertex 2
    { 0, 0, 7, 0, 9, 0, 0, 0, 0, 0},  // Vertex 3
    { 0, 0, 0, 9, 0, 0, 0, 0, 0, 0},  // Vertex 4
    { 0, 0, 4, 0, 0, 0, 2, 0, 0, 0},  // Vertex 5
    { 0, 0, 0, 0, 0, 2, 0, 1, 6, 0},  // Vertex 6 ← Added 8-6 weight 6//I add this edge to show that 
    //the Kruskal's algorithm detect the cycle
    { 8, 0, 0, 0, 0, 0, 1, 0, 0, 0},  // Vertex 7
    { 0, 0, 2, 0, 0, 0, 6, 0, 0, 0},  // Vertex 8 ← Added 6-8 weight 6
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // Vertex 9
    };

    // Display adjacency matrix
    cout << "Adjacency Matrix:\n";
    for (int row = 0; row < numberOfVertices; row++) {
        for (int column = 0; column < numberOfVertices; column++) {
            cout << adjacencyMatrix[row][column] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int minimumSpanningTreeCost = kruskalsMinimumSpanningTree(numberOfVertices, adjacencyMatrix);
    cout << "\nTotal Minimum Spanning Tree Cost: " << minimumSpanningTreeCost << endl;

    system("pause>0");
    return 0;
}
