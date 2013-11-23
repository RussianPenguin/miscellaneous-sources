// XTDateTimeCtrl.h interface for the CXTDateTimeCtrl class.
//
// This file is a part of the Xtreme MFC Toolkit.
// ©2000 Codejock.com Software, All Rights Reserved.
//
// CODEJOCK.COM SOFTWARE GRANTS TO YOU (ONE SOFTWARE PROGRAMMER) THE
// LIMITED RIGHT TO USE THIS SOFTWARE ON A SINGLE COMPUTER FOR EVALUATION
// PURPOSES ONLY. THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE 
// THE PROPERTY OF CODEJOCK.COM SOFTWARE AND ARE NOT TO BE RE-DISTRIBUTED
// BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN CONSENT OF 
// CODEJOCK.COM SOFTWARE.
//
// support@codejock.com
// http://www.codejock.com

//
//////////////////////////////////////////////////////////////////////

#if !defined(__XTDATETIMECTRL_H__)
#define __XTDATETIMECTRL_H__

// class forwards
class CXTMonthCalCtrl;

/////////////////////////////////////////////////////////////////////////////
// A CXTDateTimeCtrl object encapsulates the functionality of a date and time picker 
// control. The date and time picker control (DTP control) provides a simple interface 
// to exchange date and time information with a user. This interface contains fields, 
// each of which displays a part of the date and time information stored in the control. 
// The user can change the information stored in the control by changing the content of 
// the string in a given field. The user can move from field to field using the mouse or 
// the keyboard.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTDateTimeCtrl : public CWnd
{
	DECLARE_DYNAMIC(CXTDateTimeCtrl)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTDateTimeCtrl();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual ~CXTDateTimeCtrl();
	
	// -> Parameters:		dwStyle		-	Specifies the combination of date time control 
	//										styles. See Date and Time Picker Control Styles 
	//										in the Platform SDK for more information about 
	//										date and time picker styles.
	//						rect		-	A reference to a RECT structure, which is the 
	//										position and size of the date and time picker 
	//										control.
	//						pParentWnd	-	A pointer to a CWnd object that is the parent 
	//										window of the date and time picker control. It 
	//										must not be NULL.
	//						nID			-	Specifies the date and time picker control's 
	//										control ID.
	// -> Return Value:		
	// -> Remarks:			Creates the date and time picker control and attaches 
	//						it to the CDateTimeCtrl object. Returns nonzero if creation 
	//						was successful; otherwise 0.
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	
	// -> Parameters:		iColor -	An int value specifying which color area of the month 
	//						calendar to retrieve. For a list of values, see the iColor parameter 
	//						for SetMonthCalColor.
	// -> Return Value:		
	// -> Remarks:			Retrieves the color for a given portion of the month calendar 
	//						within the date and time picker control. Returns a COLORREF value 
	//						that represents the color setting for the specified portion of the 
	//						month calendar control if successful. The function returns -1 if 
	//						unsuccessful. 
	COLORREF GetMonthCalColor(int iColor) const;

	// -> Parameters:		iColor -	int value specifying which area of the month calendar 
	//									control to set. This value can be one of the following.
	//
	//							MCSC_BACKGROUND		-	Set the background color displayed 
	//													between months.  
	//							MCSC_MONTHBK		-	Set the background color displayed 
	//													within a month.  
	//							MCSC_TEXT			-	Set the color used to display text 
	//													within a month.  
	//							MCSC_TITLEBK		-	Set the background color displayed 
	//													in the calendar's title.  
	//							MCSC_TITLETEXT		-	Set the color used to display text 
	//													within the calendar's title.  
	//							MCSC_TRAILINGTEXT	-	Set the color used to display header 
	//													and trailing-day text. Header and trailing 
	//													days are the days from the previous and 
	//													following months that appear on the 
	//													current calendar.
	//
	//						ref	   -	A COLORREF value representing the color that will be set 
	//									for the specified area of the month calendar.
	// -> Return Value:		
	// -> Remarks:			Sets the color for a given portion of the month calendar within a 
	//						date and time picker control. Returns a COLORREF value that represents 
	//						the previous color setting for the specified portion of the month 
	//						calendar control if successful. Otherwise, the message returns -1. 
	COLORREF SetMonthCalColor(int iColor, COLORREF ref);

	// -> Parameters:		pstrFormat -	A pointer to a zero-terminated format string that 
	//										defines the desired display. Setting this parameter to 
	//										NULL will reset the control to the default format 
	//										string for the current style.
	// -> Return Value:		
	// -> Remarks:			Sets the display of a date and time picker control based on a given 
	//						format string. Returns nonzero if successful; otherwise 0.
	BOOL SetFormat(LPCTSTR pstrFormat);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves the date and time picker's child month calendar control. 
	//						Returns a pointer to a CMonthCalCtrl object, or NULL if unsuccessful 
	//						or if the window is not visible.
	CXTMonthCalCtrl* GetMonthCalCtrl() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves the font currently used by the date and time picker 
	//						control's child month calendar control. Returns a pointer to a 
	//						CFont object, or NULL if unsuccessful.		
	CFont* GetMonthCalFont() const;

	// -> Parameters:		hFont	-	Handle to the font that will be set. 
	//						bRedraw	-	Specifies whether the control should be redrawn 
	//									immediately upon setting the font. Setting this 
	//									parameter to TRUE causes the control to redraw itself. 
	// -> Return Value:		
	// -> Remarks:			Sets the font to be used by the date and time picker control's 
	//						child month calendar control.
	void SetMonthCalFont(HFONT hFont, BOOL bRedraw = TRUE);

	// -> Parameters:		pMinRange	-	A pointer to a COleDateTime object containing the 
	//										earliest time allowed in the CDateTimeCtrl object.
	//						pMaxRange	-	A pointer to a COleDateTime object containing the 
	//										latest time allowed in the CDateTimeCtrl object. 
	// -> Return Value:		
	// -> Remarks:			Sets the minimum and maximum allowable system times for a date 
	//						and time picker control. Returns nonzero if successful; otherwise 0. 
	BOOL SetRange(const COleDateTime* pMinRange, const COleDateTime* pMaxRange);

	// -> Parameters:		pMinRange	-	A pointer to a CTime object containing the earliest 
	//										time allowed in the CDateTimeCtrl object.
	//						pMaxRange	-	A pointer to a CTime object containing the latest 
	//										time allowed in the CDateTimeCtrl object. 
	// -> Return Value:		
	// -> Remarks:			Sets the minimum and maximum allowable system times for a date and 
	//						time picker control. Returns nonzero if successful; otherwise 0. 
	BOOL SetRange(const CTime* pMinRange, const CTime* pMaxRange);

	// -> Parameters:		pMinRange	-	A pointer to a COleDateTime object containing the 
	//										earliest time allowed in the CDateTimeCtrl object.
	//						pMaxRange	-	A pointer to a COleDateTime object containing the 
	//										latest time allowed in the CDateTimeCtrl object. 
	// -> Return Value:		
	// -> Remarks:			Retrieves the current minimum and maximum allowable system times 
	//						for a date and time picker control. Returns a DWORD value containing 
	//						flags that indicate which ranges are set.
	DWORD GetRange(COleDateTime* pMinRange, COleDateTime* pMaxRange) const;

	// -> Parameters:		pMinRange	-	A pointer to a CTime object containing the earliest 
	//										time allowed in the CDateTimeCtrl object.
	//						pMaxRange	-	A pointer to a CTime object containing the latest 
	//										time allowed in the CDateTimeCtrl object.
	// -> Return Value:		
	// -> Remarks:			Retrieves the current minimum and maximum allowable system times 
	//						for a date and time picker control. Returns a DWORD value containing 
	//						flags that indicate which ranges are set.
	DWORD GetRange(CTime* pMinRange, CTime* pMaxRange) const;
	
	// -> Parameters:		pTimeNew	-	A pointer to a CTime object containing the time to 
	//										which the control will be set.
	// -> Return Value:		
	// -> Remarks:			Sets the time in a date and time picker control. Returns nonzero 
	//						if successful; otherwise 0. 
	BOOL SetTime(const CTime* pTimeNew);

	// -> Parameters:		timeNew	-	A reference to a COleDateTime object containing the to 
	//									which the control will be set.
	// -> Return Value:		
	// -> Remarks:			Sets the time in a date and time picker control. Returns nonzero 
	//						if successful; otherwise 0. 
	BOOL SetTime(const COleDateTime& timeNew);

	// -> Parameters:		pTimeNew	-	A pointer to a SYSTEMTIME structure containing 
	//										the time to which the control will be set.
	// -> Return Value:		
	// -> Remarks:			Sets the time in a date and time picker control. Returns nonzero 
	//						if successful; otherwise 0. 
	BOOL SetTime(LPSYSTEMTIME pTimeNew = NULL);

	// -> Parameters:		timeDest	-	A reference to a CTime object that will receive 
	//										the system time information
	// -> Return Value:		
	// -> Remarks:			Retrieves the currently selected time from a date and time picker 
	//						control and places it in a specified SYSTEMTIME structure. Returns 
	//						a DWORD value equal to the dwFlag member set in theNMDATETIMECHANGE 
	//						structure
	DWORD GetTime(CTime& timeDest) const;

	// -> Parameters:		timeDest	-	A reference to a COleDateTime object that will 
	//										receive the system time information
	// -> Return Value:		
	// -> Remarks:			Retrieves the currently selected time from a date and time picker 
	//						control and places it in a specified SYSTEMTIME structure. Returns 
	//						nonzero if the time is successfully written to the COleDateTime 
	//						object; otherwise 0.
	BOOL GetTime(COleDateTime& timeDest) const;

	// -> Parameters:		pTimeDest	-	A pointer to theSYSTEMTIME structure to receive 
	//										the system time information. Must not be NULL.
	// -> Return Value:		
	// -> Remarks:			Retrieves the currently selected time from a date and time picker 
	//						control and places it in a specified SYSTEMTIME structure. Returns 
	//						a DWORD value equal to the dwFlag member set in theNMDATETIMECHANGE 
	//						structure
	DWORD GetTime(LPSYSTEMTIME pTimeDest) const;
};

