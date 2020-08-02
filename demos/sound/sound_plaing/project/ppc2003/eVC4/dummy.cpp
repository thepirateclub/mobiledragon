
#if defined(x86) 
	#if defined(DEBUG)
		#pragma comment(lib, "MDragon_WinCE_x86_eVC4_d.lib")
	#else
		#pragma comment(lib, "MDragon_WinCE_x86_eVC4_r.lib")
	#endif
#endif

#if defined(ARM) 
	#if defined(DEBUG)
		#pragma comment(lib, "MDragon_WinCE_ARMV4_eVC4_d.lib")
	#else
		#pragma comment(lib, "MDragon_WinCE_ARMV4_eVC4_r.lib")
	#endif
#endif
