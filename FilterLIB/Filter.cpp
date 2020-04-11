#include "stdafx.h"
#include "Filter.h"

enum {
	LeftTop,
	CenterTop,
	RightTop,
	LeftMiddle,
	CenterMiddle,
	RightMiddle,
	LeftBottom,
	CenterBottom,
	RightBottom,
};

Filter::Filter(unsigned char* inFile, unsigned char* outFile, int width, int height, int ch) {
	this->inFile = inFile;
	this->outFile = outFile;
	this->width = width;
	this->height = height;
	this->ch = ch;
}

int Filter::FilteringImage(int type) {

	if (type < 0 && type > 2) {
		return RET_FALSE;
	}

	int gyoretsu[3][9] = { {1, 0, -1,		//縦方向ソーベルフィルタ
							2, 0, -2,
							1, 0, -1},
						  { 1, 2, 1,			//横方向ソーベルフィルタ
							0, 0, 0,
							-1, -2, -1},
						  { 0, -1, 0,			//シャープネスフィルタ
							-1, 5, -1,
							0, -1, 0} };

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			for (int c = 0; c < ch; c++) {
				if ((w < 1) || (w > width - 2) || (h < 1) || (h > height - 2)) {		//wは横端またはhが縦端であるときは何もしない
					outFile[(h * width + w) * ch + c] = inFile[(h * width + w) * ch + c];
				}
				else {
					int tmp =
						(int)inFile[((h - 1) * width + (w - 1)) * ch + c] * gyoretsu[type][LeftTop] +
						(int)inFile[((h - 1) * width + (w - 0)) * ch + c] * gyoretsu[type][CenterTop] +
						(int)inFile[((h - 1) * width + (w + 1)) * ch + c] * gyoretsu[type][RightTop] +
						(int)inFile[((h - 0) * width + (w - 1)) * ch + c] * gyoretsu[type][LeftMiddle] +
						(int)inFile[((h - 0) * width + (w - 0)) * ch + c] * gyoretsu[type][CenterMiddle] +
						(int)inFile[((h - 0) * width + (w + 1)) * ch + c] * gyoretsu[type][RightMiddle] +
						(int)inFile[((h + 1) * width + (w - 1)) * ch + c] * gyoretsu[type][LeftBottom] +
						(int)inFile[((h + 1) * width + (w - 0)) * ch + c] * gyoretsu[type][CenterBottom] +
						(int)inFile[((h + 1) * width + (w + 1)) * ch + c] * gyoretsu[type][RightBottom];		//フィルタ処理
					if (tmp > 255) tmp = 255;
					else if (tmp < 0) tmp = 0;
					outFile[(h * width + w) * ch + c] = (unsigned char)tmp;
				}
			}
		}
	}

	return RET_TRUE;
}

Filter::~Filter() {

}