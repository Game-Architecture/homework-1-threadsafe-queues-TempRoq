# ga2020-homework1
First homework for RPI Game Architecture 2020.

A thread-safe queue is the backbone of many job/task systems used by games.
In this homework you will implement a thread-safe queue. The interface for
the queue is defined in src/engine/jobs/ga_queue.h. You need to fill in the
details. Go to src/engine/jobs/ga_queue.cpp to do that.

To determine if your queue implementation is functionally correct, the engine
runs some simple unit tests. See src/engine/jobs/ga_queue.tests.cpp.

For this homework:

	You *must* implement the locking queue defined in the paper by Michael and
	Scott: https://www.cs.rochester.edu/~scott/papers/1996_PODC_queues.pdf

	For 10% extra credit, you *may* also implement the lock-free version. The
	lock free version implements a common, but slightly confusing, technique.

	For an additional 10% extra credit, implement the push() and pop() operations
	such that they do not allocate or free from the system heap. Instead
	preallocate node_count elements on queue construction, and free on queue
	destruction. This is another common, but challenging, optimization.
