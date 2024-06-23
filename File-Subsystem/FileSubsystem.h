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
    void removeFile(const String& path);
    void removeDirectory(const String& path);
    void executeFile(const String& path);
    //find
    void echo(const String& str) const;
    void echoToFile(const String& str, const String& fileName, bool append);
};