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
#define INF 987654321
using namespace std;
 
class edge {
public:
    int target;
    int capacity; 
    int cost;
    edge(){}
    edge(int target, int capacity, int cost) :
        target(target), capacity(capacity), cost(cost){}
};
namespace mcmf
{
    typedef int cap_t; 
    typedef int cost_t; 
    int SIZE;
    int n;
    vector<pair<edge, int> > g;
    vector<int> p;
    vector<int> dist;
    vector<int> mincap;
    vector<int> pi;
    vector<int> pth;
    vector<int> from;
    vector<bool> visited;
    void init(const vector<vector<edge> >& graph, int size){
        g.clear();
        SIZE = 0;
        n = 0;
        p.clear();
        dist.clear();
        mincap.clear();
        pi.clear();
        pth.clear();
        from.clear();
        visited.clear();
 
        n = size;
        SIZE = size;
        for (int i = 0; i < size; i++){
            p.push_back(-1);
            dist.push_back(0);
            mincap.push_back(0);
            pi.push_back(0);
            pth.push_back(0);
            from.push_back(0);
            visited.push_back(false);
        }
        g.clear();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                int next = graph[i][j].target;
                edge tmp = graph[i][j];
                g.push_back(make_pair(tmp, p[i]));
                p[i] = g.size() - 1;
                tmp.target = i;
                tmp.capacity = 0;
                tmp.cost = -tmp.cost;
                g.push_back(make_pair(tmp, p[next]));
                p[next] = g.size() - 1;
            }
        }
    }
    int dijkstra(int src, int t){
        priority_queue<pair<int, int> > pq;
        for (int i = 0; i < n; i++){
            dist[i] = INF;
            mincap[i] = 0;
            visited[i] = false;
        }
        dist[src] = 0;
        mincap[src] = INF;
        pq.push(make_pair(0, src));
        while (!pq.empty()){
            int cost = -pq.top().first;
            int here = pq.top().second;
            pq.pop();
            if (visited[here]){ continue; }
            visited[here] = true;
            for (int i = p[here]; i != -1; i = g[i].second) {
                int next = g[i].first.target;
                if (visited[next]) { continue; }
                if (g[i].first.capacity == 0) { continue; }
                cost_t pot = dist[here] + pi[here] - pi[next] + g[i].first.cost;
                if (dist[next] > pot) {
                    dist[next] = pot;
                    mincap[next] = min(mincap[here], g[i].first.capacity);
                    pth[next] = i;
                    from[next] = here;
                    pq.push(make_pair(-dist[next], next));
                }
            }
        }
        for (int i = 0; i < n; i++) { pi[i] += dist[i]; }
        return dist[t] != INF;
    }
    pair<cap_t, cost_t> maximum_flow(int source, int sink) {
        for (int i = 0; i < pi.size(); i++){ pi[i] = 0; }
        cap_t total_flow = 0;
        cost_t total_cost = 0;
        while (dijkstra(source, sink)) {
            cap_t f = mincap[sink];
            total_flow += f;
            for (int i = sink; i != source; i = from[i]) {
                g[pth[i]].first.capacity -= f;
                g[pth[i] ^ 1].first.capacity += f;
                total_cost += g[pth[i]].first.cost * f;
            }
        }
        return make_pair(total_flow, total_cost);
    }
} 
 
int main() {
    int v, e;
    while (cin>>v>>e){
        vector<vector<edge> > graph;
        for (int i = 0; i < 4*v; i++){ vector<edge> vbuf; graph.push_back(vbuf); }
        for (int i = 0; i < e; i++){
            int start;
            int end;
            int cost;
            cin >> start >> end >> cost;
            graph[start * 2 + 1].push_back(edge(end * 2, 1, cost));
        }
 
        //0 : source, 1 : sink
        for (int i = 2; i < v; i++){
            graph[i * 2].push_back(edge(i * 2 + 1, 1, 0));
        }
        graph[2].push_back(edge(2 + 1, 2, 0));
        graph[v * 2].push_back(edge(v * 2 + 1, 2, 0));
        graph[1].push_back(edge(2, 2, 0));
        graph[2 * v + 1].push_back(edge(2 * v + 1 + 1, 2, 0));
        mcmf::init(graph, 2 * v + 1 + 2);
        pair<int, int> ans = mcmf::maximum_flow(1, 2 * v + 1 + 1);
        cout << ans.second << endl;
 
    }
}