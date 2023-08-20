#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

#include "SisyphusUtils.h"

#include <optional>
#include <cstdint>
#include <string>
#include <unordered_map>
//#include <>

//extern std::string;
//extern template class std::optional<Sisyphus::Error>;



namespace Sisyphus
{

class IOManager;

class UserManager
{
public:
	UserManager* inst();

	std::pair<User*, Error> login(std::string login, std::string password, std::string system);

	std::optional<Error> login(User& user);
	void logout(const User& user);

	std::optional<Error> addUser(User& user);

	std::optional<Error> writeTask(const Task& task);

	std::pair<Task*, Error> getUserTasks(User* user) const;

private:
	IOManager* m_iomgr = nullptr;
	std::unordered_map<uint32_t, User*> m_users;

	UserManager();

};

}
#endif

