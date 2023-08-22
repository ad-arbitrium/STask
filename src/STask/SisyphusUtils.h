#ifndef __SISYPHUS_UTILS_H__
#define __SISYPHUS_UTILS_H__

#include <string>
#include <unordered_map>
#include <cstdint>

namespace Sisyphus
{

struct User;
struct Task;
struct TaskTable;
struct Error;

// struct contains error data
struct Error
{
	Error() : text(std::string("")), hasError(false) {};
	explicit Error(const std::string& inText) : text(inText), hasError(true) {};
	std::string text;
	bool hasError;
};

// 2-way linked list, contains task header data
struct Task
{
	std::string name;
	std::string description;
	std::string creationDate;
	std::string deadlineDate;
	std::string endDate;

	Task* next;
	Task* prev;
	Task* last;
};

// struct stores user info
struct User
{
	User() = default;
	User(User&& other) = default;
	// Copy operation is prohibited due to usage of pointers to tasks
	User& operator=(const User& other) = delete; 
	User(const User& other) = delete;

	// deleting all tasks
	~User() // this is actually needed
	{ 
		Task* curr;
		while (tasks->next)
		{
			curr = tasks;
			tasks = tasks->next;
			delete curr;
		}

		if (tasks) delete tasks;
			
	}

	std::string login;
	std::string password;
	std::string system;

	Error lastErr;
	Task* tasks;
	uint32_t id;

	bool connected;
};

}

#endif
