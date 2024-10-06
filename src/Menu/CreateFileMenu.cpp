#include "CreateFileMenu.h"

#include <algorithm>
#include <string>
#include <fstream>
#include <thread>

#include "../../consoleGUI/GUI.h"
#include "../Utils.h"
#include "../global.h"

namespace database
{
    struct FileMenuState {
        bool needToCreateFile{};
        bool runEditLine{};
        bool wasLengthWarning{};
        bool wasEmptyWarning{};
        std::string input;
        int cursorPos{};
    };

    static const int editLineWidth = 48;
    static const int editLineHeight = 3;
    static const int editLinePositionX = 36;
    static const int editLinePositionY = 14;
    static const int maxNumOfChar = 14;

    /**
     * @brief Renders the dialog window for the file creation process.
     */
    static void renderDialogWindow()
    {
        Window dialogWindow(50, 8, 35, 4);
        dialogWindow.addWindowName("dialog", 1, 0);
        dialogWindow.show();
    }

    /**
     * @brief Renders the input window where the user enters the file name.
     */
    static void renderInputWindow()
    {
        Window inputWindow(1 + editLineWidth + 1, 1 + editLineHeight + 1, editLinePositionX - 1, editLinePositionY - 1);
        inputWindow.addWindowName("edit line", 1, 0);
        inputWindow.show();

        setcur(50, 5); std::cout << "ENTER NEW FILE NAME!";
        setcur(42, 7); std::cout << "TO ENTER A FILE NAME, PRESS ENTER!";
        setcur(45, 9); std::cout << "TO EXIT PRESS THE ESCAPE KEY!";
    }

    /**
     * @brief Renders the window for displaying error notifications.
     */
    static void renderErrorNotificationsWindow()
    {
        Window errorNotificationsWindow(50, 6, 35, 19);
        errorNotificationsWindow.addWindowName("error notifications", 1, 0);
        errorNotificationsWindow.show();
    }

    /**
     * @brief Renders the entire file creation menu, including dialog, input, and error notification windows.
     *
     * @param state The current state of the file menu.
     */
    static void renderCreateFileMenu(const FileMenuState& state)
    {
        renderDialogWindow();
        renderInputWindow();
        renderErrorNotificationsWindow();
        setcur(37, 15); std::cout << state.input;
    }

