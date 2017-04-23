#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

long long answer;
int n, n_alp = 0, max_len=0;
char argv[10][10] = {0};
char reverse[10][10] = {0};

int alphabet[26] = {0};		//existing check
int order[26] = {0};
int number[26] = {0};
int isused[26] = {0};

void maketree(int);

int main()
{
	scanf("%d", &n);
	
	for(int i=0; i<n; i++){
		scanf("%s", argv[i]);
		
		int len = strlen(argv[i]);
		max_len = (max_len>len)?max_len:len;
		for(int j=0; j<len; j++){
			reverse[i][j] = argv[i][len-j-1];
			alphabet[argv[i][j]-'A'] = 1;
		}
	}

	//알파벳 수 세기
	for(int i=0; i<26; i++)
		if(alphabet[i]) n_alp++;
/*
	for(int i=0; i<26; i++)
		if(alphabet[i]) printf("%c ", 'A'+i);
	cout<<endl;
*/
	//우선순위 매기기
//	for(int i=0; i<26; i++) order[i] = -1;
	for(int i=0; i<n; i++){
		int order_tmp = 10 - max_len;
		for(int j=0; j<strlen(argv[i]); j++){
			if(order[reverse[i][j]-'A']<order_tmp)
				order[reverse[i][j]-'A'] = order_tmp;
			order_tmp++;
		}
	}
/*
	for(int i=0; i<26; i++)
		if(alphabet[i]) cout<<order[i]<<" ";
	cout<<endl;
*/
	//트리만들기
	maketree(9);	

	cout<<answer<<endl;

	return 0;
}

void maketree(int depth)
{
	if(depth==9-n_alp){
		long long result = 0;
		for(int i=0; i<n; i++){
            if(number[argv[i][0]-'A']==0) return;
			long long num = 0;
			for(int j=0; j<strlen(argv[i]); j++){
				num = num*10 + number[argv[i][j]-'A'];
			}
			result += num;
		}
		if(result>answer) answer = result;
		return;		
	}

	// 우선순위로 backtracking 시도해봤으나 실패 ㅠㅠ 
	// 우선순위를 제외한 조건문이 brute-force
	for(int i=0; i<26; i++){
		if(alphabet[i] && !isused[i]){ // && order[i]>=depth){
			isused[i] = 1;
			number[i] = depth;
			maketree(depth-1);
			isused[i] = 0;
		}
	}
}

