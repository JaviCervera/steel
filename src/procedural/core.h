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

#ifdef __cplusplus
extern "C" {
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

const char* AppName();
struct List* AppArgs();
const char* Run(const char* command);
void* _IncRef(void* ptr);
void _DecRef(void* ptr);
void* _AutoDec(void* ptr);
void _DoAutoDec();

// ------------------------------------
// Console
// ------------------------------------

const char* Input(const char* prompt);
void Print(const char* msg);

// ------------------------------------
// Dir
// ------------------------------------

struct List* DirContents(const char* path);
const char* CurrentDir();
void ChangeDir(const char* dir);
const char* FullPath(const char* filename);

// ------------------------------------
// File
// ------------------------------------

int FileType(const char* filename);
void DeleteFile(const char* filename);

// ------------------------------------
// List
// ------------------------------------

struct List* _CreateList();
struct List* _SetListInt(struct List* list, size_t index, int value);
struct List* _SetListFloat(struct List* list, size_t index, float value);
struct List* _SetListString(struct List* list, size_t index, const char* value);
struct List* _SetListList(struct List* list, size_t index, struct List* value);
struct List* _SetListDict(struct List* list, size_t index, struct Dict* value);
struct List* _SetListRef(struct List* list, size_t index, void* value);
int _ListInt(struct List* list, size_t index);
float _ListFloat(struct List* list, size_t index);
const char* _ListString(struct List* list, size_t index);
struct List* _ListList(struct List* list, size_t index);
struct Dict* _ListDict(struct List* list, size_t index);
void* _ListRef(struct List* list, size_t index);
const char* _ListToString(struct List* list);
void RemoveIndex(struct List* list, int index);
int ListSize(struct List* list);
void ClearList(struct List* list);

// ------------------------------------
// Dict
// ------------------------------------

struct Dict* _CreateDict();
struct Dict* _SetDictInt(struct Dict* dict, const char* key, int value);
struct Dict* _SetDictFloat(struct Dict* dict, const char* key, float value);
struct Dict* _SetDictString(struct Dict* dict, const char* key, const char* value);
struct Dict* _SetDictList(struct Dict* dict, const char* key, struct List* value);
struct Dict* _SetDictDict(struct Dict* dict, const char* key, struct Dict* value);
struct Dict* _SetDictRef(struct Dict* dict, const char* key, void* value);
int _DictInt(struct Dict* dict, const char* key);
float _DictFloat(struct Dict* dict, const char* key);
const char* _DictString(struct Dict* dict, const char* key);
struct List* _DictList(struct Dict* dict, const char* key);
struct Dict* _DictDict(struct Dict* dict, const char* key);
void* _DictRef(struct Dict* dict, const char* key);
const char* _DictToString(struct Dict* dict);
int Contains(struct Dict* dict, const char* key);
void RemoveKey(struct Dict* dict, const char* key);
int DictSize(struct Dict* dict);
void ClearDict(struct Dict* dict);

// ------------------------------------
// Math
// ------------------------------------

float ASin(float x);
float ATan(float x);
float ATan2(float x, float y);
float Abs(float x);
float Ceil(float x);
float Clamp(float x, float min, float max);
float Cos(float x);
float Exp(float x);
float Floor(float x);
float Log(float x);
float Max(float x, float y);
float Min(float x, float y);
float Pow(float x, float y);
float Sgn(float x);
float Sin(float x);
float Sqrt(float x);
float Tan(float x);
int Int(float num);

// ------------------------------------
// Memory
// ------------------------------------

Memory* Dim(int size);
void Undim(Memory* mem);
void Redim(Memory* mem, int size);
Memory* LoadDim(const char* filename);
void SaveDim(Memory* mem, const char* filename);
int DimSize(Memory* mem);
int PeekByte(Memory* mem, int offset);
int PeekShort(Memory* mem, int offset);
int PeekInt(Memory* mem, int offset);
float PeekFloat(Memory* mem, int offset);
const char* PeekString(Memory* mem, int offset);
void* PeekRef(Memory* mem, int offset);
void PokeByte(Memory* mem, int offset, int val);
void PokeShort(Memory* mem, int offset, int val);
void PokeInt(Memory* mem, int offset, int val);
void PokeFloat(Memory* mem, int offset, float val);
void PokeString(Memory* mem, int offset, const char* val);
void PokeRef(Memory* mem, int offset, void* val);

// ------------------------------------
// String
// ------------------------------------

int Len(const char* str);
const char* Left(const char* str, int count);
const char* Right(const char* str, int count);
const char* Mid(const char* str, int offset, int count);
const char* Lower(const char* str);
const char* Upper(const char* str);
int Find(const char* str, const char* find, int offset);
const char* Replace(const char* str, const char* find, const char* replace);
const char* Trim(const char* str);
const char* Join(struct List* list, const char* separator);
struct List* Split(const char* str, const char* separator);
const char* StripExt(const char* filename);
const char* StripDir(const char* filename);
const char* ExtractExt(const char* filename);
const char* ExtractDir(const char* filename);
int Asc(const char* str, int index);
const char* Chr(int c);
const char* Str(int val);
const char* StrF(float val);
int Val(const char* str);
float ValF(const char* str);
const char* LoadString(const char* filename);
void SaveString(const char* filename, const char* str, int append);

// ------------------------------------
// Callable
// ------------------------------------

void AddIntArg(int arg);
void AddFloatArg(float arg);
void AddStringArg(const char* arg);
void Call(const char* name);
int CallInt(const char* name);
float CallFloat(const char* name);
const char* CallString(const char* name);
int Callable(const char* name);

#ifdef __cplusplus
}
#endif

#endif // CORE_H
