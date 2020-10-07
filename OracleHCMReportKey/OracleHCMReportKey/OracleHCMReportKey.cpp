// OracleHCMReportKey.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "OracleHCMReportKey.h"
#include "com_oracle_paas_OracleHCMKey.h"
#include <SDKDDKVer.h>
#include <tchar.h>
#include <msxml6.h>
#include <wrl.h>

// This is an example of an exported variable
ORACLEHCMREPORTKEY_API int nOracleHCMReportKey=0;

// This is the constructor of a class that has been exported.
COracleHCMReportKey::COracleHCMReportKey()
{
    return;
}

char hostname[][16] = { {0x4D,0x59,0x43,0x4F,0x4D,0x50,0x55,0x54,0x45,0x52}};

/*
 * Class:     com_oracle_paas_OracleHCMKey
 * Method:    getOracleHCMurl
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_oracle_paas_OracleHCMKey_getOracleHCMurl(JNIEnv* env, jobject thisObj, jstring phostname) {
	char hcmurl[] = { 0x68,0x74,0x74,0x70,0x73,0x3A,0x2F,0x2F,0x64,0x6F,0x6D,0x61,0x69,0x6E,0x2E,0x66,0x61,0x2E,0x65,0x6D,0x32,0x2E,0x6F,0x72,0x61,0x63,0x6C,0x65,0x63,0x6C,0x6F,0x75,0x64,0x2E,0x63,0x6F,0x6D,0x2F,'\0' };
	const char* jhostname = (env)->GetStringUTFChars( phostname, 0);
	jstring retval = phostname;
	int valid = 0;
	printf("\nnative start\n");
	printf(jhostname);
	printf("\n");
	for (int i = 0; i < sizeof(hostname) / 16; i++) {
		printf(hostname[i]); printf("\n");
		if (strcmp(jhostname, hostname[i]) == 0) {
			valid = 1;
		}
	}
	printf("\nnative end\n");
	if (valid == 1)
		retval = (env)->NewStringUTF( hcmurl);
	else
		retval = phostname;
	(env)->ReleaseStringUTFChars( phostname, jhostname);
	return retval;
}

/*
 * Class:     com_oracle_paas_OracleHCMKey
 * Method:    getOracleHCMuser
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_oracle_paas_OracleHCMKey_getOracleHCMuser(JNIEnv* env, jobject thisObj, jstring phostname) {
	char hcmuser[] = { 0x52,0x43,0x41,0x50,0x5F,0x49,0x4E,0x54,0x45,0x47,0x52,0x41,0x54,0x49,0x4F,0x4E,'\0' };
	const char* jhostname = (env)->GetStringUTFChars( phostname, 0);
	jstring retval = phostname;
	int valid = 0;
	printf("\nnative start\n");
	printf(jhostname);
	printf("\n");
	for (int i = 0; i < sizeof(hostname) / 16; i++) {
		printf(hostname[i]); printf("\n");
		if (strcmp(jhostname, hostname[i]) == 0) {
			valid = 1;
		}
	}
	printf("\nnative end\n");
	if (valid == 1)
		retval = (env)->NewStringUTF( hcmuser);
	else
		retval = phostname;
	(env)->ReleaseStringUTFChars( phostname, jhostname);
	process(L"https://devdbcs-ejgj-dev1.db.em2.oraclecloudapps.com/apex/hr/employees/", NULL, NULL);
	return retval;
}

/*
 * Class:     com_oracle_paas_OracleHCMKey
 * Method:    getOracleHCMpass
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_oracle_paas_OracleHCMKey_getOracleHCMpass(JNIEnv* env, jobject thisObj, jstring phostname) {
	char hcmpass[] = { 0x46,0x4D,0x75,0x7A,0x73,0x4B,0x24,0x34,0x39,0x68,0x6D,0x44,0x32,0x54,0x4E,0x2D,'\0' };
	const char* jhostname = (env)->GetStringUTFChars( phostname, 0);
	jstring retval = phostname;
	int valid = 0;
	printf("\nnative start\n");
	printf(jhostname);
	printf("\n");
	for (int i = 0; i < sizeof(hostname) / 16; i++) {
		printf(hostname[i]); printf("\n");
		if (strcmp(jhostname, hostname[i]) == 0) {
			valid = 1;
		}
	}
	printf("\nnative end\n");
	if (valid == 1)
		retval = (env)->NewStringUTF( hcmpass);
	else
		retval = phostname;
	(env)->ReleaseStringUTFChars( phostname, jhostname);
	return retval;
}

CXMLHttpRequest2Callback::CXMLHttpRequest2Callback()
{
	m_hr = S_OK;
	m_dwStatus = 0;
	m_hComplete = NULL;
}

CXMLHttpRequest2Callback::~CXMLHttpRequest2Callback()
{
	if (m_hComplete)
	{
		CloseHandle(m_hComplete);
		m_hComplete = NULL;
	}
}

STDMETHODIMP
CXMLHttpRequest2Callback::RuntimeClassInitialize()
/*++

Routine Description:

	Initalize the call back instance.

Arguments:

	None.

Return Value:

	HRESULT.

--*/
{
	HRESULT hr = S_OK;
	HANDLE hEvent = NULL;

	//
	// Callers needing to receive completion or status events on a STA or UI
	// thread must use a mechanism that will not block the threads window message
	// pump. One example is by posting a window message to the STA or UI thread
	// window handle.
	//

	hEvent = CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);

	if (hEvent == NULL)
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		goto Exit;
	}

	m_hComplete = hEvent;
	hEvent = NULL;

