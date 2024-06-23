#include <iostream>
#include "TextFile.h"
#include "ScriptFile.h"
#include "LinkFile.h"
#include "Directory.h"
#include "FileSubsystem.h"

int main()
{
    FileSubsystem fs;

    // cd dir1
    fs.changeDirectory("dir1");

    // mkdir dir1
    fs.makeDirectory("dir1");
    
    // ls
    fs.printContents();
    std::cout << std::endl;

    // ls dir1
    fs.printContents("dir1");
    std::cout << std::endl;

    // ls dir2
    fs.printContents("dir2");

    // cd dir1
    // mkdir subdir1-1 ...
    fs.changeDirectory("dir1");
    fs.makeDirectory("subdir1-1");
    fs.makeDirectory("subdir1-2");
    fs.makeDirectory("subdir1-3");

    // cd subdir1-1
    fs.changeDirectory("subdir1-1");
    // pwd
    fs.printPathToCurrentDirectory();

    // cd ..
    fs.changeDirectory("..");
    // mkdir subdir1-2
    fs.makeDirectory("subdir1-2");
    // mkdir dir.txt
    fs.makeDirectory("dir.txt");

    // touch file
    fs.makeFile("file");
    // touch file.txt
    fs.makeFile("file.txt");

    // ls
    fs.printContents();
    std::cout << std::endl;
    std::cout << std::endl;

    // touch file1.sh
    fs.makeFile("file1.sh");

    // touch file2.lnk
    fs.makeFile("file2.lnk");

    // ls
    fs.printContents();
    std::cout << std::endl;
    std::cout << std::endl;

    // touch file3.dat
    fs.makeFile("file3.dat");

    // mkdir file2
    fs.makeDirectory("file2");

    // cd root/dir1/subdir1-3
    fs.changeDirectory("root/dir1/subdir1-3");

    // ls
    fs.printContents();
    std::cout << std::endl;
    std::cout << std::endl;

    // cd root
    fs.changeDirectory("root");

    // ls
    fs.printContents();
    std::cout << std::endl;
    std::cout << std::endl;

    // rm root/dir1/subdir1-1  da probvam s tovafs.removeFile("root/dir1/subdir1-1.asd");
    fs.removeFile("root/dir1/subdir1-1");

    // cd dir1
    fs.changeDirectory("dir1");
    // rm file3.dat
    fs.removeFile("file3.dat");

    // rm file1
    fs.removeFile("file1");
    // ls
    fs.printContents();
    std::cout << std::endl;
    std::cout << std::endl;

    // rm file
    fs.removeFile("file.txt");
    // ls
    fs.printContents();
    std::cout << std::endl;
    std::cout << std::endl;


    // rmdir subdir1-1
    fs.removeDirectory("subdir1-1");

    // ls
    fs.printContents();
    std::cout << std::endl;
    std::cout << std::endl;

    // rmdir root/dir1
    fs.removeDirectory("root/dir1");

    // rmdir root
    fs.removeDirectory("root");

    // rmdir root/dir2
    fs.removeDirectory("root/dir2");

    // rmdir root/dir1/file2.lnk
    fs.removeDirectory("root/dir1/file2.lnk");

    // rmdir root/dir1/file2.lnk
    fs.removeDirectory("root/dir1/file2");

    return 0;
}