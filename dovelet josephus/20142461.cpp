#include <iostream>

using namespace std;

typedef struct node{
		int num;
		struct node *next;
}node;
 
int main()
{
		node *root;
		node *head;

		int n, m, k;

		cin>> n >> m >> k;

		node *tmp = new node;
		tmp->num = 1;
		tmp->next = NULL;

		root = tmp;
		head = tmp;

		for(int i=1; i<n; i++){
			node *tmp = new node;
			tmp->num=i+1;
			tmp->next = NULL;

			head->next = tmp;
			head = head->next;
		}

		// 원형 링크드리스트 만들기
		head->next = root;
		head = head->next;

		// m번째로 헤드 이동 및 삭제(일부러 하나 덜 이동 - 삭제를 위해)  
		for(int i=1; i<m-1; i++)
				head = head->next;

		node *del = head->next;				// 제외시킬 기사 빼기
		head->next = (head->next)->next;	// 노드 건너뛰어 잇기
		head = head->next;					// head 이동
		cout<<del->num<<" ";				// 출력
		delete del;							// 메모리해제

		int count=2;

		while((count++)<n){
			
			// k만큼 돌리기
			for(int i=1; i<k-1; i++)
					head = head->next;

			node *del = head->next;				// 제외시킬 기사 빼기
			head->next = (head->next)->next;	// 노드 건너뛰어 잇기
			head = head->next;					// head 이동
			cout<<del->num<<" ";				// 출력
			delete del;							// 메모리해제
		}

		cout<<head->num<<endl;

		return 0;
}
