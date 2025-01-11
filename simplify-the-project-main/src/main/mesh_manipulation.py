import acquisition as acq
import openmesh as om
import numpy as np

def courbure(mesh, v): # Courbure = permet de déterminer les zones importantes à conserver.
    """Calcule la courbure gaussienne en un sommet v.

    Args:
        mesh (Mesh): Maillage auquel appartient le sommet v.
        v (Vertex): Sommet du maillage

    Returns:
        Float: Courbure gaussienne en un sommet v.
    """
    A_v = 0
    sum_theta = 0
    
    # Parcours faces incidentes
    for he_incident in mesh.vih(v): # Demi-arêtes incidentes
        f1 = mesh.face_handle(he_incident)
        
        he_opposite = mesh.opposite_halfedge_handle(he_incident)
        f2 = mesh.face_handle(he_opposite)
        
        n1, n2 = mesh.calc_face_normal(f1), mesh.calc_face_normal(f2)
        
        theta_vh = np.arccos(np.dot(n1, n2))
        
        sum_theta += theta_vh
        
        # Calcul de l'aire barycentrique
        [p0, p1, p2] = [mesh.point(vh) for vh in mesh.fv(f1)]
        A_v += 0.5 * np.linalg.norm(np.cross((p1 - p0), (p2 - p0))) # Aire d'un triangle défini par des vecteurs.
    
    if (A_v < 1e-5):
        return 2*np.pi
    curv_v = 1/A_v * (2*np.pi - sum_theta) 
    curv_v /= 10
    if (curv_v > 1.0):
        curv_v = 1.0
    if (curv_v < 0.0):
        curv_v = 0.0
    return curv_v

def generate_colors(mesh):
    """Génère des couleurs pour les sommets du maillage.

    Args:
        mesh (Mesh): Maillage concerné.
    """
    for v in mesh.vertices():
        curv_v = courbure(mesh, v)
        color_v = [curv_v, 1 - curv_v, 0.5, 1.0] # Zones plates : bleu, zones avec une forte courbure : rouge.
        mesh.set_color(v, color_v)


def get_neighbors(mesh, v):
    """Permet d'obtenir les voisins d'un sommet du mesh.

    Args:
        mesh (Mesh): Maillage dans lequel se trouve le sommet.
        v (Vertex): Sommet dont on veut les voisins.

    Returns:
        IndicesList: Liste des indices des voisins de v.
    """
    neighbors = []
    for vi in mesh.vv(v):
        neighbors.append(vi.idx())
    return neighbors


def get_faces(mesh,v):
    """Permet d'obtenir les faces voisines d'un vertex.
    Args:
         mesh (Mesh): Maillage dans lequel se trouve le sommet.
         v (Vertex): Sommet dont on veut les voisins.
    Returns:
        FaceList: Liste  des faces voisiness de v

    """
    neighbors=[]
    for fh in mesh.vf(v):
        neighbors.append(fh)
    return neighbors

def get_3_vertices_of_a_face(mesh,f):
    """Permet d'avoir 2 vertices d'une même, ce qui sera utile pour 
    la création de normale grâce à gram schmidt pour calculer l'erreur Quadric"
    Args:
       mesh(Mesh): Maillage dans lequel se trouve le sommet.
       f (Face) : Face à partir de laquelle on selectionne 2 vertices 
    Returns:
        verticesLis : Liste de 2 vertices appartenant au sommet.
    """
    iterator=mesh.fv(f)
    point1=mesh.point(next(iterator))
    point2=mesh.point(next(iterator))
    point3=mesh.point(next(iterator))
    verticesList=[point1,point2,point3]
    return verticesList


# Conditions pour faire un collapse

def is_mesh_vertex_boundary(mesh, he):
    """Détermine si au moins un sommet d'une semi-arête d'un maillage est au bord.

    Args:
        mesh (Mesh): Maillage considéré.
        he (HalfEdge): Semi-arête considérée.
    
    Returns:
        Bool: Vaut True si et seulement si un des sommets de la semi-arête est au bord du maillage.
    """
    v0 = mesh.from_vertex_handle(he)
    v1 = mesh.to_vertex_handle(he)
    return mesh.is_boundary(v0) or mesh.is_boundary(v1)

# def is_strong_curvature(mesh, he, threshold=0.5):
#     """Détermine si les courbures entre les deux extrémités d'une semi-arête dépasse un certain seuil.

#     Args:
#         mesh (Mesh): Maillage considéré.
#         he (HalfEdge): Semi-arête considérée.
#         threshold (Float): Seuil de courbure.
    
#     Returns:
#         Bool: Vaut True si et seulement si la différence de courbure dépasse le seuil.
#     """
#     v0 = mesh.from_vertex_handle(he)
#     v1 = mesh.to_vertex_handle(he)
#     delta_curv = abs(courbure(mesh, v0) - courbure(mesh, v1))
#     return delta_curv > threshold


def is_collapse_possible(mesh, he):
    """Détermine si un collapse est possible ou non.

    Args:
        mesh (Mesh): Maillage où l'on souhaite effectuer un collapse.
        he (HalfEdge): Semi-arête à collapse.
    
    Returns:
        Bool: Vaut True si et seulement si le collapse est possible.
    """
    cond_boundary_vertex = not is_mesh_vertex_boundary(mesh, he)
    cond_boundary = not mesh.is_boundary(he)
    # cond_curvature = not is_strong_curvature(mesh, he)
    cond_final = mesh.is_collapse_ok(he)
    
    return cond_boundary_vertex and cond_boundary and cond_final