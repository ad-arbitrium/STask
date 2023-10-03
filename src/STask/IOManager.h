#ifndef __IO_MANAGER__
#define __IO_MANAGER__

#include "STUtils.h"

#include <optional>
#include <string>

namespace STask
{ 

const std::string s_sep = std::string("=#=");

// IOManager is NOT part of API
class IOManager
{
public:
	// creates linked-list of user tasks from file
	static std::pair<Task*, Error> readUserTasks(const User* path);
	
	// writes a new task to user file
	static std::optional<Error> writeTask(Task& task, const User& user);

	// reads user file from disk, constructs user & returns it
	// Error if user doesn't exist
	static std::pair<User*, Error> getUser(const std::string& username, const std::string& password);

	// creates a new user file, returns new user
	// error if user already exists
	static std::pair<User*, Error> createUser(const std::string& username, const std::string& password = "");
	
private:
	IOManager() = delete;
	IOManager(const IOManager& other) = delete;
	IOManager(IOManager&& other) = delete;

	static inline std::string getUserPath(const std::string& user);
	static inline std::string getUserPath(const User& user);
	static inline std::string getUserPath(const User* user);
	
	static inline bool checkFileExistance(const std::string& userPath);
	static inline std::optional<Error> ensureUserFileExistance();
	static std::optional<Error> createUserFile(const std::string& userPath);

}; // IOManager

} // namespace

#endif
