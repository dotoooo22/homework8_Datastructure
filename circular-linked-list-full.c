#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h);	//�ʱ�ȭ
int freeList(listNode* h);		//�޸�����
int insertLast(listNode* h, int key);	//ó����Ű����
int deleteLast(listNode* h);			//������������
int insertFirst(listNode* h, int key);	//ó����Ű����
int deleteFirst(listNode* h);			//ó���Ż���
int invertList(listNode* h);			//�Ųٷ�

int insertNode(listNode* h, int key);	//Ű����
int deleteNode(listNode* h, int key);	//Ű����

void printList(listNode* h);	//����Ʈ

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	printf("[----- [������] [2021041021] -----]\n");
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

	//��尡 ���� �� ������ ����Ʈ �� �޸�����
	if(*h != NULL)
		freeList(*h);

	// ��� �޸� �Ҵ�, �ʱ�ȭ
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h)		//�������� ����� ��常�ִ°Ŵϱ� ��� �޸������ϰ� ����
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink;	//p�� �����ʸ�ũ�� �ְ�

	listNode* prev = NULL;	
	while(p != NULL && p != h) {	//�������� �Ⱥ���ְ� p�� ��尡 �ƴҶ�
		prev = p;	//�������ٰ� p
		p = p->rlink;	//p�� ������
		free(prev);		//prev�޸�����
	}
	free(h);	//���޸�����
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {	//����
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {		//�Ⱥ���ְ� ��常�������� ���
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);	//Ű ����

	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);	//����� ��ũ�� �ּ� ���

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {	//����� �ּҸ� ���
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;	//����Ҵ�ȵ����� ����-1

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) //���ۿ������� ó���� ����
	{
		h->rlink = node;	//�������� �� ����
		h->llink = node;	//���ʵ� ���
		node->rlink = h;	//�׸��� ��� ���� ���
		node->llink = h;
	} else {		//�ٸ��͵鵵 �ִ� ���
		h->llink->rlink = node;	//����� ���� ��������
		node->llink = h->llink;	//�׿��ʿ� ������ �ְ�
		h->llink = node;		//���ٷ��������� ����带����Ű��
		node->rlink = h;		//���������� ���� ���ο���
	}

	return 1;
}


int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)		//�����ʵ����ų� null�̸� �ϰ͵�����
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; 	//�������� �����

	nodetoremove->llink->rlink = h;		//����ſ����� ���������� ��忡 ����
	h->llink = nodetoremove->llink;		//���ο���

	free(nodetoremove);	//�޸�����

	return 1;
}

int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink;	//���� ó����带 ����� ����������
	h->rlink->llink = node;	//���ο���
	node->llink = h;		//��������
	h->rlink = node;		//���ο���


	return 1;
}

int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)	//�޸��Ҵ�ȹ޾Ұų� �߰��ȳ������� �ϰ͵�����
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;		//�����ù��°��

	nodetoremove->rlink->llink = h;			//�ι�°�� ����
	h->rlink = nodetoremove->rlink;			//���ο���

	free(nodetoremove);		//�޸�����

	return 1;

}

int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {	//�ƹ��͵�����
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	h->llink = h->rlink;

	while(n != NULL && n != h){
		trail = middle;	//trail�� middle
		middle = n;		//middle�� n
		n = n->rlink;	//n�� n������
		middle->rlink = trail;	//middle �����ʿ� trail ���ο���
		middle->llink = n;		//middle ���ʿ� n
	}

	h->rlink = middle;		//��������dp �̵�

	return 0;
}

int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)		//�ƹ��͵������� ó���� ����
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key >= key) {	//�Էµ�Ű�� ����(n��������Ű���̵Ǵ°�)�� ã����
			if(n == h->rlink) {		//����ġ�� ó������
				insertFirst(h, key);	//ó���� ����
			} else { //�߰��̳� ��������
				node->rlink = n;	//�����ʿ� n
				node->llink = n->llink;	//���ʿ� n�����̾�����
				n->llink->rlink = node;	//���ο���
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);	//���������������� �׳� �������� ����
	return 0;
}

int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)		//������
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key == key) {	//���ã����
			if(n == h->rlink) { // ù��°���� ó���Ż���
				deleteFirst(h);
			} else if (n->rlink == h){ // ������ ���� ����������
				deleteLast(h);
			} else { //�߰��̸�
				n->llink->rlink = n->rlink;	//n�̶�����Ȱ� �ǳʶپ �����Ű��
				n->rlink->llink = n->llink;
				free(n);		//n�޸�����
			}
			return 0;
		}

		n = n->rlink;
	}
	//����
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


