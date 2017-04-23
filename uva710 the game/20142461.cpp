#include <cstdio>
#include <iostream>
#include <queue>
#include <limits.h>

using namespace std;

typedef struct node{
	int piece;
	int color;
	int segment;
	int lastdir;

	node(int _piece){
		piece = _piece;
		color = 0;	//white
		segment = 0;
		lastdir = -1;
	}
}node;

typedef struct coordinate{
	int x;
	int y;

	coordinate(){}

	coordinate(int _x, int _y){
		x = _x;
		y = _y;
	}
}coordinate;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

queue<coordinate*> q;

coordinate *coor[80][80];
node *map[80][80];


void initializeMap();
void initializeColor();


int main()
{
	int width, height, pair, board=1;
	char c;

	coordinate start; 
	coordinate end;

	for(int i=0; i<80; i++)
		for(int j=0; j<80; j++){
			coor[i][j] = new coordinate(j, i);
			map[i][j] = new node(1);
		}

	while(1){
		scanf("%d %d", &width, &height);
		if(width==0 || height==0) break;

		pair= 1;

		//map initialize
		initializeMap();

		getc(stdin);
		for(int i=1; i<=height; i++){
			for(int j=1; j<=width+1; j++){
				c = getc(stdin);
				if(c=='\n') break;
				if(c=='X') map[i][j]->piece = 0;	// there is game piece
			}
		}

		printf("Board #%d:\n", board++);

		while(1){
			scanf("%d %d %d %d", &start.x, &start.y, &end.x, &end.y);
			if(start.x==0 || start.y==0 || end.x ==0 || end.y == 0) break;

			// color initialize
			initializeColor();

			map[end.y][end.x]->segment = INT_MAX;
			q.push(coor[start.y][start.x]);

			while(!q.empty()){

				coordinate *tmp = q.front();
				q.pop();

//				printf("dequeue : (%d, %d)\n", tmp->x, tmp->y);

				for(int i=0; i<4; i++){
					int x = tmp->x + dx[i];
					int y = tmp->y + dy[i];

					if(x<0 || x>width+1 || y<0 || y>height+1) continue;

					if(map[y][x]->piece==1){
						if(map[y][x]->color<2){
							map[y][x]->color=1;
							map[y][x]->lastdir = i;
							
							if(map[tmp->y][tmp->x]->lastdir != map[y][x]->lastdir)
								map[y][x]->segment = map[tmp->y][tmp->x]->segment + 1;
							else
								map[y][x]->segment = map[tmp->y][tmp->x]->segment;
							
							q.push(coor[y][x]);
						}
					}
					else if(x==end.x && y==end.y){
						if(map[tmp->y][tmp->x]->segment < map[y][x]->segment){	
							map[y][x]->color = 1;
							map[y][x]->lastdir = i;
							
							if(map[tmp->y][tmp->x]->lastdir != map[y][x]->lastdir)
								map[y][x]->segment = map[tmp->y][tmp->x]->segment + 1;
							else
								map[y][x]->segment = map[tmp->y][tmp->x]->segment;
						}
					
					}
				}

				map[tmp->y][tmp->x]->color = 2;
			}

			//end bfs
		
			if(map[end.y][end.x]->segment==INT_MAX)
				printf("Pair %d: impossible.\n", pair++);
			else
				printf("Pair %d: %d segments.\n", pair++, map[end.y][end.x]->segment);

		}

		printf("\n");
		
	}

}

void initializeMap(){

	for(int i=0; i<80; i++)
		for(int j=0; j<80; j++){
			map[i][j]->piece = 1;
		}
	
}

void initializeColor(){

	for(int i=0; i<80; i++)
		for(int j=0; j<80; j++){
			map[i][j]->color = 0;
			map[i][j]->segment = 0;
			map[i][j]->lastdir = -1;
		}
}
