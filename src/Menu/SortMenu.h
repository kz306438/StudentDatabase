#ifndef SORT_FILE_MENU_H
#define SORT_FILE_MENU_H

#include <iostream>

namespace database
{
    enum SortingType : std::uint8_t
    {
        Descending,
        Ascending
    };

    enum SortingMethod : std::uint8_t
    {
        SortBySurname,
        SortByAverageGrade,
        SortByAveragePhisicsGrade,
        SortByAverageMathGrade,
        SortByAverageInformGrade
    };

    /** @brief Displays the sorting menu. */
    void sortMenu();

} // namespace database

#endif // SORT_FILE_MENU_H