#include<bits/stdc++.h>
using namespace std;

class MaximalClique {
private:
    unordered_map<int, set<int>> graph;
    set<int> Q;

public:
    void addEdge(int u, int v) {
        graph[u].insert(v);
        graph[v].insert(u);
    }

    void expand(set<int> SUBG, set<int> CAND) {
        if (SUBG.empty()) {
            // A maximal clique is found
            cout << "Clique: { ";
            for (int v : Q) cout << v << " ";
            cout << "}" << endl;
            return;
        }
        
        int u = -1, maxDegree = -1;
        for (int v : SUBG) {
            int degree = 0;
            for (int neighbor : CAND) {
                if (graph[v].count(neighbor)) {
                    degree++;
                }
            }
            if (degree > maxDegree) {
                maxDegree = degree;
                u = v;
            }
        }
        
        // Set EXTU = CAND - N(u)
        set<int> EXTU;
        for (int v : CAND) {
            if (!graph[u].count(v)) {
                EXTU.insert(v);
            }
        }
        
        while (!EXTU.empty()) {
            int q = *EXTU.begin();
            EXTU.erase(q);
            Q.insert(q);
            
            set<int> SUBGq, CANDq;
            for (int v : SUBG) {
                if (graph[q].count(v)) {
                    SUBGq.insert(v);
                }
            }
            for (int v : CAND) {
                if (graph[q].count(v)) {
                    CANDq.insert(v);
                }
            }
            
            expand(SUBGq, CANDq);
            Q.erase(q);
            CAND.erase(q);
        }
    }

    void findCliques() {
        set<int> allNodes;
        for (auto& pair : graph) {
            allNodes.insert(pair.first);
        }
        expand(allNodes, allNodes);
    }
};

int main() {
    MaximalClique mc;
    mc.addEdge(1, 2);
    mc.addEdge(1, 3);
    mc.addEdge(2, 3);
    mc.addEdge(2, 4);
    mc.addEdge(3, 4);
    mc.addEdge(4, 5);
    
    mc.findCliques();
    return 0;
}
