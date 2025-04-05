#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>

using namespace std;

// an edge between two nodes with weight
struct Edge {
    char node1, node2;
    int weight;
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

vector<Edge> BUCKET;
set<char> visited; //set of nodes
unordered_map<char, vector<Edge>> adjList;  // graph

//get the smallest weight to unvisited node
Edge GET_BEST_EDGE() {
    while (!BUCKET.empty()) {
        pop_heap(BUCKET.begin(), BUCKET.end(), greater<Edge>());
        //deleting element
        Edge best = BUCKET.back();
        BUCKET.pop_back();

        //determine that in the MST
        if (visited.find(best.node1) == visited.end() || visited.find(best.node2) == visited.end()) {
            return best;
        }
    }
    return { '0', '0', -1 }; // NIL edge
}

//algorithm prim's 
void MST_PRIM(char start) {
    vector<Edge> MST_EDGES;
    int TOTAL_WEIGHT = 0;
    
    //adding all edges from the start node to hte heap
    for (auto& edge : adjList[start]) {
        BUCKET.push_back(edge);
    }
    make_heap(BUCKET.begin(), BUCKET.end(), greater<Edge>());


    //getting the minimum weight until no remain
    Edge E = GET_BEST_EDGE();
    while (E.weight != -1) {
        char n1 = E.node1, n2 = E.node2;
        visited.insert(n1);
        visited.insert(n2);
        TOTAL_WEIGHT += E.weight;
        MST_EDGES.push_back(E);


        // add all together 
        for (auto& edge : adjList[n1]) BUCKET.push_back(edge);
        for (auto& edge : adjList[n2]) BUCKET.push_back(edge);
        make_heap(BUCKET.begin(), BUCKET.end(), greater<Edge>());

        E = GET_BEST_EDGE();
    }
    // output 
    cout << "MST has a weight of " << TOTAL_WEIGHT << " and consists of these edges:" << endl;
    for (const auto& edge : MST_EDGES) {
        cout << edge.node1 << " - " << edge.node2 << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string nodes;
    int edgeCount;
    infile >> nodes >> edgeCount;

    char n1, n2;
    int weight;
    //reading edges and add it to list
    while (infile >> n1 >> n2 >> weight) {
        adjList[n1].push_back({ n1, n2, weight });
        adjList[n2].push_back({ n2, n1, weight });
    }
    // run the prim's algorithm
    MST_PRIM(nodes[0]);
    return 0;
}
