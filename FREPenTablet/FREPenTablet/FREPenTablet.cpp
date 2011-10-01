#include <string>

#include "FREPenTablet.h"

extern unsigned int g_currentPressure;
extern unsigned int g_currentX;
extern unsigned int g_currentY;

extern "C"
{
	FREObject getPressure(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		FREObject result;
		FRENewObjectFromUint32(g_currentPressure, &result);
		return result;
	}

	void contextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctions, const FRENamedFunction** functions)
	{
		*numFunctions = 1;

		FRENamedFunction* func = (FRENamedFunction*) malloc(sizeof(FRENamedFunction) * (*numFunctions));

		func[0].name = (const uint8_t*) "getPressure";
		func[0].functionData = NULL;
		func[0].function = &getPressure;

		*functions = func;
	}

	void contextFinalizer(FREContext ctx)
	{
		return;
	}

	void initializer(void** extData, FREContextInitializer* ctxInitializer, FREContextFinalizer* ctxFinalizer)
	{
		*ctxInitializer = &contextInitializer;
		*ctxFinalizer = &contextFinalizer;
	}

	void finalizer(void* extData)
	{
		return;
	}
}
