
#include <iostream>
#include "../UserManager.h"

#define SISSY STask::UserManager::inst()

int main(int argc, char** argv)
{
	char pof;

	if (const auto& [usr, err]
		= SISSY->addUser(std::string("test"), std::string("test"), "");
		err.hasError)
	{
		std::cout << "no register...\n" << err.text;
		std::cin >> pof;
		
	}
	std::cout << "registered\n";

	const auto& [usr, err]
		= SISSY->login(std::string("test"), std::string("test"), "");

	if (!usr)
	{
		std::cout << "no login...\n" << err.text;
		std::cin >> pof;
		return -1;
	}

	std::cout << "logged in\n";
	
	// memory leak potential, move semantics should be implemented
	STask::Task* tsk 
		= new STask::Task("Finish stas", "it's time", "17/8/23", "18/8/23");

	if (const auto& writeErr = SISSY->writeTask(*tsk, *usr);
		writeErr != std::nullopt)
	{
		std::cout << "unable to write task:\n" << writeErr->text;
		std::cin >> pof;
		return -2;
	}

	std::cout << "wrote tasks\n";

	std::pair<STask::Task*, STask::Error> res 
		= SISSY->getUserTasks(usr);

	//auto& [tasks, readErr] = SISSY->getUserTasks(usr);

	if (res.second.hasError)
	{
		std::cout << "unable to read task:\n" << res.second.text;
		std::cin >> pof;
		return -3;
	}

	std::cout << "tasks read\n";

	STask::Task* tsk2 = res.first;
	while (tsk2)
	{
		
		std::cout << tsk2->name << ' ' << tsk2 << '\n';
		tsk2 = tsk2->next;
	}

	return 0;
}