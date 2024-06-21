#include "Directory.h"
#include <iostream>
#include <cstring>

Directory::Directory(const String& name, Directory* parent)
    : File(name), contents(new File*[2]), size(0), capacity(2), parent(parent) {}

Directory::~Directory() {
    for (size_t i = 0; i < size; ++i) {
        delete contents[i];
    }
    delete[] contents;
}

void Directory::resize() {
    capacity *= 2;
    File** newContents = new File*[capacity];
    for (size_t i = 0; i < size; ++i) {
        newContents[i] = contents[i];
    }
    delete[] contents;
    contents = newContents;
}

void Directory::addFile(File* file) {
    if (size == capacity) {
        resize();
    }
    contents[size++] = file;
}

void Directory::removeFile(const String& name) {
    for (size_t i = 0; i < size; ++i) {
        if (contents[i]->getName() == name) {
            delete contents[i];
            for (size_t j = i; j < size - 1; ++j) {
                contents[j] = contents[j + 1];
            }
            --size;
            contents[size] = nullptr;
            return;
        }
    }
    std::cerr << "File or directory not found: " << name << std::endl;
}

void Directory::print() const {
    String firstDate = std::ctime(&creationDate);
    String secondDate = std::ctime(&modificationDate);
    std::cout << "Directory " << firstDate.removeNewLine() << " " << secondDate.removeNewLine() << " " << name;
}

void Directory::printContents() const
{
    for(int i = 0; i < size; i++)
    {
        std::cout << std::endl;
        contents[i]->print();
    }
}

const String& Directory::getName() const {
    return name;
}