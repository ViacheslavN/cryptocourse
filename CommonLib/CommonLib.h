#pragma once


#ifdef _WIN32

#include <windows.h>
#include <wininet.h>
#endif

#include <stdint.h>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <set>
#include <sstream>


typedef std::string astr;
typedef std::wstring wstr;
typedef std::vector<astr> astrvec;
typedef std::vector<wstr> wstrvec;
typedef std::list<astr> astrlist;
typedef std::list<wstr> wstrlist;
typedef std::set<astr> astrset;
typedef std::set<wstr> wstrset;
typedef uint8_t byte_t;

#ifdef _WIN32
	typedef int thread_id_t;
#else
	typedef pthread_t thread_id_t;
#endif