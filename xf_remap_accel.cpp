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

void init_map_1(xf::Mat<XF_32FC1, HEIGHT, WIDTH, NPC1> & map){
	float f_val = 0.0;
	for(int i= 0; i < HEIGHT * WIDTH; i++){
		map.write_float(i, f_val);
		f_val += 1.0;
		if (f_val > 1080.0)
			f_val = 0.0;
	}
}
void init_map_2(xf::Mat<XF_32FC1, HEIGHT, WIDTH, NPC1> & map){
	float f_val = 0.0;
	for(int i= 0; i < HEIGHT * WIDTH; i++){
			map.write_float(i, f_val);
			f_val += 1.0;
			if (f_val > 1920.0)
				f_val = 0.0;
	}
}

void remap_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src,xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst)
{
	static xf::Mat<XF_32FC1, HEIGHT, WIDTH, NPC1> map_1(HEIGHT, WIDTH);
	static xf::Mat<XF_32FC1, HEIGHT, WIDTH, NPC1> map_2(HEIGHT, WIDTH);
	init_map_1(map_1);
	init_map_2(map_2);

	xf::remap<2, XF_INTERPOLATION_BILINEAR , TYPE, XF_32FC1, TYPE, HEIGHT, WIDTH, NPC1, false>(_src, _dst, map_1, map_2);

}
