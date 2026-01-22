// note: on windows, you need to link to winmm to use time module
// on macos, you need to link to the Carbon framework

#ifndef SWAN_TIME_INCLUDED
#define SWAN_TIME_INCLUDED

#include "strmanip.hh"

#if defined(_WIN32)
//#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>
//#include <Mmsystem.h>
#elif defined(__APPLE__)
#include <CoreServices/CoreServices.h>
#elif defined(__linux__)
#include <sys/sysinfo.h>
#include <sys/time.h>
#endif
#include <time.h>

#ifdef _WIN32
extern "C" unsigned int __stdcall timeGetTime();
extern "C" void __stdcall Sleep(unsigned int);
#endif

namespace swan
{
  struct timeinfo_t
  {
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
  };
  namespace time
  {
    inline unsigned int millisecs()
    {
#if defined(_WIN32)
      return timeGetTime();
#elif defined(__linux__)
      static long basetime = -1;
      long t;
      struct timeval tv;
      gettimeofday(&tv, 0);
      t = tv.tv_sec * 1000;
      t += tv.tv_usec / 1000;
      if ( basetime == -1 )
      {
        struct sysinfo info;
        sysinfo(&info);
        basetime = t - info.uptime * 1000;
      }
      return t - basetime;
#elif defined(__APPLE__)
      double t;
      UnsignedWide uw;
      Microseconds( &uw );
      t=(uw.hi<<(32-9))|(uw.lo>>9);
      return t/(1000.0/512.0);
#endif
    }

    inline void delay(unsigned int msecs)
    {
#if defined(_WIN32)
      Sleep(msecs);
#else
      struct timespec sleepval = { 0 };
      sleepval.tv_sec = msecs / 1000;
      sleepval.tv_nsec = (msecs - sleepval.tv_sec * 1000) * 1000000L;
      nanosleep(&sleepval, (struct timespec*)0);
#endif
    }

    inline timeinfo_t timeinfo()
    {
      // get local time
      time_t timer;
      ::time(&timer);
#ifdef _MSC_VER
      tm ti = { 0 };
      localtime_s(&ti, &timer);
      tm* pti = &ti;
#else
      tm* pti = localtime(&timer);
#endif

      timeinfo_t t;
      t.year = pti->tm_year+1900;
      t.month = pti->tm_mon+1;
      t.day = pti->tm_mday;
      t.hour = pti->tm_hour;
      t.min = pti->tm_min;
      t.sec = pti->tm_sec;
      return t;
    }

    inline std::string parsetimeinfo(const timeinfo_t& ti, bool parsedate = true, bool parsetime = true)
    {
      std::string str;
      
      if (parsedate)
      {
        str += strmanip::lset(strmanip::fromint(ti.year), 4, '0');
        str += "/";
        str += strmanip::lset(strmanip::fromint(ti.month), 2, '0');
        str += "/";
        str += strmanip::lset(strmanip::fromint(ti.day), 2, '0');
      }

      if (parsetime)
      {
        if ( str != "" ) str += " ";
        str += strmanip::lset(strmanip::fromint(ti.hour), 2, '0');
        str += ":";
        str += strmanip::lset(strmanip::fromint(ti.min), 2, '0');
        str += ":";
        str += strmanip::lset(strmanip::fromint(ti.sec), 2, '0');
      }

      return str;
    }
  } // namespace time
} // namespace swan

#endif // SWAN_TIME_INCLUDED
