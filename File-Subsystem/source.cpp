#include <iostream>
#include "TextFile.h"
#include "ScriptFile.h"
#include "LinkFile.h"

// -------/ To Do /-------
// function that executes the script file and if it finds a wrong command it outputs an error
// 


int main()
{
    TextFile file("file.txt");
    file.print();

    std::cout << file.getContents();
    file.setContents("\nasd\nasdasd\nlkmjnh");
    std::cout << file.getContents();

    ScriptFile file1("file.sh");
    std::cout << "\n";
    file1.print();

    LinkFile file2("file.lnk", "path");
    std::cout << "\n";
    file2.print();

    return 0;
}