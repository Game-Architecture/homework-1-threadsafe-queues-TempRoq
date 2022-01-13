/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_hello_component.h"

#include "framework/ga_drawcall.h"

ga_hello_component::ga_hello_component(ga_entity* ent, const char* name) : ga_component(ent), _name(name)
{
}

ga_hello_component::~ga_hello_component()
{
}

void ga_hello_component::update(ga_frame_params* params)
{
	ga_drawcall draw;
	draw._name = _name;

	while (params->_drawcall_lock.test_and_set(std::memory_order_acquire)) {}
	params->_drawcalls.push_back(draw);
	params->_drawcall_lock.clear(std::memory_order_release);

}
