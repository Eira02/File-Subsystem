#include "LinkFile.h"

LinkFile::LinkFile(const String& name, const String& path) : File(name), path(path) {}

void LinkFile::print() const
{
    String firstDate = std::ctime(&creationDate);
    String secondDate = std::ctime(&modificationDate);
    std::cout << "Link File " << firstDate.removeNewLine() << " " << secondDate.removeNewLine() << " " << name;
}