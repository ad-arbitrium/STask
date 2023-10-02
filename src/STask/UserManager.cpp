#include "UserManager.h"
#include "SisyphusUtils.h"
#include "IOManager.h"

#include <unordered_map>

namespace Sisyphus
{
uint32_t UserManager::getUserHash(const User* user) const
{
    std::hash<std::string> hasher;
    return (uint32_t)hasher(user->login + user->system); // including system is kind of a dumb idea
}
UserManager::UserManager()
{
    //m_iomgr = IOManager::inst();
}

UserManager::~UserManager()
{
    for (const auto& [id, ptr] : m_users)
        delete ptr;
}

UserManager* UserManager::inst()
{
    static UserManager* mgr = new UserManager();
    return mgr;
}

std::pair<User*, Error> UserManager::login(const std::string& login, const std::string& password, const std::string& system)
{
    const auto& [user, error] 
        = IOManager::getUser(login, password);
    if (error.hasError)
        return std::make_pair(nullptr, Error("Unable to login\n" + error.text));
    
    user->id = getUserHash(user);
    m_users[user->id] = user;

    return std::make_pair(user, Error(""));
}

std::optional<Error> UserManager::login(const User& user)
{
    // this method is unused
    return std::make_optional(Error("DONT USE THIS FUNCTION, " + user.login));
}

std::pair<User*, Error> UserManager::addUser(const std::string& login, const std::string& password, const std::string& system)
{
    const auto& [user, err]
        = IOManager::createUser(login, password);

    if (!user)
        return std::make_pair(nullptr, Error("Unable to register user:\n" + err.text));

    user->id = getUserHash(user);

    m_users[user->id] = user;

    return std::make_pair(user, Error());
}

std::optional<Error> UserManager::addUser(const User& user)
{
    return std::make_optional(Error("Don't call this function, " + user.login));
}

std::optional<Error> UserManager::writeTask(Task& task, const User& user)
{
    const auto& error = IOManager::writeTask(task, user);

    return error.has_value() 
        ? std::make_optional(Error("Unable to write task:\n" + error.value().text))
        : std::nullopt;
}

std::pair<Task*, Error> UserManager::getUserTasks(const User* user) const
{
    const auto& [task, err] = IOManager::readUserTasks(user);

    if (err.hasError)
        return std::make_pair(nullptr, Error("Unable to read user tasks:\n" + err.text));

    return std::make_pair(task, Error());
}

}