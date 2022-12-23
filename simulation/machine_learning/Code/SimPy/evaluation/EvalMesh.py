import trimesh
import numpy as np
import os
from config import data_rootpath, mesh_real_filename, mesh_sim_filename

class EvalMesh:
    """
    This class contains method to evaluate generate mesh model from simulation compared to the designed model
    """
    def __init__(self, partname, tr_matrix, dtype):
        """

        :param partname: str, workpiece foldername
        :param tr_matrix: np.ndarray (4,4), homogeneous transformation matrix for transforming two meshes together
        :param dtype: str, data source type for generated mesh model. It should be either 'real' for data from real cnc
                           machine or 'vnck' for data from simulated tool path
        """
        sim_mesh_path = ''
        if dtype == 'real':
            sim_mesh_path = os.path.join(data_rootpath, partname, mesh_real_filename)
        elif dtype == 'vnck':
            sim_mesh_path = os.path.join(data_rootpath, partname, mesh_sim_filename)
        else:
            raise ValueError(f'wrong dtype is given, mesh evaluation has no type of {dtype}, please check')

        real_mesh_path = os.path.join(data_rootpath, partname, 'MeshReal.stl')
        self.mesh_sim = trimesh.load_mesh(sim_mesh_path)
        self.mesh_real = trimesh.load_mesh(real_mesh_path)
        self.mesh_sim.apply_transform(tr_matrix)
        self.dtype = dtype

    def diff(self):
        """
        show difference between designed mesh model and generated mesh model

        :return: None
        """
        mesh_diff = self.mesh_real.difference([self.mesh_sim], engine="blender")

        # set color of the different part as red
        if self.dtype == 'real':
            mesh_diff.visual.vertex_colors = [255, 0, 0, 255]
        else:
            mesh_diff.visual.vertex_colors = [0, 0, 255, 255]
        mesh_diff.visual.vertex_colors = mesh_diff.visual.vertex_colors

        # set color of the designed model as light grey
        self.mesh_real.visual.vertex_colors = [128, 128, 128, 128]
        scene = trimesh.Scene([self.mesh_real, mesh_diff])
        scene.show()



    def show_together(self):
        """
        overlap the designed mesh model and generated mesh model

        :return: None
        """
        # set color of generated model as green
        self.mesh_sim.visual.face_colors = [0, 255, 0, 128]
        scene = trimesh.Scene([self.mesh_real, self.mesh_sim])
        scene.show()


if __name__ == "__main__":
    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../")
    print(f"Change the working directory: {os.getcwd()}")

    partname = "Versuchsteil_Quadrant_test"

    tr_matrix = np.eye(4, dtype=float)

    tr_matrix[0, -1] = 0
    tr_matrix[1, -1] = 0
    tr_matrix[2, -1] = 30

    myEM = EvalMesh(partname, tr_matrix, 'real')
    myEM.diff()
