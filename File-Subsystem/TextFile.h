#pragma once
#include "File.h"

class TextFile : public File
{
    String contents;

public:
    TextFile(const FileName& name);
    
    void print() const override;
    bool isDirectory() const override;
    void setContents(const String& newContetns) override;
    String getContents() const override;

    void saveToBinaryFile(std::ofstream& ofs) const;
    void readFromBinaryFile(std::ifstream& ifs);
};