/////////////////////////////////////////////////////////////////////////////
// A CXTMonthCalCtrl object encapsulates the functionality of a month calendar control. 
// The month calendar control provides the user with a simple calendar interface, from 
// which the user can select a date.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTMonthCalCtrl : public CWnd
{
  DECLARE_DYNAMIC(CXTMonthCalCtrl)
	  
public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTMonthCalCtrl();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual ~CXTMonthCalCtrl();

	// -> Parameters:		dwStyle		-	Specifies the combination of Windows styles
	//										applied to the month calendar control. SeeMonth Calendar
	//										Control Styles in the Platform SDK for more information about
	//										the styles.
	//						rect		-	A reference to aRECT structure. Contains the position
	//										and size of the month calendar control
	//						pParentWnd	-	A pointer to a CWnd object that is the parent window
	//										of the month calendar control. It must not be NULL.
	//						nID			-	Specifies the month calendar control’s control ID.
	// -> Return Value:		
	// -> Remarks:			Creates a month calendar control and attaches it to
	//						the CMonthCalCtrl object. Returns nonzero if initialization was
	//						successful; otherwise 0.
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// -> Parameters:		dwStyle		-	Specifies the combination of Windows styles
	//										applied to the month calendar control. See Month Calendar
	//										Control Styles in the Platform SDK for more information about
	//										the styles.
	//						pt			-	A reference to aPOINT structure that identifies the location
	//										of the month calendar control
	//						pParentWnd	-	A pointer to a CWnd object that is the parent window
	//										of the month calendar control. It must not be NULL.
	//						nID			-	Specifies the month calendar control’s control ID.
	// -> Return Value:		
	// -> Remarks:			Creates a month calendar control and attaches it to
	//						the CMonthCalCtrl object. Returns nonzero if initialization was
	//						successful; otherwise 0.
	BOOL Create(DWORD dwStyle, const POINT& pt, CWnd* pParentWnd, UINT nID);
	
	// -> Parameters:		pRect	-	A pointer to a RECT structure that will receive
	//									bounding rectangle information. This parameter must be a valid
	//									address and cannot be NULL. 
	// -> Return Value:		
	// -> Remarks:			Retrieves the minimum size required to show a full month
	//						in a month calendar control. Returns nonzero and lpRect receives
	//						the applicable bounding information.If unsuccessful, the member
	//						function returns 0.
	BOOL GetMinReqRect(RECT* pRect) const;

	// -> Parameters:		iDelta	-	The number of months to be set as the control's
	//									scroll rate. If this value is zero, the month delta is reset
	//									to the default, which is the number of months displayed in
	//									the control. 
	// -> Return Value:		
	// -> Remarks:			Sets the scroll rate for a month calendar control. Returns
	//						the previous scroll rate. If the scroll rate has not been previously
	//						set, the return value is 0. 
	int SetMonthDelta(int iDelta);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves the scroll rate for a month calendar control.
	//						Returns The scroll rate for the month calendar control. The scroll
	//						rate is the number of months that the control moves its display
	//						when the user clicks a scroll button once. 
	int GetMonthDelta() const;

	// -> Parameters:		iDay	-	An integer value representing which day is
	//									to be set as the first day of the week. This value must be
	//									one of the day numbers. See GetFirstDayOfWeek for a description
	//									of the day numbers.
	//						lpnOld	-	A pointer to an integer indicating the first day of
	//									the week previously set.
	// -> Return Value:		
	// -> Remarks:			Sets the day of week to be displayed in the leftmost
	//						column of the calendar. Returns nonzero if the previous first
	//						day of the week is set to a value other than that of LOCALE_IFIRSTDAYOFWEEK,
	//						which is the day indicated in the control panel setting. Otherwise,
	//						this function returns 0.
	BOOL SetFirstDayOfWeek(int iDay, int* lpnOld = NULL);

	// -> Parameters:		pbLocal	-	A pointer to a BOOL value. If the value
	//									is non-zero, the control's setting does not match the setting
	//									in the control panel. 
	// -> Return Value:		Returns an integer value that represents the first
	//						day of the week. The days of the week are represented as integers,
	//						as follows.
	// 
	//						Value	Day of the Week 
	//						0		Monday  
	//						1		Tuesday  
	//						2		Wednesday  
	//						3		Thursday  
	//						4		Friday  
	//						5		Saturday  
	//						6		Sunday  
	//
	// -> Remarks:			Gets the first day of the week to be displayed in the
	//						left most column of the calendar.
	int GetFirstDayOfWeek(BOOL* pbLocal = NULL) const;

	// -> Parameters:		nRegion	-	The region of the month calendar control
	//									from which the color is retrieved. For a list of values, see
	//									the nRegion parameter of  SetColor.
	// -> Return Value:		
	// -> Remarks:			Gets the color of a specified area of a month calendar
	//						control. Returns a COLORREF value specifying the color associated
	//						with the portion of the month calendar control, if successful.
	//						Otherwise, this member function returns -1
	COLORREF GetColor(int nRegion) const;

	// -> Parameters:		nRegion	-	An integer value specifying which month calendar color 
	//									to set. This value can be one of the following.
	//
	//							MCSC_BACKGROUND		-	The background color displayed between months.  
	//							MCSC_MONTHBK		-	The background color displayed within the month.
	//							MCSC_TEXT			-	The color used to display text within a month.  
	//							MCSC_TITLEBK		-	The background color displayed in the calendar's title.  
	//							MCSC_TITLETEXT		-	The color used to display text within the calendar's title.  
	//							MCSC_TRAILINGTEXT	-	The color used to display header and trailing-day
	//													text. Header and trailing days are the days from the previous
	//													and following months that appear on the current calendar.  
	//
	//						ref		-	A COLORREF value for the new color setting for the specified
	//									portion of the month calendar control
	// -> Return Value:		
	// -> Remarks:			Sets the color of a specified area of a month calendar
	//						control. Returns a COLORREF value that represents the previous
	//						color setting for the specified portion of the month calendar
	//						control, if successful. Otherwise this message returns -1. 
	COLORREF SetColor(int nRegion, COLORREF ref);

	// -> Parameters:		bRepaint	-	Specifies whether the control is to be
	//										repainted. By default, TRUE. If FALSE, no repainting 
	//										occurs.
	// -> Return Value:		
	// -> Remarks:			Repaints the month calendar control to its minimum,
	//						one-month size. Returns nonzero if the month calendar control
	//						is sized to its minimum; otherwise 0. 
	BOOL SizeMinReq(BOOL bRepaint = TRUE);

	// -> Parameters:		refDateTime	-	A reference to a COleDateTime object
	//										that contains the current date.
	// -> Return Value:		
	// -> Remarks:			Sets the calendar control for the current day.
	void SetToday(const COleDateTime& refDateTime);

	// -> Parameters:		pDateTime	-	A pointer to a CTime object containing
	//										the current date information.
	// -> Return Value:		
	// -> Remarks:			Sets the calendar control for the current day.
	void SetToday(const CTime* pDateTime);

	// -> Parameters:		pDateTime	-	A pointer to a SYSTEMTIME structure that
	//										contains the current date information. 
	// -> Return Value:		
	// -> Remarks:			Sets the calendar control for the current day.
	void SetToday(const LPSYSTEMTIME pDateTime);

	// -> Parameters:		refTime	-	A reference to a CTime object indicating the current day.
	// -> Return Value:		
	// -> Remarks:			Retrieves the date information for the date specified
	//						as "today" for a month calendar control. Returns nonzero if successful;
	//						otherwise 0.
	BOOL GetToday(CTime& refTime) const;

	// -> Parameters:		refDateTime	-	A reference to a COleDateTime object
	//										indicating the current day.
	// -> Return Value:		
	// -> Remarks:			Retrieves the date information for the date specified
	//						as "today" for a month calendar control. Returns nonzero if successful;
	//						otherwise 0.
	BOOL GetToday(COleDateTime& refDateTime) const;

	// -> Parameters:		pDateTime	-	A pointer to a SYSTEMTIME structure that
	//										will receive the date information.This parameter must be
	//										a valid address and cannot be NULL.
	// -> Return Value:		
	// -> Remarks:			Retrieves the date information for the date specified
	//						as "today" for a month calendar control. Returns nonzero if successful;
	//						otherwise 0.
	BOOL GetToday(LPSYSTEMTIME pDateTime) const;

	// -> Parameters:		pDateTime	-	A pointer to a SYSTEMTIME structure that
	//										will receive the currently-selected date information. This
	//										parameter must be a valid address and cannot be NULL.
	// -> Return Value:		
	// -> Remarks:			Retrieves the system time as indicated by the currently-selected
	//						date. Returns nonzero if successful; otherwize 0.
	BOOL GetCurSel(LPSYSTEMTIME pDateTime) const;

	// -> Parameters:		refDateTime	-	A reference to a CTime object. Receives the current time.
	// -> Return Value:		
	// -> Remarks:			Retrieves the system time as indicated by the currently-selected
	//						date. Returns nonzero if successful; otherwize 0.
	BOOL GetCurSel(CTime& refDateTime) const;

	// -> Parameters:		refDateTime	-	A reference to a COleDateTime object.
	//										Receives the current time.
	// -> Return Value:		
	// -> Remarks:			Retrieves the system time as indicated by the currently-selected
	//						date. Returns nonzero if successful; otherwize 0.
	BOOL GetCurSel(COleDateTime& refDateTime) const;

	// -> Parameters:		pDateTime	-	Pointer to a SYSTEMTIME structure that
	//										contains the date to be set as the current selection. 
	// -> Return Value:		
	// -> Remarks:			Sets the currently-selected date for a month calendar
	//						control. Returns nonzero if successful; otherwise 0. 
	BOOL SetCurSel(const LPSYSTEMTIME pDateTime);

	// -> Parameters:		refDateTime	-	A reference to a CTime object indicating
	//										the currently-selected month calendar control. 
	// -> Return Value:		
	// -> Remarks:			Sets the currently-selected date for a month calendar
	//						control. Returns nonzero if successful; otherwise 0. 
	BOOL SetCurSel(const CTime& refDateTime);

	// -> Parameters:		refDateTime	-	A reference to a COleDateTime indicating
	//										the currently-selected month calendar control. 
	// -> Return Value:		
	// -> Remarks:			Sets the currently-selected date for a month calendar
	//						control. Returns nonzero if successful; otherwise 0. 
	BOOL SetCurSel(const COleDateTime& refDateTime);

	// -> Parameters:		nMonths	-	Value indicating how many elements are in
	//									the array that pStates points to.
	//						pStates	-	A pointer to a MONTHDAYSTATE array of values that define
	//									how the month calendar control will draw each day in its 
	//									display. The MONTHDAYSTATE data type is a bit field, where 
	//									each bit (1 through 31) represents the state of a day in a 
	//									month. If a bit is on, the corresponding day will be displayed
	//									in bold; otherwise it will be displayed with no emphasis. 
	// -> Return Value:		
	// -> Remarks:			Sets the display for days in a month calendar control.
	//						Returns nonzero if successful; otherwise 0. 		
	BOOL SetDayState(int nMonths, LPMONTHDAYSTATE pStates);

	// -> Parameters:		nMax	-	
	// -> Return Value:		
	// -> Remarks:			Sets the maximum number of days that can be selected
	//						in a month calendar control. Returns nonzero if successful; otherwise
	//						0. 
	BOOL SetMaxSelCount(int nMax);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves the current maximum number of days that can
	//						be selected in a month calendar control. Returns an integer value
	//						that represents the total number of days that can be selected
	//						for the control.
	int GetMaxSelCount() const;

	// -> Parameters:		pMinRange	-	A pointer to a COleDateTime object containing
	//										the date at the lowest end of the range. 
	//						pMaxRange	-	A pointer to a COleDateTime object containing the
	//										date at the highest end of the range.
	// -> Return Value:		
	// -> Remarks:			Sets the minimum and maximum allowable dates for a month
	//						calendar control. Returns nonzero if successful; otherwise 0. 
	BOOL SetRange(const COleDateTime* pMinRange, const COleDateTime* pMaxRange);

	// -> Parameters:		pMinRange	-	A pointer to a CTime object containing
	//										the date at the lowest end of the range. 
	//						pMaxRange	-	A pointer to a CTime object containing the date at
	//										the highest end of the range.
	// -> Return Value:		
	// -> Remarks:			Sets the minimum and maximum allowable dates for a month
	//						calendar control. Returns nonzero if successful; otherwise 0. 
	BOOL SetRange(const CTime* pMinRange, const CTime* pMaxRange);

	// -> Parameters:		pMinRange	-	A pointer to a SYSTEMTIME structure containing
	//										the date at the lowest end of the range. 
	//						pMaxRange	-	A pointer to a SYSTEMTIME structure containing the
	//										date at the highest end of the range.
	// -> Return Value:		
	// -> Remarks:			Sets the minimum and maximum allowable dates for a month
	//						calendar control. Returns nonzero if successful; otherwise 0. 
	BOOL SetRange(const LPSYSTEMTIME pMinRange, const LPSYSTEMTIME pMaxRange);

	// -> Parameters:		pMinRange	-	A pointer to a COleDateTime object containing
	//										the date at the lowest end of the range. 
	//						pMaxRange	-	A pointer to a COleDateTime object containing the
	//										date at the highest end of the range.
	// -> Return Value:		Returns A DWORD that can be zero
	//						(no limits are set) or a combination of the following values
	//						that specify limit information. 			
	// 
	//							GDTR_MAX	-	A maximum limit is set for the control; pMaxRange
	//											is valid and contains the applicable date information.  
	//							GDTR_MIN	-	A minimum limit is set for the control; pMinRange
	//											is valid and contains the applicable date information.  
	//
	// -> Remarks:			Retrieves the current minimum and maximum dates set
	//						in a month calendar control.
	DWORD GetRange(COleDateTime* pMinRange, COleDateTime* pMaxRange) const;

	// -> Parameters:		pMinRange	-	A pointer to a CTime object containing
	//										the date at the lowest end of the range. 
	//						pMaxRange	-	A pointer to a CTime object containing the date at
	//										the highest end of the range.
	//
	// -> Return Value:		Returns A DWORD that can be zero
	//						(no limits are set) or a combination of the following values
	//						that specify limit information.
	// 
	//							GDTR_MAX	-	A maximum limit is set for the control; pMaxRange
	//											is valid and contains the applicable date information.  
	//							GDTR_MIN	-	A minimum limit is set for the control; pMinRange
	//											is valid and contains the applicable date information.  
	//
	// -> Remarks:			Retrieves the current minimum and maximum dates set
	//						in a month calendar control. 
	DWORD GetRange(CTime* pMinRange, CTime* pMaxRange) const;

	// -> Parameters:		pMinRange	-	A pointer to a SYSTEMTIME structure containing
	//										the date at the lowest end of the range. 
	//						pMaxRange	-	A pointer to a COleDateTime object, a CTime object,
	//										orSYSTEMTIME structure containing the date at the highest
	//										end of the range.
	// -> Return Value:		Returns A DWORD that can be zero
	//						(no limits are set) or a combination of the following values
	//						that specify limit information. 
	//
	//							GDTR_MAX	-	A maximum limit is set for the control; pMaxRange
	//											is valid and contains the applicable date information.  
	//							GDTR_MIN	-	A minimum limit is set for the control; pMinRange
	//											is valid and contains the applicable date information.  
	//
	// -> Remarks:			Retrieves the current minimum and maximum dates set
	//						in a month calendar control.
	DWORD GetRange(LPSYSTEMTIME pMinRange, LPSYSTEMTIME pMaxRange) const;

	// -> Parameters:		refMinRange	-	A reference to a COleDateTime object
	//										containing the minimum date allowed.
	//						refMaxRange	-	A reference to a COleDateTime object containing
	//										the maximum date allowed.
	//						dwFlags		-	Value specifying the scope of the range limits to
	//										be retrieved. This value must be one of the following.
	// 
	//							GMR_DAYSTATE	Include preceding and trailing months of visible
	//											range that are only partially displayed.  
	//							GMR_VISIBLE		Include only those months that are entirely displayed.  
	// -> Return Value:		
	// -> Remarks:			Retrieves date information representing the high and
	//						low limits of a month calendar control's display. Returns An
	//						integer that represents the range, in months, spanned by the
	//						two limits indicated by refMinRange and refMaxRange.
	int GetMonthRange(COleDateTime& refMinRange, COleDateTime& refMaxRange, DWORD dwFlags) const;

	// -> Parameters:		refMinRange	-	A reference to a CTime object containing
	//										the minimum date allowed.
	//						refMaxRange	-	A reference to a CTime object containing the maximum
	//										date allowed.
	//						dwFlags		-	Value specifying the scope of the range limits to
	//										be retrieved. This value must be one of the following.
	// 
	//							GMR_DAYSTATE	Include preceding and trailing months of visible
	//											range that are only partially displayed.  
	//							GMR_VISIBLE		Include only those months that are entirely displayed.
	//
	// -> Return Value:		
	// -> Remarks:			Retrieves date information representing the high and
	//						low limits of a month calendar control's display. Returns An
	//						integer that represents the range, in months, spanned by the
	//						two limits indicated by refMinRange and refMaxRange.
	int GetMonthRange(CTime& refMinRange, CTime& refMaxRange, DWORD dwFlags) const;

	// -> Parameters:		refMinRange	-	A pointer to a SYSTEMTIME structure
	//										containing the date at the lowest end of the range.
	//						refMaxRange	-	A pointer to a SYSTEMTIME structure containing
	//										the date at the highest end of the range.
	//						dwFlags		-	Value specifying the scope of the range limits to
	//										be retrieved. This value must be one of the following.
	// 
	//							GMR_DAYSTATE	-	Include preceding and trailing months of visible
	//												range that are only partially displayed.  
	//							GMR_VISIBLE		-	Include only those months that are entirely displayed.
	//										
	// -> Return Value:		
	// -> Remarks:			Retrieves date information representing the high and
	//						low limits of a month calendar control's display. Returns An
	//						integer that represents the range, in months, spanned by the
	//						two limits indicated by pMinRange and pMaxRange.
	int GetMonthRange(LPSYSTEMTIME pMinRange, LPSYSTEMTIME pMaxRange, DWORD dwFlags) const;

	// -> Parameters:		pMinRange	-	A pointer to a COleDateTime object containing
	//										the date at the lowest end of the range. 
	//						pMaxRange	-	A pointer to a COleDateTime object containing the
	//										date at the highest end of the range.
	// -> Return Value:		
	// -> Remarks:			Sets the selection for a month calendar control to a
	//						given date range. Returns nonzero if successful; otherwise 0. 
	BOOL SetSelRange(const COleDateTime& pMinRange, const COleDateTime& pMaxRange);

	// -> Parameters:		pMinRange	-	A pointer to a CTime object containing
	//										the date at the lowest end of the range. 
	//						pMaxRange	-	A pointer to a CTime object containing the date at
	//										the highest end of the range.
	// -> Return Value:		
	// -> Remarks:			Sets the selection for a month calendar control to a
	//						given date range. Returns nonzero if successful; otherwise 0. 
	BOOL SetSelRange(const CTime& pMinRange, const CTime& pMaxRange);

	// -> Parameters:		pMinRange	-	A pointer to a SYSTEMTIME structure containing
	//										the date at the lowest end of the range. 
	//						pMaxRange	-	A pointer to a SYSTEMTIME structure containing the
	//										date at the highest end of the range.
	// -> Return Value:		
	// -> Remarks:			Sets the selection for a month calendar control to a
	//						given date range. Returns nonzero if successful; otherwise 0. 
	BOOL SetSelRange(const LPSYSTEMTIME pMinRange, const LPSYSTEMTIME pMaxRange);

	// -> Parameters:		refMinRange	-	A reference to a COleDateTime object
	//										containing the minimum date allowed.
	//						refMaxRange	-	A reference to a COleDateTime object containing
	//										the maximum date allowed.
	// -> Return Value:		
	// -> Remarks:			Retrieves date information representing the upper and lower limits of the date range currently selected by the user. Returns nonzero if successful; otherwise 0.  
	BOOL GetSelRange(COleDateTime& refMinRange, COleDateTime& refMaxRange) const;

	// -> Parameters:		refMinRange	-	A reference to a CTime object containing
	//										the minimum date allowed.
	//						refMaxRange	-	A reference to a CTime object containing the maximum
	//										date allowed.
	// -> Return Value:		
	// -> Remarks:			Retrieves date information representing the upper and
	//						lower limits of the date range currently selected by the user.
	//						Returns nonzero if successful; otherwise 0.  
	BOOL GetSelRange(CTime& refMinRange, CTime& refMaxRange) const;

	// -> Parameters:		pMinRange	-	A pointer to a SYSTEMTIME structure containing
	//										the date at the lowest end of the range.
	//						pMaxRange	-	A pointer to a SYSTEMTIME structure containing the
	//										date at the highest end of the range.
	// -> Return Value:		
	// -> Remarks:			Retrieves date information representing the upper and
	//						lower limits of the date range currently selected by the user.
	//						Returns nonzero if successful; otherwise 0.  
	BOOL GetSelRange(LPSYSTEMTIME pMinRange, LPSYSTEMTIME pMaxRange) const;

	// -> Parameters:		pMCHitTest	-	A pointer to a MCHITTESTINFO structure
	//										containing hit testing points for the month 
	//										calendar control.
	// -> Return Value:		
	// -> Remarks:			Determines which portion of a month calendar control
	//						is at a given point on the screen. Returns A DWORD value. Equal
	//						to the uHit member of the MCHITTESTINFO structure.
	DWORD HitTest(PMCHITTESTINFO pMCHitTest);
};

