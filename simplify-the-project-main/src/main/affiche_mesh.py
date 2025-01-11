import openmesh as om
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

def print_mesh(mesh):
    """Affiche un mesh.

    Args:
        mesh (Mesh): Le mesh que l'on souhaite afficher.
    """
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

def comparison_simplification(mesh, display=False):
    """Calcule et Affiche le nombre d'arêtes et de sommets.

    Args:
        mesh (Mesh): Mesh dont on souhaite afficher le nombre d'arêtes et de sommets.
        display (Bool): Booléen valant False par défaut, qui décide si on affiche ou non les informations.
    
    Returns:
        Int, Int: Le nombre d'arêtes et le nombre de sommets.
    """
    nb_vertices, nb_edges = len(mesh.vertices()), len(mesh.edges())
    if display:
        print("Nombre de sommets : ", nb_vertices)
        print("Nombre d'arêtes : ", nb_edges)
    return nb_vertices, nb_edges

def ratio_simplification(nb_vertices, nb_vertices_simpl, nb_edges, nb_edges_simpl):
    """Affiche le pourcentage de simplification d'un maillage.

    Args:
        nb_vertices (Int): Le nombre de sommets avant simplification.
        nb_vertices_simpl (Int): Le nombre de sommets après simplification.
        nb_edges (Int): Le nombre d'arêtes avant simplification.
        nb_edges_simpl (Int): Le nombre d'arêtes après simplification.
    """
    ratio_vertices = round((1 - (nb_vertices_simpl / nb_vertices)) * 100, 1)
    ratio_edges = round((1 - (nb_edges_simpl / nb_edges)) * 100, 1)
    print("Ratio de simplification selon les sommets : ", ratio_vertices, "%")
    print("Ratio de simplification selon les arêtes : ", ratio_edges, "%")

def affiche_mesh(my_mesh):
    """Affiche graphiquement un mesh.

    Args:
        my_mesh (Openmesh::mesh): Le mesh que l'on souhaite afficher.
    """
    vertices = np.array([my_mesh.point(v) for v in my_mesh.vertices()])
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    faces = []
    for f in my_mesh.faces():
        faces.append([v.idx() for v in my_mesh.fv(f)])
    
    mesh_faces = Poly3DCollection([vertices[face] for face in faces], linewidths=1, edgecolors='r', alpha=1.0)


    ax.add_collection3d(mesh_faces)


    ax.set_axis_off()
    ax.set_title("Maillage 3D")


    ax.set_xlim([np.min(vertices[:, 0]), np.max(vertices[:, 0])])
    ax.set_ylim([np.min(vertices[:, 0]), np.max(vertices[:, 0])])
    ax.set_zlim([np.min(vertices[:, 0]), np.max(vertices[:, 0])])
    
    ax.set_aspect('auto')
    plt.show()

# Credits for bunny and teapot and torus : gaschler (github)
