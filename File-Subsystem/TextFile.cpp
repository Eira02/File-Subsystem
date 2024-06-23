#include "TextFile.h"

TextFile::TextFile(const FileName& name) : File(name) {}


void TextFile::print() const
{
    String firstDate = std::ctime(&creationDate);
    String secondDate = std::ctime(&modificationDate);
    std::cout << "Text File " << "  |" << firstDate.removeNewLine() << " |" << secondDate.removeNewLine() << " |" 
        << name.getName() << name.getExtension();
}

bool TextFile::isDirectory() const
{
    return false;
}

String TextFile::getName() const
{
    return name.getName();
}

String TextFile::getExtension() const
{
    return name.getExtension();
}


void TextFile::setContents(const String& newContents)
{
    contents = newContents;
}

String TextFile::getContents() const
{
    return contents;
}