    /**
     * @brief Checks if a file with the given name already exists.
     *
     * @param path The file name to check.
     * @return true if the file exists, false otherwise.
     */
    static bool isFileNameDuplicate(const std::string& path)
    {
        for (const auto& fileName : mainDirectory)
        {
            if (fileName == path)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Handles the case when the entered file name is a duplicate.
     *
     * @param state The current state of the file menu.
     */
    static void handleDuplicateFileName(FileMenuState& state)
    {
        Utils::notificationWindow("A FILE WITH THE SAME NAME ALREADY EXISTS!", 61, 9, 30, 10);
        Utils::paintOverBackground();
        renderCreateFileMenu(state);
        setupInputHandling();
    }

    /**
     * @brief Checks if the file can be created, validating against existing files.
     *
     * @param path The file name to check.
     * @param state The current state of the file menu.
     * @return true if the file can be created, false otherwise.
     */
    static bool checkAbilityToCreateFile(const std::string& path, FileMenuState& state)
    {
        if (isFileNameDuplicate(path))
        {
            handleDuplicateFileName(state);
            return false;
        }
        return true;
    }

    /**
     * @brief Prints a problem message at a specified position in the console.
     *
     * @param msg The message to print.
     * @param posX The X position of the message.
     * @param posY The Y position of the message.
     */
    static void printProblem(const std::string& msg, int posX, int posY)
    {
        saveConsoleAttributes();
        setColorBackground(BrightRed);
        setcur(posX, posY);
        std::cout << msg;
        restoreConsoleAttributes();
    }

    /**
     * @brief Initializes the file menu state and prepares for user input.
     *
     * @param state The state to initialize.
     */
    static void setupCreateFileMenu(FileMenuState& state)
    {
        state.input.clear();
        state.wasEmptyWarning = false;
        state.wasLengthWarning = false;
        state.runEditLine = true;
        state.needToCreateFile = true;
        renderCreateFileMenu(state);
        setupInputHandling();
    }

    /**
     * @brief Creates a new file with the given name.
     *
     * @param input The name of the file to create.
     */
    static void createFile(const std::string& input)
    {
        std::fstream file("storage/" + input, std::ios::app);
        if (!file.is_open())
        {
            setupInputHandling();
            Utils::notificationWindow("ERROR! FILE NOT CREATED!", 61, 9, 30, 10);
            return;
        }
        mainDirectory.push_back(input);
        std::sort(mainDirectory.begin(), mainDirectory.end(), std::less<std::string>());

        file.close();

        Utils::saveFiles(pathToFileStorage, mainDirectory);
        Utils::notificationWindow("FILE CREATED SUCCESSFULLY!", 61, 9, 30, 10);
    }

    /**
     * @brief Validates if the key pressed is a valid character for the file name.
     *
     * @param key The key code to validate.
     * @return true if the character is valid, false otherwise.
     */
    static bool isValidCharacter(int key)
    {
        return std::isalpha(key) || std::isspace(key) || std::isdigit(key) || key == '_';
    }

    /**
     * @brief Displays the cursor at the current position of the file name input.
     *
     * @param state The current state of the file menu.
     */
    static void displayCursor(const FileMenuState& state)
    {
        saveConsoleAttributes();
        setColorBackground(White);
        setColorForeground(Black);

        setcur(37 + state.cursorPos, 15);
        std::cout << ((state.cursorPos < state.input.size()) ? state.input[state.cursorPos] : ' ');
        setcur(37 + state.cursorPos, 15);

        restoreConsoleAttributes();
    }

    /**
     * @brief Displays the text entered in the file name input field.
     *
     * @param state The current state of the file menu.
     */
    static void displayText(const FileMenuState& state)
    {
        setcur(37, 15); std::cout << std::string(maxNumOfChar + 1, ' ');
        setcur(37, 15); std::cout << state.input;
    }

    /**
     * @brief Handles the "Enter" key press, validating the input and checking for errors.
     *
     * @param state The current state of the file menu.
     */
    static void handleEnterKey(FileMenuState& state)
    {
        if (state.input.empty())
        {
            if (!state.wasEmptyWarning)
            {
                printProblem("THE FILE NAME CANNOT BE EMPTY!", 45, 21 + state.wasLengthWarning * 2);
                state.wasEmptyWarning = true;
            }
        }
        else
        {
            state.input += ".txt";
            if (!checkAbilityToCreateFile(state.input, state))
            {
                state.input.clear();
                state.cursorPos = 0;
            }
            else
                state.runEditLine = false;
        }
    }

    /**
     * @brief Inserts a character into the file name input.
     *
     * @param key The key code of the character to insert.
     * @param state The current state of the file menu.
     */
    static void handleInsertCharacter(int key, FileMenuState& state)
    {
        if (state.input.length() < maxNumOfChar)
        {
            state.input.insert(state.cursorPos, 1, (char)key);
            state.cursorPos++;
        }
        else if (!state.wasLengthWarning)
        {
            printProblem("MAXIMUM LINE LENGTH 14 CHARACTERS!", 43, 21 + state.wasEmptyWarning * 2);
            state.wasLengthWarning = true;
        }
    }

    /**
     * @brief Handles user input for navigating and editing the file name.
     *
     * @param state The current state of the file menu.
     */
    static void handleInput(FileMenuState& state)
    {
        int key = _getch();

        if (key == 13) {
            handleEnterKey(state);
        }
        else if (key == 27) {
            state.needToCreateFile = false;
            state.runEditLine = false;
        }
        else if (key == 75) {
            if (state.cursorPos > 0) state.cursorPos--;
        }
        else if (key == 77) {
            if (state.cursorPos < state.input.length()) state.cursorPos++;
        }
        else if (key == 8) {
            if (state.cursorPos > 0) {
                state.input.erase(state.cursorPos - 1, 1);
                state.cursorPos--;
            }
        }
        else if (isValidCharacter(key)) {
            handleInsertCharacter(key, state);
        }
    }

    /**
     * @brief Edits the input line where the user enters the file name.
     *
     * @param state The current state of the file menu.
     */
    static void editLine(FileMenuState& state)
    {
        state.cursorPos = 0;

        displayText(state);
        displayCursor(state);

        while (state.runEditLine) {
            handleInput(state);

            displayText(state);
            displayCursor(state);
        }
    }

    /**
     * @brief Entry point for the file creation menu.
     */
    void createFileMenu()
    {
        FileMenuState state;
        setupCreateFileMenu(state);
        editLine(state);

        if (state.needToCreateFile)
            createFile(state.input);
    }

} // namespace database
