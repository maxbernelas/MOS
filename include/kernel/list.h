/**
 * \file list.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Doubly-linked list interface
 */
#ifndef H_LIST
#define H_LIST

#include <kernel/stddef.h>

/** List item */
typedef struct _list_item
{
	struct _list_item *prev;   /**< Previous item */
	struct _list_item *next;   /**< Next item */
} list_item;

/**
 * Add an element at head of a list
 * \param[in,out] list Pointer to the first item of the list. May be modified by
 * the function in case the list was empty
 * \param[in] item Item to add to the list
 * \retval 0 Success
 * \retval #EINVAL Item is NULL
 */
int list_add_head(list_item **list, list_item *item);

/**
 * Add an element at end of a list
 * \param[in,out] list Pointer to the first item of the list. May be modified by
 * the function in case the list was empty
 * \param[in] item Item to add to the list
 * \retval 0 Success
 * \retval #EINVAL Item is NULL
 */
int list_add_tail(list_item **list, list_item *item);

/**
 * Remove an item of a list
 * \param[in,out] list Pointer to the first item of the list. May be modified by
 * the function in case the item was first in the list
 * \param[in] item Item to add to the list
 * \retval 0 Success
 * \retval #EINVAL Item is NULL or list is empty
 */
int list_remove(list_item **list, list_item *item);

/**
 * Test if a list is empty
 * \param[in] list Pointer to the list
 * \retval 0 List is not empty
 * \retval 1 List is empty
 */
int list_is_empty(list_item *list);

/**
 * Insert a node after another
 * \param[in] a The first node
 * \param[in] b The new node to insert after a
 * \retval 0 Success
 * \retval #EINVAL Item a or b is NULL
 */
int list_insert_after(list_item *a, list_item *b);

/**
 * Get the object containing a list item
 * \param[in] p Pointer to the list item
 * \param[in] type Type of the containing object
 * \param[in] member Member name of the list item in the containing object
 * \return A pointer to the object containing the given list item
 */
#define LIST_GET_OBJECT(p, type, member) \
	((type *)(((char *)(p)) - (offsetof(type, member))))

#endif
