#pragma once

#if OpenGL

#define ENGINE_KEY_UNKNOWN            -1

/* Printable keys */
#define ENGINE_KEY_SPACE              32
#define ENGINE_KEY_APOSTROPHE         39  /* ' */
#define ENGINE_KEY_COMMA              44  /* , */
#define ENGINE_KEY_MINUS              45  /* - */
#define ENGINE_KEY_PERIOD             46  /* . */
#define ENGINE_KEY_SLASH              47  /* / */
#define ENGINE_KEY_0                  48
#define ENGINE_KEY_1                  49
#define ENGINE_KEY_2                  50
#define ENGINE_KEY_3                  51
#define ENGINE_KEY_4                  52
#define ENGINE_KEY_5                  53
#define ENGINE_KEY_6                  54
#define ENGINE_KEY_7                  55
#define ENGINE_KEY_8                  56
#define ENGINE_KEY_9                  57
#define ENGINE_KEY_SEMICOLON          59  /* ; */
#define ENGINE_KEY_EQUAL              61  /* = */
#define ENGINE_KEY_A                  65
#define ENGINE_KEY_B                  66
#define ENGINE_KEY_C                  67
#define ENGINE_KEY_D                  68
#define ENGINE_KEY_E                  69
#define ENGINE_KEY_F                  70
#define ENGINE_KEY_G                  71
#define ENGINE_KEY_H                  72
#define ENGINE_KEY_I                  73
#define ENGINE_KEY_J                  74
#define ENGINE_KEY_K                  75
#define ENGINE_KEY_L                  76
#define ENGINE_KEY_M                  77
#define ENGINE_KEY_N                  78
#define ENGINE_KEY_O                  79
#define ENGINE_KEY_P                  80
#define ENGINE_KEY_Q                  81
#define ENGINE_KEY_R                  82
#define ENGINE_KEY_S                  83
#define ENGINE_KEY_T                  84
#define ENGINE_KEY_U                  85
#define ENGINE_KEY_V                  86
#define ENGINE_KEY_W                  87
#define ENGINE_KEY_X                  88
#define ENGINE_KEY_Y                  89
#define ENGINE_KEY_Z                  90
#define ENGINE_KEY_LEFT_BRACKET       91  /* [ */
#define ENGINE_KEY_BACKSLASH          92  /* \ */
#define ENGINE_KEY_RIGHT_BRACKET      93  /* ] */
#define ENGINE_KEY_GRAVE_ACCENT       96  /* ` */
#define ENGINE_KEY_WORLD_1            161 /* non-US #1 */
#define ENGINE_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define ENGINE_KEY_ESCAPE             256
#define ENGINE_KEY_ENTER              257
#define ENGINE_KEY_TAB                258
#define ENGINE_KEY_BACKSPACE          259
#define ENGINE_KEY_INSERT             260
#define ENGINE_KEY_DELETE             261
#define ENGINE_KEY_RIGHT              262
#define ENGINE_KEY_LEFT               263
#define ENGINE_KEY_DOWN               264
#define ENGINE_KEY_UP                 265
#define ENGINE_KEY_PAGE_UP            266
#define ENGINE_KEY_PAGE_DOWN          267
#define ENGINE_KEY_HOME               268
#define ENGINE_KEY_END                269
#define ENGINE_KEY_CAPS_LOCK          280
#define ENGINE_KEY_SCROLL_LOCK        281
#define ENGINE_KEY_NUM_LOCK           282
#define ENGINE_KEY_PRINT_SCREEN       283
#define ENGINE_KEY_PAUSE              284
#define ENGINE_KEY_F1                 290
#define ENGINE_KEY_F2                 291
#define ENGINE_KEY_F3                 292
#define ENGINE_KEY_F4                 293
#define ENGINE_KEY_F5                 294
#define ENGINE_KEY_F6                 295
#define ENGINE_KEY_F7                 296
#define ENGINE_KEY_F8                 297
#define ENGINE_KEY_F9                 298
#define ENGINE_KEY_F10                299
#define ENGINE_KEY_F11                300
#define ENGINE_KEY_F12                301
#define ENGINE_KEY_F13                302
#define ENGINE_KEY_F14                303
#define ENGINE_KEY_F15                304
#define ENGINE_KEY_F16                305
#define ENGINE_KEY_F17                306
#define ENGINE_KEY_F18                307
#define ENGINE_KEY_F19                308
#define ENGINE_KEY_F20                309
#define ENGINE_KEY_F21                310
#define ENGINE_KEY_F22                311
#define ENGINE_KEY_F23                312
#define ENGINE_KEY_F24                313
#define ENGINE_KEY_F25                314
#define ENGINE_KEY_KP_0               320
#define ENGINE_KEY_KP_1               321
#define ENGINE_KEY_KP_2               322
#define ENGINE_KEY_KP_3               323
#define ENGINE_KEY_KP_4               324
#define ENGINE_KEY_KP_5               325
#define ENGINE_KEY_KP_6               326
#define ENGINE_KEY_KP_7               327
#define ENGINE_KEY_KP_8               328
#define ENGINE_KEY_KP_9               329
#define ENGINE_KEY_KP_DECIMAL         330
#define ENGINE_KEY_KP_DIVIDE          331
#define ENGINE_KEY_KP_MULTIPLY        332
#define ENGINE_KEY_KP_SUBTRACT        333
#define ENGINE_KEY_KP_ADD             334
#define ENGINE_KEY_KP_ENTER           335
#define ENGINE_KEY_KP_EQUAL           336
#define ENGINE_KEY_LEFT_SHIFT         340
#define ENGINE_KEY_LEFT_CONTROL       341
#define ENGINE_KEY_LEFT_ALT           342
#define ENGINE_KEY_LEFT_SUPER         343
#define ENGINE_KEY_RIGHT_SHIFT        344
#define ENGINE_KEY_RIGHT_CONTROL      345
#define ENGINE_KEY_RIGHT_ALT          346
#define ENGINE_KEY_RIGHT_SUPER        347
#define ENGINE_KEY_MENU               348

