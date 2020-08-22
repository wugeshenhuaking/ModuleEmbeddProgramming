#ifndef OS_MEM_H_
#define OS_MEM_H_
#include "stm32f10x.h"

#ifndef OS_MEM_C_
#define OS_MEM_Cx_  extern
#else 
#define OS_MEM_Cx_
#endif


#define OS_ENTER_CRITICAL() (__disable_irq())
#define OS_EXIT_CRITICAL() (__enable_irq())



#define OS_MAX_MEM_PART           4 

#define OS_NO_ERR                 0
#define OS_MEM_INVALID_PART     110
#define OS_MEM_INVALID_BLKS     111
#define OS_MEM_INVALID_SIZE     112
#define OS_MEM_NO_FREE_BLKS     113
#define OS_MEM_FULL             114


typedef unsigned char  INT8U;         //无符号8位数
typedef unsigned int   INT16U;        //无符号16位数
typedef unsigned long  INT32U;        //无符号32位数


typedef struct {                       /* MEMORY CONTROL BLOCK                                         */
    void   *OSMemAddr;                 /* Pointer to beginning of memory partition                     */
    void   *OSMemFreeList;             /* Pointer to list of free memory blocks                        */
    INT32U  OSMemBlkSize;              /* Size (in bytes) of each block of memory                      */
    INT32U  OSMemNBlks;                /* Total number of blocks in this partition                     */
    INT32U  OSMemNFree;                /* Number of memory blocks remaining in this partition          */
} OS_MEM;


typedef struct {
    void   *OSAddr;                    /* Pointer to the beginning address of the memory partition     */
    void   *OSFreeList;                /* Pointer to the beginning of the free list of memory blocks   */
    INT32U  OSBlkSize;                 /* Size (in bytes) of each memory block                         */
    INT32U  OSNBlks;                   /* Total number of blocks in the partition                      */
    INT32U  OSNFree;                   /* Number of memory blocks free                                 */
    INT32U  OSNUsed;                   /* Number of memory blocks used                                 */
} OS_MEM_DATA;


OS_MEM *OSMemCreate (void *addr, INT32U nblks, INT32U blksize, INT8U *err);
void *OSMemGet (OS_MEM *pmem, INT8U *err);
void OSMemInit (void);
INT8U OSMemPut (OS_MEM  *pmem, void *pblk);
INT8U OSMemQuery (OS_MEM *pmem, OS_MEM_DATA *ppdata);



#endif


