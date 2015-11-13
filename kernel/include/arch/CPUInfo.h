#ifndef __CPU_INFO_H__
#define __CPU_INFO_H__

#include <stdint.h>
#include <types.h>

char* GetCPUVendor();
char* GetCPUBrand();
char* GetCPUFeatures();

bool CheckCPUFeature();
bool CheckCPUExtendedFeature();

#endif /* __CPU_INFO_H__ */