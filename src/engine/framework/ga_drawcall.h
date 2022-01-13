#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include <string>

/*
** A draw emitted from the simulation phase and rendered in the output phase.
** @see ga_frame_params
*/
struct ga_drawcall
{
	std::string _name;
};
