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

```c
bool has_cycle(struct Node *head)
{
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}
```

## 3. Merge two sorted linked lists

Use a dummy head and repeatedly link the smaller current node. This tests pointer manipulation and stable ordering.

```c
struct Node *merge_sorted(struct Node *a, struct Node *b)
{
    struct Node dummy = {0, NULL};
    struct Node *tail = &dummy;

    while (a != NULL && b != NULL) {
        if (a->value <= b->value) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = (a != NULL) ? a : b;
    return dummy.next;
}
```

## 4. Circular buffer

A circular buffer is ideal for UART RX, logging, or streaming data. Maintain `head` and `tail`, define the full/empty rules clearly, and document whether one slot is intentionally left unused or a count is maintained.

```c
#define RB_SIZE 64u

typedef struct {
    uint8_t buffer[RB_SIZE];
    uint16_t head;   /* next write index */
    uint16_t tail;   /* next read index */
} ring_buffer_t;

bool rb_push(ring_buffer_t *rb, uint8_t byte)
{
    uint16_t next = (uint16_t)((rb->head + 1u) % RB_SIZE);
    if (next == rb->tail) {
        return false; /* full: one slot intentionally left unused */
    }
    rb->buffer[rb->head] = byte;
    rb->head = next;
    return true;
}

bool rb_pop(ring_buffer_t *rb, uint8_t *byte)
{
    if (rb->head == rb->tail) {
        return false; /* empty */
    }
    *byte = rb->buffer[rb->tail];
    rb->tail = (uint16_t)((rb->tail + 1u) % RB_SIZE);
    return true;
}
```

## 5. Array-based ring buffer with an explicit count

For single-producer/single-consumer use cases, an array plus head/tail indices gives deterministic memory use. Tracking a `count` (instead of sacrificing a slot) uses full capacity but requires the count update to be atomic with respect to the other side if producer and consumer run concurrently — establish the required memory-ordering/synchronization model rather than relying only on `volatile`.

```c
typedef struct {
    int data[32];
    uint8_t head;
    uint8_t tail;
    volatile uint8_t count; /* shared between ISR and task context */
} counted_ring_t;

bool counted_ring_push(counted_ring_t *rb, int value)
{
    if (rb->count == 32u) {
        return false;
    }
    rb->data[rb->head] = value;
    rb->head = (uint8_t)((rb->head + 1u) % 32u);
    rb->count++;
    return true;
}

bool counted_ring_pop(counted_ring_t *rb, int *value)
{
    if (rb->count == 0u) {
        return false;
    }
    *value = rb->data[rb->tail];
    rb->tail = (uint8_t)((rb->tail + 1u) % 32u);
    rb->count--;
    return true;
}
```

## 6. LRU cache interview problem

A common design uses a hash map for lookup and a doubly linked list for recency ordering, giving near `O(1)` average lookup/update when the hash table supports it. In embedded systems, ask whether fixed-capacity storage and bounded allocation are required — a fixed-size array of nodes with an intrusive doubly linked list (no `malloc`) is usually preferred over `std::unordered_map`/dynamic allocation.

```c
#define LRU_CAP 4u

typedef struct {
    int key;
    int value;
    int prev, next; /* indices into the fixed pool, -1 = none */
    bool used;
} lru_entry_t;

typedef struct {
    lru_entry_t entries[LRU_CAP];
    int head; /* most recently used */
    int tail; /* least recently used */
} lru_cache_t;
/* On a hit: unlink the entry and relink it at head.
   On a miss with a full cache: evict tail, reuse its slot, relink at head. */
```

## 7. Reverse an array in place

```c
void reverse_array(int *arr, size_t len)
{
    size_t left = 0u;
    size_t right = (len == 0u) ? 0u : len - 1u;

    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}
```

## 8. Find the middle of a linked list in one pass

Use the same slow/fast two-pointer idea as cycle detection: when `fast` reaches the end, `slow` is at the middle. This avoids a first pass just to count nodes.

```c
struct Node *find_middle(struct Node *head)
{
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```

## 9. Implement a fixed-capacity stack using an array

Common embedded interview question since a stack is often needed without `malloc` (e.g., a bounded expression evaluator or a bracket-matching validator).

