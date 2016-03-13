#ifndef __CPU_INFO_H__
#define __CPU_INFO_H__

#include <libc/stdbool.h>

char* GetCPUArchitecture();
char* GetCPUVendor();
char* GetCPUBrand();
char* GetCPUFeatures();

bool CheckCPUFeature(int feature_code);
bool CheckCPUExtendedFeature(int feature_code);

#endif /* __CPU_INFO_H__ */
