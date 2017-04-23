#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

typedef pair<int, int> p;

int D[22][10010];
vector<p> adj[10010];	// adjacent matrix

namespace std{
	template <> class greater<p>{
		public :
			bool operator()(const p &lhs, const p &rhs) const{
				return lhs.first > rhs.first;
			}
	};
};
priority_queue< p, vector<p>, greater<p> > q;

long long min(long long a, long long b){ return (a>b)?b:a;}

int main(void)
{
	int N;	//node
	int M;	//edge
	int K;	//road

	int x, y;
	long long time;

	scanf("%d %d %d", &N, &M, &K);

	//initialize
	for(int k=0; k<=K; k++)
		for(int i=0; i<=N; i++) D[k][i] = 0xfffffff;

	for(int i=1; i<=M; i++){
		scanf("%d %d %lld", &x, &y, &time);		
		adj[x].push_back(make_pair(y, time));
		adj[y].push_back(make_pair(x, time));
	}

	for(int k=0; k<=K; k++){
		D[k][1] = 0;
		q.push(make_pair(D[k][1], 1));
		while(!q.empty()){
			int v = q.top().second; q.pop();
			for(int i=0; i<adj[v].size(); i++){
				int u = adj[v][i].first;
				int time = adj[v][i].second;
				if(k==0){	//common dijkstra
					if(D[k][v] + time < D[k][u]){
						D[k][u] = D[k][v] + time;
						q.push(make_pair(D[k][u], u));
					}
				}
				else{
					if(D[k][v] + time < D[k][u] || D[k-1][v] < D[k][u]){
						D[k][u] = min(D[k][v] + time, D[k-1][v]);
						q.push(make_pair(D[k][u], u));
					}
				}
			}
		}
	}

	cout<<D[K][N]<<endl;


	return 0;
}
