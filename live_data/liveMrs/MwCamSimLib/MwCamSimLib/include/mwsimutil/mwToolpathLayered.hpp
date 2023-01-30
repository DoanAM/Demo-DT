// (C) 2014-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLPATHLAYERED_HPP_
#define MW_MWTOOLPATHLAYERED_HPP_
#include "mwCadcamFwdDecl.hpp"
#include "mwMeasurable.hpp"

namespace cadcam
{
class mwToolpathInt;
class mwToolpathLayered;

template <class Archive>
void serialize(Archive& ar, mwToolpathLayered& toolpathEx, const unsigned int);

/// This class implements a new toolpath which is a structure to store data in layered way.
///
///	The toolpath contains separate layers to keep move data like its feed rate, tool orientation and
///etc. 	These layers are accessed via constant identifiers defined in
///mwToolpathLayeredHelper::LayerTypes enum. 	For example, mwToolpathLayeredHelper::LT_FEEDRATE is
///the identifier of layer 	which stores feed rates for each move. Lets consider an example:
/// @code{.cpp}
///
///		const mwToolpathLayered src = CalculateToolpathLayered();
///
///		double feedRate = 0;
///		const bool ret src.GetMoveData(mwToolpathLayeredHelper::LT_FEEDRATE, 1, feedRate));
///
///	@endcode
/// If ret is true, the feed rate value is existed and set to valid one.
///
///	The number of layers depends on calculation based method. Before get a data,
///	one can check if a layer exists in a toolpath or not.
///
///	The mwToolpathLayeredHelper namespace contains functions to make easy work with new toolpath.
///	For example, to check move type, please use mwToolpathLayeredHelper::GetMoveType function.
///
///	To find arc in a toolpath and its middle point, please invoke mwToolpathLayeredHelper::IsArcMove
/// and mwToolpathLayeredHelper::GetArcMiddlePoint functions correspondingly.
///
///	To get an old toolpath please use mwToolpathLayered2ToolpathConverter::Convert function.
class MW_5AXUTIL_API mwToolpathLayered
{
public:
	/// Represents a constructor which takes measurement units
	mwToolpathLayered(measures::mwMeasurable::Units units);

	/// Represents a constructor to be used for internal purposes only
	mwToolpathLayered(const mwToolpathInt& toolpath);

	/// Represents a copy constructor
	mwToolpathLayered(const mwToolpathLayered& toCopy);

	/// Returns true if a layer is presented in a toolpath, otherwise false;
	bool DoesLayerExist(const size_t layerID) const;

	/// Returns total moves count in a toolpath
	size_t GetMovesCount() const;

	/// Returns move data on given position idx in a toolpath
	///
	///	@param layerID is the identification of a layer which store requested move data.
	///	@param idx is supposed position of move.
	///	@param value is template object used to return move data.
	///	@return true if a move data is existed otherwise false.
	///	If a layer does not exist in a toolpath, an exception is thrown.
	template <typename Obj>
	bool GetMoveData(const size_t layerID, const size_t idx, Obj& value) const;

	/// Returns current measurement units used in a toolpath
	measures::mwMeasurable::Units GetUnits() const;

	/// Returns true if a toolpath is equal with given one otherwise false
	bool operator==(const mwToolpathLayered& toCompare) const;

	/// Returns true if a toolpath is not equal with given one otherwise false
	bool operator!=(const mwToolpathLayered& toCompare) const;

	/// Represents an assignment operator
	mwToolpathLayered& operator=(const mwToolpathLayered& toCopy);

	/// Frees memory allocated for a toolpath
	~mwToolpathLayered();

private:
	template <class Archive>
	friend void serialize(Archive& ar, cadcam::mwToolpathLayered& toolpathEx, const unsigned int);

	mwToolpathInt* m_toolpath;
};
}  // namespace cadcam
#endif  //	MW_MWTOOLPATHLAYERED_HPP_
