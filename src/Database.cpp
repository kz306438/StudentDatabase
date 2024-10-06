#include "Database.h"
#include "global.h"
#include "Utils.h"
#include "Menu/MainMenu.h"

#include <Windows.h>
#include <filesystem>
#include <fstream>

namespace database
{

    /**
     * @brief Sets up the database environment.
     *
     * This function creates the storage directory and file if they do not exist.
     */
    static void setup()
    {
        SetConsoleTitleA("Database");

        namespace fs = std::filesystem;

        std::string folderPath = "storage";
        std::string filePath = folderPath + "/fileStorage.txt";

        // Create storage directory if it doesn't exist
        if (!fs::exists(folderPath)) {
            if (!fs::create_directory(folderPath))
                Utils::applicationErrorWindow("ERROR!", 61, 9, 30, 10);
        }

        // Create fileStorage.txt if it doesn't exist
        if (!fs::exists(filePath)) {
            std::ofstream file(filePath);
            if (file.is_open()) {
                file.close();
            }
            else {
                Utils::applicationErrorWindow("ERROR!", 61, 9, 30, 10);
            }
        }

        Utils::loadFiles(pathToFileStorage, mainDirectory); ///< Loads files from the specified storage path.
    }

    /**
     * @brief Executes the main operations of the database.
     *
     * This function sets up the database environment and loads files
     * from the specified storage path before initializing the main menu.
     */
    void run()
    {
        setup();
        mainMenu(); ///< Initializes the main menu.
    }

} // namespace database
