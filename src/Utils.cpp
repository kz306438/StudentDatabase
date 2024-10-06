#include "Utils.h"

#include <climits>
#include "../consoleGUI/GUI.h"
#include <fstream>
#include <algorithm>
#include <sstream>

namespace Utils
{
    /** @brief Fills the background with a color. */
    void paintOverBackground()
    {
        setColorBackground(BrightBlue);
        system("cls");
    }

    /** @brief Prints the logo at specified coordinates.
     *  @param x X-coordinate for the logo position.
     *  @param y Y-coordinate for the logo position.
     */
    void printLogo(int x, int y)
    {
        std::vector<std::vector<char>> databaseImage =
        {
            {' ',char(219),char(219),char(219),char(219),' ',' ',' ',' ',' ',' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),char(219),char(219),char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),char(219),char(219),char(219),' ',' ',' ',' ',' ',' ',char(219),char(219),' ',' ',' ',' ',' ',' ',char(219),char(219),char(219),char(219),' ',' ',' ',' ',char(219),char(219),char(219),char(219),char(219),char(219)},
            {' ',char(219),char(219),' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),char(219),char(219),' ',' ',' ',' ',' ',' ',char(219),char(219),' ',' ',' ',' ',' ',' ',char(219),char(219),char(219),char(219),' ',' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',' ',char(219),char(219),char(219),char(219),' ',' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219)},
            {' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),' ',' ',' ',' ',' ',' ',' ',char(219),char(219)},
            {' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),char(219),char(219),char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),char(219),char(219),char(219),char(219),' ',' ',' ',char(219),char(219),char(219),char(219),char(219),' ',' ',' ',' ',char(219),char(219),char(219),char(219),char(219),char(219),' ',' ',' ',' ',char(219),char(219),char(219),char(219),' ',' ',' ',' ',char(219),char(219),char(219),char(219)},
            {' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',' ',' ',' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219)},
            {' ',char(219),char(219),' ',char(219),char(219),' ',' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219)},
            {' ',char(219),char(219),char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',char(219),char(219),char(219),char(219),char(219),' ',' ',' ',' ',char(219),char(219),' ',' ',char(219),char(219),' ',' ',' ',' ',char(219),char(219),char(219),char(219),' ',' ',' ',' ',char(219),char(219),char(219),char(219),char(219),char(219)}
        };

        for (int i = 0; i < databaseImage.size(); i++)
        {
            std::string output;
            for (int j = 0; j < databaseImage[i].size(); j++)
                output += databaseImage[i][j];

            setcur(x, y + i);
            std::cout << output;
        }
    }

    /** @brief Clears the input buffer. */
    void clearInput()
    {
        std::cin.clear(); // Clear error flags
        std::cin.ignore(999, '\n'); // Discard input until a newline
    }

    /** @brief Loads filenames from a specified path into a vector.
     *  @param path Path to the file containing filenames.
     *  @param files Vector to store the loaded filenames.
     */
    void loadFiles(const std::string& path, std::vector<std::string>& files)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            setcur(0, 0);
            std::cout << "FILE DOWNLOAD ERROR";
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            files.push_back(line);
        }
        file.close();

        std::sort(files.begin(), files.end()); // Sort the filenames alphabetically
    }

    /** @brief Saves filenames from a vector to a specified path.
     *  @param path Path where the filenames will be saved.
     *  @param files Vector containing filenames to save.
     */
    void saveFiles(const std::string& path, const std::vector<std::string>& files)
    {
        std::ofstream file(path);

        if (!file.is_open())
        {
            setcur(0, 0);
            std::cout << "SAVE ERROR!";
            return;
        }

        for (const auto& fileName : files)
        {
            file << fileName << std::endl; // Write each filename to the file
        }

        file.close();
    }

    /** @brief Converts an array of uint16_t to a string.
     *  @param array Vector of uint16_t to convert.
     *  @return String representation of the array.
     */
    std::string arrayToString(const std::vector<uint16_t>& array)
    {
        std::stringstream ss;

        for (size_t i = 0; i < array.size(); ++i)
        {
            if (i != 0) {
                ss << " "; // Add space between elements
            }
            ss << array[i]; // Append each element to the string stream
        }
        return ss.str(); // Return the constructed string
    }

    /** @brief Displays a confirmation dialog.
     *  @param head Title of the dialog.
     *  @param width Width of the dialog.
     *  @param height Height of the dialog.
     *  @param posX X-coordinate of the dialog position.
     *  @param posY Y-coordinate of the dialog position.
     *  @return True if confirmed, false otherwise.
     */
    bool confirmDialog(const std::string& head, int width, int height, int posX, int posY)
    {
        bool returnValue = false;
        bool stopDialogWindow = false;

        Window dialogWindow(width, height, posX, posY);
        dialogWindow.show(); // Show the dialog window

        setcur(width / 2 - head.size() / 2 + posX, posY + 1);
        std::cout << head; // Display the title

        PushButton OK(width / 2 - 1, 3, "OK", posX + 1, posY + height - 4);
        PushButton cancel(width / 2 - 1, 3, "CANCEL", posX + width / 2 + 1, posY + height - 4);

        OK.connect([&]() {
            stopDialogWindow = true;
            returnValue = true; // User confirmed
            });

        cancel.connect([&]() {
            stopDialogWindow = true;
            returnValue = false; // User canceled
            });

        OK.setBackgroundColor(BrightGreen);
        OK.setForegroundColor(Black);

        cancel.setBackgroundColor(BrightRed);
        cancel.setForegroundColor(Black);

        while (!stopDialogWindow)
        {
            mouseButtonInteraction(&OK, &cancel); // Handle mouse interaction
        }

        return returnValue; // Return the confirmation result
    }

    /** @brief Displays an application error window.
     *  @param head Title of the error window.
     *  @param width Width of the error window.
     *  @param height Height of the error window.
     *  @param posX X-coordinate of the error window position.
     *  @param posY Y-coordinate of the error window position.
     */
    void applicationErrorWindow(const std::string& head, int width, int height, int posX, int posY)
    {
        bool stopApplicationErrorWindow = false;

        Window errorWindow(width, height, posX, posY);
        errorWindow.addWindowName("error", 1, 0);
        errorWindow.show(); // Show the error window

        setcur(width / 2 - head.size() / 2 + posX, posY + 1);
        std::cout << head; // Display the error title

        PushButton OK(width / 2 - 1, 3, "OK", posX + width / 2 - 1, posY + height - 4);

        OK.connect([&]() {
            stopApplicationErrorWindow = true; // Close the window
            exit(0); // Exit the application
            });

        OK.setBackgroundColor(White);
        OK.setForegroundColor(Black);

        while (!stopApplicationErrorWindow)
        {
            mouseButtonInteraction(&OK); // Handle mouse interaction
        }
    }

    /** @brief Displays a notification window.
     *  @param head Title of the notification window.
     *  @param width Width of the notification window.
     *  @param height Height of the notification window.
     *  @param posX X-coordinate of the notification window position.
     *  @param posY Y-coordinate of the notification window position.
     */
    void notificationWindow(const std::string& head, int width, int height, int posX, int posY)
    {
        bool stopNotificationWindow = false;

        Window notificationWindow(width, height, posX, posY);
        notificationWindow.addWindowName("notification", 1, 0);
        notificationWindow.show(); // Show the notification window

        setcur(width / 2 - head.size() / 2 + posX, posY + 1);
        std::cout << head; // Display the notification title

        PushButton OK(width / 2 - 1, 3, "OK", posX + width / 2 - 1, posY + height - 4);

        OK.connect([&]() {
            stopNotificationWindow = true; // Close the window
            });

        OK.setBackgroundColor(White);
        OK.setForegroundColor(Black);

        while (!stopNotificationWindow)
        {
            mouseButtonInteraction(&OK); // Handle mouse interaction
        }
    }

} // namespace Utils
