#include <iostream>
#include "TextFile.h"
#include "ScriptFile.h"
#include "LinkFile.h"
#include "Directory.h"

// -------/ To Do /-------
// function that executes the script file and if it finds a wrong command it outputs an error
// 


int main()
{
    Directory root("root", nullptr);

    TextFile* file0 = new TextFile("file0.txt");
    ScriptFile* file1 = new ScriptFile("file1.sh");
    LinkFile* file2 = new LinkFile("file2.lnk", "");

    Directory* dir1 = new Directory("dir1", &root);

    root.addFile(file0);
    root.addFile(file1);
    root.addFile(file2);
    root.addFile(dir1);

    root.printContents();

    root.removeFile("file1.sh");
    std::cout << "\n-------------------------------------------------------";
    root.printContents();
}