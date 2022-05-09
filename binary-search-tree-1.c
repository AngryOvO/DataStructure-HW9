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
		printf("--------------[201803805]------[���Ͽ�]-------------------------\n");
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

int initializeBST(Node** h) // Ʈ�� �ʱ�ȭ
{

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) // Ʈ���� ������� ������
		freeBST(*h); // Ʈ�� ��ü �Ҵ� ����

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // ����� ���� �Ҵ�
	(*h)->left = NULL;	/* root */ 
	(*h)->right = *h; 
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr) 
{
	if(ptr != NULL) // ptr�� ������� ������
	{
		inorderTraversal(ptr->left); // �������� �̵�
		printf(" [%d] ",ptr->key); // key�� ���
		inorderTraversal(ptr->right); // ���������� �̵�
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr != NULL) // ptr�� ������� �ʴٸ�
	{
		printf("[%d] ",ptr->key); // ������ ���
		preorderTraversal(ptr->left); // �������� �̵�
		preorderTraversal(ptr->right); // ���������� �̵�
	}
}

void postorderTraversal(Node* ptr) 
{
	if(ptr != NULL) // ptr�� ������� �ʴٸ�
	{
		postorderTraversal(ptr->left); //�������� �̵�
		postorderTraversal(ptr->right); // ���������� �̵�
		printf("[%d] ",ptr->key); // ������ ���
	}
}


int insert(Node* head, int key)
{
	// �� ��� ���� �� �ʱ�ȭ
	Node *node = (Node*)malloc(sizeof(Node)); 
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	// Ʈ���� ����ִ� ���
	if(head->left == NULL)
	{
		head->left = node; // �� ��尡 ��Ʈ���
		return 1;
	}
	
	Node *n = head->left; // Ʈ���� Ž���� ����ü������ ����

	while (n!= NULL) // n�� NULL�϶� ���� �ݺ�
	{
		if (key == n->key) // key ���� ��ġ�� ���
		{
			printf("Data is duplicated!\n"); 
			return 1;
		}

		if(key < n->key) // �Է��� key ���� �� �������
		{
			if(n->left == NULL) // ���� ��尡 ����ִٸ�
			{
				n->left = node; // �� ��尡 ���� ���
				return 1;
			}
			else
			{
				n = n->left; //�������� �̵�
			}	
		}
		if(key > n->key) // �Է¹��� key ���� ū���
		{
			if(n->right == NULL) // ������ ��尡 ����ִٸ�
			{
				n->right = node; // �� ��尡 ������ ���
				return 1;
			}
			else
			{
				n = n->right; // ���������� �̵�
			}
		}
	}	
}

int deleteLeafNode(Node* head, int key)
{
	Node *n = head->left; // Ʈ���� �̵��� ����ü ������
	Node *p = head; // ��带 ������ ����ü ������

	if(head == NULL) // ����尡 ����ִ°��
	{
		printf("tree is empty!\n"); // Ʈ���� �������
		return 0;
	}

	if(n == NULL) // ��Ʈ��尡 ����ִ� ���
	{
		printf("tree is empty!\n"); // Ʈ���� �������
		return 0;
	}

	while(n != NULL) // n�� NULL�� �ɶ����� �ݺ�
	{
		if(n->key == key) // �Է¹��� key ���� ��������϶�
		{
			if((n->left == NULL) && (n->right == NULL)) // ��������� ���
			{
				if(p->left == n)//�θ����� ���� �ڽ��ϰ��
				{
					p->left = NULL; // �θ����� ������ NULL ����Ŵ
					free(n); // �ڽĳ�� ����
					return 0;
				}
				else if(p->right == n) // �θ����� ������ �ڽ��ϰ��
				{
					p->right = NULL; // �θ����� ������ NULL
					free(n); // �ڽĳ�� ����
					return 0;
				}
			}
			else // ������尡 �ƴҰ��
			{
				printf("node is not leafNode!\n");
				return 0;
			}

		}
		
		if(key > n->key) // �Է¹��� key ���� �� ū ���
		{
			p = n; // p�� n�� ��ġ��
			n = n->right; //n�� ������ ���� �̵�
		}
			
		else if(key < n->key) // �Է¹��� key ���� �� �������
		{
			p = n; // p�� n�� ��ġ��
			n = n->left; // n�� ���� ���� �̵�
		}	
	}
	// �Է¹��� key ���� �ش��ϴ� ��尡 ���� ���
	printf("not exist key node in tree !!\n");
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // ��Ʈ��尡 ����ִ� ���
		return NULL; // NULL ����

	if(ptr->key == key) // key ���� �ش��ϴ� ��带 ã�����
		return ptr; //�ش� ����� �ּ� ����
	else if(key > ptr->key) // �Է¹��� ���� �� ū���
		searchRecursive(ptr->right,key); // ���������� �̵�
	else if(key < ptr->key) // �� �������
		searchRecursive(ptr->left,key); // �������� �̵�
}


Node* searchIterative(Node* head, int key)
{
	Node *n = head->left; // ����ü ������ ���� �� �ʱ�ȭ

	if(n == NULL) // ��Ʈ��尡 ���ٸ�
		return NULL; // NULL ����

	while(n != NULL) // n�� NULL�� �ɶ����� �ݺ�
	{
		if(n->key == key) // �Է¹��� key���� �ش��ϴ� ��带 ã����
			return n; // �� ����� �ּ� ����

		if(key > n->key) // �Է¹��� ���� �� ũ��
			n = n->right; // ���������� �̵�
		else if(key < n->key) // �� �۴ٸ�
			n = n->left; // �������� �̵�
	}
}

void freeNode(Node* ptr) 
{
	if(ptr) // ptr�� NULL�� �ƴҶ�
	{
		freeNode(ptr->left); // �������� �̵�
		freeNode(ptr->right); // ���������� �̵�
		free(ptr); // ptr ����
	}
}

int freeBST(Node* head)
{

	if(head->left == NULL) // ��Ʈ��尡 ���ٸ�
	{
		free(head); // ����� �Ҵ� ���� �� ����
		return 1;
	}

	Node* p = head->left; // ��Ʈ���� ������ �̵�

	freeNode(p); // Ʈ�� �Ҵ� ����

	free(head); // ����� �Ҵ� ����
	return 1;
}