#define ENGINE_KEY_LAST               ENGINE_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

 /*! @brief If this bit is set one or more Shift keys were held down.
  *
  *  If this bit is set one or more Shift keys were held down.
  */
#define ENGINE_MOD_SHIFT           0x0001
  /*! @brief If this bit is set one or more Control keys were held down.
   *
   *  If this bit is set one or more Control keys were held down.
   */
#define ENGINE_MOD_CONTROL         0x0002
   /*! @brief If this bit is set one or more Alt keys were held down.
	*
	*  If this bit is set one or more Alt keys were held down.
	*/
#define ENGINE_MOD_ALT             0x0004
	/*! @brief If this bit is set one or more Super keys were held down.
	 *
	 *  If this bit is set one or more Super keys were held down.
	 */
#define ENGINE_MOD_SUPER           0x0008
	 /*! @brief If this bit is set the Caps Lock key is enabled.
	  *
	  *  If this bit is set the Caps Lock key is enabled and the @ref
	  *  ENGINE_LOCK_KEY_MODS input mode is set.
	  */
#define ENGINE_MOD_CAPS_LOCK       0x0010
	  /*! @brief If this bit is set the Num Lock key is enabled.
	   *
	   *  If this bit is set the Num Lock key is enabled and the @ref
	   *  ENGINE_LOCK_KEY_MODS input mode is set.
	   */
#define ENGINE_MOD_NUM_LOCK        0x0020

	   /*! @} */

	   /*! @defgroup buttons Mouse buttons
		*  @brief Mouse button IDs.
		*
		*  See [mouse button input](@ref input_mouse_button) for how these are used.
		*
		*  @ingroup input
		*  @{ */
#define ENGINE_MOUSE_BUTTON_1         0
#define ENGINE_MOUSE_BUTTON_2         1
#define ENGINE_MOUSE_BUTTON_3         2
#define ENGINE_MOUSE_BUTTON_4         3
#define ENGINE_MOUSE_BUTTON_5         4
#define ENGINE_MOUSE_BUTTON_6         5
#define ENGINE_MOUSE_BUTTON_7         6
#define ENGINE_MOUSE_BUTTON_8         7
#define ENGINE_MOUSE_BUTTON_LAST      ENGINE_MOUSE_BUTTON_8
#define ENGINE_MOUSE_BUTTON_LEFT      ENGINE_MOUSE_BUTTON_1
#define ENGINE_MOUSE_BUTTON_RIGHT     ENGINE_MOUSE_BUTTON_2
#define ENGINE_MOUSE_BUTTON_MIDDLE    ENGINE_MOUSE_BUTTON_3


