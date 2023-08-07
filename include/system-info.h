#ifndef __SYSINFO_H_INCLUDE__
//===- Sysinfo.h   -------------------------------------------------------===//
//
// Under Apache License v2.0.
//
//===----------------------------------------------------------------------===//
//
// The file contains the declarations for common abstractions for Machine
// information and user information while executing a benchmark.
// It uses a standard json specification with an intent that same information
// can be used by different type of benchmarks.

// Avoid multiple inclusions
#define __SYSINFO_H_INCLUDE__
#include <map>
#include <string>
#include <vector>

namespace sysinfo {
class Processor;
class Environment;
class Machine {
public:
  static Machine &GetInstance();
  Machine(const Machine &) = delete;
  Machine(Machine &&) = delete;
  Machine &operator=(const Machine &) = delete;
  Machine &operator=(Machine &&) = delete;
private:
  // Hostname
  std::string NodeName;
  // Operating System Type
  std::string OSName;
  // Processor Architecture
  std::string Arch;
  // Total RAM Available
  double TotalRAM;
  // Free RAM Available
  double UsedRAM;
  // Processors in this machine
  const std::vector<Processor> Procs;
  // Additional attribues
  std::map<std::string, std::string> Attributes;
protected:
  // Single instance
  Machine() {}
};

class Processor {
  int Processor;
  std::string Vendor_id;
  std::string CPUFamily;
  std::string ModelName;
  std::string Microcode;
  double CpuFrequency;
  // L1 Dacache size
  double CacheSize;
  // The L1i Cache on each core(KB)
  int l1i_cache;
  // Available L2 Data Cache(KB)
  int L2_Cache;
  unsigned int PhysicalId;
  unsigned int Siblings;
  unsigned int CoreId;
  unsigned int CpuCores;
  bool FPU;
  double BogoMIPS;
  unsigned int CacheAlignment;
  // Additional attribues
  std::map<std::string, std::string> attributes;
};

class Environment {
public:
  Environment(const Environment &) = default;
  Environment(Environment &&) = delete;
  Environment &operator=(const Environment &) = delete;
  Environment &operator=(Environment &&) = delete;
  Environment(const char *Compiler, const char *Version, const char *DateTime,
              const char *UserName)
      : Compiler(Compiler), Version(Version), DateTime(DateTime),
        UserName(UserName) {}

private:
  // Compiler used for the build
  const char *Compiler;
  // Compiler version used for the build
  const char *Version;
  // Date and Time of execution
  const char *DateTime;
  // The user name who ran the benchmark
  const char *UserName;
};
} // namespace sysinfo
#endif //__SYSINFO_H_INCLUDE__