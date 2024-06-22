#pragma once
#include "File.h"

class ScriptFile : public File
{
    String contents;

public:
    ScriptFile(const FileName& name);

    void print() const override;
    bool isDirectory() const override;
    const String& getName() const override;

    String getContents() const;
    void setContents(const String& contents);
};