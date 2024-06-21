#include "ScriptFile.h"

ScriptFile::ScriptFile(const String& name) : File(name) {}

void ScriptFile::print() const
{
    String firstDate = std::ctime(&creationDate);
    String secondDate = std::ctime(&modificationDate);
    std::cout << "Script File " << firstDate.removeNewLine() << " " << secondDate.removeNewLine() << " " << name;
}

const String& ScriptFile::getName() const
{
    return name;
}

String ScriptFile::getContents() const
{
    return contents;
}

void ScriptFile::setContents(const String& contents)
{
    this->contents = contents;
}