//---------------------------------------------------------------------------
inline CXTDateTimeCtrl::CXTDateTimeCtrl()
	{ }
//---------------------------------------------------------------------------
inline CFont* CXTDateTimeCtrl::GetMonthCalFont() const
	{ ASSERT(::IsWindow(m_hWnd)); return CFont::FromHandle((HFONT) ::SendMessage(m_hWnd, DTM_GETMCFONT, 0, 0)); }
//---------------------------------------------------------------------------
inline CXTMonthCalCtrl* CXTDateTimeCtrl::GetMonthCalCtrl() const
	{ ASSERT(::IsWindow(m_hWnd)); return (CXTMonthCalCtrl*) CWnd::FromHandle((HWND) ::SendMessage(m_hWnd, DTM_GETMONTHCAL, 0, 0)); }
//---------------------------------------------------------------------------
inline void CXTDateTimeCtrl::SetMonthCalFont(HFONT hFont, BOOL bRedraw /* = TRUE */)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, DTM_SETMCFONT, (WPARAM) hFont, MAKELONG(bRedraw, 0)); }
//---------------------------------------------------------------------------
inline COLORREF CXTDateTimeCtrl::SetMonthCalColor(int iColor, COLORREF ref)
	{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, DTM_SETMCCOLOR, (WPARAM) iColor, (LPARAM) ref); }
