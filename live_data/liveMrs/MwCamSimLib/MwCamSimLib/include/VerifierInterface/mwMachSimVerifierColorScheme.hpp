// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWMACHSIMVERIFIERCOLORSCHEME_HPP_
#define MW_MWMACHSIMVERIFIERCOLORSCHEME_HPP_
#ifndef MWMSV_API
#ifdef _WIN32
#define MWMSV_API __stdcall
#elif defined(__linux__) || defined(__APPLE__)
#define MWMSV_API
#endif
#endif

/// Defines colors of a color scheme
///
/// @note When specifying colors please make sure the values are added in ascending order.
///
/// For information about available color schemes see VerifierUtil::WorkpieceDrawModes
///
///
/// ## Setting colors for absolute values
/// Examples for this are WDM_TOOL, WDM_OPERATION, WDM_CHUNKS, and WDM_OPERATION_TYPE.
///
/// Colors can be specified for each value you expect to appear. If the number of colors is exceeded
/// (e.g. if there are more tools than there are tool colors), then the highest color will be
/// chosen.
/// ```
/// colorScheme->Clear();
/// colorScheme->Add(float(toolId), 0.0f, 0.0f, 1.0f);
/// ```
///
///
/// ## Setting colors for ranges
/// Examples for this are WDM_DEVIATION, WDM_DEVIATION_OFFSET, WDM_TOOL_PATH_SEGMENT_LENGTH,
/// WDM_HEIGHT_CHANGE, and WDM_ORIENTATION_CHANGE.
///
/// Note: WDM_DEVIATION will ignore the offset given via mwMachSimVerifier::SetOffset();
/// WDM_DEVIATION_OFFSET will not.
/// ```
/// colorScheme->Clear();
///
/// // color for values in the range (-infinity, -4.0]
/// colorScheme->Add(-4.0f,    0.0f, 0.0f, 0.5f);
///
/// // color for values in the range (-4.0, -1.0]
/// colorScheme->Add(-1.0f,    0.0f, 0.0f, 1.0f);
///
/// // color for values in the range (-1.0, 1.0]
/// colorScheme->Add(1.0f,     0.0f, 1.0f, 0.0f);
///
/// // color for values in the range (1.0, infinity)
/// colorScheme->Add(FLT_MAX,  1.0f, 0.0f, 0.0f);
/// ```
///
///
/// ## Setting colors for WDM_GOUGE_EXCESS
/// This color scheme uses three fixed values: -1, 0, and 1.
///
/// Thresholds are set via mwMachSimVerifier::SetGougeThreshold() and
/// mwMachSimVerifier::SetExcessThreshold().
/// ```
/// colorScheme->Clear();
/// colorScheme->Add(-1.0f,  0.0f, 0.0f, 1.0f); // gouge color
/// colorScheme->Add(0.0f,   0.0f, 1.0f, 0.0f); // equal color
/// colorScheme->Add(1.0f,   1.0f, 0.0f, 0.0f); // excess color
/// ```
class mwMachSimVerifierColorScheme
{
public:
	/// Virtual destructor
	virtual ~mwMachSimVerifierColorScheme() {}

	/// Get color and threshold at the specified index
	/*	@param index index of specified collection item
	 *	@param value returns the value of the specified item
	 *	@param r returns the R color component value of specified item
	 *	@param g returns the G color component value of specified item
	 *	@param b returns the B color component value of specified item
	 */
	virtual void MWMSV_API
	GetItemData(int index, float& value, float& r, float& g, float& b) const = 0;

	/// Set color and threshold at the specified index
	/*	@param index index of specified collection item
	 *	@param value the value of the specified item
	 *	@param r the R color component value of specified item
	 *	@param g the G color component value of specified item
	 *	@param b the B color component value of specified item
	 *	@return new index of specified item
	 */
	virtual int MWMSV_API SetItemData(int index, float value, float r, float g, float b) = 0;

	/// Multiplies all values with a factor
	///
	/// Multiplies all values in the scheme with the factor, does not change any order
	/// @param [in] factor as float
	virtual void MWMSV_API MultiplyValues(float factor) = 0;

	/// Offsets all values with a value
	///
	/// Offsets all values in the scheme with the value, does not change any order
	/// @param [in] offset the value as float
	virtual void MWMSV_API OffsetValues(float offset) = 0;

	/// Adds new item
	///
	/// Adds a new color. Depending on the color scheme the value is interpreted differently. Some
	/// schemes are defined via absolute values, other schemes via intervals.
	///
	/// When specifying intervals the value names the upper bound of the interval. In the case that
	/// multiple upper bounds are valid the color associated with the smallest one is chosen.
	///
	/// Specified via absolute value: WDM_TOOL, WDM_OPERATION, WDM_CHUNKS, WDM_OPERATION_TYPE
	///
	/// Specified via range: WDM_DEVIATION, WDM_DEVIATION_OFFSET, WDM_TOOL_PATH_SEGMENT_LENGTH,
	/// WDM_HEIGHT_CHANGE, WDM_ORIENTATION_CHANGE (angle in degree)
	///
	/// WDM_REMOVED_MATERIAL: specify just one color (value irrelevant). Uncut material is colored
	/// in the default stock color. WDM_GOUGE_EXCESS: -1: gouge color, 0: in-tolerance color, 1:
	/// excess color WDM_CLIMB_CONVENTIONAL: -1: climb color, 1: conventional color
	///
	/// WDM_LAST_CUT: specify just one color (value irrelevant). The last cut is colored with this
	/// color, the rest has the default stock color.
	///
	/// @return index of new created item
	virtual int MWMSV_API Add(float value, float r, float g, float b) = 0;

	/// Removes specified item
	///	@param index of collection item to be deleted
	virtual void MWMSV_API Remove(int index) = 0;

	/// Gets the number of items
	///	@return the number of items currently stored in collection
	virtual int MWMSV_API GetCount() const = 0;

	/// Clear
	///
	/// Removes all items
	virtual void MWMSV_API Clear() = 0;
};
#endif  //	MW_MWMACHSIMVERIFIERCOLORSCHEME_HPP_
