#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int main(void)
{
	int N, maxSoFar, maxEndHere;
	int **arr;
	int **sum;
	int tmp, max=0;

	cin>>N;

	sum = new int*[N+1];
	arr = new int*[N+1];
	for(int i=0; i<=N; i++){
		arr[i] = new int[N+1];
		sum[i] = new int[N+1];
	}

	for(int i=1; i<=N; i++)
		for(int j=1; j<=N; j++)
			cin>>arr[i][j];

	for(int i=1; i<=N; i++)
		for(int j=1; j<=N; j++)
			sum[i][j] = arr[i][j] + sum[i-1][j] + sum[i][j-1] -sum[i-1][j-1];


	for(int i=1; i<=N; i++){
		maxSoFar = -INT_MAX;
		for(int j=1; j<=i; j++){
			maxEndHere = 0;
			for(int k=1; k<=N; k++){
				tmp = sum[i][k] - sum[i][k-1] - sum[j-1][k] + sum[j-1][k-1];
				maxEndHere = (maxEndHere+tmp>tmp)?maxEndHere+tmp:tmp;
				maxSoFar = (maxSoFar>maxEndHere)?maxSoFar:maxEndHere;
			}
			max = (max>maxSoFar)?max:maxSoFar;
		}
	}

	cout<<max<<endl;

	return 0;
}
