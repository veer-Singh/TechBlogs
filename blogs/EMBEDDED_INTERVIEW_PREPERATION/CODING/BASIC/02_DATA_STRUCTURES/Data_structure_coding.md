# Basic Embedded Coding — Data Structures

## 1. Reverse a singly linked list

```c
struct Node {
    int value;
    struct Node *next;
};

struct Node *reverse(struct Node *head)
{
    struct Node *prev = NULL;
    struct Node *curr = head;

    while (curr != NULL) {
        struct Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

## 2. Detect a loop — Floyd's algorithm

Use a slow pointer moving one node and a fast pointer moving two. If they meet, a cycle exists. Complexity: `O(n)` time and `O(1)` extra space.

## 3. Merge two sorted linked lists

Use a dummy head and repeatedly link the smaller current node. This tests pointer manipulation and stable ordering.

## 4. Circular buffer

A circular buffer is ideal for UART RX, logging, or streaming data. Maintain `head` and `tail`, define the full/empty rules clearly, and document whether one slot is intentionally left unused or a count is maintained.

## 5. Array-based ring buffer

For single-producer/single-consumer use cases, an array plus head/tail indices gives deterministic memory use. If producer and consumer run concurrently, establish the required memory-ordering/synchronization model rather than relying only on `volatile`.

## 6. LRU cache interview problem

A common design uses a hash map for lookup and a doubly linked list for recency ordering, giving near `O(1)` average lookup/update when the hash table supports it. In embedded systems, ask whether fixed-capacity storage and bounded allocation are required.

## References

