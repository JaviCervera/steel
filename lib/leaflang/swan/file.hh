#ifndef SWAN_FILE_INCLUDED
#define SWAN_FILE_INCLUDED

#include "string.hh"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#if defined _WIN32 && !defined S_ISDIR
#define S_ISDIR(m) (((m) & _S_IFDIR) == _S_IFDIR)
#endif

namespace swan
{
  class file_t
  {
  public:
    enum mode {
      read,
      write,
      append
    };

    file_t(const char* filename, mode m);
    ~file_t() { close(); }
    bool isopen() const { return handle != 0; }

    void close() { if ( handle ) fclose(handle); handle = 0; }
    size_t size() const { return size_; }
    size_t pos() const { return ftell(handle); }
    void seek(size_t offset) { fseek(handle, offset, SEEK_SET); }
    bool eof() const { return pos() == size_; }

    char readchar();
    short readshort();
    int readint();
    long long readint64();
    unsigned char readuchar();
    unsigned short readushort();
    unsigned int readuint();
    unsigned long long readuint64();
    float readfloat();
    double readdouble();
    std::string readcstring();
    std::string readcline();
    size_t readbytes(void* buffer, size_t count) { return fread(buffer, 1, count, handle); }

    void writechar(char v) { fwrite(&v, 1, sizeof(char), handle); }
    void writeshort(short v) { fwrite(&v, 1, sizeof(short), handle); }
    void writeint(int v) { fwrite(&v, 1, sizeof(int), handle); }
    void writeint64(long long v) { fwrite(&v, 1, sizeof(long long), handle); }
    void writeuchar(unsigned char v) { fwrite(&v, 1, sizeof(unsigned char), handle); }
    void writeushort(unsigned short v) { fwrite(&v, 1, sizeof(unsigned short), handle); }
    void writeuint(unsigned int v) { fwrite(&v, 1, sizeof(unsigned int), handle); }
    void writeuint64(unsigned long long v) { fwrite(&v, 1, sizeof(unsigned long long), handle); }
    void writefloat(float v) { fwrite(&v, 1, sizeof(float), handle); }
    void writedouble(double v) { fwrite(&v, 1, sizeof(double), handle); }
    void writecstring(const char* v) { fwrite(v, strlen(v)+1, sizeof(char), handle); }
    void writecline(const char* v) { std::string str = std::string(v) + "\r\n"; fwrite(str.c_str(), str.length(), sizeof(char), handle); }
    size_t writebytes(const void* buffer, size_t count) { return fwrite(buffer, 1, count, handle); }
  private:
    FILE* handle;
    size_t size_;
  };

  inline file_t::file_t(const char* filename, mode m)
  {
    std::string attr;
    switch ( m )
    {
      case read:
      attr = "rb";
      break;
      case write:
      attr = "wb";
      break;
      case append:
      attr = "ab";
      break;
    }

#ifdef _MSC_VER
    fopen_s(&handle, filename, attr.c_str());
#else
    handle = fopen(filename, attr.c_str());
#endif
    size_ = -1;
    if ( handle && m == read )
    {
      fseek(handle, 0, SEEK_END);
      size_ = ftell(handle);
      fseek(handle, 0, SEEK_SET);
    }
  }

  inline char file_t::readchar()
  {
    char v;
    fread(&v, 1, sizeof(char), handle);
    return v;
  }

  inline short file_t::readshort()
  {
    short v;
    fread(&v, 1, sizeof(short), handle);
    return v;
  }

  inline int file_t::readint()
  {
    int v;
    fread(&v, 1, sizeof(int), handle);
    return v;
  }

  inline long long file_t::readint64()
  {
    long long v;
    fread(&v, 1, sizeof(long long), handle);
    return v;
  }

  inline unsigned char file_t::readuchar()
  {
    unsigned char v;
    fread(&v, 1, sizeof(unsigned char), handle);
    return v;
  }

  inline unsigned short file_t::readushort()
  {
    unsigned short v;
    fread(&v, 1, sizeof(unsigned short), handle);
    return v;
  }

  inline unsigned int file_t::readuint()
  {
    unsigned int v;
    fread(&v, 1, sizeof(unsigned int), handle);
    return v;
  }

  inline unsigned long long file_t::readuint64()
  {
    unsigned long long v;
    fread(&v, 1, sizeof(unsigned long long), handle);
    return v;
  }

  inline float file_t::readfloat()
  {
    float v;
    fread(&v, 1, sizeof(float), handle);
    return v;
  }

  inline double file_t::readdouble()
  {
    double v;
    fread(&v, 1, sizeof(double), handle);
    return v;
  }

  inline std::string file_t::readcstring()
  {
    std::string str;
    char c = readchar();
    while ( c != 0 )
    {
      str += c;
      c = readchar();
    }
    return str;
  }

  inline std::string file_t::readcline()
  {
    std::string str;
    char c = readchar();
    while ( c != '\r' && c != '\n' )
    {
      str += c;
      if ( !eof() )
      {
        c = readchar();
      }
      else
      {
        break;
      }
    }
    if ( c == '\r' && !eof() )
    {
      c = readchar();
      if ( c != '\n' ) seek(pos()-1);
    }
    return str;
  }

  enum filetype_t
  {
    funknown,
    ffile,
    fdir
  };

  inline filetype_t filetype(const char* filename)
  {
    struct stat statbuf;
    if ( stat(filename, &statbuf) == -1 )
      return funknown;
    else if ( S_ISDIR(statbuf.st_mode) )
      return fdir;
    else
      return ffile;
  }

  inline size_t filesize(const char* filename)
  {
    struct stat statbuf;
    if ( stat(filename, &statbuf) == -1 )
      return 0;   // does not exist
    else
      return statbuf.st_size;
  }

  inline void filecopy(const char* filenameSrc, const char* filenameDst)
  {
    // TODO: copy preserving file permissions

    // open first file for reading
    file_t fin(filenameSrc, file_t::read);
    if ( fin.isopen() )
    {
      // read contents
      void* buffer = malloc(fin.size());
      fin.readbytes(buffer, fin.size());

      // write to second file
      file_t fout(filenameDst, file_t::write);
      if ( fout.isopen() )
      {
        fout.writebytes(buffer, fin.size());
        fout.close();
      }

      // free resources
      free(buffer);
      fin.close();
    }
  }

  inline void fileremove(const char* filename) {
    remove(filename);
  }

} // namespace swan

#endif // SWAN_FILE_INCLUDED

