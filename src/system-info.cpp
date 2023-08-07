#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "system-info.h"

using namespace std;
using boost::algorithm::trim;
using std::vector;

using json = nlohmann::json;

// System Info Json Object.
json SystemInfo = {};

// for string delimiter
vector<std::string> split(std::string s, std::string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> res;
  while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    trim(token);
    res.push_back(token);
  }
  res.push_back(s.substr(pos_start));
  return res;
}

namespace sysinfo {
static const char *getArch() {
  // Get current architecture, detectx nearly every architecture. Coded by Freak
#if defined(__x86_64__) || defined(_M_X64)
  return "x86_64";
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
  return "x86_32";
#elif defined(__ARM_ARCH_2__)
  return "ARM2";
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
  return "ARM3";
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
  return "ARM4T";
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
  return "ARM5"
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
  return "ARM6T2";
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) ||                   \
    defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) ||                    \
    defined(__ARM_ARCH_6ZK__)
  return "ARM6";
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) ||                   \
    defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) ||                    \
    defined(__ARM_ARCH_7S__)
  return "ARM7";
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) ||                  \
    defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
  return "ARM7A";
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) ||                  \
    defined(__ARM_ARCH_7S__)
  return "ARM7R";
#elif defined(__ARM_ARCH_7M__)
  return "ARM7M";
#elif defined(__ARM_ARCH_7S__)
  return "ARM7S";
#elif defined(__aarch64__) || defined(_M_ARM64)
  return "ARM64";
#elif defined(mips) || defined(__mips__) || defined(__mips)
  return "MIPS";
#elif defined(__sh__)
  return "SUPERH";
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) ||  \
    defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) ||            \
    defined(_ARCH_PPC)
  return "POWERPC";
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
  return "POWERPC64";
#elif defined(__sparc__) || defined(__sparc)
  return "SPARC";
#elif defined(__m68k__)
  return "M68K";
#else
  return "unknown";
#endif
}

static const char *GetOS() {
#if defined(_WIN32)
  return "MS WINDOWS win32";
#elif defined(_WIN64)
  return "MS WINDOWS win64";
#elif defined(__ANDROID__)
  return "Android";
#elif defined(__MACH__)
  return "Appled Mach OS";
#elif defined(__linux__)
  return "Linux";
#elif defined(__OpenBSD__)
  return "Open BSD";
#elif defined(__unix_) _
  return "Unix";
#else
  return "unknown";
#endif
}

static const char *GetCompiler() {
#if defined(__clang__)
  return "clang";
#elif defined(__INTEL_COMPILER)
  return "icc";
#elif defined(__GNUC__)
  return "gcc";
#elif defined(__GNUG__)
  return "g++";
#elif defined(_MSC_VER)
  return "msvc";
#else
  return "unknown";
#endif
}
} // namespace sysinfo

int main() {
  string line;
  ifstream input("/proc/cpuinfo");
  string delim = ":";
  vector<string> attrs;

  while (getline(input, line)) {
    attrs = split(line, delim);
    // Ignore complex cases for the time being.
    if (attrs.size() != 2)
      continue;
    string key = attrs[0];
    SystemInfo[key] = attrs[1];
  }
  cout << SystemInfo << endl;
  return 1;
}
