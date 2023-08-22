#include "UserManager.h"
#include "SisyphusUtils.h"
#include "IOManager.h"


namespace Sisyphus
{

UserManager::UserManager()
{
    m_iomgr = IOManager::inst();
}

UserManager::~UserManager()
{
    for (auto& user : m_users)
        delete user.second;
}

std::pair<User*, Error> UserManager::login(std::string login, std::string password, std::string system)
{
    return std::make_pair(nullptr, Error(""));
}

std::optional<Error> UserManager::login(User& user)
{
    return std::optional<Error>();
}

std::optional<Error> UserManager::addUser(User& user)
{
    return std::optional<Error>();
}

std::optional<Error> UserManager::writeTask(const Task& task)
{
    return std::optional<Error>();
}

std::pair<Task*, Error> UserManager::getUserTasks(User* user) const
{
    return std::pair<Task*, Error>();
}

}