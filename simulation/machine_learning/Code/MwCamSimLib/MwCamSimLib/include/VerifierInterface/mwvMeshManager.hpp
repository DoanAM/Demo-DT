// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef MW_MWVMESHMANAGER_HPP_
#define MW_MWVMESHMANAGER_HPP_
#include "mwvMeshHandler.hpp"

#include <map>
#include <vector>

namespace VerifierUtil
{
class MW_VERIFIER_API mwvMeshManager
{
	typedef std::map<int, misc::mwAutoPointer<mwvMeshHandler>> Map;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Map m_meshes;

public:
	/// Creates an empty mesh manager with no meshes to start
	mwvMeshManager();

	/// Creates a mesh manager
	///
	/// Creates a mesh manager based on the meshes.
	/// @param [in] meshes the meshes with indices
	mwvMeshManager(Map meshes);

	/// Creates a mesh manager
	///
	/// Creates a mesh manager based on the meshes. Indices are taken from the vector (0 to
	/// size()-1). @param [in] meshes the meshes with no indices
	mwvMeshManager(std::vector<misc::mwAutoPointer<mwvMeshHandler>> meshes);

	/// Draws all the meshes that are visible
	void Draw();

	/// Adds a new mesh
	///
	/// Adds a new mesh to the manager with an index. The visibility of the mesh is not changed. No
	/// duplicate indices allowed. @param [in] idx the index of the mesh @param [in] mesh the
	/// pointer to the mesh
	void Add(int idx, misc::mwAutoPointer<mwvMeshHandler> mesh);

	/// Removes a mesh
	///
	/// Removes the mesh with the passed index. If the index does not exist, nothing happens.
	/// @param [in] idx the index of the mesh
	void Remove(int idx);

	/// Sets the visibility
	///
	/// Sets the visibility for all meshes.
	/// @param [in] visible TRUE if the meshes should be drawn
	void SetVisibility(bool visible);

	/// Sets the visibility
	///
	/// Sets the visibility for a single mesh with the passed index. If the index does not exist,
	/// nothing happens. @param [in] visible TRUE if the mesh should be drawn @param [in] idx the
	/// index of the mesh
	void SetVisibility(bool visible, int idx);

	/// Gets the visibility
	///
	/// Gets the visibility of all meshes. TRUE if at least one mesh is visible.
	bool GetVisibility();

	/// Gets the visibility
	///
	/// Gets the visibility of a single mesh with the passed index. FALSE if the index does not
	/// exist. @param [in] idx the index of the mesh
	bool GetVisibility(int idx);

private:
	void SetVisibility(bool visible, Map::iterator it);

	bool GetVisibility(Map::iterator it);
};
}  // namespace VerifierUtil
#endif  //	MW_MWVMESHMANAGER_HPP_
