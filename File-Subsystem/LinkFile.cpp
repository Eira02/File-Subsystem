#include "LinkFile.h"

LinkFile::LinkFile(const FileName& name, const String& path) : File(name), path(path) {}


void LinkFile::print() const
{
    String firstDate = std::ctime(&creationDate);
    String secondDate = std::ctime(&modificationDate);
    std::cout << "Link File " << "  |" << firstDate.removeNewLine() << " |" << secondDate.removeNewLine() << " |" 
    << name.getName() << name.getExtension();
}

bool LinkFile::isDirectory() const
{
    return false;
}

const String& LinkFile::getName() const
{
    return name.getName();
}