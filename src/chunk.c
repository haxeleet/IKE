#include "chunk.h"

#include <stdlib.h>
#include <string.h>

chunk_t* chk_create()
{
	chunk_t* chk = calloc(1, sizeof(chunk_t));
	chk->ptr = calloc(0, 0);

	return chk;
}

void chk_free(chunk_t** chk)
{
	free((*chk)->ptr);
	free(*chk);
}

void _chk_write(chunk_t* chk, void* data, int size, bool reverse)
{
	if(size > 0) {
		int new_size = chk->size + size;
		if(chk->_size < new_size) {
			chk->ptr = realloc(chk->ptr, new_size); 
			chk->_size = new_size;
		}

		if(reverse) {
			char* d = chk->ptr + chk->size;
			char* s = data + size - 1;
			for(int i = 0; i < size; i++) {
				*d = *s;
				d++;
				s--;
			}
		} else {
			memcpy(chk->ptr + chk->size, data, size);
		}

		chk->size = new_size;
	}
}

void* _chk_read(chunk_t* chk, int size, bool reverse)
{
	void* dest = NULL;
	if(size > 0) {
		size = (size > chk->size)? chk->size: size;
		dest = calloc(1, size);
		if(reverse) {
			char* d = dest;
			char* s = chk->ptr + chk->size - 1;
			for(int i = 0; i < size; i++) {
				*d = *s;
				d++;
				s--;
			}
		} else {
			memcpy(dest, chk->ptr + chk->size - size, size);
		}

		chk->size = chk->size - size;
	}

	return dest;
}
