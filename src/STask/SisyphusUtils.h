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

#ifdef NEEDS_INTERFACE
// 255 translation units should be enough
typedef uint8_t TTI ; // text translation index

struct Translation
{
	explicit Translation(std::string filename);
	inline std::string getText(const TTI index) { return wordMap[index]; }
private:
	std::unordered_map<TTI, std::string> wordMap;
};
#endif

struct Error
{
	Error() : text(std::string("")), hasError(false) {};
	Error(std::string inText) : text(inText), hasError(true) {};
	std::string text;
	bool hasError;
};

struct Task
{
	std::string name, description, creationDate, deadlineDate, endDate;
	Task* next;
	Task* prev;
	Task* last;
};

struct TaskTable
{
	Task* currentTask;
};

struct User
{
	std::string login, password, system;

	Error lastErr;
	Task* tasks;
	uint32_t id;

	bool connected;
};

}

#endif
