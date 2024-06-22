#include "FileSubsystem.h"
#include "TextFile.h"
#include "ScriptFile.h"
#include "LinkFile.h"
#include <sstream>
#include <cstring>
#pragma warning (disable : 4996)

File* FileSubsystem::navigateToFile(const String& path) const
{
    std::stringstream ss(path.c_str());
    Directory* current = currentDirectory;

    if (path.getSize() >= 4 && strncmp(path.c_str(), "root", 4) == 0)
    {
        current = root;
        ss.seekg(4);
    }
    else if (path.getSize() == 1 && strcmp(path.c_str(), "/") == 0)
    {
        std::cout << "Error! Invalid path: " << path << std::endl;
        return nullptr;
    }

    char buff[256];
    while (ss.getline(buff, 256, '/'))
    {
        if (strcmp(buff, "") == 0) continue;
        
        if (strcmp(buff, "..") == 0) {
            if (current->getParent() != nullptr) 
                current = current->getParent();
            else 
            {
                std::cout << "Error! Cannot move up from root directory." << std::endl;
                return nullptr;
            }
        } 
        else 
        {
            File* file = current->getFile(buff);

            if (file == nullptr)
            {   
                std::cout << "Error! Invalid path: " << path << std::endl;
                return nullptr;
            }
            else if (ss.peek() == EOF)
            {
                return file;
            }
            else if (!file->isDirectory())
            {
                std::cout << "Error! Invalid path: " << path << std::endl;
                return nullptr;
            }

            current = (Directory*)(file);
        }
    }
    
    return current;
}

FileSubsystem::FileSubsystem() 
{
    root = new Directory(FileName("root"), nullptr);
    currentDirectory = root;
}

FileSubsystem::~FileSubsystem() 
{
    delete root;
}

// command: cd <path>
void FileSubsystem::changeDirectory(const String& path)
{
    Directory* current = (Directory*)navigateToFile(path);

    if(current != nullptr)
        currentDirectory = current;
}

// commands: ls and ls <path> 
void FileSubsystem::printContents(const String& path) const
{
    if(path == "" && !currentDirectory->isEmpty())
    {
        std::cout << "Type        |Creation Date            |Modification Date        |Name";
        currentDirectory->printContents();
        return;
    }
    else
    {
        Directory* current = (Directory*)navigateToFile(path);

        if(current != nullptr && !current->isEmpty())
        {
            std::cout << "Type        |Creation Date            |Modification Date        |Name";
            current->printContents();
            return;
        }
        else if (current == nullptr)
            return;
    }

    std::cout << "Empty directory!";
}

// command: pwd
void FileSubsystem::printPathToCurrentDirectory() const 
{
    Directory* current = currentDirectory;
    String path;

    while (current != root)
    {
        if (path.getSize() == 0)
        {
            path = current->getName();
        }
        else
        {
            path = current->getName() + "/" + path;
        }
        
        current = current->getParent();
    }

    if (path.getSize() == 0)
        std::cout << "root" << std::endl;
    else
        std::cout <<  "root/" << path << std::endl;
}

// command: mkdir <directory name>
void FileSubsystem::makeDirectory(const String& name) 
{
    FileName fname(name);
    if(fname.getExtension() != "")
    {
        std::cout << "Error! '" << name << "' is invalid name for a directory." << std::endl;
        return;
    }

    File* existingFile = currentDirectory->getFile(fname.getName());

    if (existingFile != nullptr && existingFile->isDirectory())
    {
        std::cout << "Error: Directory with the name '" << fname.getName() << "' already exists." << std::endl;
        return;
    }
    else if (existingFile != nullptr)
    {
        std::cout << "Error: File with the name '" << fname.getName() << "' already exists." << std::endl;
        return;
    }

    currentDirectory->addFile(new Directory(fname, currentDirectory));
}

// command: touch <file name>
void FileSubsystem::makeFile(const String& name) 
{
    FileName fname(name);
    String extension = fname.getExtension();

    File* existingFile = currentDirectory->getFile(fname.getName());
    
    if (existingFile != nullptr)
    {
        //update the modification date
        return;
    }

    if (extension == ".sh") 
        currentDirectory->addFile(new ScriptFile(fname));
    else if (extension == ".lnk") 
        currentDirectory->addFile(new LinkFile(fname, ""));
    else if (extension == ".txt") 
        currentDirectory->addFile(new TextFile(fname));
    else if (extension == "")
    {
        fname.setExtension(".txt");
        currentDirectory->addFile(new TextFile(fname));
    }
    else 
        std::cout << "Error! Unsupported file extension '" << extension << "'." << std::endl;
}