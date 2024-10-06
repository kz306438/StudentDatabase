#ifndef FILE_SORTER_MENU_H
#define FILE_SORTER_MENU_H

#include "SortMenu.h"

namespace database
{
    /**
     * @brief Displays the file sorter menu and sorts files based on the provided sorting method.
     *
     * @param sortMethod The method used to sort the files (e.g., by surname, grade, etc.).
     */
    void fileSorterMenu(SortingMethod sortMethod);

} // namespace database

#endif // FILE_SORTER_MENU_H