//---------------------------------------------------------------------------
inline DWORD CXTDateTimeCtrl::GetTime(LPSYSTEMTIME pTimeDest) const
	{ ASSERT(::IsWindow(m_hWnd)); ASSERT(pTimeDest != NULL); return (DWORD) ::SendMessage(m_hWnd, DTM_GETSYSTEMTIME, 0, (LPARAM) pTimeDest); }
//---------------------------------------------------------------------------
inline COLORREF CXTDateTimeCtrl::GetMonthCalColor(int iColor) const
	{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, DTM_GETMCCOLOR, (WPARAM) iColor, 0); }
//---------------------------------------------------------------------------
inline BOOL CXTDateTimeCtrl::SetFormat(LPCTSTR pstrFormat)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, DTM_SETFORMAT, 0, (LPARAM) pstrFormat); }

//---------------------------------------------------------------------------
inline CXTMonthCalCtrl::CXTMonthCalCtrl()
	{ } 
//---------------------------------------------------------------------------
inline DWORD CXTMonthCalCtrl::HitTest(PMCHITTESTINFO pMCHitTest)
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, MCM_HITTEST, 0, (LPARAM) pMCHitTest); }
//---------------------------------------------------------------------------
inline BOOL CXTMonthCalCtrl::GetMinReqRect(RECT* pRect) const
	{ ASSERT(m_hWnd != NULL); return (BOOL) ::SendMessage(m_hWnd, MCM_GETMINREQRECT, 0, (LPARAM) pRect); }
