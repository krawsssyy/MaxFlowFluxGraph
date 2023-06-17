#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#define INF 65537
using namespace std;


int bfs(int s, int t, vector<int>& parent, vector<vector<int>> adj, vector<vector<int>> capacity) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({ s, INF });

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next = 0; next < adj[cur].size(); next++) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({ next, new_flow });
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, int n, vector<vector<int>> adj, vector<vector<int>> capacity) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent, adj, capacity)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


int main(int argc, char** argv) {
	ifstream f(argv[1]);
	ofstream g(argv[2]);
    int V, E;
    string line;
    getline(f, line);
    V = stoi(line.substr(0, line.find(' ')));
    E = stoi(line.substr(line.find(' '), line.length() - 1));
    vector<vector<int>> capacity(V);
    vector<vector<int>> adj(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            capacity[i].emplace_back(0);
            adj[i].emplace_back(0);
        }
    }
    for (int i = 0; i < E; i++) {
        getline(f, line);
        int n1 = stoi(line.substr(0, line.find(' ')));
        line.erase(line.begin(), line.begin() + line.find(' ') + 1);
        int n2 = stoi(line.substr(0, line.find(' ')));
        int c = stoi(line.substr(line.find(' '), line.length() - 1));
        adj[n1][n2] = adj[n2][n1] = 1;
        capacity[n1][n2] = c;
    }
    g << maxflow(0, V - 1, V, adj, capacity);
	g.close();
	f.close();
	return 0;
}