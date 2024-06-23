#include "FileName.h"
#include <sstream>

FileName::FileName(const String& fileName) 
{
	const char* beg = fileName.c_str();
	const char* end = fileName.c_str() + fileName.getSize();
	const char* iter = end;

	while (iter != beg && *iter != '.')
	{
		iter--;
	}
	
	if (iter != beg && *iter == '.')
	{
		this->name = fileName.substr(0, iter - beg);
		this->extension = fileName.substr(iter - beg, end - iter);
	}
	else
	{
		this->name = fileName;
        this->extension = "";
	}
}

const String& FileName::getName() const
{
	return name;
}

const String& FileName::getExtension() const
{
	return extension;
}

void FileName::setExtension(const String& extension)
{
	this->extension = extension;
}


void FileName::saveToBinaryFile(std::ofstream& ofs) const
{
	name.saveToBinaryFile(ofs);
	extension.saveToBinaryFile(ofs);
}

void FileName::readFromBinaryFile(std::ifstream& ifs)
{
	name.readFromBinaryFile(ifs);
    extension.readFromBinaryFile(ifs);
}