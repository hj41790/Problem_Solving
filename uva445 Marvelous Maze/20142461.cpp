#include <iostream>
#include <stdio.h>

using namespace std;

int main(void){

		int sum = 0;
		char ch;

		freopen("input.txt", "r", stdin);

		while((ch = getchar()) != EOF){
			if(ch>='0' && ch<='9'){
				sum += ch - '0';
			}
			else if((ch>='A' && ch<='Z') || ch=='*'){
				for(int i=0; i<sum; i++)
						cout<<ch;
			
				sum = 0;
			}
			else if(ch=='b'){
				for(int i=0; i<sum; i++)
						cout<<" ";
			
				sum = 0;
			}
			else if(ch=='!' || ch=='\n'){
				cout<<endl;
				
				sum = 0;
			}


		}

		return 0;

}
