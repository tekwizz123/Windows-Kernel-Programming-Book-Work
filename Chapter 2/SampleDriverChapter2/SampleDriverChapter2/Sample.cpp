#include <ntddk.h>

// Driver unload function used when cleaning up the driver and removing stuff from memory.
void UnloadFunction(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Called the UnloadFunction to unload the driver!\r\n"));
}


// Main function for a driver. Called at IRQL_PASSIVE_LEVEL aka IRQL 0.
extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath);
	DriverObject->DriverUnload = UnloadFunction;
	KdPrint(("Initialized driver via DriverEntry!\r\n"));
	
	//Get the version info for the current OS.
	RTL_OSVERSIONINFOEXW osVersionInfo;
	osVersionInfo.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW);
	RtlGetVersion((PRTL_OSVERSIONINFOW)&osVersionInfo);
	KdPrint(("Version: %d.%d, Build: %d, Service Pack: %d.%d\r\n", osVersionInfo.dwMajorVersion, osVersionInfo.dwMinorVersion, osVersionInfo.dwBuildNumber, osVersionInfo.wServicePackMajor, osVersionInfo.wServicePackMinor));
	switch (osVersionInfo.wProductType) {
	case VER_NT_WORKSTATION:
		KdPrint(("Target is a Workstation machine.\r\n"));
		break;
	case VER_NT_DOMAIN_CONTROLLER:
		KdPrint(("Target is a Domain controller.\r\n"));
		break;
	case VER_NT_SERVER:
		KdPrint(("Target is a Server.\r\n"));
		break;
	}
	if (osVersionInfo.wSuiteMask != 0) {
		KdPrint(("wSuiteMask: 0x%08x\r\n", osVersionInfo.wSuiteMask));

		// Important note here which caused a lot of trouble: need to use & (bitwise AND) and not && (logical AND). 
		// Former expects a int/short/ulong etc and returns an integral value, later expects a boolean and returns a boolean.
		if (osVersionInfo.wSuiteMask & VER_SUITE_SMALLBUSINESS) {
			KdPrint(("VER_SUITE_SMALLBUSINESS flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE) {
			KdPrint(("VER_SUITE_ENTERPRISE flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_BACKOFFICE) {
			KdPrint(("VER_SUITE_BACKOFFICE flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_COMMUNICATIONS) {
			KdPrint(("VER_SUITE_COMMUNICATIONS flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_TERMINAL) {
			KdPrint(("VER_SUITE_TERMINAL flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_SMALLBUSINESS_RESTRICTED) {
			KdPrint(("VER_SUITE_SMALLBUSINESS_RESTRICTED flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_EMBEDDEDNT) {
			KdPrint(("VER_SUITE_EMBEDDEDNT flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_DATACENTER) {
			KdPrint(("VER_SUITE_DATACENTER flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_SINGLEUSERTS) {
			KdPrint(("VER_SUITE_SINGLEUSERTS flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_PERSONAL) {
			KdPrint(("VER_SUITE_PERSONAL flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_BLADE) {
			KdPrint(("VER_SUITE_BLADE flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_EMBEDDED_RESTRICTED) {
			KdPrint(("VER_SUITE_EMBEDDED_RESTRICTED flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_SECURITY_APPLIANCE) {
			KdPrint(("VER_SUITE_SECURITY_APPLIANCE flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_STORAGE_SERVER) {
			KdPrint(("VER_SUITE_STORAGE_SERVER flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_COMPUTE_SERVER) {
			KdPrint(("VER_SUITE_COMPUTE_SERVER flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_WH_SERVER) {
			KdPrint(("VER_SUITE_WH_SERVER flag was set.\r\n"));
		}

		if (osVersionInfo.wSuiteMask & VER_SUITE_MULTIUSERTS) {
			KdPrint(("VER_SUITE_MULTIUSERTS flag was set.\r\n"));
		}
	}
	return STATUS_SUCCESS;
}