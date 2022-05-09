/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
void freeNode(Node* ptr);
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("--------------[201803805]------[정하용]-------------------------\n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) // 트리 초기화
{

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) // 트리가 비어있지 않으면
		freeBST(*h); // 트리 전체 할당 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // 헤드노드 동적 할당
	(*h)->left = NULL;	/* root */ 
	(*h)->right = *h; 
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr) 
{
	if(ptr != NULL) // ptr이 비어있지 않으면
	{
		inorderTraversal(ptr->left); // 왼쪽으로 이동
		printf(" [%d] ",ptr->key); // key값 출력
		inorderTraversal(ptr->right); // 오른쪽으로 이동
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr != NULL) // ptr이 비어있지 않다면
	{
		printf("[%d] ",ptr->key); // 데이터 출력
		preorderTraversal(ptr->left); // 왼쪽으로 이동
		preorderTraversal(ptr->right); // 오른쪽으로 이동
	}
}

void postorderTraversal(Node* ptr) 
{
	if(ptr != NULL) // ptr이 비어있지 않다면
	{
		postorderTraversal(ptr->left); //왼쪽으로 이동
		postorderTraversal(ptr->right); // 오른쪽으로 이동
		printf("[%d] ",ptr->key); // 데이터 출력
	}
}


int insert(Node* head, int key)
{
	// 새 노드 생성 및 초기화
	Node *node = (Node*)malloc(sizeof(Node)); 
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	// 트리가 비어있는 경우
	if(head->left == NULL)
	{
		head->left = node; // 새 노드가 루트노드
		return 1;
	}
	
	Node *n = head->left; // 트리를 탐색할 구조체포인터 생성

	while (n!= NULL) // n이 NULL일때 까지 반복
	{
		if (key == n->key) // key 값이 겹치는 경우
		{
			printf("Data is duplicated!\n"); 
			return 1;
		}

		if(key < n->key) // 입력한 key 값이 더 작은경우
		{
			if(n->left == NULL) // 왼쪽 노드가 비어있다면
			{
				n->left = node; // 새 노드가 왼쪽 노드
				return 1;
			}
			else
			{
				n = n->left; //왼쪽으로 이동
			}	
		}
		if(key > n->key) // 입력받은 key 값이 큰경우
		{
			if(n->right == NULL) // 오른쪽 노드가 비어있다면
			{
				n->right = node; // 새 노드가 오른쪽 노드
				return 1;
			}
			else
			{
				n = n->right; // 오른쪽으로 이동
			}
		}
	}	
}

int deleteLeafNode(Node* head, int key)
{
	Node *n = head->left; // 트리를 이동할 구조체 포인터
	Node *p = head; // 노드를 삭제할 구조체 포인터

	if(head == NULL) // 헤드노드가 비어있는경우
	{
		printf("tree is empty!\n"); // 트리가 비어있음
		return 0;
	}

	if(n == NULL) // 루트노드가 비어있는 경우
	{
		printf("tree is empty!\n"); // 트리가 비어있음
		return 0;
	}

	while(n != NULL) // n이 NULL이 될때까지 반복
	{
		if(n->key == key) // 입력받은 key 값과 같은노드일때
		{
			if((n->left == NULL) && (n->right == NULL)) // 리프노드일 경우
			{
				if(p->left == n)//부모노드의 왼쪽 자식일경우
				{
					p->left = NULL; // 부모노드의 왼쪽이 NULL 가리킴
					free(n); // 자식노드 삭제
					return 0;
				}
				else if(p->right == n) // 부모노드의 오른쪽 자식일경우
				{
					p->right = NULL; // 부모노드의 오른쪽 NULL
					free(n); // 자식노드 삭제
					return 0;
				}
			}
			else // 리프노드가 아닐경우
			{
				printf("node is not leafNode!\n");
				return 0;
			}

		}
		
		if(key > n->key) // 입력받은 key 값이 더 큰 경우
		{
			p = n; // p를 n의 위치로
			n = n->right; //n을 오른쪽 노드로 이동
		}
			
		else if(key < n->key) // 입력받은 key 값이 더 작은경우
		{
			p = n; // p를 n의 위치로
			n = n->left; // n을 왼쪽 노드로 이동
		}	
	}
	// 입력받은 key 값에 해당하는 노드가 없는 경우
	printf("not exist key node in tree !!\n");
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // 루트노드가 비어있는 경우
		return NULL; // NULL 리턴

	if(ptr->key == key) // key 값에 해당하는 노드를 찾은경우
		return ptr; //해당 노드의 주소 리턴
	else if(key > ptr->key) // 입력받은 값이 더 큰경우
		searchRecursive(ptr->right,key); // 오른쪽으로 이동
	else if(key < ptr->key) // 더 작은경우
		searchRecursive(ptr->left,key); // 왼쪽으로 이동
}


Node* searchIterative(Node* head, int key)
{
	Node *n = head->left; // 구조체 포인터 선언 및 초기화

	if(n == NULL) // 루트노드가 없다면
		return NULL; // NULL 리턴

	while(n != NULL) // n이 NULL이 될때까지 반복
	{
		if(n->key == key) // 입력받은 key값에 해당하는 노드를 찾으면
			return n; // 그 노드의 주소 리턴

		if(key > n->key) // 입력받은 값이 더 크면
			n = n->right; // 오른쪽으로 이동
		else if(key < n->key) // 더 작다면
			n = n->left; // 왼쪽으로 이동
	}
}

void freeNode(Node* ptr) 
{
	if(ptr) // ptr이 NULL이 아닐때
	{
		freeNode(ptr->left); // 왼쪽으로 이동
		freeNode(ptr->right); // 오른쪽으로 이동
		free(ptr); // ptr 해제
	}
}

int freeBST(Node* head)
{

	if(head->left == NULL) // 루트노드가 없다면
	{
		free(head); // 헤드노드 할당 해제 및 종료
		return 1;
	}

	Node* p = head->left; // 루트노드로 포인터 이동

	freeNode(p); // 트리 할당 해제

	free(head); // 헤드노드 할당 해제
	return 1;
}





