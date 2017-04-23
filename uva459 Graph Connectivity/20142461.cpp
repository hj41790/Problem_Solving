#include <iostream>
#include <cstdio>
#include <cstring>

class DisjointSet{

public :
	int index;
	int parent;
	int height;

	DisjointSet(int _index) : 
		index(_index), parent(_index), height(1){}
	
	void set_parent(int _parent) { parent = _parent; }
	
	int get_parent(){ return parent; }

	void add_height() { height++; }
	
	void print(){
		printf("index : %d, parent : %d, height : %d\n", index, parent, height);
	}
};

DisjointSet *node[30];

int find_set(int);
void Union(int, int);

int main()
{

	int testcase, num_node, x, y;
	char str[5];
	char c;

	scanf("%d\n\n", &testcase);

	while(testcase--){
	
		fgets(str, sizeof(str), stdin);
		num_node = str[0]-'A' + 1;

		for(int i=0; i<num_node; i++)
			node[i] = new DisjointSet(i);

		
		while(1){
			fgets(str, sizeof(str), stdin);
			str[strlen(str)-1]=0;	//remove \n
		
			if(strlen(str)==0) break;

			x = str[0]-'A'; 
			y = str[1]-'A';
			
			Union(x, y);
		}
		
		//find set
			
		int count=0, check = 0;
		int root[30];
			
		for(int i=0; i<num_node; i++){
			check = 0;

			for(int j=0; j<count; j++)
				if(find_set(i)==root[j]) {
					check = 1;
					break;
				}
	
			if(!check) root[count++] = find_set(i);

		}

		printf("%d\n", count);
		if(testcase) printf("\n");

	}

	return 0;
}

int find_set(int x)
{
	while(x != node[x]->parent)
		x = node[x]->parent;
	return x;
}

void Union(int x, int y)
{
	int a, b;
	a = find_set(x);
	b = find_set(y);

	if(node[a]->height <= node[b]->height){
		if(node[a]->height == node[b]->height) node[b]->add_height();
		node[a]->set_parent(b);
	}
	else
		node[b]->set_parent(a);

}

