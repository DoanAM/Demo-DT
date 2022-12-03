// (C) 2013-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVMEASUREMENTDISTANCEHANDLER_HPP_
#define MW_MWVMEASUREMENTDISTANCEHANDLER_HPP_
#include "mwMachSimVerifier.hpp"
#include "mwVerifierDllDefinition.hpp"
#include "mwvMeasurementDistance.hpp"

#include <vector>

namespace VerifierUtil
{
class MW_VERIFIER_API mwvMeasurementDistanceHandler
{
public:
	mwvMeasurementDistanceHandler(mwMachSimVerifier* const pVerifier);
	~mwvMeasurementDistanceHandler();

	int Select(int x, int y, const float3d& pos, float3d& vertex, bool removeOnly);

	void Clear();

	bool GetFirstClick() const { return firstClick; }

	void ResetFirstClick() { firstClick = true; }

	const mwvMeasurementDistance& GetUnfinishedDistance() const { return unfinishedDistance; }

	std::vector<mwvMeasurementDistance> m_selectedDistances;

private:
	mwMachSimVerifier* const m_pVerifier;

	bool firstClick;
	mwvMeasurementDistance unfinishedDistance;

	bool WindowPosToScenePos(int x, int y, float2d& dest);
	mwvMeasurementDistanceHandler& operator=(const mwvMeasurementDistanceHandler&);  // = delete
};
}  // namespace VerifierUtil
#endif  //	MW_MWVMEASUREMENTDISTANCEHANDLER_HPP_
