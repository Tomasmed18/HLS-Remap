#include "xf_remap_config.h"

void dilation_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src,xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst, unsigned char kernel[FILTER_SIZE*FILTER_SIZE]);

void ip_accel_app(hls::stream< ap_axiu<8,1,1,1> >& _src,hls::stream< ap_axiu<8,1,1,1> >& _dst,int height,int width, unsigned char kernel[FILTER_SIZE*FILTER_SIZE])
{
#pragma HLS INTERFACE axis register both  port=_src
#pragma HLS INTERFACE axis register both  port=_dst

	static xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> imgInput1(height,width);
	static xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> imgOutput1(height,width);

#pragma HLS stream variable=imgInput1.data dim=1 depth=1
#pragma HLS stream variable=imgOutput1.data dim=1 depth=1
	#pragma HLS dataflow

	xf::AXIvideo2xfMat(_src, imgInput1);

	 dilation_accel(imgInput1,imgOutput1, kernel);

	xf::xfMat2AXIvideo(imgOutput1, _dst);


}
