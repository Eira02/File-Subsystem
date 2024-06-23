#pragma once
#include "File.h"

class LinkFile : public File
{
    String path;

public:
    LinkFile(const FileName& name);

    void print() const override;
    bool isDirectory() const override;
    void setContents(const String& newContents) override;
    String getContents() const override;

    void saveToBinaryFile(std::ofstream& ofs) const;
    void readFromBinaryFile(std::ifstream& ifs);
};