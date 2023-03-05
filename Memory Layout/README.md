# Memory Layout of C/C++ program
Refer: https://www.scaler.com/topics/c/memory-layout-in-c/

After compiling a C program, a binary executable file(.exe) is created, and when we execute the program, this binary file loads into RAM in an organized manner. After being loaded into the RAM, memory layout in C Program has six components which are <b>text segment, initialized data segment, uninitialized data segment, command-line arguments, stack, and heap</b>. Each of these six different segments stores different parts of code and have their own read, write permissions. If a program tries to access the value stored in any segment differently than it is supposed to, it results in a segmentation fault error.

<img src = "https://raw.githubusercontent.com/arhankundu99/CPP/main/Memory%20Layout/Memory%20Layout.png">

What this diagram tells is that text segment addresses < data segment addresses < heap address < stack address. And also we can see in the diagram that stack grows backward and heap grows upward.

### Stack grows backward
```cpp
{
  int x = 5;
  int y = 10;
  
  // this means that address of y < address of x. 
  // And as the memory in stack is allcated in contiguous locations, address of y = address of x - 1. So what happens is
  // that after x is allocated, for allocating y, 
  // the stack pointer is moved by 4 bytes backwards and the address of the stack pointer is returned.
}
```

### Heap grows upward.
What this means is that unlike stack memory allocation, for the above example (Assume x and y are allocated on heap), address of y > address of x.


# Text Segment
After we compile the program, a binary file generates, which is used to execute our program by loading it into RAM. This binary file contains instructions, and these instructions get stored in the text segment of the memory.
Text segment has read-only permission that prevents the program from accidental modifications.

<b>Text Segment is basically the machine code of the program.</b>

# Initialised and Uninitialised Data segment
All the global, static variables fall in this memory layout. Intialised variables fall in initialised data segment and uninitialised data fall in unintialised data segment.

# Stack and Heap

Refer: https://www.youtube.com/watch?v=wJ1L2nSIV1s

```cpp
#include <iostream>
#include <string>

int main()
{
  int value = 5; // allocate this integer on stack
  int arr[2];
  arr[0] = 1;
  arr[1] = 2;
  
  int *hvalue = new int; // new keyword is used to allocate memory on heap
  *hvalue = 5; // allocate this integer on heap
  int *harray = new int[2]; // create an array on heap
  harray[0] = 1;
  harray[1] = 2;
  
  delete hvalue; // memory allocated on heap has to be manually deallocated.
  delete harray[]; // deallocate the memory allocated to harray
}

```
In stack, memory is allocated in contiguous locations <b>unlike the memory allocation on heap which happens on random addresses</b>. In the above example, the address of value and arr is in <b>contiguous location</b>.
When we allocate an integer on stack, we <b>move the stack pointer by 4 bytes backwards and return the stack pointer.</b>.

In the below code, as px and py are allocated contiguous locations, using py, we are able to manipulate the data in px address (Here address of py is more than px which is contradictory to the first diagram, but it depends on the implementation of the compiler).
```cpp
#include <iostream>

int main(){

    int x = 5;
    int y = 10;

    int *px = &x;
    int *py = &y;

    *(py - 1) = 10;

    std::cout << px << " " << (py - 1) << std::endl;
    std::cout << x << " " << y << std::endl;
}

```

In stack, we dont have to worry about deallocation of memory. When the scope ends, the memory gets automatically deallocated. 
But in heap memory, we would have to manually deallocate the memory.

When we allocate heap memory, what internally happens is that <b>we iterate through a free memory list and check if sufficient memory is available to allocate the required space </b>. This takes more time as compared to allocate memory on stack where we just move the stack pointer forward or backward for allocation.
<b>So stack based memory allocation is much faster than heap</b>.

### Why heap?
In case we need to assign some memory which should not be deallocated once the scope ends, we can use heap.

### Why stack memory is lower than heap memory?
Typically, stack memory by default is around 1 or 2 MB, which is significantly lower than the heap memory. We can also get more stack size but increasing the stack size has downsides.
Let's say, we have 32 bit system and also 2 mb stack size by default. That means our system can have maximum 4 GB ram. Now as <b> Different threads get their own stack, </b> that means we would be able
to spawn a maximum of 2048 threads. And if we increase the stack size, the number of threads that we can spawn would become less.

Refer: https://stackoverflow.com/questions/10482974/why-is-stack-memory-size-so-limited

### Heap Memory Fragmentation 
Reference: https://cpp4arduino.com/2018/11/06/what-is-heap-fragmentation.html

Imagine that you have a "large" (32 bytes) expanse of free memory:
```
----------------------------------
|                                |
----------------------------------
```
Now, allocate some of it (5 allocations):
```
----------------------------------
|aaaabbccccccddeeee              |
----------------------------------
```
Now, free the first four allocations but not the fifth:
```
----------------------------------
|              eeee              |
----------------------------------
```
Now try to allocate 16 bytes. Even though we have nearly double memory free, we cannot allocate 16 bytes because there is no contiguous block with 16 bytes size.

#### Why is heap fragmentation bad?
Consequence 1: Unreliable program
By definition, a high fragmentation level means you have a lot of free memory, but you can only allocate small blocks. If your program needs a bigger block, it will not get it and will stop working.

Consequence 2: Degraded performance
A highly fragmented heap is slower because the memory allocator takes more time to find the best hole, the so-called “best-fit.”

#### Heap fragmentation is solved using Virtual memory
The programs running on our computers use Virtual Memory. The value of the pointer is not the physical location in the RAM; instead, the CPU translates the address on the fly. This decoupling allows defragmenting the RAM without moving anything but requires dedicated hardware that we do not have on our microcontrollers.

Heap fragmentation can be reduced by avoid allocation of memory on heap unless required.





