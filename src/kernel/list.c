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
 * \file list.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Doubly-linked list implementation
 */
#include <kernel/list.h>
#include <kernel/stddef.h>
#include <kernel/errno.h>

/*******************************************************************************
 * Private functions
 ******************************************************************************/
/**
 * Get the last item of a list
 * \param[in] list Poitner to the list
 * \return Pointer to the last item of the list, NULL if list is empty
 */
static list_item * last_item(list_item *list)
{
	if(list == NULL)
	{
		return NULL;
	}

	while(list->next != NULL)
	{
		list = list->next;
	}

	return list;
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/
int list_add_head(list_item **list, list_item *item)
{
	if(item == NULL)
	{
		return EINVAL;
	}

	item->prev = NULL;
	item->next = NULL;

	if(!list_is_empty(*list))
	{
		(*list)->prev = item;
		item->next = *list;
	}

	*list = item;

	return 0;
}

int list_add_tail(list_item **list, list_item *item)
{
	list_item *last;

	if(item == NULL)
	{
		return EINVAL;
	}

	item->next = NULL;
	item->prev = NULL;

	last = last_item(*list);

	if(last == NULL)
	{
		/* List is empty */
		*list = item;
	}
	else
	{
		last->next = item;
		item->prev = last;
	}

	return 0;
}

int list_remove(list_item **list, list_item *item)
{
	if((item == NULL) || (list == NULL) || list_is_empty(*list))
	{
		return EINVAL;
	}

	if(*list == item)
	{
		/* Removing first element */
		*list = item->next;
	}

	if(item->next != NULL)
	{
		item->next->prev = item->prev;
	}

	if(item->prev != NULL)
	{
		item->prev->next = item->next;
	}

	item->next = NULL;
	item->prev = NULL;

	return 0;
}

int list_is_empty(list_item *list)
{
	return (list == NULL);
}

int list_insert_after(list_item *a, list_item *b)
{
	if((a == NULL) || (b == NULL))
	{
		return EINVAL;
	}

	b->next = a->next;
	b->prev = a;
	a->next = b;

	if((b->next) != NULL)
	{
		b->next->prev = b;
	}

	return 0;
}
