#pragma once
#include "File.h"

class Directory : public File
{
    File** contents;
    size_t size;
    size_t capacity;
    Directory* parent;

    void resize();

public:
    Directory(const String& name, Directory* parent = nullptr);
    ~Directory();

    void addFile(File* file);
    void removeFile(const String& name);
    void print() const override;
    void printContents() const;
    const String& getName() const override;
};