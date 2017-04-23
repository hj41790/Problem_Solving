#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
	char name[16];
	int len;
	int visited;
}node;

typedef struct prohibitpair{
	int topic1;
	int topic2;
}prohibitpair;

void dfs(int, int);
int checkprohibit();
void sort();
void initialize(void);

node topic[16];
prohibitpair ban_pair[130];

int set, num_topic, prohibit, num_pair;

int main(void)
{
	char tmp1[16], tmp2[16];

	char printpair[1000];

	scanf("%d", &set);

	int i, j, k;
	for(i=0; i<set; i++){

		initialize();

		scanf("%d %d %d", &num_topic, &prohibit, &num_pair);

		// input topics
		for(j=0; j<num_topic; j++){
			scanf("%s", topic[j].name);
			topic[j].len = strlen(topic[j].name);
			for(k=0; topic[j].name[k]!=0; k++)
				topic[j].name[k] = toupper(topic[j].name[k]);
		}

		// sort topics
		sort();

		// input prohibit combinations
		for(j=0; j<prohibit; j++){
			scanf("%s", tmp1);
			scanf("%s", tmp2);

			for(k=0; k<strlen(tmp1); k++)
				tmp1[k] = toupper(tmp1[k]);
			for(k=0; k<strlen(tmp2); k++)
				tmp2[k] = toupper(tmp2[k]);

			// make prohibit pair array
			for(int m=0; m<num_topic; m++){
				if(strcmp(topic[m].name, tmp1)==0)
					ban_pair[j].topic1 = m;
				if(strcmp(topic[m].name, tmp2)==0)
					ban_pair[j].topic2 = m;
			}

		}

		// ready for dfs
		printf("Set %d:\n", i+1);
		for(j=0; j<num_topic; j++){
			strncpy(printpair, "", 1);
			dfs(1, j);
			
			for(k=j+1; k<num_topic; k++)
				topic[k].visited = 0;	
		}

		printf("\n");


	}

	return 0;
}

void dfs(int depth, int index){

	topic[index].visited = 1;
	if(checkprohibit()){
		topic[index].visited = 0;
		return;
	}

	if(depth==num_pair){
		int count=1;
		for(int i=0; i<num_topic; i++){
			if(topic[i].visited==1){
				printf("%s", topic[i].name);
				if(count++<num_pair) printf(" ");
			}
		}
		printf("\n");
	}
	else{
		for(int i=index+1; i<num_topic; i++)
			dfs(depth+1, i);
	}

	topic[index].visited = 0;

}

int checkprohibit()
{
	int tmp1, tmp2;
	for(int i=0; i<prohibit; i++){
		tmp1 = ban_pair[i].topic1;
		tmp2 = ban_pair[i].topic2;
		if(topic[tmp1].visited && topic[tmp2].visited)
			return 1;
	}

	return 0;
}

void sort()
{
	node tmp;
	int i, j;

	for(i=0; i<num_topic-1; i++){
		for(j=i+1; j<num_topic; j++){
			if(topic[i].len < topic[j].len){
				strcpy(tmp.name, topic[i].name);
				tmp.len = topic[i].len;
				strcpy(topic[i].name, topic[j].name);
				topic[i].len = topic[j].len;
				strcpy(topic[j].name, tmp.name);
				topic[j].len = tmp.len;
			}
			else if(topic[i].len==topic[j].len){
				if(strcmp(topic[i].name, topic[j].name)>0){
					strcpy(tmp.name, topic[i].name);
					tmp.len = topic[i].len;
					strcpy(topic[i].name, topic[j].name);
					topic[i].len = topic[j].len;
					strcpy(topic[j].name, tmp.name);
					topic[j].len = tmp.len;			
				}
			}
		}
	
	}

}

void initialize(void)
{
	int i,j;
	
	for(i=0; i<16; i++){
		strcpy(topic[i].name, "");
		topic[i].len = 0;
		topic[i].visited = 0;
	}
}
