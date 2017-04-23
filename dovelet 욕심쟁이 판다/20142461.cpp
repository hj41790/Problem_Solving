#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int forest[500][500] = {0};
int day[500][500] = {0};
int N;

int arr_x[] = {1, -1, 0, 0};
int arr_y[] = {0, 0, 1, -1};

int getmaxdays(int, int);

int main()
{
	int i, j, max;
   	int	x, y;

	scanf("%d", &N);

	for(i=0; i<N; i++){
		for(j=0; j<N; j++)
			scanf("%d", &forest[i][j]);
	}

	max = -INT_MAX;
	for(i=0; i<N; i++)
		for(j=0; j<N; j++){
			day[i][j] = getmaxdays(i, j);
			max = (day[i][j] > max) ? day[i][j] : max;
		}

	printf("%d\n", max+1);
	
}

int getmaxdays(int x, int y)
{
	int i, next_x, next_y, tmp;
	
	if(day[x][y]==0){
		
		for(i=0; i<4; i++){
			next_x = x + arr_x[i];
			next_y = y + arr_y[i];

			if(next_x>=0 && next_x<N && next_y>=0 && next_y<N){
				if(forest[next_x][next_y]>forest[x][y]){
					tmp = getmaxdays(next_x, next_y);
					day[x][y] = (day[x][y]>tmp+1) ? day[x][y] : tmp+1;
				}
			}
		}		


	}

	return day[x][y];
}


