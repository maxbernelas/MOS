/*
 * Copyright (c) 2014, Maxime Bernelas
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the owner nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * \file kalloc.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Kernel memory allocator implementation
 */
#include <kernel/string.h>
#include <kernel/kalloc.h>
#include <kernel/list.h>
#include <kernel/stddef.h>
#include <kernel/stdint.h>

/* Linker-defined symbols */
extern uint32_t __stack_limit, __bss_end;

/*******************************************************************************
 * Private definitions
 ******************************************************************************/
/** Block states */
typedef enum
{
	STATE_FREE,      /**< Block is free */
	STATE_USED       /**< Block is used */
} block_state;

/** Memory block information */
typedef struct
{
	list_item node;         /**< List node for this block */
	block_state state;      /**< State of the block */
} block_info;

/** Linked list of memory blocks */
static block_info *first_block = NULL;

/**
 * Computes the size of a block
 * \param[in] b Pointer to the block
 * \return The size of the block in bytes
 */
static size_t block_size(block_info *b)
{
	char *start, *end;

	start = (char *)b;

	if(b->node.next == NULL)
	{
		end = (char *)&__stack_limit;
	}
	else
	{
		end = (char *)(b->node.next);
	}

	return (end - start);
}

/**
 * Computes the usable size of a block (total size minus management data size)
 * \param[in] b Pointer to the block
 * \return The usable size of the block in bytes
 */
static size_t usable_block_size(block_info *b)
{
	return (block_size(b) - sizeof(*b));
}

/**
 * Split a block to adjust its size to the requested size
 * \param[in,out] b Pointer to the block to split
 * \param[in] n Target usable size of the block
 * \note This function assumes that the usable size of the block b is at least n
 */
static void block_split(block_info *b, size_t n)
{
	block_info *new_block;

	if((usable_block_size(b) - n) <= sizeof(*b))
	{
		/* 
		 * No need to split the block because there is not enough free
		 * space to create a new block after this one
		 */
		 return;
	}

	/* Fill in the management data of the new block */
	new_block = (block_info *)(((char *)(b + 1)) + n);
	new_block->state = STATE_FREE;

	/* Insert the new block in the list of blocks */
	list_insert_after(&(b->node), &(new_block->node));
}

/**
 * Test if a block can be merged with the next one
 * \param[in] b The block to test
 * \retval 0 The block cannot be merged
 * \retval 1 The block can be merged
 * \note This function assumes that b is not NULL
 */
static int can_merge_with_next(block_info *b)
{
	block_info *next_block;

	if((b->state == STATE_FREE) && (b->node.next != NULL))
	{
		next_block = LIST_GET_OBJECT(b->node.next, block_info, node);

		return (next_block->state == STATE_FREE);
	}

	return 0;
}

/** Merge adjacent free blocks in list of blocks */
static void merge_blocks(void)
{
	list_item *cur_node;
	block_info *cur_block;

	cur_node = &(first_block->node);
	while(cur_node)
	{
		cur_block = LIST_GET_OBJECT(cur_node, block_info, node);

		if(can_merge_with_next(cur_block))
		{
			/* 
			 * Merge the block, it is equivalent to removing
			 * the next block from the list
			 */
			list_remove(&cur_node, cur_block->node.next);
		}
		else
		{
			/* Advance to next block */
			cur_node = cur_node->next;
		}
	}
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/
int kalloc_init(void)
{
	/* Initialize the memory allocator data structures */
	/* Heap starts at end of BSS and ends at the top of the stack space */
	first_block = (block_info *)&__bss_end;
	first_block->node.next = NULL;
	first_block->node.prev = NULL;
	first_block->state = STATE_FREE;

	return 0;
}

void * kmalloc(size_t n)
{
	list_item *cur_node;
	block_info *best;

	if(n == 0)
	{
		return NULL;
	}

	/* Find the best fitting free block */
	cur_node = &(first_block->node);
	best = NULL;

	while(cur_node)
	{
		block_info *b;

		b = LIST_GET_OBJECT(cur_node, block_info, node);

		if((b->state == STATE_FREE) && (usable_block_size(b) >= n))
		{
			if(best == NULL)
			{
				best = b;
			}
			else if(block_size(b) < block_size(best))
			{
				/* This one fits best */
				best = b;
			}
		}

		cur_node = cur_node->next;
	}

	/* Search is finished */
	if(best == NULL)
	{
		return NULL;
	}

	/* We have found a block, split it to the requested size */
	block_split(best, n);

	/* Mark block as used and return the pointer to usable data */
	best->state = STATE_USED;

	return (best + 1);
}

void * kcalloc(size_t n)
{
	void *p;

	p = kmalloc(n);

	if(p != NULL)
	{
		memset(p, 0x00, n);
	}

	return p;
}

void kfree(void *p)
{
	block_info *b;

	if(p == NULL)
	{
		return;
	}

	/* Retrieve the block info pointer */
	b = p;
	b--;

	/* Mark block as free */
	b->state = STATE_FREE;

	/* Merge free blocks */
	merge_blocks();
}
