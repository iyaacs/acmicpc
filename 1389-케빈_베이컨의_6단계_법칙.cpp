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
#define INF 987654321
int solve(vector<vector<int> >& board){
    int N=board.size();
    for(int k=0;k<N;k++){
        for(int i=0; i<N;i++){
            for(int j=0;j<N;j++){
                if(board[i][j]>board[i][k]+board[k][j]){
                    board[i][j]=board[i][k]+board[k][j];
                }
            }
        }
    }
    int mmin=INF;
    int ret=0;
    for(int i=0; i<N;i++){
        int ssum=0;
        for(int j=0;j<N;j++){
           // cout<<board[i][j]<<" ";
            ssum+=board[i][j];
        }
       // cout<<ssum<<endl;
        if(ssum<mmin){ret=i;mmin=ssum;}
    }
    return ret+1;
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int> > board(N,vector<int>(N,INF));
    for(int i=0; i<M;i++){
        int a,b;
        cin>>a>>b;
        a--;b--;
        board[a][b]=1;
        board[b][a]=1;
    }
    cout<<solve(board)<<endl;
}