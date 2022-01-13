/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
** test
*/

#include "ga_queue.h"

#include <cassert>
#include <iostream>
#include <thread>

static const int k_node_count = 10000;
static const int k_producer_count = 2;

static void* producer_func(ga_queue* queue, int thread_index);
static void* consumer_func(ga_queue* queue);

void ga_queue_tests()
{
	ga_queue queue(k_node_count);

	// Empty queue test:
	std::cout << "Testing get_count on empty queue..." << std::endl;
	assert(queue.get_count() == 0);
	std::cout << "Testing pop on empty queue..." << std::endl;
	void* data = 0;
	bool result = queue.pop(&data);
	assert(!result);

	// Basic push and pop tests:
	std::cout << "Testing simple push..." << std::endl;
	data = 0;
	queue.push(data);
	data = (void*)1;
	queue.push(data);
	std::cout << "Testing get_count with partially filled queue..." << std::endl;
	assert(queue.get_count() == 2);
	std::cout << "Testing pop with partially filled queue..." << std::endl;
	result = queue.pop(&data);
	assert(result && data == 0);
	result = queue.pop(&data);
	assert(result && data == (void*)1);
	result = queue.pop(&data);
	assert(!result);

	// Thread tests:
	std::cout << "Testing queue with 2 producer threads and 1 consumer thread..." << std::endl;
	std::thread producer0(producer_func, &queue, 0);
	std::thread producer1(producer_func, &queue, 1);
	std::thread consumer(consumer_func, &queue);
	consumer.join();
	producer1.join();
	producer0.join();
}

static void* producer_func(ga_queue* queue, int thread_index)
{
	// XXX: Produce 2x more than our capacity.
	// Force the consumer to actually do work before we complete.
	// (For queues that preallocate elements.)
	for (int i = 0; i < k_node_count * 2; ++i)
	{
		size_t data = (thread_index << 16) | i;
		queue->push((void*)data);
	}

	return 0;
}

static void* consumer_func(ga_queue* queue)
{
	int next_payload[k_producer_count] = { 0 };

	// XXX: Consume data from the queue.
	// Produced data from the two producers will be interleaved.
	// Verify that each producer's data is ordered appropriately.
	// In other words, the queue is giving us FIFO behavior.
	for (int count = 0; count < k_node_count * 4;)
	{
		void* data;
		if (queue->pop(&data))
		{
			int thread_index = (int)(((size_t)data) >> 16);
			int payload = (int)(((size_t)data) & 0xffff);

			assert(payload == next_payload[thread_index]);
			next_payload[thread_index] = payload + 1;

			++count;
		}
	}

	return 0;
}