//---------------------------------------------------------------------------
inline int CXTMonthCalCtrl::SetMonthDelta(int iDelta)
	{ ASSERT(m_hWnd != NULL); return (int) ::SendMessage(m_hWnd, MCM_SETMONTHDELTA, (WPARAM) iDelta, 0); }
//---------------------------------------------------------------------------
inline int CXTMonthCalCtrl::GetMonthDelta() const
	{ ASSERT(m_hWnd != NULL); return (int) ::SendMessage(m_hWnd, MCM_GETMONTHDELTA, 0, 0); }
//---------------------------------------------------------------------------
inline COLORREF CXTMonthCalCtrl::GetColor(int nRegion) const
	{ ASSERT(m_hWnd != NULL); return (COLORREF) ::SendMessage(m_hWnd, MCM_GETCOLOR, (WPARAM) nRegion, 0); }
//---------------------------------------------------------------------------
inline COLORREF CXTMonthCalCtrl::SetColor(int nRegion, COLORREF ref)
	{ ASSERT(m_hWnd != NULL); return (COLORREF) ::SendMessage(m_hWnd, MCM_SETCOLOR, (WPARAM) nRegion, (LPARAM) ref); }
//---------------------------------------------------------------------------
inline BOOL CXTMonthCalCtrl::SetMaxSelCount(int nMax)
	{ ASSERT(m_hWnd != NULL); return (BOOL) ::SendMessage(m_hWnd, MCM_SETMAXSELCOUNT, nMax, 0); }
