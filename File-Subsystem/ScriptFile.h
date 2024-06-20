#pragma once
#include "File.h"

class ScriptFile : public File
{
    String contents;

public:
    ScriptFile(const String& name);

    void print() const override;
    String getContents() const;
    void setContents(const String& contents);
};