/****************************************************************
*		 This client was writen by Diuuude & Snoopy81.			*
*					Based on Cleroth work.						*
*																*
*			V3.51 compatibility by Cleroth						*
*			V3.51 dialogs by Diuuude							*
*			Effects, mobs, Apocalypse, Heldenian				*
*			& finalizing by Snoopy81							*
*****************************************************************/

/****************************************************************
*	Find here all compilation options							*
*	I removed useless ones and tryed to add some explanations	*
*	( Snoopy81 04/2005 )										*
*****************************************************************/

/*** Put here global data for your server ***/
#define NAME_WORLDNAME1			"snoopy81" // Name for default (1st) server
#define MSG_WORLDNAME1			"Equilibrium Project" // Long name for 1st server...
#define MSG_HOMEPAGE			"http://www.equiprojet.com/"
#define DEF_UPPERVERSION		4
#define DEF_LOWERVERSION		00
#define DEF_SERVER_IP			"192.168.1.101"
#define DEF_SERVER_PORT			2848

#define DEF_MAX_STATS			250
#define DEF_MAX_DELETE_LEVEL	50 // Max level to delete a character from client

#define DEF_SNOW_POSITION_Y		430 // Used to change snow position il status bar changed.(def 426)

/*** Some more compilation options ***/




//#define DEF_USING_WIN_IME		// Used for unicode characters (unchecked)
//#define DEF_MAKE_ACCOUNT		// Enable acc creation. Missing sprites, fixed!
//#define DEF_SELECTSERVER		// Show/Hides server selection screen.

// #define DEF_COMMA_GOLD		// Allows to show comma nbe as original HB (ie: 1,200,000)
// #define DEF_4XXP_PER_LVL		// limits xp niv 140, then 4 x XP per lvl (affects XP shown as % on status)


// #define  _DEBUG				// Multi-Client, Instant-logout, Version check, Badwords,
								// Mics debug msgs, CtrlQ for admins, Show status, Cursor position
//#define DEF_WINDOWED_MODE		// Shows HB in a windowed mode (for debug purpose only, sprite will bug....)


#define DEF_ANTI_HACK			// Snoopy: Mes antiHacks personels!
// changes CCM routine to send "real checked time" instead of "sending time". 
// CCM is reduced to 6150, and cKeys reduced to F5

#define DEF_MULTI_SHORTCUT  	// Snoopy: Uses 6 shortcuts. (F1, F2, F3, F10, F11, F12) 
								// Ctrl+H used for help, Ctrl+W used for tranparency, Ctrl+X for systemdiag.

#define DEF_EQUILIBRIUM_PROJECT	// A enlever avant release, définit un certain nombre de particularités EP


/*** Special conditions   ***/
#ifndef _DEBUG
	#undef DEF_WINDOWED_MODE
#endif

#ifdef DEF_ANTI_HACK
#define DEF_CCM_DELAY			6150
#define DEF_HIDDEN_UPPERVERSION	4
#define DEF_HIDDEN_LOWERVERSION	96
//that can be whatever number you wish, 1 byte-sized numbers will work fine
#define DEF_VERSIONPLUSMODIFIER     1+(DEF_HIDDEN_LOWERVERSION % 7) 

#else
#define DEF_VERSIONPLUSMODIFIER     0 
#endif