#endif

#if DirectX11


		/*
		 * Virtual Keys, Standard Set
		 */
#define ENGINE_KEY_LBUTTON        0x01
#define ENGINE_KEY_RBUTTON        0x02
#define ENGINE_KEY_CANCEL         0x03
#define ENGINE_KEY_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */

#if(_WIN32_WINNT >= 0x0500)
#define ENGINE_KEY_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define ENGINE_KEY_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
#endif /* _WIN32_WINNT >= 0x0500 */

		 /*
		  * 0x07 : reserved
		  */


#define ENGINE_KEY_BACK           0x08
#define ENGINE_KEY_TAB            0x09

		  /*
		   * 0x0A - 0x0B : reserved
		   */

#define ENGINE_KEY_CLEAR          0x0C
#define ENGINE_KEY_RETURN         0x0D

		   /*
			* 0x0E - 0x0F : unassigned
			*/

#define ENGINE_KEY_SHIFT          0x10
#define ENGINE_KEY_CONTROL        0x11
#define ENGINE_KEY_MENU           0x12
#define ENGINE_KEY_PAUSE          0x13
#define ENGINE_KEY_CAPITAL        0x14

#define ENGINE_KEY_KANA           0x15
#define ENGINE_KEY_HANGEUL        0x15  /* old name - should be here for compatibility */
#define ENGINE_KEY_HANGUL         0x15

			/*
			 * 0x16 : unassigned
			 */

#define ENGINE_KEY_JUNJA          0x17
#define ENGINE_KEY_FINAL          0x18
#define ENGINE_KEY_HANJA          0x19
#define ENGINE_KEY_KANJI          0x19

			 /*
			  * 0x1A : unassigned
			  */

#define ENGINE_KEY_ESCAPE         0x1B

#define ENGINE_KEY_CONVERT        0x1C
#define ENGINE_KEY_NONCONVERT     0x1D
#define ENGINE_KEY_ACCEPT         0x1E
#define ENGINE_KEY_MODECHANGE     0x1F

#define ENGINE_KEY_SPACE          0x20
#define ENGINE_KEY_PRIOR          0x21
#define ENGINE_KEY_NEXT           0x22
#define ENGINE_KEY_END            0x23
#define ENGINE_KEY_HOME           0x24
#define ENGINE_KEY_LEFT           0x25
#define ENGINE_KEY_UP             0x26
#define ENGINE_KEY_RIGHT          0x27
#define ENGINE_KEY_DOWN           0x28
#define ENGINE_KEY_SELECT         0x29
#define ENGINE_KEY_PRINT          0x2A
#define ENGINE_KEY_EXECUTE        0x2B
#define ENGINE_KEY_SNAPSHOT       0x2C
#define ENGINE_KEY_INSERT         0x2D
#define ENGINE_KEY_DELETE         0x2E
#define ENGINE_KEY_HELP           0x2F

			  /*
			   * ENGINE_KEY_0 - ENGINE_KEY_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
			   * 0x3A - 0x40 : unassigned
			   * ENGINE_KEY_A - ENGINE_KEY_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
			   */

#define ENGINE_KEY_LWIN           0x5B
#define ENGINE_KEY_RWIN           0x5C
#define ENGINE_KEY_APPS           0x5D

			   /*
				* 0x5E : reserved
				*/

#define ENGINE_KEY_SLEEP          0x5F

