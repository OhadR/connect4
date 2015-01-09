#include "ListUtils.h"
#include <stdlib.h>

ListRef newList(void* headData) {

	ListRef result=(ListRef)malloc(sizeof(List));

	 //if the malloc fails
	if (result == NULL) return NULL;

	result->data = headData;
	result->next = NULL;

	// return the list
	return result;
}

void* headData(ListRef list) {
	if(isEmpty(list)) return NULL;
	return list->data;
}

int isEmpty(ListRef list) {
	if (list == NULL) return 1;
	if (list->data == NULL) return 1;
	return 0;
}

ListRef tail(ListRef list) {

	if (list->next == NULL) return NULL;
	return list->next;
}

ListRef append(ListRef list, void* data) {
	// if the data is NULL
	if (data == NULL) return NULL;

	// First append
	if (list->data == NULL) {
		list->data = data;
		return list;
	}

	// Not First append
	ListRef newList=(ListRef)malloc(sizeof(List));

	//if the malloc fails
	if (newList == NULL) return NULL;
	newList->data = data;
	list->next = newList;
	newList->next = NULL;
	return newList;
}

void destroyList(ListRef list, FreeFunc freeData) {
	ListRef currentItem = list;
	ListRef nextItem = NULL;

	while (currentItem != NULL)
	{
		if (currentItem->data != NULL) freeData(currentItem->data);
		nextItem = currentItem->next;
		free(currentItem);
		currentItem = nextItem;
	}
}


