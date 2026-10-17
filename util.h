#pragma once

#include<graphics.h>
#include<cstdlib>
#include<fstream>
#pragma comment(lib, "msimg32.lib") 

inline void putimage_alpha(int x, int y, IMAGE* img) {
	BLENDFUNCTION blend_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, img->getwidth(), img->getheight(),
		GetImageHDC(img), 0, 0, img->getwidth(), img->getheight(), blend_func);
}

inline int rand_range(int x, int y) {
	int num = rand() % y + x;
	return num;
}

inline void write_max_score(int score) {
	std::ofstream out_file("MaxScore.txt");
	out_file << score;
	out_file.close();
}