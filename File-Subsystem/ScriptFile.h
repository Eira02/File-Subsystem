#pragma once
#include "File.h"

class ScriptFile : public File
{
    String contents;

public:
    ScriptFile(const FileName& name);

    void print() const override;
    bool isDirectory() const override;
    String getName() const override;
    String getExtension() const override;
    void setContents(const String& contents) override;
    String getContents() const override;
};