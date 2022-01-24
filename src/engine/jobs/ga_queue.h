#pragma once
#include<mutex>;
/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

/*
** Thread-safe queue.
** https://www.research.ibm.com/people/m/michael/podc-1996.pdf
*/
class ga_queue
{
	//Did the double locked version. 

	struct node_t { 
		void* value;
		node_t* next;

	};

	struct queue_t {
		node_t* head;
		node_t* tail;
		std::mutex h_lock;
		std::mutex t_lock;
	};
public:

	queue_t* queue; //Just realized that queue_t out loud is cutie

	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;
};
