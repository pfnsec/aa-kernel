#ifndef BB_ALLOC
#define BB_ALLOC
#include "registers.h"

//Linked list, with each node containing info on a block of 2^size pages

typedef struct bb_alloc_t {
	unsigned int size;
	void *addr;
	int free;
	struct bb_alloc_t *next;
} bb_alloc_t;


typedef struct slab_block_list {
	addr_t free;
	struct slab_block_list *next;
} slab_block_list;


typedef struct slab_page_list {
	void *addr;
	slab_block_list blocks;
	struct slab_page_list *next;
} slab_page_list;


typedef struct slab {
	addr_t alignment;
	slab_page_list pages;
} slab;


//Slab caches can be declared and initialized entirely statically,
//meaning that we can create and use them (without being able to expand them)
//before having initialized the page allocator.
//
//Pages must in this case be statically allocated also; the first page available
//is so reserved for the static heads of dynamic data structures used by the slab cache and 
//buddy-block allocator implementations.
//
//Each 'block' in a slab has a word-sized bitmap indicating whether a given entry in the block is free.
//Each slab therefore has (PAGESIZE/BLOCKSIZE) blocks per page.


#define BLOCKSIZE(align) (align * WORDSIZE)


//bb_slab_static():
//
//This Macro declares a struct bb_slab with the following format:
//bb_slab {
//	align,					//Entry size in bytes 
//						//(I.E., sizeof(struct T) for typical cache usage)
//
//	struct bb_slab_page_list {		//Linked list of pages allocated to this slab
//		addr,				//Address of the pre-allocated page
//
//		struct bb_slab_block_list {	//Linked list of bitmasks corresponding to the 
//						//free/used states of entries in a block
//
//			0b111...		//Mark all entries as free initially
//			0			//next = null (static head - only a single block declared)
//		};
//
//		0				//next = null (static head - only a single page declared)
//	};
//
//

#define bb_slab_static(align, addr)  {			\
		.alignment = align,			\
		.pages = &((bb_slab_page_list) {	\
			.addr = addr,			\
	 		.blocks = &((bb_slab_block_list) {\
				.free = ~(addr_t)(0),	\
				.next = 0		\
			}),				\
			.next = 0			\
		})					\
	}



void  slab_create(slab *, addr_t, void *);

void *slab_alloc(slab *);
void  slab_free (slab *, void *);


#endif
