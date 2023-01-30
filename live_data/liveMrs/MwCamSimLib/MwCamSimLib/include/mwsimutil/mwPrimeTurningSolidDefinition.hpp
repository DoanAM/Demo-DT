// (C) 2014-2021 by ModuleWorks GmbH
// Owner: 3Axis

/*ToDoDoc: Do we need any general introduction/description for this hpp file?*/

#ifndef MW_MWPRIMETURNINGSOLIDDEFINITION_HPP_
#define MW_MWPRIMETURNINGSOLIDDEFINITION_HPP_

#include "mwDefines.hpp"
#ifndef MW_USE_VS2008_COMPATIBILITY

#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedSolidDefinition.hpp"

namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwPrimeTurningSolidDefinition: public mwTypedExtrudedSolidDefinition<T>
{
public:
	typedef typename misc::mwAutoPointer<mwPrimeTurningSolidDefinition<T>> Ptr;

	typedef typename mwTypedExtrudedSolidDefinition<T>::Units Units;
	typedef typename mwTypedExtrudedSolidDefinition<T>::Contour Contour;
	typedef typename mwTypedExtrudedSolidDefinition<T>::ContourPtr ContourPtr;
	typedef typename mwTypedExtrudedSolidDefinition<T>::Hand Hand;

	explicit mwPrimeTurningSolidDefinition(const Units units);

	enum CodeNumber
	{
		C4_CP_25BL_27060_11B,
		C4_CP_25BR_27060_11B,
		C4_CP_30AL_27050_11C,
		C4_CP_30AR_27050_11C,

		C5_CP_25BL_35060_11B,
		C5_CP_25BR_35060_11B,
		C5_CP_30AL_35060_11C,
		C5_CP_30AR_35060_11C,
		C5_CP_70BL00115_11B,
		C5_CP_75AL00115_11C,
		C5_CP_A_25BL40060_11B,
		C5_CP_A_25BR40060_11B,
		C5_CP_A_30AL40060_11C,
		C5_CP_A_30AR40060_11C,

		C6_CP_25BL_45065_11B,
		C6_CP_25BR_45065_11B,
		C6_CP_30AL_45065_11C,
		C6_CP_30AR_45065_11C,
		C6_CP_70BL00130_11B,
		C6_CP_75AL00130_11C,
		C6_CP_A_25BL50065_11B,
		C6_CP_A_25BR50065_11B,
		C6_CP_A_30AL50065_11C,
		C6_CP_A_30AR50065_11C,

		C8_CP_70BL00160_11B,
		C8_CP_75AL00160_11C,

		CP_25BL_12_11,
		CP_25BL_16_11,
		CP_25BL_20_11,
		CP_25BL_2020_11,
		CP_25BL_2525_11,
		CP_25BL_3232_11,
		CP_25BR_12_11,
		CP_25BR_16_11,
		CP_25BR_20_11,
		CP_25BR_2020_11,
		CP_25BR_2525_11,
		CP_25BR_3232_11,

		CP_30AL_12_11,
		CP_30AL_16_11,
		CP_30AL_20_11,
		CP_30AL_2020_11,
		CP_30AL_2525_11,
		CP_30AL_3232_11,
		CP_30AR_12_11,
		CP_30AR_16_11,
		CP_30AR_20_11,
		CP_30AR_2020_11,
		CP_30AR_2525_11,
		CP_30AR_3232_11,

		QS_CP_25BL_12_11B,
		QS_CP_25BL_16_11B,
		QS_CP_25BL_2020_11B,
		QS_CP_25BL_2525_11B,
		QS_CP_25BR_12_11B,
		QS_CP_25BR_16_11B,
		QS_CP_25BR_2020_11B,
		QS_CP_25BR_2525_11B,

		QS_CP_30AL_12_11C,
		QS_CP_30AL_16_11C,
		QS_CP_30AL_2020_11C,
		QS_CP_30AL_2525_11C,
		QS_CP_30AR_12_11C,
		QS_CP_30AR_16_11C,
		QS_CP_30AR_2020_11C,
		QS_CP_30AR_2525_11C
	};

	enum ShankInfo
	{
		SI_RECTANGULAR,
		SI_QS,
		SI_CAPTO
	};

	mwPrimeTurningSolidDefinition(const CodeNumber src, const double height, const Units units);

	/// Returns the contour solid.
	CodeNumber GetCodeNumber() const;

	/// Returns the shank info.
	ShankInfo GetShankInfo() const;

	/// Returns the solid contour .
	const Contour& GetContour() const;

	bool operator==(const mwPrimeTurningSolidDefinition& rToCompare) const;

	/// Returns the 3D bounding box of the revolved solid.
	virtual const mw3dBoundingBox<T> GetBoundingBox3d() const;

	/// Implements the visitor pattern.
	///
	/// @param visitor is a reference to the setter visitor.
	virtual void AcceptVisitor(const mwSolidDefinitionVisitorSetter<T>& visitor);

	/// Implements the visitor pattern
	///
	/// @param visitor is a const reference to the getter visitor.
	virtual void AcceptVisitor(mwSolidDefinitionVisitorGetter<T>& visitor) const;
private:
	CodeNumber m_codeNumber;
	Contour m_contour;

	virtual void Scale(const Units units, const double& scaleFactor);
};

template <typename T>
class MW_5AXUTIL_API mwPrimeTurningSolidDefinitionExtractor: public mwSolidDefinitionVisitorGetter<T>
{
public:
	mwPrimeTurningSolidDefinitionExtractor();

	virtual void Visit(const mwSolidDefinition<T>& visitor);

	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor);

	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor);

	virtual void Visit(const mwMeshSolidDefinition<T>& visitor);

	virtual void Visit(const mwTurningSolidDefinition<T>& visitor);

	virtual void Visit(const mwContourTurningSolidDefinition<T>& visitor);

	virtual void Visit(const mwWireSolidDefinition<T>& visitor);

	virtual void Visit(const mwPrimeTurningSolidDefinition<T>& visitor);

	virtual void Visit(const mwThreadTapSolidDefinition<T>& visitor);

	const mwPrimeTurningSolidDefinition<T>& GetSolid() const;

private:
	mwPrimeTurningSolidDefinition<T> m_primeTurningSolid;
};
}  // namespace cadcam
#endif
#endif  //	MW_MWCONTOURTURNINGSOLIDDEFINITION_HPP_
