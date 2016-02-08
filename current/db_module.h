/*
 * File:   robot_module.h
 * Author: m79lol
 *
 */

#ifndef DB_MODULE_H
#define DB_MODULE_H

#define DB_MODULE_API_VERSION 101;

struct ModuleData {
  const char *iid;
  const char *hash
  unsigned short version;
}

struct RobotData {
  const ModuleData *mdoule_data;
  const char *robot_uid;
};

class DBModule {
 protected:
  DBModule() {}

 public:
  // init
  virtual const struct ModuleInfo& getModuleInfo() = 0;
  virtual void prepare(colorPrintfModule_t *colorPrintf_p,
                       colorPrintfModuleVA_t *colorPrintfVA_p) = 0;

  // compiler only
  virtual void *writePC(unsigned int *buffer_length) = 0;

  // intepreter - devices
  virtual int init() = 0;
  virtual void final() = 0;

  // intepreter - program & lib
  virtual void readPC(void *buffer, unsigned int buffer_length) = 0;

  // intepreter - program
  virtual int startProgram(int uniq_index) = 0;
  virtual RobotData **makeChoise(RobotData** robots_data, unsigned int count_robots);
  virtual int endProgram(int uniq_index) = 0;

  // destructor
  virtual void destroy() = 0;
  virtual ~DBModule() {}
};

typedef unsigned short (*getDBModuleApiVersion_t)();
typedef DBModule *(*getDBModuleObject_t)();

#ifndef MODULE_WRAPPER
extern "C" {
    PREFIX_FUNC_DLL unsigned short getDBModuleApiVersion() /*{ return ROBOT_MODULE_API_VERSION; }*/;
    PREFIX_FUNC_DLL DBModule *getDBModuleObject();
}
#endif

#endif /* DB_MODULE_H */
