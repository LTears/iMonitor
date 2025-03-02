//******************************************************************************
/*++
	FileName:		iMonitorSDK.h
	Description:

--*/
//******************************************************************************
#ifndef __iMonitorSDK_41E77D06_B3FA_45EC_A1C4_117CF979D841__
#define __iMonitorSDK_41E77D06_B3FA_45EC_A1C4_117CF979D841__
//******************************************************************************
// clang-format off
//******************************************************************************
#include <tchar.h>
#include <windows.h>
#include <atlbase.h>
//******************************************************************************
#include "iMonitor.h"
#include "iMonitorSDKExtension.h"
//******************************************************************************
#ifdef _M_IX86
#define MONITOR_MODULE_NAME _T("iMonitor.dll")
#else
#define MONITOR_MODULE_NAME _T("iMonitor64.dll")
#endif
//******************************************************************************
//
//	interface
//
//******************************************************************************
interface IMonitorMessage
{
	struct Binary {
		PVOID Data;
		ULONG Length;
	};

	virtual cxMSGHeader*	GetHeader			(void) = 0;
	inline ULONG			GetType				(void) { return GetHeader()->Type; }
	inline ULONG			GetStatus			(void) { return GetHeader()->Status; }
	inline ULONG			GetCurrentProcessId	(void) { return GetHeader()->CurrentProcessId; }
	inline ULONG			GetCurrentThreadId	(void) { return GetHeader()->CurrentThreadId; }

	virtual LPCWSTR			GetTypeName			(void) = 0;
	virtual ULONG			GetFieldCount		(void) = 0;
	virtual emMSGDataType	GetFieldType		(ULONG Index) = 0;
	virtual LPCWSTR			GetFieldName		(ULONG Index) = 0;
	virtual ULONG			GetFieldIndex		(LPCWSTR Name) = 0;

	virtual ULONG			GetULONG			(ULONG Index) = 0;
	virtual ULONGLONG		GetULONGLONG		(ULONG Index) = 0;
	virtual LPCWSTR			GetString			(ULONG Index) = 0;
	virtual LPCWSTR			GetFormatedString	(ULONG Index) = 0;
	virtual Binary			GetBinary			(ULONG Index) = 0;

	virtual bool			IsMatch				(ULONG Index, LPCWSTR Pattern) = 0;

	virtual bool			IsWaiting			(void) = 0;
	virtual bool			SetAction			(const cxMSGAction& Action) = 0;
	virtual bool			SetBlock			(void) = 0;
	virtual bool			SetGrantedAccess	(ULONG Access) = 0;
	virtual bool			SetIPRedirect		(ULONG IP, USHORT Port, ULONG ProcessId = ::GetCurrentProcessId()) = 0;
	virtual bool			SetFileRedirect		(LPCWSTR Path) = 0;
};
//******************************************************************************
interface IMonitorCallbackInternal
{
	virtual void			OnCallback			(cxMSGHeader* Header, cxMSGAction* Action) = 0;
};
//******************************************************************************
interface IMonitorCallback
{
	virtual void			OnCallback			(IMonitorMessage* Message) = 0;
};
//******************************************************************************
interface __declspec (uuid("51237525-2811-4BE2-A6A3-D8889E0D0CA0")) IMonitorManager : public IUnknown
{
	virtual HRESULT			Start				(IMonitorCallbackInternal* Callback) = 0;
	virtual HRESULT			Start				(IMonitorCallback* Callback) = 0;
	virtual HRESULT			Control				(PVOID Data, ULONG Length, PVOID OutData = NULL, ULONG OutLength = 0, PULONG ReturnLength = NULL) = 0;
	virtual HRESULT			Stop				(void) = 0;

	virtual	HRESULT			CreateRuleService	(LPCWSTR Path, IRuleService** Service) = 0;
	virtual HRESULT			CreateAgentService	(ULONG MaxThread, IAgentService** Service) = 0;
};
//******************************************************************************
//
//	helper
//
//******************************************************************************
// clang-format on
//******************************************************************************
class MonitorManager
{
public:
	MonitorManager(void)
		: m_MonitorModule(NULL)
	{
	}

	HRESULT Start(IMonitorCallback* Callback, LPCTSTR Path = MONITOR_MODULE_NAME)
	{
		HRESULT hr = LoadMonitor(Path);

		if (hr != S_OK && hr != S_FALSE)
			return hr;

		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->Start(Callback);
	}

	HRESULT InternalStart(IMonitorCallbackInternal* Callback, LPCTSTR Path = MONITOR_MODULE_NAME)
	{
		HRESULT hr = LoadMonitor(Path);

		if (hr != S_OK && hr != S_FALSE)
			return hr;

		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->Start(Callback);
	}

	HRESULT Stop(void)
	{
		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->Stop();
	}

public:
	template<typename T>
	HRESULT InControl(const T& config)
	{
		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->Control((PVOID)&config, sizeof(config));
	}

	CComPtr<IRuleService> CreateRuleService(LPCWSTR Path)
	{
		if (!m_Monitor)
			return NULL;

		CComPtr<IRuleService> service;
		HRESULT hr = m_Monitor->CreateRuleService(Path, &service);

		if (hr != S_OK)
			return NULL;

		return service;
	}

	CComPtr<IAgentService> CreateAgentService(ULONG MaxThread = 1)
	{
		if (!m_Monitor)
			return NULL;

		CComPtr<IAgentService> service;
		HRESULT hr = m_Monitor->CreateAgentService(MaxThread, &service);

		if (hr != S_OK)
			return NULL;

		return service;
	}

protected:
	HRESULT LoadMonitor(LPCTSTR Path)
	{
		if (m_Monitor)
			return S_FALSE;

		if (!Path)
			Path = MONITOR_MODULE_NAME;

		if (!m_MonitorModule) {
			m_MonitorModule = LoadLibraryEx(Path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

			if (!m_MonitorModule)
				return HRESULT_FROM_WIN32(GetLastError());
		}

		typedef HRESULT(STDAPICALLTYPE * PFN_DllGetClassObject)(REFCLSID, REFIID, PVOID*);

		PFN_DllGetClassObject pfn = (PFN_DllGetClassObject)GetProcAddress(m_MonitorModule, "DllGetClassObject");

		if (!pfn)
			return E_FAIL;

		return pfn(CLSID_NULL, __uuidof(IMonitorManager), (PVOID*)&m_Monitor);
	}

protected:
	HMODULE m_MonitorModule;
	CComPtr<IMonitorManager> m_Monitor;
};
//******************************************************************************
#endif
