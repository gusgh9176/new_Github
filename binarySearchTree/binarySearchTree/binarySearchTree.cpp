// binarySearchTree.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

// 노드의 전달할 정보(data, key) 를 담고있는 클래스
class Element
{
public:
	int data;
	int key;
	// 생성자
	Element(int d, int k)
	{
		data = d;
		key = k;
	}
};

// Node
class BstNode
{
public:
	BstNode() {}; // 생성자
	BstNode * LeftChild; // 왼쪽 자식
	int data;			// data 값
	int key;                     //key 값
	BstNode * RightChild; // 오른쪽 자식
};

// 트리에 관한 삽입, 삭제, 탐색, 중위우선순회 하는 클래스
class BST
{
private:
	BstNode * root= NULL; // 트리의 root
public:
	BST() {}; // 생성자
	// 클래스 생성시 root 값을 넣는 생성자
	BST(Element e)
	{
		root->data = e.data;
		root->key = e.key;
	}
	// 트리에 x노드 삽입하는 함수
	bool Insert(const Element &x)
	{
		BstNode *p = root; // x.key를 탐색할 노드
		BstNode *q = 0; // p의 부모

		// 이미 트리에 같은 key값이 있는지 탐색, 같은 값 없고 p에 빈주소 할당시 탈출
		while (p) {
			q = p;
			if (x.key == p->key) 
			{
				cout << "이미 존재하는 키입니다." << endl; return false; //x.key가 이미 존재 함수 실행 종료
			}
			if (x.key < p->key) p = p->LeftChild; // x의 키값이 현재 노드의 키값보다 작을경우 왼쪽 자식으로 현재 노드 이동
			else p = p->RightChild; // x의 키값이 현재 노드의 키값보다 클경우 오른쪽 자식으로 현재 노드 이동
		}
		
		p = new BstNode; // 빈주소 p에 삽입 수행
		p->LeftChild = p->RightChild = 0; p->data = x.data; p->key = x.key; // 삽입된 노드 값 입력
		if (!root) root = p; // 만약 root가 비었다면 root에 p 설정
		else if (x.key < q->key) q->LeftChild = p; // 현재 노드의 key값이 부모 노드의 키 값보다 작다면 부모 노드의 왼쪽 자식에 p 삽입
		else q->RightChild = p; // 현재 노드의 key값이 부모 노드의 키 값보다 크다면 부모 노드의 오른쪽 자식에 p 삽입

		return true; // 삽입 성공시 true 리턴
	}
	// 탐색 함수
	BstNode *lterSearch(const Element &x)
		// 이진 탐색 트리에서 키 x의 원소를 탐색
	{
		for (BstNode *t = root; t; )
		{
			if (x.key == t->key) return t; // 키 값 같은 노드 t 발견시 t 리턴
			if (x.key < t->key) t = t->LeftChild; // x의 키값이 t의 키값보다 작을경우 t의 왼쪽자식으로 t 이동
			else t = t->RightChild; // x의 키값이 t의 키값보다 클경우 t의 오른쪽자식으로 t 이동
		}
		return 0; //없을경우 0 반환
	}
	// 노드 삭제하는 함수
	int Delete(int key)
	{
		BstNode * q = 0; // 부모노드
		BstNode * temp = 0; // Delete 할때 쓰기위한 temp
		// 같은 키 값을 가진 노드 찾는 for문
		for (BstNode *t = root; t; )
		{
			if (key == t->key)
			{
				// 삭제할 노드에 자식노드가 없을때
				if (!(t->LeftChild) && !(t->RightChild))
				{
					if (q->LeftChild == t) q->LeftChild = NULL; // 부모노드의 왼쪽 자식과 삭제할 키 값을 가진 노드 t가 같다면 왼쪽 자식 주소에 NULL
					else q->RightChild = NULL; // 부모노드의 오른쪽 자식과 삭제할 키 값을 가진 노드 t가 같다면 오른쪽 자식 주소에 NULL
					return 0; // 성공시 실행 종료
				}
				// 삭제할 노드에 자식노드가 좌측 1개 있을때
				else if (t->LeftChild && !(t->RightChild))
				{
					t->data = t->LeftChild->data; // 자식노드의 데이터 현재 노드로 이동
					t->key = t->LeftChild->key; // 자식노드의 키 값 현재 노드로 이동
					t->RightChild = t->LeftChild->RightChild; // 현재 노드의 오른쪽 자식 노드에 자식노드의 오른쪽 자식노드 할당
					temp = t->LeftChild; // 삭제위해 temp에 t의 왼쪽 자식 노드 할당
					t->LeftChild = t->LeftChild->LeftChild; // 현재 노드의 왼쪽 자식 노드에 자식노드의 왼쪽 자식노드 할당
					delete temp; // 왼쪽 자식 노드 삭제
					temp = NULL; // temp에 NULL
					return 0; // 성공시 실행 종료
				}
				// 삭제할 노드에 자식노드가 우측 1개 있을때
				// 좌측일때와 방식 같음
				else if (t->RightChild && !(t->LeftChild))
				{
					t->data = t->RightChild->data; 
					t->key = t->RightChild->key;
					t->LeftChild = t->RightChild->LeftChild;
					temp = t->RightChild;
					
					t->RightChild = t->RightChild->RightChild;
					delete temp;
					temp = NULL;
					return 0;
				}
				// 삭제할 노드에 자식노드가 양측 있을때
				else
				{
					BstNode *search = t; // 삭제할 노드에서 시작하여 가장 아래 탐색할 변수 생성
					// 삭제할 노드의 가장 아래 오른쪽에 있을 노드로 이동하는 for문
					for ( ; search->RightChild;)
					{
						q = search; // search의 부모 노드
						search = search->RightChild; // search의 오른쪽 자식으로 이동
					}

					//삭제된 위치로 옴길 노드에 왼쪽 자식노드 있음
					if (search->LeftChild)
					{
						t->data = search->data; // search에서 t로 데이터 이동
						t->key = search->key; // search에서 t로 키 값 이동

						search->data = search->LeftChild->data; // 왼쪽 자식 데이터 search로 이동
						search->key = search->LeftChild->key; // 왼쪽 자식 키 값 search로 이동
						search->RightChild = search->LeftChild->RightChild; // 왼쪽 자식의 오른쪽 자식 주소 search의 오른쪽 자식으로 이동
						search->LeftChild = search->LeftChild->LeftChild; // 왼쪽 자식의 왼쪽 자식 주소 search의 왼쪽 자식으로 이동
					}
					//삭제될 위치로 옴길 노드가 비단말노드
					else
					{
						t->data = search->data; // search의 데이터 t로 이동
						t->key = search->key; // search의 키 값 t로 이동
						delete q->RightChild; // search 삭제
					}
					return 0;
				}
			}
			// 삭제할 노드의 키 값이 현재 노드의 키 값보다 작을시 왼쪽 자식으로 이동
			if (key < t->key)
			{
				q = t;
				t = t->LeftChild;
			}
			// 삭제할 노드의 키 값이 현재 노드의 키 값보다 클시 오른쪽 자식으로 이동
			else
			{
				q = t;
				t = t->RightChild;
			}
		}
		return 1; // 삭제실패
	}
	// 중위우선순회
	void travel(BstNode * currentNode)
	{
		BstNode *p = currentNode; // root의 주소 줌
		
		// root의 주소가 NULL이 아닐시 if문 실행
		if (currentNode)
		{
			travel(currentNode->LeftChild); // 재귀함수
			cout << currentNode->key; // 키 값 출력
			cout << " ";
			travel(currentNode->RightChild); // 재귀함수
		}
	}
	//메인문에서 출력위한 함수
	void travel()
	{
		travel(root);
	}
};

int main()
{
	int n = 0;
	BST bst;
	while (1)
	{
		cout << "1)삽입    2)삭제    3)탐색    4)중위우선순회" << endl;
		cin >> n;
		if (n == 1)
		{
			int j, k;
			cout << "삽입할 data와 key 값을 입력해주세요 : ";
			cin >> j;
			cin >> k;
			bst.Insert(Element(j, k));
		}
		else if (n == 2)
		{
			int m = 0;
			cout << "삭제할 노드의 키값을 입력해주세요 : ";
			cin >> m;
			if (bst.Delete(m) == 0) cout << "삭제가 성공했습니다" << endl;
			else cout << "삭제 실패" << endl;
		}
		else if (n == 3)
		{
			int m = 0;
			cout << "탐색할 노드의 키값을 입력해주세요 : ";
			cin >> m;
			if (!(bst.lterSearch(Element(0, m)))) cout << "해당하는 키값이 없습니다" << endl;
			else cout << "해당하는 키가 트리에 존재합니다" << endl;
		}
		else if (n == 4)
		{
			bst.travel();
			cout << endl;
		}
		else cout << "올바른 값을 입력해주세요." << endl;
	}
    return 0;
}

