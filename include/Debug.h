#ifndef DEBUG_H
#define DEBUG_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "glm/glm.hpp"
#include "Time.h"


//OSTREAM OPERATORS //////////////////////////////////
std::ostream& operator<<(std::ostream &log, const glm::vec3 &v);
std::ostream& operator<<(std::ostream &log, const glm::quat &q);
std::ostream& operator<<(std::ostream &log, const glm::vec2 &v);
std::ostream& operator<<(std::ostream &log, const glm::vec4 &v);
std::ostream& operator<<(std::ostream &log, const std::string &str);
std::ostream& operator<<(std::ostream &log, const glm::mat4 &v);

namespace RE
{

enum DbgMode
{
    DbgModeLog = 1,
    DbgModeWarning = 2,
    DbgModeError = 4,
    DbgModeFile = 8,
    DbgModeTerm = 10
};

#define CZ_AUTO_LOG_FILE "cz_auto_log_file"
#define CZ_LOG_DIR "log"

#define DbgWarning(x) do{\
    std::ostringstream log;\
    std::ostringstream wrn;\
    log << x;\
    wrn << "Warning(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << log.str() << std::endl;\
    Debug::Warning(wrn);\
    log.flush();\
    wrn.flush();\
} while(0)

#define DbgError(x) do{\
    std::ostringstream log;\
    std::ostringstream err;\
    log << x;\
    err << "Error(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << log.str() << std::endl;\
    Debug::Error(err);\
    log.flush();\
    err.flush();\
} while(0)

#define DbgLog(x) do{\
    std::ostringstream log;\
    log << x << std::endl;\
    Debug::Log(log);\
    log.flush();\
} while(0)


#define DBG_ASSERT_GL(x) do{\
    x;\
    int error = glGetError();\
    if(error > 0) DbgError("GL Error('" << gluErrorString(error)  << "')");\
} while(0)

#define DBG_ASSERT_GL_MSG(x, msg) do{\
    x;\
    int error = glGetError();\
    if(error > 0) DbgError("GL Error('" << gluErrorString(error) << "')" << ": " << msg);\
} while(0)

#define DBG_ASSERT_GL_RET(x) do{\
    x;\
    int error = glGetError();\
    if(error > 0){ DbgError("GL Error('" << gluErrorString(error) << "')"); return false;} \
} while(0)

#define DBG_ASSERT_GL_RET_MSG(x, msg) do{\
    x;\
    int error = glGetError();\
    if(error > 0){ DbgError("GL Error('" << gluErrorString(error)  << "')" << ": " << msg); return false;} \
} while(0)


#define DBG_ASSERT(x) do{\
    if((x) < 0) DbgError("There was an error");\
} while(0)

#define DBG_ASSERT_MSG(x, msg) do{\
    if((x) < 0) DbgError(msg);\
} while(0)

#define DBG_ASSERT_RET(x) do{\
    if((x) < 0) { DbgError("There was an error"); return false;}\
} while(0)

#define DBG_ASSERT_RET_MSG(x, msg) do{\
    if((x) < 0){ DbgError(msg); return false;} \
} while(0)

#define DBG_ASSERT_RET_VOID_MSG(x, msg) do{\
    x;\
    int error = glGetError();\
    if(error > 0){ DbgError("GL Error('" << gluErrorString(error)  << "')" << ": " << msg); return;} \
} while(0)

class Debug
{
private:
    static std::string logFile;
    static std::ofstream fileStream;

public:
    static unsigned int fileMode;
    static unsigned int outputMode;
    static void SetFile(std::string filepath);
    static void Log(std::ostringstream &log);
    static void Warning(std::ostringstream &log);
    static void Error(std::ostringstream &log);
};

}

#endif //DEBUG_H
