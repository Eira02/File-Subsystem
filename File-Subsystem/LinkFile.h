#pragma once
#include "File.h"

class LinkFile : public File
{
    String path;

public:
    LinkFile(const String& name, const String& targetPath);
    void print() const override;
};