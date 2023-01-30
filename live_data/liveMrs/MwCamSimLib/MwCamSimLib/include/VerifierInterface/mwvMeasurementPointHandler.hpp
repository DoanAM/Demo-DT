// (C) 2013-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVMEASUREMENTPOINTHANDLER_HPP_
#define MW_MWVMEASUREMENTPOINTHANDLER_HPP_
#include "mwMachSimVerifier.hpp"
#include "mwVerifierDllDefinition.hpp"
#include "mwvMeasurementPoint.hpp"

#include <vector>

namespace VerifierUtil
{
class MW_VERIFIER_API mwvMeasurementPointHandler
{
public:
	mwvMeasurementPointHandler(mwMachSimVerifier* const pVerifier);
	~mwvMeasurementPointHandler();

	int Select(int x, int y, const float3d& pos, float3d& vertex, bool removeOnly);

	void Clear();

	std::vector<mwvMeasurementPoint> m_selectedPoints;

private:
	mwMachSimVerifier* const m_pVerifier;

	bool WindowPosToScenePos(int x, int y, float2d& dest);
	mwvMeasurementPointHandler& operator=(const mwvMeasurementPointHandler&);  // = delete
};
}  // namespace VerifierUtil
#endif  //	MW_MWVMEASUREMENTPOINTHANDLER_HPP_
