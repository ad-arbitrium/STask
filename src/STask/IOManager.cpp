#include "IOManager.h"
#include "SisyphusUtils.h"

#include <optional>
#include <string>
#include <fstream>
#include <filesystem>

namespace Sisyphus
{

IOManager* IOManager::inst()
{
    static IOManager* mgr = new IOManager();

    return mgr;
}

std::pair<Task*, Error> IOManager::readUserTasks(const User& user) const
{
    std::pair<std::string, Error> pathErrPair = getOrCreateUser(user);

    if (pathErrPair.second.hasError)
        return std::make_pair(nullptr, Error(pathErrPair.second));
    
    std::string path(pathErrPair.first);

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

        if (!first) first = newTask;

        if (prev)
        {
            newTask->prev = prev;
            prev->next = newTask;
        }
        prev = newTask;

        newTask->name = taskText; // tmp solution
    }

    if (first)
        first->last = newTask;
    
    tasks.close();

    return std::make_pair(first, Error());
}

std::optional<Error> IOManager::writeTask(Task& task, const User& user) const
{
    std::string path(getUserPath(user));

    if (!checkFileExistance(path))
        return std::make_optional(Error("User file does not exist"));

    std::ofstream userFile;
    
    userFile.open(path, std::ios::out | std::ios::app);
    if (!userFile.is_open())
        return std::make_optional(Error("Unable to open user file"));

    userFile << task.name << s_sep << task.description << s_sep << task.creationDate
        << s_sep << task.deadlineDate << s_sep << task.endDate;
    
    userFile.close();

    Task* previousLast = user.tasks->last;
    previousLast->next = &task;
    task.prev = previousLast;

    return std::optional<Error>();
}

std::pair<std::string, Error> IOManager::getOrCreateUser(const User& user) const
{
    std::string path(getUserPath(user));

    if (!checkFileExistance(path))
    {
        std::optional<Error> err = createUser(path);
        if (err.has_value())
            return std::pair<std::string, Error>("", err.value());
    }

    return std::pair<std::string, Error>(path, Error());;
}

std::string IOManager::getUserPath(const User& user) const
{
    return std::string("users/" + user.system + "/" + std::to_string(user.id));
}

bool IOManager::checkFileExistance(const std::string& userPath) const
{
    std::filesystem::path userPath{ userPath };
    return std::filesystem::exists(userPath);
}

std::optional<Error> IOManager::createUser(const std::string& userPath) const
{
    std::ofstream user;
    user.open(userPath, std::ios::out);
    if (!user.is_open())
        return std::optional<Error>(Error("Unable to create user file"));

    return std::nullopt;
}

}