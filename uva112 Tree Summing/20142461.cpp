#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Stack{

		int *data;
		int depth;
		int size;
		int tmp;

	public:
		Stack(){
			data = new int[100];
			depth = 0;
			size = 50;
			tmp = 0;
		}
		void push(int num);
		int pop();
		~Stack();

};

void Stack::push(int num){

	data[depth] = tmp +  num;
	tmp = data[depth];

	depth++;

}

int Stack::pop(){
		int popnum;

	if(depth>0){
		popnum = data[--depth];
		tmp = data[depth-1];
	}
	else{
		return -1;
	}

	return popnum;
}

Stack::~Stack(){
	delete data;
}

bool cal_tree(const int);

Stack *stack;
bool result;

char *tree;

int main(){

		bool end = true;
		int num;
		int open = 0, close = 0;

		stack = new Stack();

		int size;

		int num_tree = 0;

		while(end){

			open = 0;
			close = 0;

			result = false;
			tree = new char[10000];
			size = 0;

			stack = new Stack();
			
			if(scanf("%d", &num)==-1) break;

			char ch;
			
			while(1){
				ch = getchar();

				if(ch=='(')
				{
						open++;
						tree[size++] = ch;
				}
				else if(ch==')'){
					close++;
					tree[size++] = ch;
				}
				else if(ch>='0'&&ch<='9'){
					tree[size++] = ch;
				}
				else if(ch=='-'){
					tree[size++] = ch;
				}
				else if(ch==EOF){
					end = false;
					break;
				}
				else if(ch=='\n'){
					if(open==close){
						break;
					}
				}
				
			}

			if(cal_tree(num)){
					if(result)
							cout<<"yes"<<endl;
					else
							cout<<"no"<<endl;
			}
			else
					cout<<"no"<<endl;

		}

		return 0;
}

bool cal_tree(const int find){

		int tmp;
		int sign;
		bool left = true;
		bool right = true;

		tree += sizeof(char);

		if(tree[0]=='-') {
			sign = -1;
			tree += sizeof(char);
		}
		else sign = 1;

		if(tree[0]==')'){
			return false;
		}
		else {
			tmp = atoi(tree);
			stack->push(tmp * sign);
			while(tree[0]<='9'&& tree[0]>='0')
					tree += sizeof(char);
		}

		left = cal_tree(find);
		tree += sizeof(char);
	

		right = cal_tree(find);
		tree += sizeof(char);

		if(left==false && right==false){
				if(stack->pop() == find)
						result = true;
		}
		else stack->pop();

		return true;
}