#include <iostream>

using namespace std;

int data[50001];
int sum[50001];
int dy[4][50001];

int main(void){

	int car, n;
	
	cin>>car;

	for(int i=1; i<=car; i++)
		cin>>data[i];

	cin>>n;

	for(int i=n; i<=car; i++)
		for(int j=0; j<n; j++)
			sum[i] += data[i-j];


	for(int i=n; i<=car; i++)
		for(int j=1; j<=i; j++){
		
			dy[1][i] = (dy[1][i] > sum[j]) ? dy[1][i] : sum[j];
		}


	for(int i=2; i<=3; i++){
	
		for(int j=n*i; j<=car; j++){

			int tmp1 = dy[i][j-1];
			int tmp2 = sum[j] + dy[i-1][j-n];

			dy[i][j] = (tmp1>tmp2) ? tmp1 : tmp2;
		}
	
	}

	cout<<dy[3][car]<<endl;

	return 0;

}
