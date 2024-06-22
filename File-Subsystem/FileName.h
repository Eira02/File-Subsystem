#pragma once
#include "String.h"

class FileName
{
	String name;
	String extension;

public:
	FileName(const String& fileName);
	const String& getName() const;
	const String& getExtension() const;

	void setExtension(const String& extension);
};