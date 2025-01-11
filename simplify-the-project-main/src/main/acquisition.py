import openmesh as om
import sys 
from affiche_mesh import affiche_mesh


def acquire(my_file_off):
    my_mesh = om.read_trimesh(my_file_off)
    my_mesh.request_vertex_colors()
    return my_mesh

