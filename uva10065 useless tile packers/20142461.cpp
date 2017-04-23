#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node{
	int x;
	int y;
}node;

node polygon[101];
node tile[101];

double signedArea(node, node, node);
double getangle(node);
void sort(int n);

int main()
{
	int N, count=1;
	int i, j, min;

	int root, head;

	double area_polygon;
	double area_tile;

	node tmp;

	while(1){

		root = -1;
		head = -1;
		area_polygon = 0;
		area_tile = 0;

		memset(&polygon, 0, sizeof(node)*101);
		memset(&tile, 0, sizeof(node)*101);

		scanf("%d",&N);
		if(N==0) break;

		min = INT_MAX;
		for(i=0; i<N; i++){
			scanf("%d %d", &polygon[i].x, &polygon[i].y);
			if(polygon[i].y<min){
				min = polygon[i].y;
				root = i;
			}
		}

		node p = {0, 0};	
		for(i=0; i<N-1; i++)
			area_polygon += signedArea(p, polygon[i], polygon[i+1]);
		area_polygon += signedArea(p, polygon[N-1], polygon[0]);

		tmp.x = polygon[root].x;
		tmp.y = polygon[root].y;
		polygon[root].x = polygon[0].x;
		polygon[root].y = polygon[0].y;
		polygon[0].x = tmp.x;
		polygon[0].y = tmp.y;

		root = 0;

		polygon[N].x = polygon[0].x;
		polygon[N].y = polygon[0].y;

		sort(N);

		head = root;

		int size = 0;
		i=0;
		while(i<=N){
			if(size<2){
				tile[size].x = polygon[head].x;
				tile[size].y = polygon[head].y;
				size++; i++;
				head += 1;
				continue;
			}

			if(signedArea(tile[size-2], tile[size-1], polygon[head])>0){
				if(head!=N) {
					tile[size].x = polygon[head].x;
					tile[size].y = polygon[head].y;
					size++;
					head += 1;
				}
				i++;
			}
			else{
				size--;
			}
		}
		tile[size].x = tile[0].x;
		tile[size].y = tile[0].y;

		for(i=0; i<size; i++){
			area_tile += signedArea(p, tile[i], tile[i+1]);
		}

		if(area_polygon<0) area_polygon *= -1;
		if(area_tile<0) area_tile *= -1;

		double UTP = 100*((area_tile - area_polygon)/area_tile);

		printf("Tile #%d\n", count);
		printf("Wasted Space = %.2f %\n\n", UTP);

		count++;
	}
}

double signedArea(node a, node b, node c)
{
	return 0.5*((a.x*(b.y-c.y))
				-(a.y*(b.x - c.x))
				+(b.x*c.y - b.y*c.x));
}

void sort(int n)
{
	int i, j;
	node tmp;

	for(i=1; i<n; i++)
		for(j=i+1; j<n; j++){
			if(signedArea(polygon[0], polygon[i], polygon[j])<0){
				tmp.x = polygon[i].x;
				tmp.y = polygon[i].y;
				polygon[i].x = polygon[j].x;
				polygon[i].y = polygon[j].y;
				polygon[j].x = tmp.x;
				polygon[j].y = tmp.y;
			}
		}
}

