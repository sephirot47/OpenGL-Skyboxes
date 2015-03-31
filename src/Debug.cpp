#include "../include/Debug.h"

using namespace RE;

std::string Debug::logFile;
std::ofstream Debug::fileStream;
unsigned int Debug::fileMode = DbgModeLog | DbgModeWarning | DbgModeError;
unsigned int Debug::outputMode = DbgModeFile | DbgModeTerm;

void Debug::Log(std::ostringstream &log)
{
    using std::operator<<;
    if (outputMode & DbgModeFile and fileMode & DbgModeLog)
	{
        if (fileStream.is_open()) fileStream << log.str();
    }

    if (outputMode & DbgModeTerm)
    {
        std::cout << log.str();
	}
}

void Debug::Warning(std::ostringstream &log)
{
    using std::operator<<;
    if (outputMode & DbgModeFile and fileMode & DbgModeWarning)
	{
        if (fileStream.is_open()) fileStream << log.str();
    }

    if (outputMode & DbgModeTerm)
    {
        std::cerr << log.str();
    }
}

void Debug::Error(std::ostringstream &log)
{
    using std::operator<<;
    if (outputMode & DbgModeFile and fileMode & DbgModeError)
	{
        if (fileStream.is_open()) fileStream << log.str(); 
    }

    if (outputMode & DbgModeTerm)
    {
        std::cerr << log.str();
    }
}

void Debug::SetFile(std::string filepath)
{
    using std::operator<<;
	if (filepath == CZ_AUTO_LOG_FILE) 
	{
        std::string dbg = CZ_LOG_DIR;
		dbg.append("/");
		dbg.append(Time::GetDateStr());
		dbg.append(".log");
		filepath = dbg;
        std::cerr << "Saving log to: " << filepath << std::endl;
	}
    logFile = filepath;
	if (fileStream.is_open()) fileStream.close();
        fileStream.open(logFile, std::ofstream::out);
}


std::ostream& operator<<(std::ostream &log, const std::string &str)
{
    log << str.c_str();
    return log;
}

std::ostream& operator<<(std::ostream &log, const glm::vec2 &v)
{
    log << "(" << v.x << ", " << v.y << ")";
    return log;
}

std::ostream& operator<<(std::ostream &log, const glm::vec3 &v)
{
    log << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return log;
}

std::ostream& operator<<(std::ostream &log, const glm::vec4 &v)
{
    log << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return log;
}

std::ostream& operator<<(std::ostream &log, const glm::quat &q)
{
    log << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
    return log;
}


std::ostream &operator<<(std::ostream &log, const glm::mat4 &v)
{
    log << "(" << v[0][0] << ", " << v[1][0] << ", " << v[2][0] << ", " << v[3][0] << "," << std::endl;
    log << " " << v[0][1] << ", " << v[1][1] << ", " << v[2][1] << ", " << v[3][1] << "," << std::endl;
    log << " " << v[0][2] << ", " << v[1][2] << ", " << v[2][2] << ", " << v[3][2] << "," << std::endl;
    log << " " << v[0][3] << ", " << v[1][3] << ", " << v[2][3] << ", " << v[3][3] << ")" << std::endl;
    return log;
}
