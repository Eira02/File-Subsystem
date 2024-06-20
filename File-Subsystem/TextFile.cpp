#include "TextFile.h"

TextFile::TextFile(const String& name) : File(name) {}

void TextFile::print() const
{
    String firstDate = std::ctime(&creationDate);
    String secondDate = std::ctime(&modificationDate);
    std::cout << "Text File " << firstDate.removeNewLine() << " " << secondDate.removeNewLine() << " " << name;
}

String TextFile::getContents() const
{
    return contents;
}

void TextFile::setContents(const String& contents)
{
    this->contents = contents;
}