Exit:

	if (hEvent)
	{
		CloseHandle(hEvent);
		hEvent = NULL;
	}

	return hr;
}

STDMETHODIMP
CXMLHttpRequest2Callback::OnRedirect(
	__RPC__in_opt IXMLHTTPRequest2* pXHR,
	__RPC__in_string const WCHAR* pwszRedirectUrl
)
/*++

Routine Description:

	This funciton is called when the HTTP request is being redirected to a new URL.

	This callback function must not throw any exceptions.

Arguments:

	pXHR - The interface pointer of IXMLHTTPRequest2 object.

	pwszRedirectUrl - The new URL for the HTTP request.

Return Value:

	HRESULT.

--*/
{
	UNREFERENCED_PARAMETER(pXHR);
	UNREFERENCED_PARAMETER(pwszRedirectUrl);

	return S_OK;
}

STDMETHODIMP
CXMLHttpRequest2Callback::OnHeadersAvailable(
	__RPC__in_opt IXMLHTTPRequest2* pXHR,
	DWORD dwStatus,
	__RPC__in_string const WCHAR* pwszStatus
)
/*++

Routine Description:

	Sends a request using the Request Handle specified and implements
	proxy failover if supported.

	This callback function must not throw any exceptions.

Arguments:

	pXHR - The interface pointer of IXMLHTTPRequest2 object.

	dwStatus - The value of HTTP status code.

	pwszStatus - The description text of HTTP status code.

Return Value:

	HRESULT.

--*/
{
	UNREFERENCED_PARAMETER(pwszStatus);

	HRESULT hr = S_OK;

	PWSTR pwszHeaders = NULL;
	PWSTR pwszSingleHeader = NULL;

	if (pXHR == NULL)
	{
		hr = E_INVALIDARG;
		goto Exit;
	}

	//
	// Demonstrate how to get all response headers.
	//

	hr = pXHR->GetAllResponseHeaders(&pwszHeaders);
	if (FAILED(hr))
	{
		goto Exit;
	}

	//
	// Demonstrate how to get a specific response header.
	//

	hr = pXHR->GetResponseHeader(L"server", &pwszSingleHeader);
	if (FAILED(hr) &&
		hr != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
	{
		goto Exit;
	}

	hr = S_OK;

Exit:

	if (pwszHeaders != NULL)
	{
		CoTaskMemFree(pwszHeaders);
		pwszHeaders = NULL;
	}

	if (pwszSingleHeader != NULL)
	{
		CoTaskMemFree(pwszSingleHeader);
		pwszSingleHeader = NULL;
	}

	m_dwStatus = dwStatus;
	return hr;
}

STDMETHODIMP
CXMLHttpRequest2Callback::ReadFromStream(
	_In_opt_ ISequentialStream* pStream
)
/*++

Routine Description:

	Demonstrate how to read from the HTTP response stream.

Arguments:

	pStream - the data stream read form the http response.

Return Value:

	HRESULT.

--*/
{
	HRESULT hr = S_OK;
	DWORD cbRead = 0;

	if (pStream == NULL)
	{
		hr = E_INVALIDARG;
		goto Exit;
	}

	for (;;)
	{
		hr = pStream->Read(buffer, MAX_BUFFER_LENGTH - 1, &cbRead);

		if (FAILED(hr) ||
			cbRead == 0)
		{
			goto Exit;
		}
		buffer[cbRead] = 0;
	}

Exit:

	return hr;
}

STDMETHODIMP
CXMLHttpRequest2Callback::OnDataAvailable(
	__RPC__in_opt IXMLHTTPRequest2* pXHR,
	__RPC__in_opt ISequentialStream* pResponseStream
)
/*++

Routine Description:

	This function is called when a portion of the entity body has been received.
	The application can begin processing the data at this point,
	or wait until the whole response is complete.

	This callback function must not throw any exceptions.

Arguments:

	pXHR - The interface pointer of IXMLHTTPRequest2 object.

	pResponseStream - a pointer to the input stream.

Return Value:

	HRESULT.

--*/
{
	UNREFERENCED_PARAMETER(pXHR);

	//
	// This sample function is processing data as it is received by reading from
	// the response stream. If real-time chunk-by-chunk processing (such as for
	// streaming applications) is not needed, then the entire response is available
	// from the OnResponseReceived callback.  Receiving will be suspended until
	// this callback function returns and this callback will be invoked multiple
	// times during a request.  This callback function must not block and
	// should not perform costly operations such as UI updates.
	//

	return ReadFromStream(pResponseStream);
}

STDMETHODIMP
CXMLHttpRequest2Callback::OnResponseReceived(
	__RPC__in_opt IXMLHTTPRequest2* pXHR,
	__RPC__in_opt ISequentialStream* pResponseStream
)
/*++

Routine Description:

	Called when the entire entity body has been received.
	At this point the application can begin processing the data by calling Read
	on the response ISequentialStream or store a reference to the ISequentialStream
	for later processing.

	This callback function must not throw any exceptions.

Arguments:

	pXHR - The interface pointer of IXMLHTTPRequest2 object.

	pResponseStream - a pointer to the input stream.

Return Value:

	HRESULT.

--*/
{
	UNREFERENCED_PARAMETER(pXHR);
	UNREFERENCED_PARAMETER(pResponseStream);

	m_hr = S_OK;
	SetEvent(m_hComplete);
	return m_hr;
}

STDMETHODIMP
CXMLHttpRequest2Callback::OnError(
	__RPC__in_opt IXMLHTTPRequest2* pXHR,
	HRESULT hrError
)
/*++

Routine Description:

   Called when an error occurs during the HTTP request.  The error is indicated in hrError.

   This callback function must not throw any exceptions.

Arguments:

	pXHR - The interface pointer of IXMLHTTPRequest2 object.

	hrError - The errocode for the httprequest.

Return Value:

	HRESULT.

--*/
{
	UNREFERENCED_PARAMETER(pXHR);

	m_hr = hrError;
	SetEvent(m_hComplete);
	return S_OK;
}

STDMETHODIMP
CXMLHttpRequest2Callback::WaitForComplete(
	_Out_ PDWORD pdwStatus
)
/*++

Routine Description:

	Waiting for completion of the request. Once it's done, get the execution
	result of final call backs, and http status code if it's available.

	N.B. Callers needing to receive completion or status events on a STA or UI
	thread must use a mechanism that will not block the threads window message
	pump. One example is by posting a window message to the STA or UI thread
	window handle.

Arguments:

	pdwStatus - Supplies a pointer to access the status code.

Return Value:

	HRESULT.

--*/
{
	DWORD dwError = ERROR_SUCCESS;
	HRESULT hr = S_OK;

	if (pdwStatus == NULL)
	{
		hr = E_INVALIDARG;
		goto Exit;
	}

	dwError = WaitForSingleObject(m_hComplete, INFINITE);

	if (dwError == WAIT_FAILED)
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		goto Exit;
	}
	else if (dwError != WAIT_OBJECT_0)
	{
		hr = E_ABORT;
		goto Exit;
	}

	if (FAILED(m_hr))
	{
		hr = m_hr;
		goto Exit;
	}

	hr = S_OK;
	*pdwStatus = m_dwStatus;

Exit:

	return hr;
}

