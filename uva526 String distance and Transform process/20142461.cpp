#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

char strA[83];
char strB[83];

int c[83][83];
int d[83][83];
// 0 none / 1 change / 2 insert / 3 delete

int m_count;
int count=0;
int linecnt=0;

void print(int i, int j){
	if(i==0 && j==0) return;

	if(c[i][j]==1){
		print(i-1, j-1);
		printf("%d Replace %d,%c\n", linecnt++, j, strB[j-1]);
	}
	else if(c[i][j]==2){
		print(i, j-1);
		printf("%d Insert %d,%c\n", linecnt++, j, strB[j-1]);
		count--;
	}
	else if(c[i][j]==3){
		print(i-1, j);
		printf("%d Delete %d\n", linecnt++, i-count);
		count++;
	}
	else
		print(i-1, j-1);
}

int main(){

	int lenA, lenB, val;
	int a=0;

	while(fgets(strA, 83, stdin)!=NULL){
		if(fgets(strB, 83, stdin)==NULL) break;

		if(a==1) cout<<endl;
		memset(d,0,83*83*4);
		memset(c,0,83*83*4);
		strA[strlen(strA)-1]=0;
		strB[strlen(strB)-1]=0;

		count = 0;
		m_count = 0;
		linecnt = 1;
		lenA = strlen(strA);
		lenB = strlen(strB);
		
		d[0][0] = 0;

		for(int i=1; i<=lenA; i++){
			for(int j=0; j<=lenB; j++){
				c[i][j] = 0;
				d[i][j] = 0;
			}
		}

		for(int i=1; i<=lenA; i++){
			d[i][0] = i;
			c[i][0] = 3;
		}

		for(int j=1; j<=lenB; j++){
			d[0][j] = j;
			c[0][j] = 2;
		}

		for(int i=1; i<=lenA; i++){
			for(int j=1; j<=lenB; j++){
				val = (strA[i-1]==strB[j-1])?0:1;

				if(d[i-1][j-1]+val <= d[i-1][j]+1){
					d[i][j] = d[i-1][j-1]+val;
					c[i][j] = (val==0)?0:1;
				}
				else{
					d[i][j] = d[i-1][j]+1;
					c[i][j] = 3;
				}

				if(d[i][j] > d[i][j-1]+1){
					d[i][j] = d[i][j-1]+1;
					c[i][j] = 2;
				}

			}

		}

		a=1;
		cout<<d[lenA][lenB]<<endl;
		print(lenA, lenB);

		memset(strA,0,83);
		memset(strB,0,83);
	}

	return 0;

}
