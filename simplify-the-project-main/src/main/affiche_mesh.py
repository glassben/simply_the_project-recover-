import openmesh as om
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

def print_mesh(mesh):
    print("\nSommets:")
    for vh in mesh.vertices():
        print(f"Sommet {vh.idx()}: {mesh.point(vh)}, RGB : {mesh.color(vh)}")

    print("\nFaces:")
    for fh in mesh.faces():
        verts = [v.idx() for v in mesh.fv(fh)]
        print(f"Face {fh.idx()}: Sommets {verts}")

    print("\nArêtes:")
    for eh in mesh.edges():
        heh = mesh.halfedge_handle(eh, 0)
        v1 = mesh.from_vertex_handle(heh)
        v2 = mesh.to_vertex_handle(heh)
        print(f"Arête {eh.idx()}: ({v1.idx()}, {v2.idx()})")

def affiche_mesh(my_mesh):
    """Affiche graphiquement un mesh.

    Args:
        my_mesh (Openmesh::mesh): Le mesh que l'on souhaite afficher.
    """
    vertices = np.array([my_mesh.point(v) for v in my_mesh.vertices()])
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(vertices[:, 0], vertices[:, 1], vertices[:, 2])
    
    faces = []
    for f in my_mesh.faces():
        faces.append([v.idx() for v in my_mesh.fv(f)])
    
    mesh_faces = Poly3DCollection([vertices[face] for face in faces], linewidths=1, edgecolors='r', alpha=0.25)


    ax.add_collection3d(mesh_faces)


    ax.set_axis_off()
    ax.set_title("Maillage 3D")


    ax.set_xlim([np.min(vertices[:, 0]), np.max(vertices[:, 0])])
    ax.set_ylim([np.min(vertices[:, 0]), np.max(vertices[:, 0])])
    ax.set_zlim([np.min(vertices[:, 0]), np.max(vertices[:, 0])])
    
    ax.set_aspect('auto')
    plt.show()
    
    #edge=[vertices[face] for face in faces]
    #sum_edge=0
    #for k in edge:
        #sum_edge+=k.shape[0]*k.shape[1]

    #print("nombre de vertice",len(vertices))
    #print("nombre de edge", sum_edge)

# Credits for bunny and teapot and torus : gaschler (github)
#affiche_mesh(om.read_trimesh("teapot.off"))
