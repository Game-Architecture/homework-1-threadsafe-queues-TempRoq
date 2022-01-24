/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"
ga_queue::ga_queue(int node_count)
{
	node_t* node = new node_t();				//Initialize a new node and queue
	this->queue = new queue_t();
	node->next = NULL;							//Needs a next, but ensure it's null and not garbage data. Always a dummy node.
	queue->head = node;							//The head and tail are the dummy node.
	queue->tail = node;

	// TODO:
	// Initialize the queue.
	// For extra credit, preallocate 'node_count' elements (instead of
	// allocating on push).
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

ga_queue::~ga_queue()
{



	queue->h_lock.lock();						//Double locks
	queue->t_lock.lock();
	node_t* n;
	int i = 1;
	while (queue->head != nullptr) {			//Iterate through the linked list by getting a reference to head, making head  = head -> next, and iterate until head is a null pointer.
		n = queue->head;
		queue->head = queue->head->next;
		free(n->next);
	}
	queue->h_lock.unlock();						//Double unlocks
	queue->t_lock.unlock();
	free(n);									//free n
	free(queue);								//free the queue


	// TODO:
	// Free any resources held by the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

void ga_queue::push(void* data)
{
	node_t* n = new node_t();					//Make a new node
	n->value = data;							//Fill it with relevant data
	n->next = NULL;
	queue->t_lock.lock();						//Lock the tail, put on the new node, set the prior tail to connect to this through next, and set this to be the new tail
	queue->tail->next = n;
	queue->tail = n;
	queue->t_lock.unlock();						//Unlock the tail

	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
}

bool ga_queue::pop(void** data)
{
	queue->h_lock.lock();						//Lock the head, get a reference to the head, and head -> next
	node_t* n = queue->head;
	node_t* new_head = n->next;
	if (new_head == nullptr) {					//IF the head is null, unlock it and do nothing and return false
		queue->h_lock.unlock();
		return false;
	}

	*data = new_head->value;					//Reference to popped's value and send it to data
	queue->head = new_head;						//set head to new head and unlock head. Free n and return true
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
	unsigned int count = 0;						//returned value
	node_t* n = queue->head;					//Start from the head and increment count for every node.
	if (n->next == nullptr) {
		return 0;								//Starting case to ensure that no empty / null / just initialized queues arise.
	}
	while (n != nullptr) {						//keep going until the iterator node is null
		count += 1;			
		n = n->next;
	}
	return count - 1;							//Count is subtracted by one to account for the dummy node at the head;
}
