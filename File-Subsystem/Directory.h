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
    Directory(const FileName& name, Directory* parent = nullptr);
    ~Directory();

    void print() const override;
    void printContents() const;
    bool isDirectory() const override;
    String getName() const override;
    String getExtension() const override;
    void setContents(const String& newContents) override;
    String getContents() const override;

    bool isEmpty()const;
    void addFile(File* file);
    void removeFile(const String& name);
    
    File* getFile(const String& name) const;
    Directory* getParent() const;
};