#ifndef CORE_H
#define CORE_H

#ifdef _WIN32
#ifdef DeleteFile
#undef DeleteFile
#endif
#ifdef LoadString
#undef LoadString
#endif
#endif

#include "common.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef CORE_IMPL
  typedef void Memory;
#else
struct Memory;
#endif
  struct List;
  struct Dict;

  // ------------------------------------
  // App
  // ------------------------------------

  EXPORT const char *CALL AppName();
  EXPORT struct List *CALL AppArgs();
  EXPORT const char *CALL Run(const char *command);
  void *_IncRef(void *ptr);
  void _DecRef(void *ptr);
  void *_AutoDec(void *ptr);
  void _DoAutoDec();

  // ------------------------------------
  // Console
  // ------------------------------------

  EXPORT const char *CALL Input(const char *prompt);
  EXPORT void CALL Print(const char *msg);

  // ------------------------------------
  // Dir
  // ------------------------------------

  EXPORT struct List *CALL DirContents(const char *path);
  EXPORT const char *CALL CurrentDir();
  EXPORT void CALL ChangeDir(const char *dir);
  EXPORT const char *CALL FullPath(const char *filename);

  // ------------------------------------
  // File
  // ------------------------------------

  EXPORT int CALL FileType(const char *filename);
  EXPORT void CALL DeleteFile(const char *filename);

  // ------------------------------------
  // List
  // ------------------------------------

  struct List *_CreateList();
  struct List *_SetListInt(struct List *list, size_t index, int value);
  struct List *_SetListFloat(struct List *list, size_t index, float value);
  struct List *_SetListString(struct List *list, size_t index, const char *value);
  struct List *_SetListList(struct List *list, size_t index, struct List *value);
  struct List *_SetListDict(struct List *list, size_t index, struct Dict *value);
  struct List *_SetListRef(struct List *list, size_t index, void *value);
  int _ListInt(struct List *list, size_t index);
  float _ListFloat(struct List *list, size_t index);
  const char *_ListString(struct List *list, size_t index);
  struct List *_ListList(struct List *list, size_t index);
  struct Dict *_ListDict(struct List *list, size_t index);
  void *_ListRef(struct List *list, size_t index);
  const char *_ListToString(struct List *list);
  EXPORT void CALL RemoveIndex(struct List *list, int index);
  EXPORT int CALL ListSize(struct List *list);
  EXPORT void CALL ClearList(struct List *list);

  // ------------------------------------
  // Dict
  // ------------------------------------

  struct Dict *_CreateDict();
  struct Dict *_SetDictInt(struct Dict *dict, const char *key, int value);
  struct Dict *_SetDictFloat(struct Dict *dict, const char *key, float value);
  struct Dict *_SetDictString(struct Dict *dict, const char *key, const char *value);
  struct Dict *_SetDictList(struct Dict *dict, const char *key, struct List *value);
  struct Dict *_SetDictDict(struct Dict *dict, const char *key, struct Dict *value);
  struct Dict *_SetDictRef(struct Dict *dict, const char *key, void *value);
  int _DictInt(struct Dict *dict, const char *key);
  float _DictFloat(struct Dict *dict, const char *key);
  const char *_DictString(struct Dict *dict, const char *key);
  struct List *_DictList(struct Dict *dict, const char *key);
  struct Dict *_DictDict(struct Dict *dict, const char *key);
  void *_DictRef(struct Dict *dict, const char *key);
  const char *_DictToString(struct Dict *dict);
  EXPORT int CALL Contains(struct Dict *dict, const char *key);
  EXPORT void CALL RemoveKey(struct Dict *dict, const char *key);
  EXPORT int CALL DictSize(struct Dict *dict);
  EXPORT void CALL ClearDict(struct Dict *dict);

  // ------------------------------------
  // Math
  // ------------------------------------

  EXPORT float CALL ACos(float x);
  EXPORT float CALL ASin(float x);
  EXPORT float CALL ATan(float x);
  EXPORT float CALL ATan2(float x, float y);
  EXPORT float CALL Abs(float x);
  EXPORT float CALL Ceil(float x);
  EXPORT float CALL Clamp(float x, float min, float max);
  EXPORT float CALL Cos(float x);
  EXPORT float CALL Exp(float x);
  EXPORT float CALL Floor(float x);
  EXPORT float CALL Log(float x);
  EXPORT float CALL Max(float x, float y);
  EXPORT float CALL Min(float x, float y);
  EXPORT float CALL Pow(float x, float y);
  EXPORT float CALL Sgn(float x);
  EXPORT float CALL Sin(float x);
  EXPORT float CALL Sqrt(float x);
  EXPORT float CALL Tan(float x);
  EXPORT int CALL Int(float num);
  EXPORT int CALL Rand(int min, int max);
  EXPORT void CALL RandSeed(int seed);
  EXPORT float CALL Deg(float rad);
  EXPORT float CALL Rad(float deg);
  EXPORT float CALL Wrap(float val, float mod);

  // ------------------------------------
  // String
  // ------------------------------------

  EXPORT int CALL Len(const char *str);
  EXPORT const char *CALL Left(const char *str, int count);
  EXPORT const char *CALL Right(const char *str, int count);
  EXPORT const char *CALL Mid(const char *str, int offset, int count);
  EXPORT const char *CALL Lower(const char *str);
  EXPORT const char *CALL Upper(const char *str);
  EXPORT int CALL Find(const char *str, const char *find, int offset);
  EXPORT const char *CALL Replace(const char *str, const char *find, const char *replace);
  EXPORT const char *CALL Trim(const char *str);
  EXPORT const char *CALL Join(struct List *list, const char *separator);
  EXPORT struct List *CALL Split(const char *str, const char *separator);
  EXPORT const char *CALL StripExt(const char *filename);
  EXPORT const char *CALL StripDir(const char *filename);
  EXPORT const char *CALL ExtractExt(const char *filename);
  EXPORT const char *CALL ExtractDir(const char *filename);
  EXPORT int CALL Asc(const char *str, int index);
  EXPORT const char *CALL Chr(int c);
  EXPORT const char *CALL Str(int val);
  EXPORT const char *CALL StrF(float val);
  EXPORT int CALL Val(const char *str);
  EXPORT float CALL ValF(const char *str);
  EXPORT const char *CALL LoadString(const char *filename);
  EXPORT void CALL SaveString(const char *filename, const char *str, int append);

  // ------------------------------------
  // Callable
  // ------------------------------------

  EXPORT void CALL AddIntArg(int arg);
  EXPORT void CALL AddFloatArg(float arg);
  EXPORT void CALL AddStringArg(const char *arg);
  EXPORT void CALL Call(const char *name);
  EXPORT int CALL CallInt(const char *name);
  EXPORT float CALL CallFloat(const char *name);
  EXPORT const char *CALL CallString(const char *name);
  EXPORT int CALL Callable(const char *name);

#ifdef __cplusplus
}
#endif

#endif // CORE_H
