// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MWMXPWRITERPARAM_HPP_
#define MW_MWMXPWRITERPARAM_HPP_

//#############################################################################
#include "mwMxpDllImpExpDef.hpp"
#include "mwStringConversions.hpp"
#include "mwUnitsFactory.hpp"
#include "mwMachDef.hpp"
#include <vector>
#pragma warning(push)
#pragma warning(disable: 4251)
//#############################################################################
class MWMXP_API mwMXPWriterParam
{
public:
	//#############################################################################
	//The coordinate type that will be outputted( absolute or relative)
	//Refactoring (release 2010.09)
	//CT_ABS_MACH_AXIS_COORDS will become CT_ABSOLUTE_WITHOUT_TLC (old value 0, new value 0)
	//CT_WORKPIECE_BASED_COORDS will become CT_RELATIVE (old value 1, new value 2)
	//Add new entry CT_ABSOLUTE_WITH_TLC (new value 1)
	//Refactoring (release 2015.08)
	//Add new entry CT_RELATIVE_WITH_TLC
	enum OutputCoordinatesType
	{
		CT_ABSOLUTE_WITHOUT_TLC = 0, // "Absolute Machine Axis Values"      
		CT_ABSOLUTE_WITH_TLC = 1, // "Absolute Machine Axis Values (at Tool Tip)"
		CT_RELATIVE = 2, // "Relative to Workpiece Position Values (at Tool Tip)"
		CT_RELATIVE_WITH_TLC = 3, // "Relative to Workpiece Position Values"
		CT_GEOMETRY_AXIS_VALUE_RTCP_OFF = 4, // "Values of Tool Tip in Workpiece Coordinate System"
		CT_CONTACT_POINT_FOR_WORK_OFFSET // only for 6-axis
	};
	//#############################################################################
	//how the file NC is created (old output format = DIFFERENCE or new format)
	enum OutputNCFormat
	{
		SHOW_DIFFERENCE = 0,
		SHOW_ALL_VALUES = 1
	};
	//#############################################################################
	enum OutputArcFormat
	{
		SHOW_ARC_LINEAR_INTERPOLATION = 0,
		SHOW_ARC_CENTER_FORMAT = 1,
		SHOW_ARC_RADIUS_FORMAT = 2
	};
	//#############################################################################
	typedef enum measures::mwUnitsFactory::Units	Units;
	//#############################################################################
	//! Constructor
	mwMXPWriterParam( const Units units );
	//#############################################################################
	//! Constructor
	mwMXPWriterParam( const mwMXPWriterParam &toCopy );
	//#############################################################################
	//! Default function used to set all members to default values
	void Default();
	//#############################################################################
	//! Copy operator
	const mwMXPWriterParam &operator=( const mwMXPWriterParam &toCopy );
	//#############################################################################
	//! This function sets the program number to be output
	void SetProgNo( const int progNo );
	//#############################################################################
	//! This function sets the name of the axis, e.g. X,Y,Z,A,B
	/* 
		It is requiring an vector of size equal with ne of machine axis and no duplicates are allowed otherwise a post::mwPostException is throw.
	*/
	void SetAxisNames(const std::vector<misc::mwstring> &axisNames, size_t machineNrOfAxes);
	//#############################################################################
	//! This function sets the name of the axis, e.g. X,Y,Z,A,B
	/*
	It is requiring an vector of size equal with ne of machine axis and no duplicates are allowed otherwise a post::mwPostException is throw.
	*/
	void SetAxisNames(const std::vector<misc::mwstring> &axisNames, const post::mwMachDef::NumbersOfAxes machineNrOfAxes);
	//#############################################################################
	//! This function sets the comment of the tool, e.g. _T("FLATMILL") etc.
	void SetToolComment( const misc::mwstring	&toolComment );
	//#############################################################################
	//! This function sets the tool path comment, e.g. _T("Swarf cutting of walls")
	void SetToolPathComment( const misc::mwstring	&tpComment  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN02( const misc::mwstring	&addSetN02  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN03( const misc::mwstring	&addSetN03  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN04( const misc::mwstring	&addSetN04  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN06( const misc::mwstring	&addSetN06  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN07( const misc::mwstring	&addSetN07  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN08( const misc::mwstring	&addSetN08  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN09( const misc::mwstring	&addSetN09  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN11( const misc::mwstring	&addSetN11  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN12( const misc::mwstring	&addSetN12  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN3( const misc::mwstring	&addSetN3  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN2( const misc::mwstring	&addSetN2  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN1( const misc::mwstring	&addSetN1  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	void SetAddNCSettingsN0( const misc::mwstring	&addSetN0  );
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN02() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN03() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN04() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN06() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN07() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN08() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN09() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN11() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN12() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN3() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN2() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN1() const;
	//#############################################################################
	//! This function set the Additional NC file settings fields
	const misc::mwstring GetAddNCSettingsN0() const;
	//#############################################################################
	//! This function sets the tool number
	void SetToolNumber( const int toolNumber );
	//#############################################################################
	//! This function set the starting line number
	/* 
		e.g. 10 would mean that the program would start with e.g. N10 ...
	*/
	void SetStartLineNo( const int startLineNo );
	//#############################################################################
	//! This function sets the line increment, e.g. 5 would mean that the lines would count N10, N15, N20 etc.
	void SetLineNoIncrement( const int lineNoInc );
	//#############################################################################
	//! This function sets the spindle speed
	void SetSpindleSpeed( const int spindleSpeed );
	//#############################################################################
	//! -DEPRECATED- will be removed in future. Only kept for compatibility reasons, use OutputCoordinatesType instead
	const bool GetOutputAbsoluteMachineCoordsFlag( ) const; 
	//#############################################################################
	//! This function sets the flag for outputting absolute machine coordinates -DEPRECATED- will be removed in future. Only kept for compatibility reasons, use OutputCoordinatesType instead
	/* If this flag is true, then the writer will writer absolute machine tool coordinates
		if this flag is false, then the writer will output tool tip positions in
		part coordinate system. Then the machine tool control is responsible
		of calculating the compensation of the linear axis. The default value is false
	*/
	void SetOutputAbsoluteMachineCoordsFlag(const bool absolMachCoords); 
	//#############################################################################
	//! Is TLC (tool length compensation) length added to output NC result -DEPRECATED- will be removed in future. Only kept for compatibility reasons, use OutputCoordinatesType instead
	const bool IsWithTLC() const; 
	//#############################################################################
	//! Set TLC (tool length compensation) length to output NC result -DEPRECATED- will be removed in future. Only kept for compatibility reasons, use OutputCoordinatesType instead
	void SetWithTLC(const bool withTLC);
	//#############################################################################
	//! This function returns the program number to be output
	const int GetProgNo( ) const;
	//#############################################################################
	//! This function returns the name of the axis, e.g. X,Y,Z,A,B
	const std::vector<misc::mwstring> GetAxisNames( ) const;
	//#############################################################################
	//! This function Gets the comment of the tool, e.g. _T("FLATMILL") etc.
	const misc::mwstring GetToolComment( ) const;
	//#############################################################################
	//! This function returns the tool path comment, e.g. _T("Swarf cutting of walls")
	const misc::mwstring GetToolPathComment( ) const;
	//#############################################################################
	//! This function returns the tool number
	const int GetToolNumber( ) const;
	//#############################################################################
	//! This function Get the starting line number
	const int GetStartLineNo( ) const;
	//#############################################################################
	//! This function returns the line increment
	const int GetLineNoIncrement( ) const;
	//#############################################################################
	//! This function returns the spindle speed
	const int GetSpindleSpeed(  ) const;
	//#############################################################################
	//! This function returns the metric flag
	const Units GetUnits(  ) const;
	//#############################################################################
	//! This function sets the metric flag
	void SetUnits( const mwMXPWriterParam::Units units ); 
	//#############################################################################
	//! Gets the coordinate type that will be outputted by the writer
	/* 	The writer can output coordinates in absolute machine tool
		coordinates or tool tip positions in part coordinate system.
		\return the type of coordinates to be displayed (absolute or relative)
	*/	 
	const OutputCoordinatesType& GetOutputCoordinatesType() const;
	//#############################################################################
	//! Sets the coordinate type that will be outputted by the writer 
	/* The writer can output coordinates in absolute machine tool
	  coordinates or tool tip positions in part coordinate system.
		\param newValue new coordinates type to be set
	 */
	void SetOutputCoordinatesType(const OutputCoordinatesType& newValue);
	//#############################################################################
	//! Gets the NC output format type 
	/* 	
		\return output format type used to create NC file
	*/	 
	const OutputNCFormat& GetOutputNCFormat() const;
	//#############################################################################
	//! Sets output format type for NC file
	/* 
		\param outputNCFormat represent type used to create NC file
	*/
	void SetOutputNCFormat(const OutputNCFormat& outputNCFormat);
	//#############################################################################
	//! Gets number of decimal places
	/* 	
		\return number of decimal places used in NC file
	*/	 
	const unsigned short GetOutputNCPrecision() const;
	//#############################################################################
	//! Sets number of decimal places
	/* 
		\param dec represent number of decimal places used in NC file
	*/
	void SetOutputNCPrecision(const unsigned short dec);
	//#############################################################################
	//! Gets the Arc output format type 
	/* 	
		\return output Arc format type 
	*/	 
	const OutputArcFormat& GetOutputArcFormat() const;
	//#############################################################################
	//! Sets output format type for Arc 
	/* 
		\param outputArcFormat represent Arc type used...
	*/
	void SetOutputArcFormat(const OutputArcFormat& outputArcFormat);
	//#############################################################################
	//! Gets machine rapid feed rate
	double GetMachineRapideFeedRate() const;
	//#############################################################################
	//! Sets machine rapid feed rate
	void SetMachineRapideFeedRate(double machineFeedRate);
	//#############################################################################
	//! Gets contact point using given work offset for 6-axis posting
	cadcam::mwPoint3d GetContactPointForWorkOffset() const;
	//#############################################################################
	//! Sets contact point using given work offset for 6-axis posting
	void SetContactPointForWorkOffset(const cadcam::mwPoint3d& contactPointForWorkOffset);
	//#############################################################################
private:
	//#############################################################################
	double							m_machineRapideFeedRate;
	bool							mAbsolMachCoordsFlag;
	Units		                    m_Units;
	int								mProgNo;
	std::vector<misc::mwstring>		mAxisNames;
	misc::mwstring					mToolComment;
	misc::mwstring					mTPComment;
	int								mToolNumber;
	int								mStartLineNo;
	int								mLineNoInc;
	int								mSpindleSpeed;
	OutputCoordinatesType			m_outputCoordinatesType;
	OutputNCFormat                  m_outputNCFormat;
	unsigned short                  m_decimal;
	bool                            m_withTLC;
	OutputArcFormat                 m_outputArcFormat;
	cadcam::mwPoint3d               m_contactPointForWorkOffset;
	//#############################################################################
	//Additional NC settings lines functions
	misc::mwstring					mAddNCSetN02;
	misc::mwstring					mAddNCSetN03;
	misc::mwstring					mAddNCSetN04;
	misc::mwstring					mAddNCSetN06;
	misc::mwstring					mAddNCSetN07;
	misc::mwstring					mAddNCSetN08;
	misc::mwstring					mAddNCSetN09;
	misc::mwstring					mAddNCSetN11;
	misc::mwstring					mAddNCSetN12;
	misc::mwstring					mAddNCSetN3;
	misc::mwstring					mAddNCSetN2;
	misc::mwstring					mAddNCSetN1;
	misc::mwstring					mAddNCSetN0;
	//#############################################################################
	void Copy(const mwMXPWriterParam &toCopy);
	//#############################################################################
};
//#############################################################################
#pragma warning(pop)
#endif	