#define ENGINE_KEY_NUMPAD0        0x60
#define ENGINE_KEY_NUMPAD1        0x61
#define ENGINE_KEY_NUMPAD2        0x62
#define ENGINE_KEY_NUMPAD3        0x63
#define ENGINE_KEY_NUMPAD4        0x64
#define ENGINE_KEY_NUMPAD5        0x65
#define ENGINE_KEY_NUMPAD6        0x66
#define ENGINE_KEY_NUMPAD7        0x67
#define ENGINE_KEY_NUMPAD8        0x68
#define ENGINE_KEY_NUMPAD9        0x69
#define ENGINE_KEY_MULTIPLY       0x6A
#define ENGINE_KEY_ADD            0x6B
#define ENGINE_KEY_SEPARATOR      0x6C
#define ENGINE_KEY_SUBTRACT       0x6D
#define ENGINE_KEY_DECIMAL        0x6E
#define ENGINE_KEY_DIVIDE         0x6F
#define ENGINE_KEY_F1             0x70
#define ENGINE_KEY_F2             0x71
#define ENGINE_KEY_F3             0x72
#define ENGINE_KEY_F4             0x73
#define ENGINE_KEY_F5             0x74
#define ENGINE_KEY_F6             0x75
#define ENGINE_KEY_F7             0x76
#define ENGINE_KEY_F8             0x77
#define ENGINE_KEY_F9             0x78
#define ENGINE_KEY_F10            0x79
#define ENGINE_KEY_F11            0x7A
#define ENGINE_KEY_F12            0x7B
#define ENGINE_KEY_F13            0x7C
#define ENGINE_KEY_F14            0x7D
#define ENGINE_KEY_F15            0x7E
#define ENGINE_KEY_F16            0x7F
#define ENGINE_KEY_F17            0x80
#define ENGINE_KEY_F18            0x81
#define ENGINE_KEY_F19            0x82
#define ENGINE_KEY_F20            0x83
#define ENGINE_KEY_F21            0x84
#define ENGINE_KEY_F22            0x85
#define ENGINE_KEY_F23            0x86
#define ENGINE_KEY_F24            0x87

#if(_WIN32_WINNT >= 0x0604)

				/*
				 * 0x88 - 0x8F : UI navigation
				 */

#define ENGINE_KEY_NAVIGATION_VIEW     0x88 // reserved
#define ENGINE_KEY_NAVIGATION_MENU     0x89 // reserved
#define ENGINE_KEY_NAVIGATION_UP       0x8A // reserved
#define ENGINE_KEY_NAVIGATION_DOWN     0x8B // reserved
#define ENGINE_KEY_NAVIGATION_LEFT     0x8C // reserved
#define ENGINE_KEY_NAVIGATION_RIGHT    0x8D // reserved
#define ENGINE_KEY_NAVIGATION_ACCEPT   0x8E // reserved
#define ENGINE_KEY_NAVIGATION_CANCEL   0x8F // reserved

#endif /* _WIN32_WINNT >= 0x0604 */

#define ENGINE_KEY_NUMLOCK        0x90
#define ENGINE_KEY_SCROLL         0x91

				 /*
				  * NEC PC-9800 kbd definitions
				  */
#define ENGINE_KEY_OEM_NEC_EQUAL  0x92   // '=' key on numpad

				  /*
				   * Fujitsu/OASYS kbd definitions
				   */
#define ENGINE_KEY_OEM_FJ_JISHO   0x92   // 'Dictionary' key
#define ENGINE_KEY_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
#define ENGINE_KEY_OEM_FJ_TOUROKU 0x94   // 'Register word' key
#define ENGINE_KEY_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
#define ENGINE_KEY_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key

				   /*
					* 0x97 - 0x9F : unassigned
					*/

					/*
					 * ENGINE_KEY_L* & ENGINE_KEY_R* - left and right Alt, Ctrl and Shift virtual keys.
					 * Used only as parameters to GetAsyncKeyState() and GetKeyState().
					 * No other API or message will distinguish left and right keys in this way.
					 */
#define ENGINE_KEY_LSHIFT         0xA0
#define ENGINE_KEY_RSHIFT         0xA1
#define ENGINE_KEY_LCONTROL       0xA2
#define ENGINE_KEY_RCONTROL       0xA3
#define ENGINE_KEY_LMENU          0xA4
#define ENGINE_KEY_RMENU          0xA5

