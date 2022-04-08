#pragma once

#include "Headers.h"

using namespace  cv;

class Texture
{
	private:
		unsigned int m_RendererID;
		std::string PathFile;
		Mat Image;

	public:
		Texture(Mat image);
		~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;
};