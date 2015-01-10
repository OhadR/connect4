#include "MiniMax.h"
#include <stdio.h>
#include "stdbool.h"
#include "utils.h"

struct MiniMaxResult getBestChild(
		void* state,
		unsigned int maxDepth,
		ListRef (*getChildren) (void* state),
		FreeFunc freeState,
		int (*evaluate) (void* state),
		int isMaxPlayer) {

	struct MiniMaxResult result;
	struct MiniMaxResult childResult;
	ListRef childrenlistTemp;

	bool isFirstChild;;
	int index = 0;

	result.index = 0;
	result.value = evaluate(state);

	// Recursion Stop Conditions
	if( result.value == MAX_EVALUATION || result.value == MIN_EVALUATION )
	{
//		debug("stop condition: MIN or MAX values.");
		return result;
	}

	if( maxDepth == 0)
	{
//		debug("stop condition: maxDepth == 0.");
		return result;
	}

	--maxDepth; // Checking children in lower depth
	ListRef childrenslist = NULL;
	childrenslist = getChildren(state);
	childrenlistTemp = childrenslist;
	isFirstChild = true;
	do {
			if (headData(childrenlistTemp) != NULL) {
				childResult = getBestChild(headData(childrenlistTemp),maxDepth,
								  getChildren, freeState ,evaluate,!isMaxPlayer);

				if (isFirstChild) { // If it is the first child set the child value
					result.index = index;
					result.value = childResult.value;
					isFirstChild = false;
				}
				else // if it is not the first child check conditions
				{
					if (isMaxPlayer) // If it is max player
					{
						if (childResult.value > result.value) {
							result.index = index;
							result.value = childResult.value;
						}
					}
					else // If it is min player
					{
						if (childResult.value < result.value) {
							result.index = index;
							result.value = childResult.value;
						}
					}
				}
				childrenlistTemp = tail(childrenlistTemp);
				index++;
			}
		} while (childrenlistTemp != NULL);

	// Free the memory of the list
	destroyList(childrenslist,freeState);

	return result;
}

