/***************************************************************************
Copyright (c) 2018, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
may be used to endorse or promote products derived from this software 
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/

#include "xf_remap_config.h"
#include "xf_read_map_value.h"

void init_map_x(xf::Mat<XF_32FC1, HEIGHT, WIDTH, NPC1> & map){
	for(int i= 0; i < HEIGHT * WIDTH; i++){
		map.write_float(i, read_map_x_value(i));
	}
}
void init_map_y(xf::Mat<XF_32FC1, HEIGHT, WIDTH, NPC1> & map){
	for(int i= 0; i < HEIGHT * WIDTH; i++){
		map.write_float(i, read_map_y_value(i));
	}
}

void remap_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src, xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst)
{
	 xf::Mat<XF_32FC1, HEIGHT, WIDTH, NPC1> map_x(HEIGHT, WIDTH);
	 xf::Mat<XF_32FC1, HEIGHT, WIDTH, NPC1> map_y(HEIGHT, WIDTH);
	init_map_x(map_x);
	init_map_y(map_y);

	xf::remap<REMAP_WIN_ROWS, XF_INTERPOLATION_BILINEAR , TYPE, XF_32FC1, TYPE, HEIGHT, WIDTH, NPC1, false>(_src, _dst, map_x, map_y);

}
