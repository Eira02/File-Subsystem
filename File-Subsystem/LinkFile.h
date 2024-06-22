#pragma once
#include "File.h"

class LinkFile : public File
{
    String path;

public:
    LinkFile(const FileName& name, const String& targetPath);

    void print() const override;
    bool isDirectory() const override;
    const String& getName() const override;
};