#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>
#include <string.h>

using namespace std;

typedef pair<int, int> p;

double W[755][755];

double getdistance(p a, p b)
{
	double x = a.first - b.first;
	double y = a.second - b.second;
	return sqrt(x*x+y*y);
}

int main(void)
{
	int N, M, count, vnear;
	double total, min;

	double distance[755];

	while(1){
		vector<p> input;

		if(scanf("%d", &N)!=1) break;
		for(int i=0; i<N; i++){
			int x, y;
			scanf("%d %d", &x, &y);
			input.push_back(make_pair(x, y));
		}

		memset(W, 0, sizeof(double)*755*755);

		for(int i=1; i<=N; i++){
			for(int j=1; j<=N; j++){
				if(i!=j) {
					double dist = getdistance(input[i-1], input[j-1]);
					W[i][j] = dist;
				}
				else W[i][j] = 0;
			}
		}

		scanf("%d", &M);
		for(int i=1; i<=M; i++){
			int a, b;
			scanf("%d %d", &a, &b);
			W[a][b] = 0; W[b][a] = 0;
		}

		for(int i=1; i<=N; i++) distance[i] = W[1][i];

		total = 0;
		count = N-1;
		while(count--){
			min = 0xffffff;
			for(int i=2; i<=N; i++){
				if(distance[i]>=0 && distance[i]<min){
					min = distance[i];
					vnear = i;
				}
			}

			total += distance[vnear];
			distance[vnear] = -1;
			for(int i=2; i<=N; i++)
				if(W[vnear][i]<distance[i]) distance[i] = W[vnear][i];
			
		}

		printf("%.2f\n", total);
	
	}

	return 0;
}
