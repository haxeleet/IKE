#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <stdbool.h>

typedef struct {
  void*   ptr;
  int     size;
  int     _size;  // real_size
}chunk_t;

chunk_t*  chk_create();
void      chk_free(chunk_t** chk);

void      _chk_write(chunk_t* chk, void* data, int size, bool reverse);
#define   chk_write(chk, data, size) _chk_write(chk, data, size, false)
#define   chk_rwrite(chk, data, size) _chk_write(chk, data, size, true)
void*     _chk_read(chunk_t* chk, int size, bool reverse);
#define   chk_read(chk, size) _chk_read(chk, size, false)
#define   chk_rread(chk, size) _chk_read(chk, size, true)

#endif //__CHUNK_H__