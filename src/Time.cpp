#include "../include/Time.h"

using namespace RE;


long Time::GetMiliseconds()
{
	return SDL_GetTicks();
}

float Time::GetSeconds()
{
    return float(SDL_GetTicks())/1000.0f;
}

std::string Time::GetDateStr()
{
    std::stringstream sstr;
	time_t t = time(0);
    struct tm * now = localtime(&t);
    sstr << now->tm_year + 1900 << "-" << now->tm_mon + 1 << "-" << now->tm_mday 
    << "-" << now->tm_hour << "-" << now->tm_min;
    return sstr.str();
}
