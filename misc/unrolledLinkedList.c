#include <stdio.h>
#include <stdlib.h>

int blockSize = 3;

struct ListNode {
    int value;
    struct ListNode* next;
};

struct LinkedBlock {
    int nodeCount;
    struct ListNode* head;  // dummy head
    struct LinkedBlock* next;
};

struct LinkedBlock* blockHead = NULL;

// Create a new list node
struct ListNode* newListNode(int value) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->value = value;
    node->next = NULL;
    return node;
}

// Create a new block with dummy head
struct LinkedBlock* newLinkedBlock() {
    struct LinkedBlock* block = (struct LinkedBlock*)malloc(sizeof(struct LinkedBlock));
    block->nodeCount = 0;
    block->head = newListNode(-1); // dummy head
    block->next = NULL;
    return block;
}

// Get total number of nodes in list
int getTotalNodeCount() {
    int count = 0;
    struct LinkedBlock* blk = blockHead;
    while (blk) {
        count += blk->nodeCount;
        blk = blk->next;
    }
    return count;
}

// Get block and node pointer at position k (0-based)
void searchElement(int k, struct LinkedBlock** fBlock, struct ListNode** prevNode) {
    struct LinkedBlock* p = blockHead;
    while (p) {
        if (k < p->nodeCount) {
            struct ListNode* prev = p->head;
            for (int i = 0; i < k; ++i) {
                prev = prev->next;
            }
            *fBlock = p;
            *prevNode = prev;
            return;
        }
        k -= p->nodeCount;
        p = p->next;
    }
    // If position is at the end, point to last block and tail
    *fBlock = NULL;
    *prevNode = NULL;
}

// Shift extra elements from a full block
void shift(struct LinkedBlock* A) {
    while (A->nodeCount > blockSize) {
        if (A->next == NULL) {
            A->next = newLinkedBlock();
        }
        struct LinkedBlock* B = A->next;

        // Remove last node from A
        struct ListNode* prev = A->head;
        while (prev->next && prev->next->next) {
            prev = prev->next;
        }
        struct ListNode* moveNode = prev->next;
        prev->next = NULL;

        // Insert at front of B
        moveNode->next = B->head->next;
        B->head->next = moveNode;

        A->nodeCount--;
        B->nodeCount++;

        A = B;
    }
}

// Insert value at position k (1-based index)
void insertAt(int k, int value) {
    if (blockHead == NULL)
        blockHead = newLinkedBlock();

    int total = getTotalNodeCount();
    if (k > total + 1)
        k = total + 1;

    struct LinkedBlock* p;
    struct ListNode* prev;
    searchElement(k - 1, &p, &prev);

    if (p == NULL || prev == NULL) {
        p = blockHead;
        while (p->next) p = p->next;
        prev = p->head;
        while (prev->next) prev = prev->next;
    }

    struct ListNode* newNode = newListNode(value);
    newNode->next = prev->next;
    prev->next = newNode;
    p->nodeCount++;

    shift(p);
}

// Delete node at position k (1-based)
void deleteAt(int k) {
    if (blockHead == NULL) return;

    int total = getTotalNodeCount();
    if (k > total || k < 1) return;

    struct LinkedBlock* p;
    struct ListNode* prev;
    searchElement(k - 1, &p, &prev);
    if (p && prev && prev->next) {
        struct ListNode* temp = prev->next;
        prev->next = temp->next;
        free(temp);
        p->nodeCount--;
    }
}

// Print the full list
void printList() {
    printf("List contents:\n");
    struct LinkedBlock* blk = blockHead;
    int i = 1;
    while (blk) {
        printf("Block %d (%d nodes): ", i++, blk->nodeCount);
        struct ListNode* node = blk->head->next;
        while (node) {
            printf("%d ", node->value);
            node = node->next;
        }
        printf("\n");
        blk = blk->next;
    }
    printf("\n");
}

// Free the entire structure
void freeList() {
    struct LinkedBlock* blk = blockHead;
    while (blk) {
        struct ListNode* node = blk->head;
        while (node) {
            struct ListNode* temp = node;
            node = node->next;
            free(temp);
        }
        struct LinkedBlock* tempBlk = blk;
        blk = blk->next;
        free(tempBlk);
    }
}

int main() {
    insertAt(1, 10);
    insertAt(2, 20);
    insertAt(3, 30);
    insertAt(2, 15);
    insertAt(5, 35);
    insertAt(6, 40);
    insertAt(7, 50);
    insertAt(8, 60);
    insertAt(9, 70);

    printList();

    deleteAt(3);
    deleteAt(1);
    deleteAt(7);

    printList();

    freeList();
    return 0;
}
