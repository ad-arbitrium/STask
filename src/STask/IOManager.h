#ifndef __IO_MANAGER__
#define __IO_MANAGER__

#include "SisyphusUtils.h"

#include <optional>
#include <string>

namespace Sisyphus
{ 

class IOManager
{
public:
	IOManager* inst();
	
	std::pair<Task*, Error> readUserTasks(const User& path) const;
	std::optional<Error> writeTask(Task& task, const User& user) const;

	std::pair<std::string, Error> getOrCreateUser(const User& user);
	
private:
	const std::string s_sep = "=#=";

	IOManager() {};

	inline std::string getUserPath(const User& user) const;
	
	inline bool checkFileExistance(const std::string& userPath) const;
	std::optional<Error> createUser(const std::string& userPath);

}; // IOManager

} // namespace

#endif
