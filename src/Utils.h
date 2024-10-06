#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>

#include "global.h"

namespace Utils
{
    /** @brief Fills the background with a color. */
    void paintOverBackground();

    /** @brief Prints the logo at specified coordinates.
     *  @param x X-coordinate for the logo position.
     *  @param y Y-coordinate for the logo position.
     */
    void printLogo(int x, int y);

    /** @brief Clears the input buffer. */
    void clearInput();

    /** @brief Gets input value from the user with an optional validation function.
     *  @param prompt Message displayed to the user for input.
     *  @param value Reference to the variable to store the input value.
     *  @param checkFunc Optional function to validate the input value.
     */
    template <typename T>
    void inputValue(const std::string& prompt, T& value, bool (*checkFunc)(const T&) = nullptr) {
        while (true) {
            std::cout << prompt << std::endl;
            std::cin >> value;
            if (std::cin.good())
            {
                if (!checkFunc || checkFunc(value))
                {
                    break;
                }
            }
            else {
                std::cout << "INCORRECT ENTRY! TRY AGAIN!" << std::endl;
                clearInput();
            }
        }
    }

    /** @brief Loads filenames from a specified path into a vector.
     *  @param path Path to the file containing filenames.
     *  @param files Vector to store the loaded filenames.
     */
    void loadFiles(const std::string& path, std::vector<std::string>& files);

    /** @brief Saves filenames from a vector to a specified path.
     *  @param path Path where the filenames will be saved.
     *  @param files Vector containing filenames to save.
     */
    void saveFiles(const std::string& path, const std::vector<std::string>& files);

    /** @brief Converts an array of uint16_t to a string.
     *  @param array Vector of uint16_t to convert.
     *  @return String representation of the array.
     */
    std::string arrayToString(const std::vector<uint16_t>& array);

    /** @brief Displays a confirmation dialog.
     *  @param head Title of the dialog.
     *  @param width Width of the dialog.
     *  @param height Height of the dialog.
     *  @param posX X-coordinate of the dialog position.
     *  @param posY Y-coordinate of the dialog position.
     *  @return True if confirmed, false otherwise.
     */
    bool confirmDialog(const std::string& head, int width, int height, int posX, int posY);

    /** @brief Displays an application error window.
     *  @param head Title of the error window.
     *  @param width Width of the error window.
     *  @param height Height of the error window.
     *  @param posX X-coordinate of the error window position.
     *  @param posY Y-coordinate of the error window position.
     */
    void applicationErrorWindow(const std::string& head, int width, int height, int posX, int posY);

    /** @brief Displays a notification window.
     *  @param head Title of the notification window.
     *  @param width Width of the notification window.
     *  @param height Height of the notification window.
     *  @param posX X-coordinate of the notification window position.
     *  @param posY Y-coordinate of the notification window position.
     */
    void notificationWindow(const std::string& head, int width, int height, int posX, int posY);

    /** @brief Clears the current line in the input buffer. */
    inline void eatline() { while (std::cin.get() != '\n') continue; }

} // namespace Utils

#endif // UTILS_H