#if(_WIN32_WINNT >= 0x0500)
#define ENGINE_KEY_BROWSER_BACK        0xA6
#define ENGINE_KEY_BROWSER_FORWARD     0xA7
#define ENGINE_KEY_BROWSER_REFRESH     0xA8
#define ENGINE_KEY_BROWSER_STOP        0xA9
#define ENGINE_KEY_BROWSER_SEARCH      0xAA
#define ENGINE_KEY_BROWSER_FAVORITES   0xAB
#define ENGINE_KEY_BROWSER_HOME        0xAC

#define ENGINE_KEY_VOLUME_MUTE         0xAD
#define ENGINE_KEY_VOLUME_DOWN         0xAE
#define ENGINE_KEY_VOLUME_UP           0xAF
#define ENGINE_KEY_MEDIA_NEXT_TRACK    0xB0
#define ENGINE_KEY_MEDIA_PREV_TRACK    0xB1
#define ENGINE_KEY_MEDIA_STOP          0xB2
#define ENGINE_KEY_MEDIA_PLAY_PAUSE    0xB3
#define ENGINE_KEY_LAUNCH_MAIL         0xB4
#define ENGINE_KEY_LAUNCH_MEDIA_SELECT 0xB5
#define ENGINE_KEY_LAUNCH_APP1         0xB6
#define ENGINE_KEY_LAUNCH_APP2         0xB7

#endif /* _WIN32_WINNT >= 0x0500 */

					 /*
					  * 0xB8 - 0xB9 : reserved
					  */

#define ENGINE_KEY_OEM_1          0xBA   // ';:' for US
#define ENGINE_KEY_OEM_PLUS       0xBB   // '+' any country
#define ENGINE_KEY_OEM_COMMA      0xBC   // ',' any country
#define ENGINE_KEY_OEM_MINUS      0xBD   // '-' any country
#define ENGINE_KEY_OEM_PERIOD     0xBE   // '.' any country
#define ENGINE_KEY_OEM_2          0xBF   // '/?' for US
#define ENGINE_KEY_OEM_3          0xC0   // '`~' for US


#define ENGINE_KEY_SPACE              32
#define ENGINE_KEY_APOSTROPHE         39  /* ' */
#define ENGINE_KEY_COMMA              44  /* , */
#define ENGINE_KEY_MINUS              45  /* - */
#define ENGINE_KEY_PERIOD             46  /* . */
#define ENGINE_KEY_SLASH              47  /* / */
#define ENGINE_KEY_0                  48
#define ENGINE_KEY_1                  49
#define ENGINE_KEY_2                  50
#define ENGINE_KEY_3                  51
#define ENGINE_KEY_4                  52
#define ENGINE_KEY_5                  53
#define ENGINE_KEY_6                  54
#define ENGINE_KEY_7                  55
#define ENGINE_KEY_8                  56
#define ENGINE_KEY_9                  57
#define ENGINE_KEY_SEMICOLON          59  /* ; */
#define ENGINE_KEY_EQUAL              61  /* = */
#define ENGINE_KEY_A                  65
#define ENGINE_KEY_B                  66
#define ENGINE_KEY_C                  67
#define ENGINE_KEY_D                  68
#define ENGINE_KEY_E                  69
#define ENGINE_KEY_F                  70
#define ENGINE_KEY_G                  71
#define ENGINE_KEY_H                  72
#define ENGINE_KEY_I                  73
#define ENGINE_KEY_J                  74
#define ENGINE_KEY_K                  75
#define ENGINE_KEY_L                  76
#define ENGINE_KEY_M                  77
#define ENGINE_KEY_N                  78
#define ENGINE_KEY_O                  79
#define ENGINE_KEY_P                  80
#define ENGINE_KEY_Q                  81
#define ENGINE_KEY_R                  82
#define ENGINE_KEY_S                  83
#define ENGINE_KEY_T                  84
#define ENGINE_KEY_U                  85
#define ENGINE_KEY_V                  86
#define ENGINE_KEY_W                  87
#define ENGINE_KEY_X                  88
#define ENGINE_KEY_Y                  89
#define ENGINE_KEY_Z                  90
#define ENGINE_KEY_LEFT_BRACKET       91  /* [ */
#define ENGINE_KEY_BACKSLASH          92  /* \ */
#define ENGINE_KEY_RIGHT_BRACKET      93  /* ] */
#define ENGINE_KEY_GRAVE_ACCENT       96  /* ` */

#endif