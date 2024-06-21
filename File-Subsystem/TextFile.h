#pragma once
#include "File.h"

class TextFile : public File
{
    String contents;

public:
    TextFile(const String& name);
    
    void print() const override;
    const String& getName() const override;

    String getContents() const;
    void setContents(const String& contents);

};