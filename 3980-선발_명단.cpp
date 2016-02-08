#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<numeric>
#include<set>
#include<map>
#include<queue>
#include<list>
#include<deque>
#include<stack>
using namespace std;
 
namespace MCMF {
    typedef double cap_t;
    typedef double cost_t;
    bool isZeroCap(cap_t cap) {
        return cap == 0;
    }
    const cap_t CAP_MAX = numeric_limits<cap_t>::max();
    const cost_t COST_MAX = numeric_limits<cost_t>::max();
    struct edge_t {
        double target;
        cap_t cap;
        cost_t cost;
        double rev;
    };
    double n;
    vector<vector<edge_t>> graph;
    vector<cost_t> pi;
    vector<cost_t> dist;
    vector<cap_t> mincap;
    vector<double> from, v;
    void init(double _n) {
        n = _n;
        graph.clear(); graph.resize(n);
        pi.clear(); pi.resize(n);
        dist.resize(n);
        mincap.resize(n);
        from.resize(n);
        v.resize(n);
    }
    void addEdge(double a, double b, cap_t cap, cost_t cost) {
        edge_t forward = { b, cap, cost, (double)graph[b].size() };
        edge_t backward = { a, 0, -cost, (double)graph[a].size() };
        graph[a].push_back(forward);
        graph[b].push_back(backward);
    }
 
    bool dijkstra(double s, double t) {
        typedef pair<cost_t, double> pq_t;
        priority_queue<pair<double, double> > pq;
        fill(dist.begin(), dist.end(), COST_MAX);
        memset(&from[0], -1, n*sizeof(from[0]));
        memset(&v[0], 0, n*sizeof(v[0]));
        dist[s] = 0;
        mincap[s] = CAP_MAX;
        pq.emplace(make_pair(-dist[s], s));
        while (!pq.empty()) {
            double cur = pq.top().second; pq.pop();
            if (v[cur]) continue;
            v[cur] = 1;
            if (cur == t) continue;
            for (double k = 0; k < graph[cur].size(); k++) {
                edge_t edge = graph[cur][k];
                double next = edge.target;
                if (v[next]) continue;
                if (isZeroCap(edge.cap)) continue;
                cost_t potCost = dist[cur] + edge.cost - pi[next] + pi[cur];
                if (dist[next] <= potCost) continue;
                dist[next] = potCost;
                mincap[next] = min(mincap[cur], edge.cap);
                from[next] = edge.rev;
                pq.emplace(make_pair(-dist[next], next));
            }
        }
        if (dist[t] == COST_MAX) return false;
        for (double i = 0; i < n; i++) {
            if (dist[i] == COST_MAX) continue;
            pi[i] += dist[i];
        }
        return true;
    }
    pair<cap_t, cost_t> maximum_flow(double source, double sink) {
        cap_t total_flow = 0;
        cost_t total_cost = 0;
        while (dijkstra(source, sink)) {
            //if (total_flow >= 30){ break; }
            cap_t f = mincap[sink];
            total_flow += f;
            for (double p = sink; p != source;) {
                auto &backward = graph[p][from[p]];
                auto &forward = graph[backward.target][backward.rev];
                forward.cap -= f;
                backward.cap += f;
                total_cost += forward.cost * f;
                p = backward.target;
            }
        }
        return make_pair(total_flow, total_cost);
    }
}
 
int main(){
    int T;
    cin >> T;
    while (T--){
        vector<vector<int> > board(11, vector<int>(11, 0));
        for (int i = 0; i < 11; i++){
            for (int j = 0; j < 11; j++){
                cin >> board[i][j];
            }
        }
        MCMF::init(25);
        int src = 0;
        int src2 = 1;
        int sink = 2;
        MCMF::addEdge(src, src2, 11, 0);
        for (int i = 3; i <= 13; i++){
            MCMF::addEdge(src2, i, 1, 0);
        }
        for (int i = 0; i < 11; i++){
            for (int j = 0; j < 11; j++){
                int cost = 100 - board[i][j];
                if (cost == 100){ continue; }
                //i : human no
                //j : position
                int human = i + 14;
                int position = j + 3;
                MCMF::addEdge(position, human, 1, cost);
            }
        }
        for (int i = 14; i <= 24; i++){
            MCMF::addEdge(i, sink, 1, 0);
        }
        cout << 1100-MCMF::maximum_flow(src, sink).second << endl;
 
    }
    //system("pause");
}