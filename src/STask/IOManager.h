#ifndef __IO_MANAGER__
#define __IO_MANAGER__

#include "SisyphusUtils.h"

#include <optional>
#include <string>

namespace Sisyphus
{ 

// IOManager is NOT part of API
class IOManager
{
public:

	static IOManager* inst()
	{
		static IOManager* mgr = new IOManager; // this is not worthy of an inline static

		return mgr;
	}
	// creates linked-list of user tasks from file
	std::pair<Task*, Error> readUserTasks(const User& path);
	
	// writes a new task to user file
	std::optional<Error> writeTask(Task& task, const User& user) const;
	
	// creates a new user file (if it doesnt exist) & returns path to a file
	std::pair<std::string, Error> getOrCreateUser(const User& user);
	
private:
	const std::string s_sep = "=#=";

	IOManager() = default;
	IOManager(const IOManager& other) = delete;
	IOManager(IOManager&& other) = delete;

	inline std::string getUserPath(const User& user) const;
	
	inline bool checkFileExistance(const std::string& userPath) const;
	std::optional<Error> createUser(const std::string& userPath);

}; // IOManager

} // namespace

#endif
