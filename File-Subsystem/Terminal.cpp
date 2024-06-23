#include "Terminal.h"
#include <sstream>

void Terminal::run() {
    String command;
    while (true)
    {
        fileSubsystem.printPathToCurrentDirectory();
        std::cout << "# ";

        std::cin >> command;

        if (command == "exit")
        {
            //fileSubsystem.saveToFile("filesystem.txt");
            break;
        }
        else if (command == "pwd")
        {
            fileSubsystem.printPathToCurrentDirectory();
            std::cout << std::endl;
        }
        else if (command == "ls")
        {   
            if(std::cin.get() == '\n')
                fileSubsystem.printContents();
            else
            {
                std::cin >> command;
                fileSubsystem.printContents(command);
            }   
        }
        else if (command == "cd")
        {
            std::cin >> command;
            fileSubsystem.changeDirectory(command);
        }
        else if (command == "mkdir")
        {
            std::cin >> command;
            fileSubsystem.makeDirectory(command);
        }
        else if (command == "touch")
        {
            std::cin >> command;
            fileSubsystem.makeFile(command);
        }
        else if (command == "rm")
        {
            std::cin >> command;
            fileSubsystem.removeFile(command);
        }
        else if (command == "rmdir")
        {
            std::cin >> command;
            fileSubsystem.removeDirectory(command);
        }
        else if (command == "exec")
        {
            std::cin >> command;
            fileSubsystem.executeFile(command);
        }
        else if (command == "echo")
        {
            String text;

            while(std::cin >> command && command != ">" && command != ">>")
            {
                text += command + " ";
                if(std::cin.get() == '\n')
                {
                    fileSubsystem.echo(text);
                    break;
                }
            }

            if(command != ">" && command != ">>")
                continue;

            String fileName;
            std::cin >> fileName;

            if (command == ">")
                fileSubsystem.echoToFile(text, fileName, 0);
            else if (command == ">>")
                fileSubsystem.echoToFile(text, fileName, 1);
            else
                std::cout << "Error!" << std::endl;
        }
        else
        {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }
}