#ifndef __KERNEL_MODULE__
#define __KERNEL_MODULE__

// KFIFO_THRESHOLD_LEN is set to half of maximum size
#define KFIFO_LEN 1024
#define KFIFO_THRESHOLD_LEN (KFIFO_LEN / 2)

#define PROC_NAME "nvmveri"


#define NVMVERI_MAJOR 0

#if defined (NVMVERI_KERNEL_CODE) && !defined(NVMVERI_USER_CODE)

#include <linux/fs.h>
#include <linux/ioctl.h>
#include "nvmveri.hh"

ssize_t NVMVeriDeviceRead(struct file *, char __user *, size_t, loff_t *);
void NVMVeriFifoWrite(Metadata *input);

int kC_initNVMVeriDevice(void);
int kC_exitNVMVeriDevice(void);

void kC_createMetadata_Assign(void *, size_t, const char[], unsigned short);
void kC_createMetadata_Flush(void *, size_t, const char[], unsigned short);
void kC_createMetadata_Commit(const char[], unsigned short);
void kC_createMetadata_Barrier(const char[], unsigned short);
void kC_createMetadata_Fence(const char[], unsigned short);
void kC_createMetadata_Persist(void *, size_t, const char[], unsigned short);
void kC_createMetadata_Order(void *, size_t, void *, size_t, const char[], unsigned short);

void kC_createMetadata_TransactionDelim(void);
void kC_createMetadata_Ending(void);

void kC_createMetadata_TransactionBegin(const char[], unsigned short);
void kC_createMetadata_TransactionEnd(const char[], unsigned short);
void kC_createMetadata_TransactionAdd(void *, size_t, const char[], unsigned short);
void kC_createMetadata_Exclude(void *, size_t, const char[], unsigned short);
void kC_createMetadata_Include(void *, size_t, const char[], unsigned short);

extern void* metadataPtr;
extern int existVeriInstance;

/* Interface macro */
#define NVTest_START existVeriInstance = 1
#define NVTest_END existVeriInstance = 0
#define TX_CHECKER_START kC_createMetadata_TransactionBegin(__FILE__, __LINE__)
#define TX_CHECKER_END kC_createMetadata_TransactionEnd(__FILE__, __LINE__)
#define NVTest_transactionAdd() kC_createMetadata_TransactionAdd((addr), (size), __FILE__, __LINE__)
#define NVTest_assign(addr, size) kC_createMetadata_Assign((addr), (size), __FILE__, __LINE__)
#define NVTest_flush(addr, size) kC_createMetadata_Flush((addr), (size), __FILE__, __LINE__)
#define NVTest_commit() kC_createMetadata_Commit(__FILE__, __LINE__)
#define NVTest_barrier() kC_createMetadata_Barrier(__FILE__, __LINE__)
#define NVTest_fence() kC_createMetadata_Fence(__FILE__, __LINE__)
#define NVTest_isPersistent(addr, size) kC_createMetadata_Persist((addr), (size), __FILE__, __LINE__)
#define NVTest_isPersistedBefore(addrA, sizeA, addrB, sizeB) kC_createMetadata_Order((addrA), (sizeA), (addrB), (sizeB), __FILE__, __LINE__)
#define NVTest_exclude(addr, size) kC_createMetadata_Exclude((addr), (size), __FILE__, __LINE__)
#define NVTest_include(addr, size) kC_createMetadata_Include((addr), (size), __FILE__, __LINE__)
#define NVTest_transactionDelim() kC_createMetadata_TransactionDelim()
#define NVTest_ending() kC_createMetadata_Ending()


#endif // NVMVERI_KERNEL_CODE && !NVMVERI_USER_CODE

#endif // __KERNEL_MODULE__
