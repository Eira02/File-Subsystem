#pragma once
#include "File.h"

class ScriptFile : public File
{
    String contents;

public:
    ScriptFile(const FileName& name);

    void print() const override;
    bool isDirectory() const override;
    void setContents(const String& contents) override;
    String getContents() const override;

    void saveToBinaryFile(std::ofstream& ofs) const;
    void readFromBinaryFile(std::ifstream& ifs);
};