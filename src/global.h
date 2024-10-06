#ifndef GLOBAL_H
#define GLOBAL_H

#include <vector>
#include <string>

namespace database
{

	extern std::vector<std::string> mainDirectory; ///< Main directory containing file paths.

	extern std::string activeFile; ///< Currently active file in use.
	extern std::string pathToFileStorage; ///< Path to the file storage location.

} // namespace database

#endif // GLOBAL_H
