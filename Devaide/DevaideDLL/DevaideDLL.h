#ifndef _DEVAIDEDLL_H_
#define _DEVAIDEDLL_H_

#ifdef _DEVAIDE_DLL_EXPORT_
#define DEVAIDE_DLLAPI __declspec(dllexport)
#else
#define DEVAIDE_DLLAPI __declspec(dllimport)
#endif


#endif