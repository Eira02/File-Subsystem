#pragma once
#include "String.h"
#include "FileName.h"
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
    virtual String getName() const = 0;
    virtual String getExtension() const = 0;
    virtual void setContents(const String& newContetns) = 0;
    virtual String getContents() const = 0;
};