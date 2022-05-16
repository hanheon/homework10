/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;  //왼쪽 자식노드에 대한 포인터
	struct node *right;  //오른쪽 자식노드에 대한 포인터
} Node;

/* for stack */
#define MAX_STACK_SIZE		20  
Node* stack[MAX_STACK_SIZE];  //스택 구조체 생성 사이즈 20
int top = -1;  //스택 초기화

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;  //큐 초기화
int rear = -1;  //큐 초기화

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);  //포인터의 주소값을 레퍼런스하기 때문에 이중포인터 사용

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
void freeNode(Node* ptr);
/* you may add your own defined functions if necessary */





int main()
{
	char command;
	int key;
	Node* head = NULL;

  printf("[----- [HanSeungheon] [%d] -----]\n", 2020023057);
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z      Print Stack                  = p \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
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
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {  //초기화 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);  //함수 호출

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));  //헤드노드에 동적 메모리 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;  //헤드노드 초기화
	(*h)->key = -9999;  //헤드노드 초기화

	top = -1;  //스택 초기화

	front = rear = -1;  //큐 초기화

	return 1;
}



void recursiveInorder(Node* ptr)  //재귀형 중위순회
{
	if(ptr) {  //if(ptr!==null), 
		recursiveInorder(ptr->left);  //단말노드까지 반복
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for(;;)  //무한반복
	{
		for(; node; node = node->left)
			push(node);  //엘리먼트 삽입
		node = pop();  //엘리먼트 삭제

		if(!node) break;  //if(node ==null)
		printf(" [%d] ", node->key);

		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) 
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */ //if([tr == null])

	enQueue(ptr);  //데이터 입력

	for(;;)  //무한반복
	{
		ptr = deQueue();
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left) //if(ptr->left != null)
				enQueue(ptr->left);
			if(ptr->right) //if(ptr->right != null)
				enQueue(ptr->right);
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));  //새로운 노드 생성
	newNode->key = key;  //입력한 키값 대입
	newNode->left = NULL;  //새로운 노드 초기화
	newNode->right = NULL;  // 노드 초기화

	if (head->left == NULL) {  //루트노드가 비었을 때
		head->left = newNode;  //새로운 노드 주소값 대입
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;  //ptr = root

	Node* parentNode = NULL;  //parentnode 선언 및 초기화
	while(ptr != NULL) {  //헤드노드가 null이 아닌 경우

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;  //parentnode = 루트노드

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;  //키값에 따라 오른쪽 서브트리로
		else
			ptr = ptr->left;  //키값에 따라 왼쪽 서브트리로
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)  //키값에 따라
		parentNode->left = newNode;  //왼쪽 서브트리에 뉴노드 주소 저장
	else
		parentNode->right = newNode;  //오른쪽 서브트리에 뉴노드 주소 저장
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {  //프리컨디션 조사
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {  //프리컨디션 조사
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left;



	Node* parent = NULL;  //패런트 노드 선언 및 초기화
	Node* ptr = root;  //ptr에 루트 노드 대입

	while((ptr != NULL)&&(ptr->key != key)){  //널이 아니고 찾는 키값이 아닐 때
		if(ptr->key != key) {

			parent = ptr;	/* save the parent */

			if(ptr->key > key)  //키값이 더 클 때
				ptr = ptr->left;  //왼쪽 트리로
			else
				ptr = ptr->right;  //오른쪽 트리로
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)  //단말노드 지워야 할 경우
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr) //
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;

		}

		free(ptr);  //메모리 할당 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */  
	if ((ptr->left == NULL || ptr->right == NULL))  //자식노드를 삭제할 경우
	{
		Node* child;  //포인터 변수 생성
		if (ptr->left != NULL)// 루트노드가 null이 아닐 때
			child = ptr->left;  //루트노드 주소 child 대입
		else
			child = ptr->right;  //null일 때

		if(parent != NULL)  
		{
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr);
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;  
	parent = ptr;


	candidate = ptr->right;

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;

	free(candidate);
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) { //if (ptr != null)
		freeNode(ptr->left);  //왼쪽 자식노드 단말까지 가서 할당 해제
		freeNode(ptr->right);  //오른쪽 자식노드 단말까지 가서 할당 해제
		free(ptr);
	}
}

int freeBST(Node* head)  
{

	if(head->left == head)  //루트만 있을 때
	{
		free(head);  //루트만 메모리 해제
		return 1;
	}

	Node* p = head->left;  // p == root

	freeNode(p);  //freeNode 호출해서 메모리 전부 해제

	free(head);  //루트노드노 마지막으로 해제
	return 1;
}



Node* pop()
{
	if (top < 0) return NULL;  //스택이 비었을 경우
	return stack[top--];  //스택 팝해서 반환
}

void push(Node* aNode)
{
	stack[++top] = aNode;  //노드에 추가
}



Node* deQueue()
{
	if (front == rear) {  //큐가 비었을 경우
		 printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;  
	return queue[front];

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		 printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;
}





