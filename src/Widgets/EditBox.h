#pragma once

#include <vector>
#include <string>

namespace widgets
{
    namespace editBox
    {
        // Global variables
        extern std::vector<std::string> currentContent;  // Stores the current content of the edit box
        extern std::vector<int> slidingWindow;           // Tracks visible lines in the edit box

        // Edit box configuration constants
        extern const int editBoxHeight;    // Height of the edit box (in lines)
        extern const int editBoxWidth;     // Width of the edit box (in characters)
        extern const int editBoxPositionX; // X position of the edit box on the console
        extern const int editBoxPositionY; // Y position of the edit box on the console

        // Rendering functions
        /**
         * @brief Renders the edit box frame on the console.
         */
        void render();

        /**
         * @brief Initializes the edit box with the content from the specified file.
         * @param path Path to the file to load content from.
         */
        void setup(const std::string& path);

        /**
         * @brief Loads content from the specified file into currentContent.
         * @param path Path to the file to load content from.
         */
        void getFileContent(const std::string& path);

        // Cursor and text display functions
        /**
         * @brief Displays the cursor at the specified position.
         * @param curPosX X position of the cursor within the edit box.
         * @param curPosY Y position of the cursor within the edit box.
         */
        void displayCursor(int curPosX, int curPosY);

        /**
         * @brief Displays the current text within the edit box.
         * @param curPosX X position of the text to start displaying.
         * @param curPosY Y position of the text to start displaying.
         */
        void displayText(int curPosX, int curPosY);

        // Text editing functions
        /**
         * @brief Handles the Backspace keypress, removing a character at the cursor.
         * @param cursorX Current X position of the cursor.
         * @param cursorY Current Y position of the cursor.
         */
        void handleBackspace(int& cursorX, int& cursorY);

        /**
         * @brief Handles character insertion at the cursor's position.
         * @param cursorX Current X position of the cursor.
         * @param cursorY Current Y position of the cursor.
         * @param ch Character to insert.
         */
        void handleInsert(int& cursorX, int& cursorY, char ch);

        // File saving function
        /**
         * @brief Saves the current content of the edit box to a file.
         * @param path Path to the file to save content to.
         */
        void saveChanges(const std::string& path);

        // Window management functions
        /**
         * @brief Initializes the sliding window for scrolling through the edit box content.
         */
        void initializeSlidingWindow();

        /**
         * @brief Scrolls the content of the edit box one line up.
         */
        void scrollFileContentsUp();

        /**
         * @brief Scrolls the content of the edit box one line down.
         */
        void scrollFileContentsDown();

        /**
         * @brief Processes user input and modifies the cursor position or content accordingly.
         * @param ch Character or key code input by the user.
         * @param cursorX X position of the cursor.
         * @param cursorY Y position of the cursor.
         */
        void processInput(int ch, int& cursorX, int& cursorY);

        // Main edit box handler
        /**
         * @brief Main loop for handling input and updates to the edit box.
         */
        void handleEditBox();

    } // namespace editBox

} // namespace widgets
