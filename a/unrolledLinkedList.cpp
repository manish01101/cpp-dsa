#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int blockSize;

struct ListNode {
  struct ListNode* next;
  int value;
};

struct LinkedBlock {
  struct LinkedBlock* next;
  struct ListNode* head;
  int nodeCount;
};

struct LinkedBlock* blockHead;

// create and empty block
struct LinkedBlock* newLinkedBlock() {
  struct LinkedBlock* block = (struct LinkedBlock*)malloc(sizeof(struct LinkedBlock));
  block->next = NULL;
  block->head = NULL;
  block->nodeCount = 0;
  return block;
}

//create a node
struct ListNode* newListNode(int value) {
  struct ListNode* temp = (struct ListNode*)malloc(sizeof(struct ListNode));
  temp->next = NULL;
  temp->value = value;
  return temp;
}

void searchElement(int k, struct LinkedBlock **fLinkedBlock, struct ListNode **fListNode) {
  // find the block 
  int j = (k+blockSize -1) / blockSize; // k-th node is in the j-th block
  struct LinkedBlock* p = blockHead;
  while(--j) {
    p=p->next;
  }
  *fLinkedBlock = p;
  // find the node
  struct ListNode* q = p->head;
  k = k%blockSize;
  if(k==0) k = blockSize;
  k = p->nodeCount + 1 - k;
  while(k--) {
    q = q->next;
  }
  *fListNode = q;
}

// start shift opearation from block *p
void shift(struct LinkedBlock *A) {
  struct LinkedBlock * B;
  struct ListNode* temp;
  while(A->nodeCount > blockSize) { //if this block still have to shift
    if(A->next == NULL) { // reach the end. Alittle different
    A->next = newLinkedBlock();
    B = A->next;
    temp = A->head->next;
    A->head->next = A->head->next->next;
    B->head = temp;
    temp->next = temp;
    A->nodeCount--;
    B->nodeCount++;
    } else {
      B = A->next;
      temp = A->head->next;
      A->head->next = A->head->next->next;
      temp->next = B->head->next;
      B->head->next = temp;
      B->head = temp;
      A->nodeCount--;
      B->nodeCount++;
    }
    A = B;
  }
}

