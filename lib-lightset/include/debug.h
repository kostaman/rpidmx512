#ifndef DEBUG_H_
#define DEBUG_H_

#ifndef NDEBUG
#include <stdio.h>

#define DEBUG_ENTRY		printf("--> %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
#define DEBUG_EXIT		printf("<-- %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
#define DEBUG1_ENTRY	printf("\t--> %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
#define DEBUG1_EXIT		printf("\t<-- %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
#define DEBUG2_ENTRY	printf("\t\t--> %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
#define DEBUG2_EXIT		printf("\t\t<-- %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
#else
#define DEBUG_ENTRY
#define DEBUG_EXIT
#define DEBUG1_ENTRY
#define DEBUG1_EXIT
#define DEBUG2_ENTRY
#define DEBUG2_EXIT
#endif

#endif /* DEBUG_H_ */
