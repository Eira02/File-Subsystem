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

    if(strcmp(path.c_str(), "root") == 0)
    {
        current = root;
        return current;
    }
    else if (path.getSize() >= 4 && strncmp(path.c_str(), "root", 4) == 0)
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
        std::cout << std::endl;
        return;
    }
    else
    {
        Directory* current = (Directory*)navigateToFile(path);

        if(current != nullptr && !current->isEmpty())
        {
            std::cout << "Type        |Creation Date            |Modification Date        |Name";
            current->printContents();
            std::cout << std::endl;
            return;
        }
        else if (current == nullptr)
            return;
    }

    std::cout << "Empty directory!" << std::endl;
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
        std::cout << "root";
    else
        std::cout <<  "root/" << path;
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

// command: rm <path>
void FileSubsystem::removeFile(const String& path)
{
    int lastSlashIndex = -1;
    for (int i = path.getSize() - 1; i >= 0; --i) {
        if (path[i] == '/') {
            lastSlashIndex = i;
            break;
        }
    }

    String fileNameOnly = path;
    Directory* parentDir = currentDirectory;

    FileName fname(fileNameOnly);
    if (fname.getExtension() == "")
    {
        std::cout << "Error! File '" << path << "' must include its extension to be removed." << std::endl;
        return;
    }

    if (lastSlashIndex != -1) {
        String dirPath = path.substr(0, lastSlashIndex);
        fileNameOnly = path.substr(lastSlashIndex + 1, path.getSize() - lastSlashIndex - 1);

        parentDir = (Directory*)(navigateToFile(dirPath));
        if (parentDir == nullptr) {
            std::cout << "Error! Directory '" << dirPath << "' not found." << std::endl;
            return;
        }
    }

    File* fileToRemove = navigateToFile(fname.getName());

    if (fileToRemove == nullptr)
    {
        std::cout << "Error! File '" << fileNameOnly << "' not found in directory '" << parentDir->getName() << "'." << std::endl;
        return;
    }
    else if (fileToRemove->isDirectory())
    {
        std::cout << "Error! '" << fileNameOnly << "' is a directory, not a file." << std::endl;
        return;
    }
    
    parentDir->removeFile(fileToRemove->getName());
}

// command: rmdir <path>
void FileSubsystem::removeDirectory(const String& path)
{
    //FileName fname(path);
    //if (fname.getExtension() != "")
    //{
    //    std::cout << "Error! '" << path << "' is not a directory." << std::endl;
    //    return;
    //}

    File* fileToRemove = navigateToFile(path);

    if (fileToRemove == nullptr || !fileToRemove->isDirectory()) 
    {
        std::cout << "Error! Directory '" << path << "' not found." << std::endl;
        return;
    }
    else if (fileToRemove == root)
    {
        std::cout << "Error! Cannot remove 'root' directory." << std::endl;
        return;
    }

    Directory* dirToRemove = (Directory*)(fileToRemove);

    if (!dirToRemove->isEmpty())
    {
        std::cout << "Error! Directory '" << path << "' must be empty to be removed." << std::endl;
        return;
    }

    Directory* parentDir = dirToRemove->getParent();

    if (parentDir != nullptr && currentDirectory != dirToRemove) 
        parentDir->removeFile(dirToRemove->getName());
    else 
    {
        currentDirectory = parentDir;
        parentDir->removeFile(dirToRemove->getName());
    }
}

// command: exec <file path>
void FileSubsystem::executeFile(const String& path)
{
    int lastSlashIndex = -1;
    for (int i = path.getSize() - 1; i >= 0; --i) {
        if (path[i] == '/') {
            lastSlashIndex = i;
            break;
        }
    }

    String fileNameOnly = path;

    FileName fname(fileNameOnly);
    if (fname.getExtension() == "")
    {
        std::cout << "Error! File '" << path << "' must include its extension to be executed." << std::endl;
        return;
    }

    File* fileToExecute = navigateToFile(path);

    if (fileToExecute == nullptr)
    {
        std::cout << "Error! File '" << fileNameOnly << "' not found." << std::endl;
        return;
    }
    else if (fileToExecute->isDirectory())
    {
        std::cout << "Error! '" << fileNameOnly << "' is a directory, not a file." << std::endl;
        return;
    }
    else if (fileToExecute->getExtension() == ".txt")
    {
        std::cout << fileToExecute->getContents() << std::endl;
    } 
    else if (fileToExecute->getExtension() == ".sh")
    {
        // execute the script file
    } 
    else if (fileToExecute->getExtension() == ".lnk")
    {
        executeFile(fileToExecute->getContents());
    } 
    else {
        std::cout << "Error! Unsupported file type for '" << path << "'." << std::endl;
    }
}

// command: echo
 void FileSubsystem::echo(const String& str) const
 {
    std::cout << str << std::endl;
 }

// command: echo <text> > <file> and <text> >> <file>
void FileSubsystem::echoToFile(const String& str, const String& fileName, bool append)
{
    //trqbva i da promenq modification date
    FileName fname(fileName);
    File* file = currentDirectory->getFile(fname.getName());
    
    if (file->isDirectory())
    {
        std::cout << "Error! Cannot echo to a directory." << std::endl;
    }

    if(append)
    {
        // should i add newline between the old and new contents
        file->setContents(file->getContents() + str);
    }
    else
    {
        file->setContents(str);
    }
}

