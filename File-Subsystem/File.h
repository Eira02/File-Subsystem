#pragma once
#include "String.h"
#include "FileName.h"
#include <fstream>
#include <ctime>

class File
{
protected:
    FileName name;
    std::time_t creationDate;
    std::time_t modificationDate;
    
public:
    File(const FileName& name) : name(name), creationDate(std::time(nullptr)), modificationDate(creationDate) {}
    virtual ~File() = default;
    
    virtual void print() const = 0;
    virtual bool isDirectory() const = 0;
    virtual void setContents(const String& newContetns) = 0;
    virtual String getContents() const = 0;

    String getName() const { return name.getName(); }
    String getExtension() const { return name.getExtension(); }
    void updateModificationDate() { modificationDate = std::time(nullptr); }

    void saveToBinaryFile(std::ofstream& ofs) const
    {
        name.saveToBinaryFile(ofs);

        ofs.write((const char*)&creationDate, sizeof(creationDate));
        ofs.write((const char*)&modificationDate, sizeof(modificationDate));
    }

    void readFromBinaryFile(std::ifstream& ifs)
    {
        name.readFromBinaryFile(ifs);

        ifs.read((char*)&creationDate, sizeof(creationDate));
        ifs.read((char*)&modificationDate, sizeof(modificationDate));
    }
};