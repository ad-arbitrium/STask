#ifndef LOGGER_H_
#define LOGGER_H_

namespace Sisyphus
{ 

class Logger
{
public:
	static void log();
	Logger() = delete;

private:
	static void* m_logFile;
};

}

#endif