#pragma once
#include "File.h"

class TextFile : public File
{
    String contents;

public:
    TextFile(const FileName& name);
    
    void print() const override;
    bool isDirectory() const override;
    String getName() const override;
    String getExtension() const override;
    void setContents(const String& newContetns) override;
    String getContents() const override;
};