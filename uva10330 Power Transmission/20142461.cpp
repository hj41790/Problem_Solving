#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <climits>

#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;

typedef struct node{
	int color;
	int pred;
}node;

int start, target;
int C[210][210];	//capacity
node R[210];		//regulators

queue<int> q;

void BFS();

int main(void)
{
	int N, M, B, D;
	int cap, maxflow;
	
	while(1){
	
		//initial
		for(int i=0; i<210; i++)
			for(int j=0; j<210; j++)
				C[i][j]=0;

		if(scanf("%d", &N)!=1) break;
		start = 0; target = 2*N+1;
		for(int i=1; i<=N; i++){
			scanf("%d", &cap);
			C[2*i-1][2*i] = cap;
		}
		
		scanf("%d", &M);
		while(M--){
			int i, j;
			scanf("%d %d %d", &i, &j, &cap);
			C[2*i][2*j-1] = cap;
		}

		scanf("%d %d", &B, &D);
		while(B--){
			int tmp;
			scanf("%d", &tmp);
			C[start][2*tmp-1] = INT_MAX;
		}
		while(D--){
			int tmp;
			scanf("%d", &tmp);
			C[2*tmp][target] = INT_MAX;
		}
		
		maxflow = 0;
		while(1){
			int index = target; 
			int minC = INT_MAX;

			BFS();
			if(R[target].color==WHITE) break;

			while(index!=start){
				int tmp = C[R[index].pred][index];
				minC = (minC<tmp)?minC:tmp;
				index = R[index].pred;
			}
			maxflow += minC;

			index = target;
			while(index!=start){
				C[R[index].pred][index] -= minC;
				C[index][R[index].pred] += minC;
				index = R[index].pred;
			}
		}

		printf("%d\n", maxflow);
	}

	return 0;
}

void BFS()
{
	for(int i=0; i<=target; i++){
		R[i].color = WHITE;
		R[i].pred = 0;
	}

	R[0].color = GRAY;
	R[0].pred = 0;
	q.push(0);

	while(!q.empty()){
		int u = q.front(); q.pop();
		if(u==target) break;
		for(int i=1; i<=target; i++){
			if(C[u][i]>0 && R[i].color==WHITE){
				R[i].color = GRAY;
				R[i].pred = u;
				q.push(i);
			}
		}
		R[u].color = BLACK;
	}
	while(!q.empty()) q.pop();
}

