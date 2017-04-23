#include <iostream>
#include <cstdio>
#include <stack>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NEVER 3

using namespace std;

typedef struct node{

	int color;
	int pred;
	int d_time;
	int f_time;
	int scc;

}node;

node *V[110];
int W[110][110];
int R[110][110];	//reverse graph

int scc_in[110];
int scc_out[110];

int num_node, timecount;
int p1_count, p2_count, SCC;

void make_scc();
void dfs_revisit(int);
int dfs_max();
void dfs_visit(int);
int check_never();

stack<int> nodestack;

int main()
{
	int x;

	scanf("%d", &num_node);

	//initialize
	for(int i=1; i<=num_node; i++){		
		V[i] = new node();
		for(int j=1; j<=num_node; j++){
			if(i==j) {
				W[i][j] = 0;
				R[i][j] = 0;
			}
			else {
				W[i][j] = 0xffff;
				R[i][j] = 0xffff;
			}
		}
	}

	for(int i=1; i<=num_node; i++){
		while(1){
			scanf("%d", &x);
			if(x==0) break;
			W[i][x] = 1;
			R[x][i] = 1;
		}
	}

	p1_count = 0;

	while(1){
		int max = dfs_max();

		for(int i=1; i<=num_node; i++){
			if(V[i]->color != NEVER){
				V[i]->color = WHITE;
				V[i]->pred = i;
			}
		}
		timecount = 0;
		dfs_visit(max);
		for(int i=1; i<=num_node; i++){
			if(V[i]->color==BLACK) V[i]->color = NEVER;
		
		}

		p1_count++;

		if(check_never()) break;
	}

	printf("%d\n", p1_count);

	//p2
	p2_count = 0;

	while(!nodestack.empty()) nodestack.pop();
	//dfs
	for(int j=1; j<=num_node; j++){
		V[j]->color = WHITE;
		V[j]->pred = j;
	}
	timecount = 0;
	for(int i=1; i<=num_node; i++)
		if(V[i]->color==WHITE) dfs_visit(i);

	// reverse dfs
	make_scc();

	for(int i=0; i<SCC; i++){
		scc_in[i] = 0;
		scc_out[i] = 0;
	}
	for(int i=1; i<=num_node; i++){
		int tmp = V[i]->scc;
		for(int j=1; j<=num_node; j++){
			if(tmp != V[j]->scc && W[i][j]==1)
				scc_out[tmp]++;
			if(tmp != V[j]->scc && R[i][j]==1)
				scc_in[tmp]++;
		}
	}

	int in_zero=0, out_zero=0;
	for(int i=0; i<SCC; i++){
		if(scc_in[i]==0) in_zero++;
		if(scc_out[i]==0) out_zero++;
	}

	p2_count = (in_zero>=out_zero)? in_zero:out_zero;

	printf("%d\n", (SCC==1)? 0 : p2_count);


	return 0;

}

void make_scc()
{
	int index;

	for(int j=1; j<=num_node; j++){
		V[j]->color = WHITE;
		V[j]->pred = j;
	}

	timecount = 0;
	SCC = 0;

	while(!nodestack.empty()){
		index = nodestack.top();	
		nodestack.pop();
		if(V[index]->color!=WHITE) continue;
		dfs_revisit(index);
		SCC++;
	}

}

int dfs_max()
{
	int max = 0, index;
	for(int i=1; i<=num_node; i++){
		for(int j=1; j<=num_node; j++){
			if(V[j]->color != NEVER){
				V[j]->color = WHITE;
				V[j]->pred = j;
			}
		}
		timecount = 0;

		if(V[i]->color == WHITE) {
			dfs_visit(i);
			if(max < V[i]->f_time - V[i]->d_time){
				max = V[i]->f_time - V[i]->d_time;
				index = i;
			}
		}
	}

	return index;
}

void dfs_revisit(int u)
{
	V[u]->color = GRAY;	//gray
	timecount += 1;
	V[u]->d_time = timecount;

	for(int i=1; i<=num_node; i++){
		if(R[u][i]==1 && V[i]->color==WHITE){
			V[i]->pred = u;
			dfs_revisit(i);
		}
	}

	V[u]->color = BLACK;
	timecount += 1;
	V[u]->f_time = timecount;
	V[u]->scc = SCC;
}

void dfs_visit(int u)
{
	V[u]->color = GRAY;	//gray
	timecount += 1;
	V[u]->d_time = timecount;

	for(int i=1; i<=num_node; i++){
		if(W[u][i]==1 && V[i]->color==WHITE){
			V[i]->pred = u;
			dfs_visit(i);
		}
	}

	V[u]->color = BLACK;
	timecount += 1;
	V[u]->f_time = timecount;
	nodestack.push(u);
}

int check_never()
{
	int check = 1;
	for(int i=1; i<=num_node; i++)
		if(V[i]->color != NEVER){
			check = 0;
			break;
		}

	return check;
}
