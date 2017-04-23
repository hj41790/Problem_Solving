#include <iostream>
#include <cstdio>
#include <string.h>
#include <stdlib.h>

using namespace std;

void clear();

int val[1000];
int w[200];
double p[200];
double minP[200][10000];

int main(){

	char c;
	int item;
	int count = 0;
	int tmp = 0;
	int max = 0;
	int num_case = 1;

	while(1){

		// initialize & input

		clear();

		count = 0;
		item = 0;
		tmp = 0;
		max = 0;

		w[1] = 1;
	
		if(scanf("%lf %d", &p[1], &item)<=0) break;

		item++;

		for(int i=2; i<=item; i++)
			scanf("%d %lf", &w[i], &p[i]);		

		getchar();

		while(1){
			c = getchar();

			if(c=='\n'){
				if(tmp>0){
					max = (tmp>max) ? tmp : max;
					val[count++] = tmp;
					tmp = 0;
				}
				break;
			}
			else if(c>='0' && c<='9'){
				tmp = (tmp*10) + (c-'0');
			}
			else if(tmp>0){
				max = (tmp>max) ? tmp : max;
				val[count++] = tmp;
				tmp = 0;
			}
		
		
		}

		// algorithm start!!!
		
		for(int i=1; i<=item; i++){
		
			for(int j=1; j<=max; j++){
			
				if(w[i]>=j)
					minP[i][j] = (minP[i-1][j] < p[i]) ? minP[i-1][j] : p[i];
				else
					minP[i][j] = (minP[i-1][j] < p[i]+minP[i][j-w[i]]) ?
					   			  minP[i-1][j] : 	p[i] + minP[i][j-w[i]];
			
			}
		
		}

		cout<<"Case "<<num_case<<":"<<endl;

		for(int i=0; i<count; i++){
		
			printf("Buy %d for $%.2f\n", val[i], minP[item][val[i]]);

//			cout<<"Buy "<<val[i]<<" for $"<<minP[item][val[i]]<<endl;

		}

		num_case++;
	
	}
}

void clear(){

	for(int i=0; i<200; i++){
	
		w[i] = 0;
		p[i] = 0;

		for(int j=0; j<10000; j++)
			minP[i][j] = 99999;
	
	}

}
