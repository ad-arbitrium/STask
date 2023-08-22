#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

#include "SisyphusUtils.h"

#include <optional>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace Sisyphus
{

class IOManager;

class UserManager
{
public:
	// singleton realization
	UserManager* inst();
	~UserManager();

	// API functions, checks if user w/ this login & password exists in this system,
	// constructs User object & sets them as logged in
	std::pair<User*, Error> login(std::string login, std::string password, std::string system);
	std::optional<Error> login(User& user);
	
	// API function, logs the user out
	void logout(const User& user);

	// API functions, create a new user
	std::pair<User*, Error> addUser(std::string login, std::string password, std::string system);
	std::optional<Error> addUser(User& user);

	// API fucntion, writes a task for a given user
	std::optional<Error> writeTask(const Task& task);

	// returns pointer to a linked list of tasks of a given user
	std::pair<Task*, Error> getUserTasks(User* user) const;

private:
	IOManager* m_iomgr = nullptr;
	std::unordered_map<uint32_t, User*> m_users;

	UserManager();

};

}
#endif

