// (C) 2007-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCNCMOVEHELPERS_HPP_
#define MW_MWCNCMOVEHELPERS_HPP_
#include "mwCNCMove.hpp"
#include "mwDllImpExpDef.hpp"


namespace cadcam
{
// -------------------  Scale visitor class ----------------

class MW_5AXUTIL_API mwCNCMoveScaleVisitor: public mwCNCMoveVisitorSetter
{
public:
	/// mwCNCMoveScaleVisitor constructor
	///
	/// @param scaleFactor the factor to scale the toolpath with
	mwCNCMoveScaleVisitor(double scaleFactor);

	/// ~mwCNCMoveScaleVisitor destructor
	~mwCNCMoveScaleVisitor();

	/// Visit
	///
	/// Visit method for mwCNCMove objects
	/// @param mw the mwCNCMove object to visit
	void Visit(mwCNCMove& mw);

	/// Visit
	///
	/// Visit method for mw3axMove objects
	/// @param mw the mw3axMove object to visit
	void Visit(mw3axMove& mw);

	/// Visit
	///
	/// Visit method for mw5axMove objects
	/// @param mw the mw5axMove object to visit
	void Visit(mw5axMove& mw);

	/// Visit
	///
	/// Visit method for mw5axMarkedMove objects
	/// @param mw the mw5axMarkedMove object to visit
	void Visit(mw5axMarkedMove& mw);

	/// Visit
	///
	/// Visit method for mw6axMove objects
	/// @param mw the mw5axMove object to visit
	void Visit(mw6axMove& mw);

private:
	/// scaling factor
	double m_scaleFactor;
};
}  // namespace cadcam
#endif  //	MW_MWCNCMOVEHELPERS_HPP_
