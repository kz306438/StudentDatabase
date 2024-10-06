#ifndef SCROLLABLE_TEXT_BOX_H
#define SCROLLABLE_TEXT_BOX_H

#include <vector>
#include <fstream>
#include "../../consoleGUI/GUI.h"

namespace widgets
{
    namespace scrollableTextBox
    {
        extern PushButton upFileContent; ///< Button to scroll content up
        extern PushButton downFileContent; ///< Button to scroll content down
        extern std::vector<std::string> currentContent; ///< Vector to hold the current content of the file
        extern std::vector<int> slidingWindow; ///< Vector to hold the indices of the currently displayed lines

        // Constants for text box dimensions and position
        extern const int textBoxHeight; ///< Height of the text box
        extern const int textBoxWidth; ///< Width of the text box
        extern const int textBoxPositionX; ///< X-coordinate of the text box position
        extern const int textBoxPositionY; ///< Y-coordinate of the text box position

        /** @brief Creates the up and down buttons for scrolling.
          * @param posX The x-coordinate for button placement.
          * @param posY The y-coordinate for button placement.
          */
        void create(int posX, int posY);

        /** @brief Sets up the appearance of the buttons. */
        void setup();

        /** @brief Renders the text box and its buttons on the screen. */
        void render();

        /** @brief Scrolls the content up by one line. */
        void scrollFileContentsUp();

        /** @brief Scrolls the content down by one line. */
        void scrollFileContentsDown();

        /** @brief Sets up the current open file and initializes the sliding window.
          * @param path The path of the file to open.
          */
        void setupCurrentOpenFile(const std::string& path);

        /** @brief Displays the current content of the file on the screen. */
        void showFileContent();

    } // namespace scrollableTextBox

} // namespace widgets

#endif // SCROLLABLE_TEXT_BOX_H