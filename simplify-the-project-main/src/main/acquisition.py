import openmesh as om
import sys 
from affiche_mesh import affiche_mesh


def acquire(my_file_off):
    my_mesh=om.read_trimesh(my_file_off)
    my_mesh.request_vertex_colors()
    #Exemple d'utilisation du half edge collapse 
    #iterator=my_mesh.halfedges() 
    #vh=next(iterator)
    #my_mesh.collapse(vh)
    return my_mesh





my_file=sys.argv[1]
mesh=acquire(my_file)







# for bh in mesh.vertices():
#     print(mesh.point(bh))
# print(mesh.face_handle(0))
# print(mesh.face_handle(1))
# print(mesh.face_handle(2))

affiche_mesh(mesh)