```c
#define STACK_CAP 16u

typedef struct {
    int data[STACK_CAP];
    uint8_t top; /* number of elements currently stored */
} stack_t;

bool stack_push(stack_t *s, int value)
{
    if (s->top >= STACK_CAP) {
        return false; /* overflow */
    }
    s->data[s->top++] = value;
    return true;
}

bool stack_pop(stack_t *s, int *value)
{
    if (s->top == 0u) {
        return false; /* underflow */
    }
    *value = s->data[--s->top];
    return true;
}
```

## 10. Implement a queue using two stacks

A classic conceptual question to check understanding of amortized complexity: push always goes to `in_stack`; a pop/peek moves everything from `in_stack` to `out_stack` only when `out_stack` is empty, so each element is moved at most once — giving amortized `O(1)` per operation even though a single pop can occasionally cost `O(n)`.

```c
typedef struct {
    stack_t in_stack;
    stack_t out_stack;
} queue_t;

bool queue_enqueue(queue_t *q, int value)
{
    return stack_push(&q->in_stack, value);
}

bool queue_dequeue(queue_t *q, int *value)
{
    if (q->out_stack.top == 0u) {
        int temp;
        while (stack_pop(&q->in_stack, &temp)) {
            if (!stack_push(&q->out_stack, temp)) {
                return false;
            }
        }
    }
    return stack_pop(&q->out_stack, value);
}
```

## 11. Binary search on a sorted array

Frequently asked to check for the classic off-by-one and integer-overflow mistakes in the midpoint calculation.

```c
int binary_search(const int *arr, size_t len, int target)
{
    size_t low = 0u;
    size_t high = len; /* exclusive upper bound avoids len==0 underflow */

    while (low < high) {
        size_t mid = low + (high - low) / 2u; /* avoids (low+high) overflow */
        if (arr[mid] == target) {
            return (int)mid;
        } else if (arr[mid] < target) {
            low = mid + 1u;
        } else {
            high = mid;
        }
    }
    return -1;
}
```

## 12. Swap two variables without a temporary variable

Asked as a quick warm-up question, often followed by "why is the XOR version risky?" — it fails silently if both arguments happen to be the same memory location, because `a ^= a` zeroes it out before the swap can happen.

```c
void swap_xor(int *a, int *b)
{
    if (a == b) {
        return; /* required guard: XOR swap breaks on aliasing */
    }
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
```

## 13. Check if a number is a power of two

A very common bit-manipulation warm-up in embedded interviews, since power-of-two sizes come up constantly (buffer sizes, alignment, masks).

```c
bool is_power_of_two(unsigned int n)
{
    return (n != 0u) && ((n & (n - 1u)) == 0u);
}
```

**Why it works:** a power of two has exactly one bit set (e.g., `01000`). Subtracting 1 flips that bit and every bit below it (`00111`). ANDing the two together always yields 0 — for any non-power-of-two value, at least one bit survives the AND.

## 14. Count the number of set bits in an integer (Brian Kernighan's algorithm)

```c
unsigned int count_set_bits(unsigned int n)
{
    unsigned int count = 0u;
    while (n != 0u) {
        n &= (n - 1u); /* clears the lowest set bit each iteration */
        count++;
    }
    return count;
}
```

This runs in `O(number of set bits)` rather than looping over every bit position, which matters when checking, say, a 32-bit GPIO register where usually only a few pins are set.

## 15. Array vs linked list — when would you use each in an embedded system?

Arrays give contiguous, cache-friendly, statically-allocatable storage with O(1) indexed access, but insertion/deletion in the middle requires shifting elements and the capacity must be fixed (or reallocated) up front — a good fit for a fixed-size sensor sample buffer or lookup table. Linked lists give O(1) insertion/deletion once you have a pointer to the node, without needing contiguous memory or a pre-known maximum size, but every node needs its own allocation (ideally from a static pool, not the heap, on a memory-constrained target), pointer traversal defeats cache locality, and there's per-node pointer overhead — better suited to something like a free-list of fixed-size buffers or a linked list of active timers where the count varies at runtime but total memory is still bounded by a fixed pool.

## References

