#include "ScriptFile.h"

ScriptFile::ScriptFile(const FileName& name) : File(name) {}


void ScriptFile::print() const
{
    String firstDate = std::ctime(&creationDate);
    String secondDate = std::ctime(&modificationDate);
    std::cout << "Script File " << "|" << firstDate.removeNewLine() << " |" << secondDate.removeNewLine() << " |" 
    << name.getName() << name.getExtension();
}

bool ScriptFile::isDirectory() const
{
    return false;
}


void ScriptFile::setContents(const String& newContents)
{
    contents = newContents;
}

String ScriptFile::getContents() const
{
    return contents;
}


void ScriptFile::saveToBinaryFile(std::ofstream& ofs) const
{
    File::saveToBinaryFile(ofs);
    contents.saveToBinaryFile(ofs);
}

void ScriptFile::readFromBinaryFile(std::ifstream& ifs)
{
    File::readFromBinaryFile(ifs);
    contents.readFromBinaryFile(ifs);
}