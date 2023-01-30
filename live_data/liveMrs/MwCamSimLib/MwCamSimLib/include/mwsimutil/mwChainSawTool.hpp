// (C) 2012-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWCHAINSAWTOOL_HPP_
#define MW_MWCHAINSAWTOOL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwRevolvedSolidDefinition.hpp"
#include "mwToolHelper.hpp"
#include "mwTypedSawingTool.hpp"

#include "iostream"


namespace cadcam
{
class mwChainSawTool;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwChainSawTool& toDump);

namespace cadcam
{
/// This class represents a chain saw tool.
class MW_5AXUTIL_API mwChainSawTool: public mwTypedSawingTool
{
	/// Part of serialization mechanism
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwChainSawTool& toDump);

public:
	using mwSawingTool::AcceptVirtual;

	enum chainSawType
	{
		straight,
		simple
	};

	explicit mwChainSawTool(const Units units = Units::METRIC);

	~mwChainSawTool();

	/// Constructor
	///
	/// Constructs an chain saw tool using the given parameters.
	///	@param newHolder is the holder.
	///	@param newCornerRad is the corner radius.
	///	@param newcornerRadiusType is the corner radius type.
	///	@param newChainSawType is the chainsaw type.
	///	@param newBladeWidth is the blade width.
	///	@param newBladeThickness is the blade thickness.
	///	@param newBladeLength is the blade length.
	///	@param newStraightBladeLength is the straight length portion of the blade.
	///	@param newUpperWidth is the upper width of the blade.
	///	@param units are the measurement units.

	mwChainSawTool(
		const HolderDefinition& newHolder,
		const double& newCornerRad,
		const cornerRadiusType& newcornerRadiusType,
		const chainSawType& newChainSawType,
		const double newBladeWidth,
		const double newBladeThickness,
		const double newBladeLength,
		const double newStraightBladeLength,
		const double newUpperWidth,
		const Units units);

	mwChainSawTool(
		const HolderDefinition& newHolder,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const cornerRadiusType& newcornerRadiusType,
		const chainSawType& newChainSawType,
		const double newBladeWidth,
		const double newBladeThickness,
		const double newBladeLength,
		const double newStraightBladeLength,
		const double newUpperWidth,
		const Units units);

public:
	/// Gets the corner radius.
	/// @returns The corner radius of the tool.
	const double GetCornerRadius() const;

	/// Gets the corner radius type.
	/// @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	/// Gets the chain saw type.
	/// @returns The chain saw type.
	const chainSawType GetChainSawType() const;

	/// Gets the blade width.
	/// @returns The blade width of the tool.
	const double GetBladeWidth() const;

	/// Gets the blade length.
	/// @returns The blade length of the tool.
	const double GetBladeLength() const;

	/// Gets the straight blade length.
	/// @returns The straight blade length of the tool.
	const double GetStraightBladeLength() const;

	/// Gets the upper width of the tool.
	///
	///	@returns The upper width of the tool blade.
	const double GetBladeUpperWidth() const;

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///	@param toCompare is the tool that will be compared with the current tool.
	///	@returns <b>True</b> if both tools contain the same parameters,
	///	<b>false</b> otherwise.
	bool operator==(const mwChainSawTool& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///	@param toCompare is the tool that will be compared with the current tool.
	///	@returns <b>False</b> if both tools contain the same parameters,
	///	<b>true</b> otherwise
	bool operator!=(const mwChainSawTool& toCompare);

	/// AcceptVirtual function
	///
	///	@param virtualVisitor of type const mwToolVisitor &
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Get specifyed tool part(s) bounding box. See base class function for more details
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const;

private:
	/// Checks the validity of the corner radius of the ChainSaw tool.
	///
	/// Tool is valid if \f$cornerRadius > 0\f$
	///	@param cornerRadius corner radius to be validated.
	void ValidateCornerRadius(const double& cornerRadius) const;

	/// Checks the validity of the blade width of the ChainSaw tool.
	/// @param bladeWidth is the blade width to be validated.
	void ValidateBladeWidth(const double& bladeWidth) const;

	/// Checks the validity of the blade length of the ChainSaw tool.
	/// @param bladeLength is the blade length to be validated.
	void ValidateBladeLength(const double& bladeLength) const;
	/// Checks the validity of the straight blade length of the ChainSaw tool.
	///
	///	@param straightBladeLength is the straight blade length to be validated.
	void ValidateStraightBladeLength(const double& straightBladeLength) const;

	/// Checks the validity of the constraints which must be kept between the blade length and the
	/// straight blade length.
	///
	/// Straight chainsaw tool is valid if \f$bladeLength >= straightBladeLength\f$
	///	@param bladeLength blade length to be validated.
	///	@param straightBladeLength is the straight blade length to be validated.
	void ValidateBladeLengthVsStraighBladeLength(
		const double& bladeLength, const double& straightBladeLength) const;
	/// Checks the validity of the blade upper width of the ChainSaw tool.
	///
	/// Tool is valid if \f$bladeUpperWidth > 0\f$
	///	@param bladeUpperWidth blade upper width to be validated.
	void ValidateBladeUpperWidth(const double& bladeUpperWidth) const;

	double m_cornerRadius;
	cornerRadiusType m_cornerRadiusType;
	chainSawType m_chainSawType;

	double m_bladeWidth;
	double m_bladeLength;
	double m_straightBladeLength;
	double m_bladeUpperWidth;
};
}  // namespace cadcam
#endif  //	MW_MWCHAINSAWTOOL_HPP_
