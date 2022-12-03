// (C) 2014-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTURNINGSOLIDDEFINITION_HPP_
#define MW_MWTURNINGSOLIDDEFINITION_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMathConstants.hpp"
#include "mwSolidDefinition.hpp"
#include "mwTypedExtrudedSolidDefinition.hpp"

namespace cadcam
{
/// @class mwTurningSolidDefinition
/// Implements the turning tool as a solid
/// Solid representation of the turning tool is mainly used for visualization purposes
template <typename T>
class MW_5AXUTIL_API mwTurningSolidDefinition: public mwTypedExtrudedSolidDefinition<T>
{
public:
	typedef typename misc::mwAutoPointer<mwTurningSolidDefinition<T>> Ptr;

	typedef typename measures::mwUnitsFactory::Units Units;
	typedef typename mwSolidDefinition<T>::ContourPtr ContourPtr;

	typedef typename mwTypedExtrudedSolidDefinition<T>::Hand Hand;
	typedef typename mwTypedExtrudedSolidDefinition<T>::Shank Shank;

public:
	enum Insert
	{
		IT_TRIANGLE = 0,
		IT_DIAMOND = 1,
		IT_PARALLELOGRAM = 2,
		IT_SQUARE = 3,
		IT_OCTAGONAL = 4,
		IT_PENTAGONAL = 5,
		IT_ROUND = 6,
		IT_HEXAGONAL = 7,
		IT_GROOVE = 8,
		IT_THREAD_TRIANGLE = 9
	};

	enum Type
	{
		TP_GENERIC_TYPE_A = 0,
		TP_GENERIC_TYPE_B = 1,
		TP_GENERIC_TYPE_C = 2,
		TP_GENERIC_TYPE_D = 3,
		TP_GENERIC_TYPE_E = 4,
		TP_GENERIC_TYPE_F = 5,
		TP_GENERIC_TYPE_G = 6,
		TP_BORE_TYPE_A = 8,
		TP_BORE_TYPE_B = 9,
		TP_BORE_TYPE_C = 10
	};

public:
	/// @class Parameters
	/// Parameters of turning solid definition
	struct MW_5AXUTIL_API Parameters
	{
		explicit Parameters(const Units units = Units::METRIC);

		Parameters(const Units units, const Insert insert);

		Parameters(const Units units, const Insert insert, const Type type);

		Parameters& SetInsert(const Insert insert);

		Parameters& SetType(const Type type);

		Parameters& SetShank(const Shank shank);

		Parameters& SetHand(const Hand hand);

		Parameters& Height(const T height);

		Parameters& A(const T a);

		Parameters& B(const T b);

		Parameters& C(const T c);

		Parameters& D(const T d);

		Parameters& E(const T e);

		Parameters& F(const T f);

		Parameters& G(const T g);

		Parameters& H(const T h);

		Parameters& I(const T i);

		Parameters& SetUnits(const Units units);

		Insert insert;
		Type type;
		Shank shank;
		Hand hand;
		T height;
		T a;
		T b;
		T c;
		T d;
		T e;
		T f;
		T g;
		T h;
		T i;
		Units units;
	};

public:
	explicit mwTurningSolidDefinition(const Units units);

	explicit mwTurningSolidDefinition(const Parameters& data);

	mwTurningSolidDefinition(const Units units, const Insert insert);

	mwTurningSolidDefinition(const Units units, const Insert insert, const Type type);

	bool operator==(const mwTurningSolidDefinition<T>& rToCompare) const;

public:
	/// Returns the holder's insert type.
	Insert GetInsert() const;

	/// Returns the holder's type.
	Type GetType() const;

	/// Returns the typed extruded solid 'A' value.
	const T GetA() const;

	/// Returns the typed extruded solid 'B' value.
	const T GetB() const;

	/// Returns the typed extruded solid 'C' value.
	const T GetC() const;

	/// Returns the typed extruded solid 'D' value.
	const T GetD() const;

	/// Returns the typed extruded solid 'E' value.
	const T GetE() const;

	/// Returns the typed extruded solid 'F' value.
	const T GetF() const;

	/// Returns the typed extruded solid 'G' value.
	const T GetG() const;

	/// Returns the typed extruded solid 'H' value.
	const T GetH() const;

	/// Returns the typed extruded solid 'I' value.
	const T GetI() const;

	/// Returns the 3D bounding box of the revolved solid.
	virtual const mw3dBoundingBox<T> GetBoundingBox3d() const;

public:
	/// Implements the visitor pattern.
	///
	/// @param visitor is a reference to the setter visitor.
	virtual void AcceptVisitor(const mwSolidDefinitionVisitorSetter<T>& visitor);

	/// Implements the visitor pattern
	///
	/// @param visitor is a const reference to the getter visitor.
	virtual void AcceptVisitor(mwSolidDefinitionVisitorGetter<T>& visitor) const;

private:
	Insert m_insert;
	Type m_type;
	T m_a;
	T m_b;
	T m_c;
	T m_d;
	T m_e;
	T m_f;
	T m_g;
	T m_h;
	T m_i;

private:
	virtual void Scale(const Units units, const double& scaleFactor);
	void Init(const Parameters& data);
};

/// This class represents an extruded solid extractor.
///
/// I ensures that a given mwSolidDefinition derived object is in fact of type
/// mwTurningSolidDefinition. If not, an exception is thrown.
template <typename T>
class mwTurningSolidDefinitionExtractor: public mwSolidDefinitionVisitorGetter<T>
{
public:
	mwTurningSolidDefinitionExtractor();

	virtual void Visit(const mwSolidDefinition<T>& visitor);
	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor);
	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor);
	virtual void Visit(const mwMeshSolidDefinition<T>& visitor);
	virtual void Visit(const mwTurningSolidDefinition<T>& visitor);
	virtual void Visit(const mwContourTurningSolidDefinition<T>& visitor);
	virtual void Visit(const mwPrimeTurningSolidDefinition<T>& visitor);
	virtual void Visit(const mwWireSolidDefinition<T>& visitor);
	virtual void Visit(const mwThreadTapSolidDefinition<T>& visitor);

	/// Returns the mwTurningSolidDefinition object.
	const mwTurningSolidDefinition<T>& GetSolid() const;

private:
	mwTurningSolidDefinition<T> m_turningSolid;
};
}  // namespace cadcam
#endif  //	MW_MWTURNINGSOLIDDEFINITION_HPP_
