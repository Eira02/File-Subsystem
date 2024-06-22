#pragma once
#include "Directory.h"

class FileSubsystem
{
    Directory* root;
    Directory* currentDirectory;

    File* navigateToFile(const String& path) const;

public:
    FileSubsystem();
    ~FileSubsystem();

    void changeDirectory(const String& path);
    void printContents(const String& path = "") const;
    void printPathToCurrentDirectory() const;
    void makeDirectory(const String& name);
    void makeFile(const String& name);
};