#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h);	//초기화
int freeList(listNode* h);		//메모리해제
int insertLast(listNode* h, int key);	//처음에키삽입
int deleteLast(listNode* h);			//마지막노드삭제
int insertFirst(listNode* h, int key);	//처음에키삽입
int deleteFirst(listNode* h);			//처음거삭제
int invertList(listNode* h);			//거꾸로

int insertNode(listNode* h, int key);	//키삽입
int deleteNode(listNode* h, int key);	//키삭제

void printList(listNode* h);	//프린트

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	printf("[----- [곽민정] [2021041021] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	//헤드가 딴거 뭐 있으면 리스트 다 메모리해제
	if(*h != NULL)
		freeList(*h);

	// 헤드 메모리 할당, 초기화
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h)		//오른쪽이 헤드임 헤드만있는거니까 헤드 메모리해제하고 리턴
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink;	//p에 오른쪽링크를 넣고

	listNode* prev = NULL;	
	while(p != NULL && p != h) {	//오른쪽이 안비어있고 p가 헤드가 아닐때
		prev = p;	//이전에다가 p
		p = p->rlink;	//p는 다음거
		free(prev);		//prev메모리해제
	}
	free(h);	//헤드메모리해제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {	//헤드빔
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {		//안비어있고 헤드만날때까지 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);	//키 갯수

	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);	//헤드의 링크들 주소 출력

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {	//노드의 주소를 출력
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;	//헤드할당안됐으면 리턴-1

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) //헤드밖에없으면 처음에 삽입
	{
		h->rlink = node;	//헤드오른쪽 은 노드고
		h->llink = node;	//왼쪽도 노드
		node->rlink = h;	//그리고 노드 옆이 헤드
		node->llink = h;
	} else {		//다른것들도 있는 경우
		h->llink->rlink = node;	//끝노드 옆에 새노드삽입
		node->llink = h->llink;	//그왼쪽에 이전걸 넣고
		h->llink = node;		//헤드바로직전꺼는 새노드를가리키고
		node->rlink = h;		//노드오른쪽은 헤드로 서로연결
	}

	return 1;
}


int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)		//헤드왼쪽도헤드거나 null이면 암것도없음
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; 	//헤드왼쪽을 지울거

	nodetoremove->llink->rlink = h;		//지울거왼쪽을 마지막으로 헤드에 연결
	h->llink = nodetoremove->llink;		//서로연결

	free(nodetoremove);	//메모리해제

	return 1;
}

int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink;	//원래 처음노드를 새노드 오른쪽으로
	h->rlink->llink = node;	//서로연결
	node->llink = h;		//왼쪽헤드랑
	h->rlink = node;		//서로연결


	return 1;
}

int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)	//메모리할당안받았거나 추가된노드없으면 암것도없음
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;		//지울거첫번째거

	nodetoremove->rlink->llink = h;			//두번째걸 헤드랑
	h->rlink = nodetoremove->rlink;			//서로연결

	free(nodetoremove);		//메모리해제

	return 1;

}

int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {	//아무것도없음
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	h->llink = h->rlink;

	while(n != NULL && n != h){
		trail = middle;	//trail에 middle
		middle = n;		//middle에 n
		n = n->rlink;	//n에 n다음거
		middle->rlink = trail;	//middle 오른쪽에 trail 서로연결
		middle->llink = n;		//middle 왼쪽에 n
	}

	h->rlink = middle;		//헤드오른쪽dp 미들

	return 0;
}

int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)		//아무것도없으면 처음에 삽입
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key >= key) {	//입력된키가 들어갈곳(n보다작은키값이되는곳)을 찾으면
			if(n == h->rlink) {		//그위치가 처음노드면
				insertFirst(h, key);	//처음에 삽입
			} else { //중간이나 마지막은
				node->rlink = n;	//오른쪽에 n
				node->llink = n->llink;	//왼쪽에 n왼쪽이었던거
				n->llink->rlink = node;	//서로연결
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);	//마지막까지갔으면 그냥 마지막에 삽입
	return 0;
}

int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)		//노드없음
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key == key) {	//노드찾으면
			if(n == h->rlink) { // 첫번째노드면 처음거삭제
				deleteFirst(h);
			} else if (n->rlink == h){ // 마지막 노드면 마지막삭제
				deleteLast(h);
			} else { //중간이면
				n->llink->rlink = n->rlink;	//n이랑연결된걸 건너뛰어서 연결시키고
				n->rlink->llink = n->llink;
				free(n);		//n메모리해제
			}
			return 0;
		}

		n = n->rlink;
	}
	//없음
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


