#ifndef FILE_SLIDER_H
#define FILE_SLIDER_H

#include <vector>
#include <string>
#include "../../consoleGUI/GUI.h"
#include "../global.h"

namespace widgets
{
    namespace fileSlider
    {
        extern PushButton upFile, file1, file2, file3, file4, file5, downFile; ///< File navigation buttons
        extern std::vector<int> slidingFileWindow; ///< Vector holding the currently displayed file indices

        /** @brief Initializes the sliding file window with the first five file indices. */
        void setupSlidingFileWindow();

        /** @brief Moves the sliding file window up by one index. */
        void moveSlidingFileWindowUp();

        /** @brief Moves the sliding file window down by one index. */
        void moveSlidingFileWindowDown();

        /** @brief Creates buttons for file navigation at specified coordinates.
          * @param posX The x-coordinate for button placement.
          * @param posY The y-coordinate for button placement.
          */
        void createFilesButtons(int posX, int posY);

        /** @brief Updates the names of the file buttons based on the current sliding window. */
        void updateFileButtonNames();

        /** @brief Sets up the appearance of all file buttons. */
        void setupFileButtons();

        /** @brief Renders the file slider at specified coordinates.
          * @param posX The x-coordinate for the file slider.
          * @param posY The y-coordinate for the file slider.
          */
        void renderFileSlider(int posX, int posY);

        /** @brief Securely retrieves the filename based on the provided index.
          * @param index The index of the file to retrieve.
          * @return The name of the file if valid; otherwise, an empty string.
          */
        inline std::string getFileName(int index) {
            return index < database::mainDirectory.size() ? database::mainDirectory[index] : "";
        }

    } // namespace fileSlider

} // namespace widgets

#endif // FILE_SLIDER_H