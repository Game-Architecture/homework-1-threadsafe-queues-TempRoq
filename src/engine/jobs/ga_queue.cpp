/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"
#include <iostream>;
ga_queue::ga_queue(int node_count)
{
	node_t* node = new node_t();
	this->queue = new queue_t();
	node->next = NULL;
	queue->head = node;
	queue->tail = node;

	// TODO:
	// Initialize the queue.
	// For extra credit, preallocate 'node_count' elements (instead of
	// allocating on push).
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

ga_queue::~ga_queue()
{
	queue->h_lock.lock();
	queue->t_lock.lock();
	node_t* n;
	int i = 1;
	while (queue->head != nullptr) {
		std::cout << i << std::endl;
		n = queue->head;
		queue->head = queue->head->next;
		free(n->next);
	}
	queue->h_lock.unlock();
	queue->t_lock.unlock();
	free(n);
	free(queue);


	// TODO:
	// Free any resources held by the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

void ga_queue::push(void* data)
{
	node_t* n = new node_t();
	n->value = data;
	n->next = NULL;
	queue->t_lock.lock();
	queue->tail->next = n;
	queue->tail = n;
	queue->t_lock.unlock();

	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
}

bool ga_queue::pop(void** data)
{
	queue->h_lock.lock();
	node_t* n = queue->head;
	node_t* new_head = n->next;
	if (new_head == nullptr) {
		queue->h_lock.unlock();
		return false;
	}

	*data = new_head->value;
	queue->head = new_head;
	queue->h_lock.unlock();
	free(n);
	return true;
	// TODO:
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.

}

int ga_queue::get_count() const
{
	unsigned int count = 0;
	node_t* n = queue->head;
	if (n->next == nullptr) {
		return 0;
	}
	while (n != nullptr) {
		count += 1;
		n = n->next;
	}
	std::cout << count << std::endl;
	return count - 1; //Count is subtracted by one to account for the dummy node at the head;
}
