#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

#define MAX 310

using namespace std;

int W[MAX][MAX];
int D[MAX][MAX];
int P[MAX][MAX];

int num_node;

void path(int, int);
void initialize();

int main()
{
	int testcase, x, y;
	char str[150];
	char *token; 

	while(1){
		if(scanf("%d", &num_node)!=1) break;
	
		//initialize
		initialize();

		getc(stdin);
		for(int i=1; i<=num_node; i++){
			fgets(str, sizeof(str), stdin);
			str[strlen(str)-1] = 0;

			token = strtok(str, "-,");
			x = atoi(token);
			while((token=strtok(NULL, "-,"))!=NULL){
				y = atoi(token);
				W[x][y] = 1;
			}
		}

		//floyd's algorithm
		for(int i=1; i<=num_node; i++)
			for(int j=1; j<=num_node; j++){
				P[i][j] = 0;
				D[i][j] = W[i][j];
			}

		for(int k=1; k<=num_node; k++)
			for(int i=1; i<=num_node; i++)
				for(int j=1; j<=num_node; j++){
					if(D[i][k] + D[k][j]<D[i][j]){
						P[i][j] = k;
						D[i][j] = D[i][k] + D[k][j];
					}
					else if(D[i][k]+D[k][j]==D[i][j]){
						if(k<P[i][j]){
							P[i][j] = k;
							D[i][j] = D[i][k] + D[k][j];
						}
					}
				}


		scanf("%d", &testcase);

		printf("-----\n");
		// call path() func, every testcases!
		for(int i=0; i<testcase; i++){
			scanf("%d %d", &x, &y);
			if(D[x][y]==0xffff) printf("connection impossible\n");
			else {
				printf("%d", x);
				path(x, y);
				printf(" %d\n", y);
			}
		}

	}
}

void path(int q, int r)
{
	if(P[q][r]!=0){
		path(q, P[q][r]);
		printf(" %d", P[q][r]);
		path(P[q][r], r);
	}
}

void initialize()
{
	for(int i=0; i<=num_node; i++)
		for(int j=0; j<=num_node; j++){
			W[i][j] = (i==j)? 0 : 0xffff;
			D[i][j] = 0;
			P[i][j] = 0;
		}
}

