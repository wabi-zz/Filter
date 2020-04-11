#pragma once

#include <stdio.h>
#define	RET_TRUE	0
#define	RET_FALSE	-1

class Filter {
private:
	unsigned char* inFile;
	unsigned char* outFile;
	int width, height, ch, type;
public:
	//コンストラクタ
	Filter(unsigned char* inFile, unsigned char* outFile, int width, int height, int ch);

	//フィルタ実行
	int FilteringImage(int type);

	//デストラクタ
	~Filter();
};