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
	//�R���X�g���N�^
	Filter(unsigned char* inFile, unsigned char* outFile, int width, int height, int ch);

	//�t�B���^���s
	int FilteringImage(int type);

	//�f�X�g���N�^
	~Filter();
};