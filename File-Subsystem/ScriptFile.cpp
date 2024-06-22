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

const String& ScriptFile::getName() const
{
    return name.getName();
}


String ScriptFile::getContents() const
{
    return contents;
}

void ScriptFile::setContents(const String& contents)
{
    this->contents = contents;
}