#pragma once

struct Mouse 
{
	Mouse() 
	{
		x = 0;
		y = 0;

		left_button = false;
		right_button = false;
	}

	float x;
	float y;

	bool left_button;
	bool right_button;
};