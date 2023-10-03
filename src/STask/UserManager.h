#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

#include "STUtils.h"

#include <optional>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace STask
{

class IOManager;

class UserManager
{
public:
	// singleton realization
	static UserManager* inst();
	~UserManager();

	// API functions, checks if user w/ this login & password exists in this system,
	// constructs User object & sets them as logged in
	std::pair<User*, Error> login(const std::string& login, const std::string& password, const std::string& system);
	std::optional<Error> login(const User& user);
	
	// API function, logs the user out
	void logout(const User& user);

	// API functions, create a new user
	std::pair<User*, Error> addUser(const std::string& login, const std::string& password, const std::string& system);
	
	// unnecessary at the current moment
	std::optional<Error> addUser(const User& user);

	// API fucntion, writes a task for a given user
	std::optional<Error> writeTask(Task& task, const User& user);

	// returns pointer to a linked list of tasks of a given user
	std::pair<Task*, Error> getUserTasks(const User* user) const;

private:
	// why did i comment this out...
	//IOManager* m_iomgr = nullptr;
	std::unordered_map<uint32_t, User*> m_users;

	uint32_t getUserHash(const User* user) const;
	UserManager();
};

}
#endif

