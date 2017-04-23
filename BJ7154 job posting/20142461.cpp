#include <iostream>
#include <vector>
#include <cstdio>
#include <climits>
#include <queue>

#define START 0
#define TARGET 1

using namespace std;

typedef struct node{
	int to;
	int capacity;
	int	cost;
	node *reverse;

	node(int x, int y, int z){
		to = x;
		capacity = y;
		cost = z;
	}
}node;

int satisfaction[4][5] = {	{0,  0,  0,  0, 0},
							{0,  -4,  -3,  -2, -1},
							{0,  -8,  -7,  -6, -5},
							{0, -12, -11, -10, -9}};

vector<node*> edgelist[220]; // s, t, jobs, students maximum size

int main()
{
	int n_job, n_student;
	int s_job = 2;
	int s_student;
	int mincost = 0;

	int nodesize=0;

	while(1){
		scanf("%d %d", &n_job, &n_student);
		if(!n_job && !n_student) break;

		//initial
		for(int i=0; i<nodesize; i++)
			while(!edgelist[i].empty()) edgelist[i].pop_back();
		mincost = 0;

		s_job = 2;
		s_student = s_job + n_job;
		nodesize = n_job + n_student + 2;

		// job -> target edge
		for(int i=0; i<n_job; i++){
			int tmp;
			scanf("%d", &tmp);
			node *n = new node(TARGET, tmp, 0);
			node *r = new node(i+s_job, 0, 0);
			
			n->reverse = r;
			r->reverse = n;

			edgelist[i + s_job].push_back(n);
			edgelist[TARGET].push_back(r);
		}

		for(int i=0; i<n_student; i++){
			// make start -> student edge
			node *n = new node(s_student+i, 1, 0);
			node *r = new node(START, 0, 0);
			n->reverse = r;
			r->reverse = n;
			edgelist[START].push_back(n);
			edgelist[s_student+i].push_back(r);

			int grade, want[5];
			scanf("%d", &grade);

			// student -> job edge
			for(int j=1; j<=4; j++){
				int want;
				scanf("%d", &want);
				node *tmp_n = new node(want+s_job, 1, satisfaction[grade][j]);
				node *tmp_r = new node(s_student+i, 0, -1*satisfaction[grade][j]);
				tmp_n->reverse = tmp_r;
				tmp_r->reverse = tmp_n;
				edgelist[s_student+i].push_back(tmp_n);
				edgelist[s_job+want].push_back(tmp_r);
			}
		}

		while(1){
			//bellmanford
			int pred[nodesize];
			int dist[nodesize];
			int edgenum[nodesize];
			int check[nodesize];

			for(int i=0; i<nodesize; i++) {
				check[i] = 0;
				pred[i] = -1;
				dist[i] = INT_MAX;
			}
			pred[0] = 0;
			dist[0] = 0;
			check[0] = 1;

			// spfa algorithm
			queue<int> q;
			q.push(0);
			while(!q.empty()){
				int from = q.front(); q.pop();
				check[from] = 0;
				for(int i=0; i<edgelist[from].size(); i++){
					int to = edgelist[from][i]->to;
					if(edgelist[from][i]->capacity>0 && dist[from]+edgelist[from][i]->cost < dist[to]){
						dist[to] = dist[from]+edgelist[from][i]->cost;
						pred[to] = from;
						edgenum[to] = i;
						if(!check[to]) {
							q.push(to);
							check[to] = 1;
						}
					}
				}
			}
/*
			// bellmanford ----> TLE
			int n = nodesize-1;
			while(n--){
				for(int i=0; i<nodesize; i++){
					if(!check[i]) continue;
					for(int j=0; j<edgelist[i].size(); j++){
						int to = edgelist[i][j]->to;
						if(edgelist[i][j]->capacity>0 && dist[i]+edgelist[i][j]->cost < dist[to]){
							check[to] = 1;
							dist[to] = dist[i]+edgelist[i][j]->cost;
							pred[to] = i;
							edgenum[to] = j;
						}
					}
				}
			}
*/
			//traceback
			if(dist[TARGET]==INT_MAX) break;
			else{
				// 부모노드 찾아서 엣지 거꾸로 하고 코스트 더하기
				int target = TARGET;
				while(target != START){
					// pred[target] -> target
					int p = pred[target];

					node *edge = edgelist[p][edgenum[target]];
					node *reedge = edge->reverse;

					mincost += edge->cost;
					edge->capacity--;
					reedge->capacity++;
					
					target = p;
				}
			}
		}

		cout<<-1*mincost<<endl;
	}

	return 0;
}
