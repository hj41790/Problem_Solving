#include <iostream>
#include <cstdio>
#include <stdlib.h>

using namespace std;

int n, minimum=1000;
int door[25];	// 열려있으면 1 닫혀있으면 0
int order[25];	// 벽장 여는 순서
int num_order;	// 벽장 순서 길이


void maketree(int index, int count)
{
	if(index==num_order){
		minimum = (minimum>count)?count:minimum;
		return;
	}
	else if(minimum<count) return;

	int dist, tmp;
	int target = order[index];
	
	if(door[target]) maketree(index+1, count);
	else{
		for(int i=0; i<n; i++){
			if(door[i]){
				dist = abs(target-i);
				tmp = i;

				count += dist;
				door[i] = 0;
				door[target] = 1;

				maketree(index+1, count);
			
				count -= dist;
				door[i] = 1;
				door[target] = 0;
			}
		}
	}
}

int main()
{
	int a, b;
	scanf("%d", &n);
	scanf("%d %d", &a, &b);
	for(int i=0; i<n; i++)
		if(i==a-1) door[i] = 1;
		else if(i==b-1) door[i] = 1;
		else door[i] = 0;

	scanf("%d", &num_order);
	for(int i=0; i<num_order; i++){
		int tmp;
		scanf("%d", &tmp);
		order[i] = tmp-1;
	}

	maketree(0, 0);
	
	cout<<minimum<<endl;
}
