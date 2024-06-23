#include "LinkFile.h"

LinkFile::LinkFile(const FileName& name) : File(name) {}


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


void LinkFile::setContents(const String& newContents)
{
    path = newContents;
}
    
String LinkFile::getContents() const
{
    return path;
}


void LinkFile::saveToBinaryFile(std::ofstream& ofs) const
{
    File::saveToBinaryFile(ofs);
    path.saveToBinaryFile(ofs);
}

void LinkFile::readFromBinaryFile(std::ifstream& ifs)
{
    File::readFromBinaryFile(ifs);
    path.readFromBinaryFile(ifs);
}