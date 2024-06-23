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


void TextFile::setContents(const String& newContents)
{
    contents = newContents;
}

String TextFile::getContents() const
{
    return contents;
}


void TextFile::saveToBinaryFile(std::ofstream& ofs) const
{
    File::saveToBinaryFile(ofs);
    contents.saveToBinaryFile(ofs);
}

void TextFile::readFromBinaryFile(std::ifstream& ifs)
{
    File::readFromBinaryFile(ifs);
    contents.readFromBinaryFile(ifs);
}