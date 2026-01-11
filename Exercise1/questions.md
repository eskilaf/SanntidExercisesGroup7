Exercise 1 - Theory questions
-----------------------------

### Concepts

What is the difference between *concurrency* and *parallelism*?
> Concurrency is about managing several tasks at the same time. Parallelism is one way of doing this, where work is done at the same time in multiple threads (for example on different processors).

What is the difference between a *race condition* and a *data race*? 
> A race condition is a condition in which the result is dependent on some unknown timing/sequence of events.
A data race occurs if one thread attemps accesses some memory location that is currently being written by another thread, and this happens in such a context that the end result may be wrong.
One example of a data race is the increment decrement situation we looked at. A data race is thus an example of a race condition.
 
*Very* roughly - what does a *scheduler* do, and how does it do it?
> A scheduler manages the assignment of resources to different threads. Here resources are for example the CPU or network links. 
The scheduler wants to manage the resources in an effective way, which may be different based on the problem (througput/latency/wait time etc).

-> How does the scheduler do this


### Engineering

Why would we use multiple threads? What kinds of problems do threads solve?
> We use multiple threads to do different kinds of work at the same time. 
-> Can make more efficient use of CPU by running some other thread while one thread waits for some resource
-> Threads solve the problem of managing multiple independent activities

Some languages support "fibers" (sometimes called "green threads") or "coroutines"? What are they, and why would we rather use them over threads?
> Fibers are thread with well defined start and stop points. It is interrupted only if the fibre allows it.
-> One reason to use this is that is much easier to be sure of data integrity. For example when it comes to the problem of data races
-> Fibres are also called "light weight". Uses less memory and is much faster at context switching. 

Does creating concurrent programs make the programmer's life easier? Harder? Maybe both?
>  Concurrent programs make the programmer's life easier in the sense that they have the ability to solve complex tasks where multiple activities must run at once.
However, concurrent programs introduce problems such as race conditions that the programmer must take care of, and these problems can often be suttle. 

What do you think is best - *shared variables* or *message passing*?
> What is best probably depends on what the goal is. 

Using shared variables will have the possibility of race conditions, and may thus be more error prone. However it may be faster than
message passing, and it is more convenient to access data. 

Message passing on the other hand will be easier to syncronize, and processes are more isolated from each other. Thus probably less prone to bugs. However, may be slowe due to more overhead.

Thus shared variable may be the best option for relatively simple programs that need to run fast.
Message passing may be the best option for larger program that are less time sensitive but more complex. 



