#include <iostream>

#define SIZE 19

using namespace std;

int data[SIZE][SIZE];

int check_h(int, int);
int check_v(int, int);
int check_d1(int, int);
int check_d2(int, int);

int main(void){

	int winner = 0;
	int count = 0;
	int x, y;

	for(int i=0; i<SIZE; i++)
		for(int j=0; j<SIZE; j++)
			cin>>data[i][j];

	for(int j=0; j<SIZE; j++){
		for(int i=0; i<SIZE; i++){

			if(data[i][j]>0){
				x = i;
				y = j;

				if((winner = check_h(i, j))>0) break;
				if((winner = check_v(i, j))>0) break;
				if((winner = check_d1(i, j))>0) break;
				if((winner = check_d2(i, j))>0) break;
			}

		}	
		
		if(winner>0) break;
	}


	if(winner > 0){
		cout<<winner<<endl;
		cout<<x+1<<" "<<y+1<<endl;
	}
	else
		cout<<"0"<<endl;


	return 0;

}

int check_h(int i, int j){

	int a;	
	int count = 0;
	int tmp = data[i][j];

	for(a=j+1; a<SIZE; a++){
	
		if(data[i][a] != tmp) break;
		else count++;
	
	}

	if(count==4 && (j-1<0 || data[i][j-1]!=tmp)) return tmp;
	else return 0;

}


int check_v(int i, int j){
	
	int a;
	int count = 0;
	int tmp = data[i][j];

	for(a=i+1; a<SIZE; a++){
	
		if(data[a][j] != tmp) break;
		else count++;
	
	}

	if(count==4 && (i-1<0 || data[i-1][j] != tmp)) return tmp;
	else return 0;

}

int check_d1(int i, int j){

	int a, b;
	int count = 0;
	int tmp = data[i][j];

	for(a=i+1, b=j+1; a<SIZE && b<SIZE; a++, b++){
		if(data[a][b] != tmp) break;
		else count++;
	}

	if(count==4 && (i-1<0 || j-1<0 || data[i-1][j-1] != tmp)) return tmp;
	else return 0;

}



int check_d2(int i, int j){

	int a, b;
	int count = 0;
	int tmp = data[i][j];

	for(a=i-1, b=j+1; a>=0 && b<SIZE; a--, b++){
		if(data[a][b] != tmp) break;
		else count++;
	}

	if(count==4 && (i+1==SIZE || j-1<0 || data[i+1][j-1] != tmp)) return tmp;
	else return 0;

}

