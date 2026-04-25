# Memory Maps — AI Memory Visualizer (Corrected Analysis)

## Overview

This document contains detailed, manually-corrected memory visualizations for four C programs that expose common memory errors. Each analysis explicitly tracks:
- **Stack memory**: Local variables, function parameters, return addresses, and frame pointers
- **Heap memory**: Dynamically allocated blocks, lifetimes, and deallocation
- **Pointer aliasing**: Multiple pointers referencing the same memory location
- **Object lifetimes**: When objects become valid or invalid
- **Critical corrections** to AI-generated analyses

---

## 1. stack_example.c — Recursion and Stack Frames

### Program Summary
`stack_example` demonstrates how the stack grows and shrinks during recursive function calls. Each recursive call creates a new stack frame with its own local variables.

### Code Structure
```c
walk_stack(0, 3)
  ├─ walk_stack(1, 3)
  │  ├─ walk_stack(2, 3)
  │  │  └─ walk_stack(3, 3)
  │  │     [returns, no further recursion]
  │  [returns]
  └─ [returns]
Detailed Memory State at Key Points
Point A: Entry to walk_stack(depth=0)
Stack layout (top to bottom, decreasing address):

Code
┌──────────────────────────────┐
│ Local variables:             │
│  - marker (int) = 0          │  ← 0x7ffc39787b24 (example)
│  - return address            │
│  - saved RBP (frame pointer)  │
├──────────────────────────────┤
│ dump_frame("enter", 0) call: │
│  - label = "enter"           │
│  - depth = 0                 │
│  - local_int (from caller) = 100 │
│  - local_buf = {A, \0, ...}  │  ← 0x7ffc39787ae0
│  - p_local → &local_int      │  ← 0x7ffc39787ad4
├──────────────────────────────┤
│ walk_stack(1, 3) call        │ ← Next frame pushed
└──────────────────────────────┘
Key observation: local_int and marker are distinct variables in the same stack frame. They do not overwrite each other because the compiler allocates separate storage for each.

Point B: Entry to walk_stack(depth=1)
A new stack frame is created. The previous frame (depth=0) remains intact on the stack.

Code
┌──────────────────────────────┐
│ Depth 0 frame (still valid): │
│  - marker = 0                │  ← 0x7ffc39787b24
│  - local_int = 100           │  ← 0x7ffc39787ad4
│  - local_buf[0] = 'A'        │  ← 0x7ffc39787ae0
├──────────────────────────────┤
│ Depth 1 frame (NEW):         │
│  - marker = 10               │  ← 0x7ffc39787af4
│  - local_int = 101           │  ← 0x7ffc39787aa4
│  - local_buf[0] = 'B'        │  ← 0x7ffc39787ab0
├──────────────────────────────┤
│ Depth 2 & 3 frames...        │
└──────────────────────────────┘
Critical fact: Each recursive call gets a distinct memory location for local_int. The addresses differ by ~0x30 bytes (typical stack frame size).

Point C: Maximum Recursion (depth=3)
Code
┌──────────────────────────────┐
│ Depth 0: marker=0            │  0x7ffc39787b24
├──────────────────────────────┤
│ Depth 1: marker=10           │  0x7ffc39787af4
├──────────────────────────────┤
│ Depth 2: marker=20           │  0x7ffc39787ac4
├──────────────────────────────┤
│ Depth 3: marker=30 (TOP)     │  0x7ffc39787a94
└──────────────────────────────┘
All markers coexist simultaneously. Each occupies a unique address.

Point D: Unwinding (Return Path)
As each function returns:

depth=3 exits → its stack frame is deallocated
depth=2 exits → its stack frame is deallocated
depth=1 exits → its stack frame is deallocated
depth=0 exits → the entire call stack is gone
The stack rewinds in reverse order of allocation.

Sample Output Interpretation
Code
[enter] depth=0
  &local_int=0x7ffc39787ad4  p_local=0x7ffc39787ad4  local_int=100
  local_buf=0x7ffc39787ae0  local_buf[0]=A
  &marker=0x7ffc39787b24  marker=0
This confirms:

local_int is stored at 0x7ffc39787ad4 and contains 100
p_local (a pointer) holds the address of local_int
marker is at a higher address (0x7ffc39787b24), proving they are separate variables
local_buf is at 0x7ffc39787ae0
2. heap_example.c — Heap Allocations and Memory Leaks
Program Summary
heap_example dynamically allocates a Person struct on the heap. Each Person contains a char *name that points to separately allocated heap memory.

Struct Definition
C
typedef struct Person {
    char *name;     // Pointer to dynamically allocated string
    int age;        // Integer value
} Person;
Memory Layout
Person Structure
The Person struct itself is 16 bytes on a 64-bit system:

Code
struct Person (16 bytes total)
┌──────────────────┐
│ char *name  (8)  │  ← Points to heap-allocated string
├──────────────────┤
│ int age     (4)  │  ← Value (30 or 41)
│ padding     (4)  │  ← Alignment padding
└──────────────────┘
Execution Trace
Initial state:

Code
alice = NULL  (stack)
bob = NULL    (stack)
After person_new("Alice", 30):

Code
HEAP:
┌─ 0x5555557591a0 (Person struct) ──────────┐
│ name → 0x5555557591b0                      │
│ age = 30                                   │
│ padding                                    │
└────────────────────────────────────────────┘
    ↑
    │
┌─ 0x5555557591b0 (char array) ──────┐
│ "Alice\0" (6 bytes + null term)    │
└────────────────────────────────────┘

STACK:
alice = 0x5555557591a0  (pointer to Person)
bob = NULL
After person_new("Bob", 41):

Code
HEAP:
┌─ 0x5555557591a0 (Person: Alice) ──────────┐
│ name → 0x5555557591b0                      │
│ age = 30                                   │
└────────────────────────────────────────────┘

┌─ 0x5555557591b0 (char: "Alice") ──────────┐
│ A l i c e \0                               │
└────────────────────────────────────────────┘

┌─ 0x5555557591d0 (Person: Bob) ────────────┐
│ name → 0x5555557591e0                      │
│ age = 41                                   │
└────────────────────────────────────────────┘

┌─ 0x5555557591e0 (char: "Bob") ────────────┐
│ B o b \0                                   │
└────────────────────────────────────────────┘

STACK:
alice = 0x5555557591a0
bob = 0x5555557591d0
After Partial Cleanup
C
free(bob->name);   // Deallocates "Bob" string
free(bob);         // Deallocates Bob's Person struct
person_free_partial(alice);  // Deallocates only alice struct, NOT alice->name
Result after cleanup:

Code
HEAP:
┌─ 0x5555557591b0 (char: "Alice") ──────────┐
│ A l i c e \0                               │  ← LEAK: Still allocated!
└────────────────────────────────────────────┘
                                              

Deallocated:
┌─ 0x5555557591a0 (Person: Alice) ──────────┐  ← FREE'D (but...)
│ name → 0x5555557591b0                      │
│ age = 30                                   │
└────────────────────────────────────────────┘

┌─ 0x5555557591d0 (Person: Bob) ────────────┐  ← FREE'D
│ [freed memory]                             │
└────────────────────────────────────────────┘

┌─ 0x5555557591e0 (char: "Bob") ────────────┐  ← FREE'D
│ [freed memory]                             │
└────────────────────────────────────────────┘

STACK:
alice = 0x5555557591a0  (dangling pointer to freed struct)
bob = NULL (or dangling)
Critical Error in the Code
The function person_free_partial() only frees the Person struct itself, not the name string it points to:

C
static void person_free_partial(Person *p) {
    if (!p)
        return;
    free(p);  // ← BUG: Only frees the struct, ignores p->name
}
What should happen:

C
static void person_free_complete(Person *p) {
    if (!p)
        return;
    free(p->name);  // ← FREE the string first
    free(p);        // ← Then free the struct
}
Valgrind Output Interpretation
Valgrind would report:

Code
LEAK SUMMARY:
  still reachable: 6 bytes in 1 blocks  (Alice string)
  lost: 16 bytes in 1 block              (Alice struct, no longer reachable from alice ptr)
The "lost" 16 bytes is actually the freed Alice struct (which we still have a pointer to on the stack, but never use again). The "still reachable" is the unfreed Alice string.

3. aliasing_example.c — Pointer Aliasing and Use-After-Free
Program Summary
aliasing_example demonstrates a classic use-after-free bug through pointer aliasing. Two pointers (a and b) initially point to the same heap memory. After freeing through one pointer, the other becomes a dangling pointer.

Code Walkthrough
C
int main(void) {
    int *a = NULL;
    int *b = NULL;
    
    a = make_numbers(5);     // a → heap block with 5 integers
    b = a;                   // b → same heap block (aliasing!)
    
    printf("a=%p b=%p a[2]=%d b[2]=%d\n", a, b, a[2], b[2]);
    
    free(a);                 // Deallocate the heap block
    
    printf("b=%p (dangling)\n", b);
    printf("b[2]=%d\n", b[2]);   // USE-AFTER-FREE: Reading freed memory
    
    b[3] = 1234;             // USE-AFTER-FREE: Writing to freed memory
    return 0;
}
Memory State Progression
State 1: After make_numbers(5)
Code
HEAP (40 bytes: 5 ints × 4 bytes):
┌───────────────────────────────────────┐
│ arr[0] = 0    (0x7fff1000)           │
│ arr[1] = 11   (0x7fff1004)           │
│ arr[2] = 22   (0x7fff1008)           │
│ arr[3] = 33   (0x7fff100c)           │
│ arr[4] = 44   (0x7fff1010)           │
└───────────────────────────────────────┘

STACK:
a = 0x7fff1000  (points to start of array)
b = NULL
State 2: After b = a
Code
HEAP:
┌───────────────────────────────────────┐
│ arr[0] = 0                            │
│ arr[1] = 11                           │
│ arr[2] = 22                           │
│ arr[3] = 33                           │
│ arr[4] = 44                           │
└───────────────────────────────────────┘
   ↑
   │
BOTH point here

STACK:
a = 0x7fff1000
b = 0x7fff1000  ← ALIASING: a and b point to same memory
At this point, a[2] and b[2] both read the same value (22).

State 3: After free(a)
Code
HEAP:
┌───────────────────────────────────────┐
│ [freed memory / garbage]              │
│ The allocator marks this as free      │
│ Memory is no longer owned by our code │
└───────────────────────────────────────┘

STACK:
a = 0x7fff1000  ← Dangling pointer (invalid)
b = 0x7fff1000  ← Dangling pointer (invalid)
Both pointers now point to freed memory. Any access through either pointer is undefined behavior.

State 4: Accessing freed memory
C
printf("b[2]=%d\n", b[2]);
This reads from the freed heap block at offset +8 bytes (b + 2 = 0x7fff1000 + 8). The value read is unpredictable:

It might still contain 22 (if the allocator hasn't reused the memory)
It might be garbage
It might crash
C
b[3] = 1234;
This writes to offset +12 bytes (b + 3 = 0x7fff1000 + 12). The consequences:

If the allocator reuses this memory for another object, we corrupt that object
If no one else owns it yet, the corruption goes unnoticed until later
This is one of the hardest bugs to find: memory corruption may not crash immediately
Critical Point: Aliasing vs. Dangling Pointers
Aliasing (State 2) is not inherently bad:

C
int x = 10;
int *p1 = &x;
int *q1 = &x;  // Both valid, same address, safe
Dangling pointers (State 3 onwards) are always bad:

C
int *p = malloc(sizeof(int));
free(p);
int *q = p;  // q is now dangling, use of q is undefined behavior
This program combines both:

Valid aliasing (lines up to free(a))
Dangling pointers (lines after free(a))
4. crash_example.c — NULL Pointer Dereference
Program Summary
crash_example allocates memory only if n > 0. Since n = 0, the allocation returns NULL. The program then attempts to dereference this NULL pointer, causing a segmentation fault.

Code Analysis
C
int main(void) {
    int *nums = NULL;
    int n = 0;
    
    nums = allocate_numbers(0);  // Returns NULL because n <= 0
    
    nums[0] = 42;  // Dereference NULL → SEGFAULT
    
    free(nums);    // Never reached
    return 0;
}
Memory State at Crash Point
Code
STACK:
n = 0
nums = NULL  ← 0x0 (the null pointer)

Attempting to execute:
nums[0] = 42
├─ Equivalent to: *(nums + 0) = 42
├─ Equivalent to: *NULL = 42
└─ CPU raises SIGSEGV (segmentation fault)
Why the CPU Crashes
Memory layout (conceptual):

Code
┌──────────────────────────────┐
│ 0x00000000 to 0x0000FFFF     │  ← User space guard page (read-only)
│ Access is prohibited         │
└──────────────────────────────┘
         ↓
┌──────────────────────────────┐
│ User-space memory begins     │
│ 0x00010000 and above         │
└──────────────────────────────┘
Address 0x0 is always protected. The kernel prevents any read or write access to this address. When the CPU tries to execute *NULL, the MMU (memory management unit) traps the access and sends a SIGSEGV signal to the process.

Correct Error Handling
The bug is in the missing error check:

C
// WRONG (no check):
nums = allocate_numbers(n);
nums[0] = 42;  // Crash if nums is NULL

// CORRECT:
nums = allocate_numbers(n);
if (!nums) {
    fprintf(stderr, "Error: allocation failed\n");
    return 1;
}
nums[0] = 42;  // Safe: nums is not NULL
Or, allocate a minimum size:

C
int min_size = (n > 0) ? n : 1;
nums = allocate_numbers(min_size);
AI Explanation Corrections
Common AI Errors Encountered
Error 1: "The stack grows upward"
Incorrect AI claim:

"The stack grows upward, so when recursion deepens, addresses increase."

Reality: On x86-64 (most modern systems), the stack grows downward (toward lower addresses). When a function call happens, rsp decreases, not increases. The addresses in stack_example output confirm this: 0x7ffc39787ad4 (depth 0) > 0x7ffc39787aa4 (depth 1).

Error 2: "The heap block is fully cleaned up after free(a)"
Incorrect AI claim (from heap_example):

"After free(a), all memory is deallocated because alice->name is part of the Person structure."

Reality: The Person struct and the name string are two separate allocations:

malloc(sizeof(Person)) → creates struct block
malloc(len + 1) → creates name string block (separate!)
Freeing only the struct does not free the string. The string remains on the heap until explicitly freed.

Error 3: "Pointer aliasing is a form of memory leak"
Incorrect AI claim (from aliasing_example):

"Two pointers to the same object cause a memory leak because the memory is counted twice."

Reality: Pointer aliasing itself does not cause leaks. Multiple pointers to valid memory are safe. The bug is in the use-after-free, not the aliasing.

Corrected description:

Before free(a): aliasing is fine (both pointers valid)
After free(a): both pointers are dangling, accessing them is undefined behavior
Error 4: "NULL is always address zero"
Incorrect AI claim (sometimes vague):

"The NULL pointer is address 0 on all systems."

Technical reality: NULL represents address 0 conceptually, but:

On some exotic architectures, NULL might have a different representation
The important fact is: NULL is guaranteed to not point to any valid object
The kernel prevents access to address 0 to catch these bugs
For this assignment, we assume standard x86-64 where NULL = 0x0.