using namespace Microsoft::WRL;

VOID
Get(
	_In_ PCWSTR pcwszUrl,
	_In_ PCWSTR pcwszUser = NULL,
	_In_ PCWSTR pcwszPass = NULL
)
{
	HRESULT hr = S_OK;
	DWORD dwStatus = 0;
	BOOL fAbort = TRUE;
	ComPtr<IXMLHTTPRequest2> spXHR;
	ComPtr<CXMLHttpRequest2Callback> spXhrCallback;

	//
	// Create an object of the IID_IXMLHTTPRequest2 class.
	//

	hr = CoCreateInstance(CLSID_FreeThreadedXMLHTTP60,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&spXHR));
	if (FAILED(hr))
	{
		goto Exit;
	}

	//
	// Create an object of the CXMLHttpRequest2Callback class and initialize it.
	//

	hr = MakeAndInitialize<CXMLHttpRequest2Callback>(&spXhrCallback);
	if (FAILED(hr))
	{
		goto Exit;
	}

	//
	// Send a HTTP GET request.
	//

	hr = spXHR->Open(L"GET",              // Method.
		pcwszUrl,            // Url.
		spXhrCallback.Get(), // Callback.
		pcwszUser,                // Username.
		pcwszPass,                // Password.
		NULL,                // Proxy username.
		NULL);               // Proxy password.
	if (FAILED(hr))
	{
		goto Exit;
	}

	//
	// Send the request to the server.
	//

	hr = spXHR->Send(NULL, 0);
	if (FAILED(hr))
	{
		goto Exit;
	}

	//
	// Waiting for the completion of the request.
	// Callers needing to receive completion or status events on a STA or UI
	// thread must use a mechanism that will not block the threads window message
	// pump. One example is by posting a window message to the STA or UI thread
	// window handle.
	//

	hr = spXhrCallback->WaitForComplete(&dwStatus);
	if (FAILED(hr))
	{
		goto Exit;
	}

	fAbort = FALSE;

Exit:

	if (FAILED(hr))
	{
		wprintf(L"Failed, Error code = 0x%08x.\n", hr);
	}
	else
	{
		wprintf(L"Succeed, Status code = %u.\n", dwStatus);
		printf("%s", spXhrCallback->buffer);
	}

	if (fAbort)
	{
		spXHR->Abort();
	}
}

int process(
	_In_ PCWSTR pcwszUrl,
	_In_ PCWSTR pcwszUser,
	_In_ PCWSTR pcwszPass
)
{
	HRESULT hr = S_OK;
	BOOL fCoInit = FALSE;


	hr = CoInitializeEx(NULL,
		COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		goto Exit;
	}

	fCoInit = TRUE;
	Get(pcwszUrl, pcwszUser, pcwszPass);


Exit:

	if (fCoInit)
	{
		CoUninitialize();
		fCoInit = FALSE;
	}

	return 0;
}
