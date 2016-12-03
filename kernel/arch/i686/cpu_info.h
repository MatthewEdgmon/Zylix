#ifndef __CPU_INFO_H__
#define __CPU_INFO_H__

#include <stdbool.h>

typedef struct {

	/* What's the max value CPUID supports? */
	long highest_request_level;

	/* Information */
	char vendor[13];
	char brand[48];
	char features[128];

	/* Features */
	bool features_FPU;
	bool features_APIC;
	bool features_MMX;
	bool features_SSE;
	bool features_SSE2;
	bool features_SSE3;
	bool features_IA64;
	bool features_HYPERTHREADING;

} cpu_info_t;

char* GetCPUArchitecture();
char* GetCPUVendor();
char* GetCPUBrand();
char* GetCPUFeatures();

long GetCPUMaxRequestLevel();

bool CheckCPUFeature(int feature_code);
bool CheckCPUExtendedFeature(int feature_code);

void StoreCPUInformation();

#endif /* __CPU_INFO_H__ */
