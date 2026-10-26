
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// Harshit Pal
//25/Da/031

struct Edge {
    int u, v, weight;
};

void bellmanFord(int V, int E, vector<Edge>& edges, int source) {
    vector<long long> dist(V, LLONG_MAX);

    dist[source] = 0;

    // Relax all edges V - 1 times
    for (int i = 1; i <= V - 1; i++) {
        bool updated = false;

        for (const Edge& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int w = edge.weight;

            if (dist[u] != LLONG_MAX &&
                dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }

        // Stop early if no distance changes
        if (!updated)
            break;
    }

    // Detect a reachable negative-weight cycle
    for (const Edge& edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int w = edge.weight;

        if (dist[u] != LLONG_MAX &&
            dist[u] + w < dist[v]) {
            cout << "Graph contains a negative-weight cycle "
                 << "reachable from the source.\n";
            return;
        }
    }

    // Print shortest distances
    cout << "\nVertex\tShortest Distance from Source\n";

    for (int i = 0; i < V; i++) {
        cout << i << "\t";

        if (dist[i] == LLONG_MAX)
            cout << "Unreachable";
        else
            cout << dist[i];

        cout << endl;
    }

    cout << "\nNo reachable negative-weight cycle detected.\n";
}

int main() {
    int V, E;

    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    if (V <= 0 || E < 0) {
        cout << "Invalid number of vertices or edges.\n";
        return 0;
    }

    vector<Edge> edges(E);

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v
            >> edges[i].weight;

        if (edges[i].u < 0 || edges[i].u >= V ||
            edges[i].v < 0 || edges[i].v >= V) {
            cout << "Invalid vertex number.\n";
            return 0;
        }
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    if (source < 0 || source >= V) {
        cout << "Invalid source vertex.\n";
        return 0;
    }

    bellmanFord(V, E, edges, source);

    return 0;
}
