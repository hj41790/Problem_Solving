#include <iostream>
#include <cstring>
#include <string.h>
#include <stdio.h>

using namespace std;

int main()
{
	char tmp[100];
	char str[201];
	char cmp[5000][100];
	int count = 0;

	while(fgets(str, 100, stdin)!=NULL){

		strncpy(tmp, "", 1);
	
		for(int i=0; i<strlen(str); i++){
			if((str[i] >='A' && str[i]<='Z')||(str[i]>='a' && str[i]<='z')){
				str[i] = tolower(str[i]);
				strncat(tmp, &str[i], 1);
			}
			else{
				if(strcmp(tmp, "")!=0){
					int j;
					for(j=0; j<count; j++){
						if(strcmp(tmp, cmp[j])==0) break;
					}

					if(j==count){
						strncpy(cmp[count], tmp, strlen(tmp));
						count++;
					}
					
					strncpy(tmp, "", 1);
				}
			}
		}
	}

	for(int i=0; i<count-1; i++){
		for(int j=i+1; j<count; j++)
			if(strcmp(cmp[i], cmp[j])>0){
				strncpy(tmp, "", 1);
				strncpy(tmp, cmp[i], strlen(cmp[i])+1);
				strncpy(cmp[i], "", 1);
				strncpy(cmp[i], cmp[j], strlen(cmp[j])+1);
				strncpy(cmp[j], "", 1);
				strncpy(cmp[j], tmp, strlen(tmp)+1);
			}
	
	}





	for(int i=0; i<count; i++)
		cout<<cmp[i]<<endl;

	return 0;
	
}