//---------------------------------------------------------------------------
inline int CXTMonthCalCtrl::GetMaxSelCount() const
	{ ASSERT(m_hWnd != NULL); return (int) ::SendMessage(m_hWnd, MCM_GETMAXSELCOUNT, 0, 0); }
//---------------------------------------------------------------------------
inline void CXTMonthCalCtrl::SetToday(const LPSYSTEMTIME pDateTime)
	{ ASSERT(m_hWnd != NULL); ::SendMessage(m_hWnd, MCM_SETTODAY, 0, (LPARAM) pDateTime); }
//---------------------------------------------------------------------------
inline BOOL CXTMonthCalCtrl::GetToday(LPSYSTEMTIME pDateTime) const
	{ ASSERT(m_hWnd != NULL); return (BOOL) ::SendMessage(m_hWnd, MCM_GETTODAY, 0, (LPARAM) pDateTime); }
//---------------------------------------------------------------------------
inline BOOL CXTMonthCalCtrl::SetCurSel(const LPSYSTEMTIME pDateTime)
	{ ASSERT(m_hWnd != NULL); return (BOOL) ::SendMessage(m_hWnd, MCM_SETCURSEL, 0, (LPARAM) pDateTime); }
//---------------------------------------------------------------------------
inline BOOL CXTMonthCalCtrl::GetCurSel(LPSYSTEMTIME pDateTime) const
	{ ASSERT(m_hWnd != NULL); return (BOOL) ::SendMessage(m_hWnd, MCM_GETCURSEL, 0, (LPARAM) pDateTime); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTDATETIMECTRL_H__)
