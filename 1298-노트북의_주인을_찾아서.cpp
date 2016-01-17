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
const double INF = 1e200;
const double EPSILON = 1e-8;
using namespace std;
vector<vector<bool> > adj;
vector<int> amatch;
vector<int> bmatch;
vector<bool> visited;
int n, m;
bool dfs(int here){
    if (visited[here]){ return false; }
    visited[here] = true;
    for (int dst = 0; dst < n; dst++){
        if (adj[here][dst]){
            if (bmatch[dst] == -1 || dfs(bmatch[dst])){
                amatch[here] = dst;
                bmatch[dst] = here;
                return true;
            }
        }
    }
    return false;
}
 
int bimatch(){
    amatch = vector<int>(n, -1);
    bmatch = vector<int>(n, -1);
    int size = 0;
    for (int start = 0; start < n; start++){
        visited = vector<bool>(n, false);
        if (dfs(start)){ size++; }
    }
    return size;
}
     
int main(){
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        vector<bool> vbuf;
        for (int j = 0; j < n; j++){
            vbuf.push_back(false);
        }
        adj.push_back(vbuf);
    }
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a][b] = true;
    }
    cout << bimatch() << endl;
}