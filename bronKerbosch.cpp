#include<bits/stdc++.h>
using namespace std;

class BronKerbosch {
private:
    unordered_map<int, set<int>> graph;
    vector<int> degeneracy_order;

    void bronKerboschPivot(set<int> P, set<int> R, set<int> X) {
        if (P.empty() && X.empty()) {
            cout << "Maximal Clique: { ";
            for (int v : R) cout << v << " ";
            cout << "}" << endl;
            return;
        }
        
        int pivot = *P.begin();
        for (int v : P) {
            if (graph[pivot].size() < graph[v].size()) {
                pivot = v;
            }
        }
        
        set<int> P_copy = P;
        for (int v : P_copy) {
            if (graph[pivot].count(v)) continue;
            
            set<int> P_new, X_new;
            for (int neighbor : P) {
                if (graph[v].count(neighbor)) {
                    P_new.insert(neighbor);
                }
            }
            for (int neighbor : X) {
                if (graph[v].count(neighbor)) {
                    X_new.insert(neighbor);
                }
            }
            
            set<int> R_new = R;
            R_new.insert(v);
            bronKerboschPivot(P_new, R_new, X_new);
            
            P.erase(v);
            X.insert(v);
        }
    }
    
public:
    void addEdge(int u, int v) {
        graph[u].insert(v);
        graph[v].insert(u);
    }
    
    void computeDegeneracyOrder() {
        unordered_map<int, int> degree;
        set<pair<int, int>> degSet;
        for (auto& node : graph) {
            degree[node.first] = node.second.size();
            degSet.insert({node.second.size(), node.first});
        }
        while (!degSet.empty()) {
            int v = degSet.begin()->second;
            degeneracy_order.push_back(v);
            degSet.erase(degSet.begin());
            for (int neighbor : graph[v]) {
                if (degSet.count({degree[neighbor], neighbor})) {
                    degSet.erase({degree[neighbor], neighbor});
                    degree[neighbor]--;
                    degSet.insert({degree[neighbor], neighbor});
                }
            }
        }
    }
    
    void findCliques() {
        computeDegeneracyOrder();
        unordered_map<int, int> orderIndex;
        for (int i = 0; i < degeneracy_order.size(); i++) {
            orderIndex[degeneracy_order[i]] = i;
        }
        for (int v : degeneracy_order) {
            set<int> P, X;
            for (int neighbor : graph[v]) {
                if (orderIndex[neighbor] > orderIndex[v]) {
                    P.insert(neighbor);
                } else {
                    X.insert(neighbor);
                }
            }
            bronKerboschPivot(P, {v}, X);
        }
    }
};

int main() {
    BronKerbosch bk;
    bk.addEdge(1, 2);
    bk.addEdge(1, 3);
    bk.addEdge(2, 3);
    bk.addEdge(2, 4);
    bk.addEdge(3, 4);
    bk.addEdge(4, 5);
    
    bk.findCliques();
    return 0;
}
