// (C) 2015-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWGENERICTOOL_HPP_
#define MW_MWGENERICTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwCuttingPartDefinition.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwNonCuttingPartDefinition.hpp"
#include "mwTool.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwGenericTool: public mwTool
{
public:
	typedef misc::mwAutoPointer<mwGenericTool> Ptr;
	typedef mwHolderDefinition<double> HolderDefinition;
	typedef mwArborDefinition<double> ArborDefinition;
	typedef mwNonCuttingPartDefinition<double> NonCuttingPartDefinition;
	typedef mwCuttingPartDefinition<double> CuttingPartDefinition;

	typedef mwMatrix<double, 4, 4> Matrix;
	typedef misc::mwAutoPointer<Matrix> MatrixPtr;
	typedef misc::mwAutoPointer<HolderDefinition> HolderPartDefinitionPtr;
	typedef misc::mwAutoPointer<ArborDefinition> ArborPartDefinitionPtr;
	typedef misc::mwAutoPointer<NonCuttingPartDefinition> NonCuttingPartDefinitionPtr;
	typedef misc::mwAutoPointer<CuttingPartDefinition> CuttingPartDefinitionPtr;

	struct HolderPositionedPart
	{
		typedef HolderDefinition PartDefinition;

		PartDefinition::Ptr m_definition;
		MatrixPtr m_matrix;

		HolderPositionedPart(HolderPartDefinitionPtr def): m_definition(def), m_matrix(new Matrix())
		{
		}

		HolderPositionedPart(HolderPartDefinitionPtr def, MatrixPtr mtx)
			: m_definition(def), m_matrix(mtx)
		{
		}

		bool operator==(const HolderPositionedPart& toCompare) const
		{
			if (&toCompare == this)
				return true;
			return (*m_matrix == *toCompare.m_matrix && *m_definition == *toCompare.m_definition);
		}
	};
	struct ArborPositionedPart
	{
		typedef ArborDefinition PartDefinition;

		PartDefinition::Ptr m_definition;
		MatrixPtr m_matrix;

		ArborPositionedPart(ArborPartDefinitionPtr def): m_definition(def), m_matrix(new Matrix())
		{
		}

		ArborPositionedPart(ArborPartDefinitionPtr def, MatrixPtr mtx)
			: m_definition(def), m_matrix(mtx)
		{
		}

		bool operator==(const ArborPositionedPart& toCompare) const
		{
			if (&toCompare == this)
				return true;
			return (*m_matrix == *toCompare.m_matrix && *m_definition == *toCompare.m_definition);
		}
	};
	struct CuttingPositionedPart
	{
		typedef CuttingPartDefinition PartDefinition;

		PartDefinition::Ptr m_definition;
		MatrixPtr m_matrix;

		CuttingPositionedPart(CuttingPartDefinitionPtr def)
			: m_definition(def), m_matrix(new Matrix())
		{
		}

		CuttingPositionedPart(CuttingPartDefinitionPtr def, MatrixPtr mtx)
			: m_definition(def), m_matrix(mtx)
		{
		}

		bool operator==(const CuttingPositionedPart& toCompare) const
		{
			if (&toCompare == this)
				return true;
			return (*m_matrix == *toCompare.m_matrix && *m_definition == *toCompare.m_definition);
		}
	};

	struct NonCuttingPositionedPart
	{
		typedef NonCuttingPartDefinition PartDefinition;

		PartDefinition::Ptr m_definition;
		MatrixPtr m_matrix;

		NonCuttingPositionedPart(NonCuttingPartDefinitionPtr def)
			: m_definition(def), m_matrix(new Matrix())
		{
		}
		NonCuttingPositionedPart(NonCuttingPartDefinitionPtr def, MatrixPtr mtx)
			: m_definition(def), m_matrix(mtx)
		{
		}

		bool operator==(const NonCuttingPositionedPart& toCompare) const
		{
			if (&toCompare == this)
				return true;
			return (*m_matrix == *toCompare.m_matrix && *m_definition == *toCompare.m_definition);
		}
	};

	typedef std::vector<HolderPositionedPart> HolderGroup;
	typedef std::vector<ArborPositionedPart> ArborGroup;
	typedef std::vector<NonCuttingPositionedPart> NonCuttingGroup;
	typedef std::vector<CuttingPositionedPart> CuttingGroup;

	explicit mwGenericTool(const Units units = Units::METRIC);

	mwGenericTool(
		const HolderGroup& holderGroup,
		const ArborGroup& arborGroup,
		const NonCuttingGroup& nonCuttingGroup,
		const CuttingGroup& cuttingGroup,
		const Units units);

	mwGenericTool(
		const HolderPositionedPart& holderPositionedPart,
		const ArborPositionedPart& arborPositionedPart,
		const NonCuttingPositionedPart& nonCuttingPositionedPart,
		const CuttingPositionedPart& cuttingPositionedPart,
		const Units units);


	mwGenericTool(const mwGenericTool& toCopy);

	const mwGenericTool& operator=(const mwGenericTool& toCopy);

	bool operator==(const mwGenericTool& toCompare) const;

	virtual const HolderGroup& GetHolderGroup() const;
	virtual const ArborGroup& GetArborGroup() const;
	virtual const CuttingGroup& GetCuttingGroup() const;
	virtual const NonCuttingGroup& GetNonCuttingGroup() const;

	virtual const double GetHolderLength() const;
	virtual const double GetArborLength() const;

	const HolderDefinition& GetHolder() const;
	const ArborDefinition& GetArbor() const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;
	void virtual AcceptVirtual(mwToolBranchVisitor& visitor) const;

	virtual ~mwGenericTool();
	/// Get specifyed tool part(s) bounding box. See base class function for more details
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const;

protected:
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	template <typename T>
	void EnlargeForGroupOfParts(mw3dBoundingBox<double>& bb2Enlarge, const T& group) const;

	void Validate() const;

	template <typename T>
	void ScaleHelper(T& group, const Units units, const double& scaleFactor);

	HolderGroup m_holderGroup;
	ArborGroup m_arborGroup;
	NonCuttingGroup m_nonCuttingGroup;
	CuttingGroup m_cuttingGroup;

	void Copy(const mwGenericTool& rToCopy);
};

typedef misc::mwAutoPointer<mwGenericTool> mwGenericToolPtr;

}  // namespace cadcam
#endif  //	MW_MWGENERICTOOL_HPP_
