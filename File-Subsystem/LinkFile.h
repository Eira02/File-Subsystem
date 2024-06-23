#pragma once
#include "File.h"

class LinkFile : public File
{
    String path;

public:
    LinkFile(const FileName& name, const String& targetPath);

    void print() const override;
    bool isDirectory() const override;
    String getName() const override;
    String getExtension() const override;
    void setContents(const String& newContents) override;
    String getContents() const override;
};