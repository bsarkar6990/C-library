// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the ORACLEHCMREPORTKEY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// ORACLEHCMREPORTKEY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ORACLEHCMREPORTKEY_EXPORTS
#define ORACLEHCMREPORTKEY_API __declspec(dllexport)
#else
#define ORACLEHCMREPORTKEY_API __declspec(dllimport)
#endif
#include <msxml6.h>
#include <wrl.h>
#include<stdio.h>
#include<string.h>
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Details;
// This class is exported from the dll
class ORACLEHCMREPORTKEY_API COracleHCMReportKey {
public:
	COracleHCMReportKey(void);
	// TODO: add your methods here.
};


#define MAX_BUFFER_LENGTH 4096

class ORACLEHCMREPORTKEY_API CXMLHttpRequest2Callback :
	public Microsoft::WRL::RuntimeClass<RuntimeClassFlags<ClassicCom>, IXMLHTTPRequest2Callback>
{
private:

	//
	// Event object handle.
	//

	HANDLE m_hComplete;

	//
	// Return value from final callbacks, including OnResponseReceived or
	// OnError event handler. Once a final callback is called, no more callback
	// will be executed.
	//

	HRESULT m_hr;

	//
	// HTTP status code from OnHeadersAvailable event handler.
	//

	DWORD m_dwStatus;

	CXMLHttpRequest2Callback();

	~CXMLHttpRequest2Callback();

	STDMETHODIMP
		RuntimeClassInitialize();

	friend HRESULT Microsoft::WRL::Details::MakeAndInitialize<CXMLHttpRequest2Callback, CXMLHttpRequest2Callback>(CXMLHttpRequest2Callback**);

public:
	BYTE buffer[MAX_BUFFER_LENGTH];
	STDMETHODIMP
		OnRedirect(
			__RPC__in_opt IXMLHTTPRequest2* pXHR,
			__RPC__in_string const WCHAR* pwszRedirectUrl
		);

	STDMETHODIMP
		OnHeadersAvailable(
			__RPC__in_opt IXMLHTTPRequest2* pXHR,
			DWORD dwStatus,
			__RPC__in_string const WCHAR* pwszStatus
		);

	STDMETHODIMP
		OnDataAvailable(
			__RPC__in_opt IXMLHTTPRequest2* pXHR,
			__RPC__in_opt ISequentialStream* pResponseStream
		);

	STDMETHODIMP
		OnResponseReceived(
			__RPC__in_opt IXMLHTTPRequest2* pXHR,
			__RPC__in_opt ISequentialStream* pResponseStream
		);

	STDMETHODIMP
		OnError(
			__RPC__in_opt IXMLHTTPRequest2* pXHR,
			HRESULT hrError
		);

	STDMETHODIMP
		ReadFromStream(
			_In_opt_ ISequentialStream* pStream
		);

	STDMETHODIMP
		WaitForComplete(
			_Out_ PDWORD pdwStatus
		);
};

int process(
	_In_ PCWSTR pcwszUrl,
	_In_ PCWSTR pcwszUser,
	_In_ PCWSTR pcwszPass
);

