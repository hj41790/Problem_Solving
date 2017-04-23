#include <iostream>

using namespace std;

int main()
{
	int len, val;
	char *str, *rev;
	int *d[5001];

	cin>>len;
	str = new char[len+1];
	rev = new char[len+1];
	for(int i=0; i<=len; i++)
		d[i] = new int[len+1];
	cin>>str;

	for(int i=0; i<len; i++)
		rev[i] = str[len-i-1];

	for(int i=0; i<=len; i++){
		d[i][0] = 0;
		d[0][i] = 0;
	}

	for(int i=1; i<=len; i++){
		for(int j=1; j<=len; j++){
			if(str[i-1]==rev[j-1]){
				d[i][j] = d[i-1][j-1]+1;
			}
			else
				d[i][j] = (d[i-1][j] > d[i][j-1]) ? d[i-1][j] : d[i][j-1];
		}
	}

	
	cout<<len-d[len][len]<<endl;

	return 0;
}
