#include<bits/stdc++.h>

using namespace std;

class CliqueFinder {
public:
    int n;
    vector<set<int>> adj; 
    vector<int> order;    

    CliqueFinder(int vertices) {
        n = vertices;
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].insert(v);
        adj[v].insert(u);
    }

    void sortVerticesByDegree() {
        vector<pair<int, int>> degree(n);
        for (int i = 0; i < n; i++)
            degree[i] = {adj[i].size(), i};

        sort(degree.begin(), degree.end());
        for (int i = 0; i < n; i++)
            order.push_back(degree[i].second);
    }

    void update(int i, set<int> C) {
        if (i == n) {
            printClique(C);
            return;
        }

        int v = order[i]; // Current vertex in sorted order
        set<int> newC;

        for (int u : C) {
            if (adj[v].count(u)) // Intersection with neighborhood of v
                newC.insert(u);
        }

        if (!newC.empty()) update(i + 1, newC);

        if (isMaximal(C, v)) {
            set<int> save = subtractSet(C, adj[v]);
            C.insert(v);
            update(i + 1, C);
            C.erase(v);
            for (int u : save) C.insert(u);
        }
    }

    bool isMaximal(set<int> &C, int v) {
        for (int u : adj[v]) {
            if (C.count(u) == 0) return false;
        }
        return true;
    }

    set<int> subtractSet(set<int> &A, set<int> &B) {
        set<int> result;
        for (int x : A) {
            if (B.count(x) == 0) result.insert(x);
        }
        return result;
    }

    void printClique(set<int> &C) {
        cout << "{ ";
        for (int v : C) cout << v << " ";
        cout << "}" << endl;
    }

    void findCliques() {
        sortVerticesByDegree();
        set<int> C = {order[0]};
        update(1, C);
    }
};

int main() {
    int n = 5; 
    CliqueFinder cf(n);

    cf.addEdge(0, 1);
    cf.addEdge(1, 2);
    cf.addEdge(2, 3);
    cf.addEdge(3, 4);
    cf.addEdge(4, 0);
    cf.addEdge(1, 3);
    cf.addEdge(2, 4);

    cf.findCliques();
    return 0;
}
