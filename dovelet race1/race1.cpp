#include <iostream>

using namespace std;

int main(void)
{
	int N, maxD;
	int *time;
	int *distance;
	int *dp;

	cin>>maxD;
	cin>>N;

	N++;

	time = new int[N+1];
	distance = new int[N+1];
	dp = new int[N+1];

	for(int i=0; i<N; i++)
		cin>>distance[i];

	for(int i=1; i<=N; i++)
		cin>>time[i];

	for(int i=1; i<=N; i++){
		dp[i] = dp[i-1] + time[i];
		if(distance[i-1]>=maxD) dp[i] = dp[i-1] + time[i];
		else{
			int j, sumD=0;
			for(j=i-1; j>=0; j--){
				sumD += distance[j];
				if(sumD<=maxD) {
					dp[i] = (dp[i]<dp[j]+time[i]) ? dp[i]:dp[j] + time[i];
				}
			
			}
		}
	
	}

	cout<<dp[N]<<endl;

	return 0;
}
