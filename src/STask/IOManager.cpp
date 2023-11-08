#include "IOManager.h"
#include "STUtils.h"

#include <optional>
#include <string>
#include <fstream>
#include <filesystem>
#include <format>
#include <sstream>

namespace STask
{

std::pair<Task*, Error> IOManager::readUserTasks(const User* user)
{
    std::string path = getUserPath(user);

    if (!checkFileExistance(path))
        return std::make_pair(nullptr, Error("Could not locate file"));
    
    std::ifstream tasks;
    tasks.open(path, std::ios::in);
    

    if (!tasks.is_open())
        return std::make_pair(nullptr, Error("Unable to open file for read"));

    Task* prev = nullptr;
    Task* first = nullptr;
    Task* newTask = nullptr;

    std::string taskText;
    while (getline(tasks, taskText))
    {
        newTask = new Task;
        newTask->name = taskText; // tmp solution
        newTask->next = nullptr;
        newTask->prev = nullptr;
        newTask->last = nullptr;
        if (!first) first = newTask;

        if (prev)
        {
            newTask->prev = prev;
            prev->next = newTask;
        }
        prev = newTask;

    }

    if (first)
        first->last = newTask;
    
    tasks.close();

    return std::make_pair(first, Error());
}

std::optional<Error> IOManager::writeTask(Task& task, const User& user)
{
    std::string path(getUserPath(user));

    if (!checkFileExistance(path))
        return std::make_optional(Error("User file does not exist"));

    std::ofstream userFile;
    
    userFile.open(path, std::ios::out | std::ios::app);
    if (!userFile.is_open())
        return std::make_optional(Error("Unable to open user file"));

    userFile << task.name << s_sep << task.description << s_sep << task.creationDate
        << s_sep << task.deadlineDate << s_sep << task.endDate << '\n';
    
    userFile.close();

    // this is fucked. Writing this drunk af
    // this solution is a piece of shit
    if (user.tasks)
    {
        Task* previousLast = user.tasks->last;
        if (previousLast)
        {
            previousLast->next = &task;
            task.prev = previousLast;
        }
    }

    return std::nullopt;
}

std::pair<User*, Error> IOManager::createUser(const std::string& username, const std::string& password)
{
    // we ensure that the file, which lists all users actually exists
    ensureUserFileExistance();
    
    std::filesystem::create_directory("./" + USERS_PATH);

    // todo add user to usersfile
    std::string path(getUserPath(username));

    if (checkFileExistance(path))
        return std::make_pair(nullptr, Error("User already exists!"));

    std::optional<Error> err = createUserFile(path);

    if (err.has_value())
        return std::make_pair(nullptr, 
            Error("Error while creating new user:\n" + err.value().text));



    User* createdUser = new User();

    createdUser->login = username;
    createdUser->password = password;

    return std::make_pair(createdUser, Error());
}

// wtf is this...
std::string IOManager::getUserPath(const std::string& user)
{
    return std::format("users/{}", user);
}

inline std::string IOManager::getUserPath(const User* user)
{
    return getUserPath(user->login);
}

inline std::string IOManager::getUserPath(const User& user)
{
    return getUserPath(user.login);
}

bool IOManager::checkFileExistance(const std::string& userPath)
{
    std::filesystem::path path{ "./" + userPath};
    return std::filesystem::exists(path);
}

inline std::optional<Error> IOManager::ensureUserFileExistance()
{
    // crutch, whatever
    std::filesystem::create_directory("./" + DATA_PATH);

    std::string path = "./" + DATA_PATH + "/users";

    // funny c++17 construct
    if (std::filesystem::path fsPath{path}; 
        !std::filesystem::exists(fsPath))
    {
        std::ofstream users;
        users.open(path, std::ios::out);

        if (!users.is_open())
            return std::make_optional(Error("Unable to create users file"));

        users.close();
    }

    return std::nullopt;
}

std::pair<User*, Error> IOManager::getUser(const std::string& user, const std::string& password)
{
    std::ifstream userFile("./" + DATA_PATH + "/" + "users");

    if (!userFile.is_open())
        return std::make_pair(nullptr, Error("Unable to read users file"));

    //std::string line;
    std::string log;
    std::string pass;
    
    while (userFile >> log >> pass)
    {
        //std::istringstream l(line);
        //std::getline(l, log, ':');
        //std::getline(l, pass, ':');

        if (log == user && pass == password)
        {
            User* res = new User;
            userFile.close();
            res->login = log;
            res->password = pass;
            return std::make_pair(res, Error());
        } // endif

    } // end while

    return std::make_pair(nullptr, Error("User doesn't exist!"));
}

std::optional<Error> IOManager::createUserFile(const std::string& userPath)
{
    std::ofstream user;
    user.open(userPath, std::ios::out);
    
    if (!user.is_open())
        return std::make_optional(Error("Unable to create user file"));

    user.close();

    std::ofstream users;
    users.open("./" + DATA_PATH + "/users", std::ios::out | std::ios::app);
    users << "test" << ' ' << "test" << '\n';
    users.close(); 

    return std::nullopt;
}

}