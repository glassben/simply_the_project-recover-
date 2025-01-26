import mesh_manipulation as meshman
import numpy as np



# Evaluation of Edge Cost

# Visual Importance for Vertex Color

def get_rgb(mesh, vi):
    """Permet d'obtenir le code RGB d'un sommet

    Args:
        mesh(Mesh): Maillage dans lequel se situe le sommet.
        vi (Vertex): Sommet dont on veut le code RGB.

    Returns:
        Vec3: Code RGB du sommet vi.
    """
    ci = mesh.color(vi)[:2]
    return ci

def rgb_dist(c0, ci):
    """Calcule la distance RGB entre deux sommets.

    Args:
        c0 (Vec3): Code RGB du sommet v0.
        ci (Vec3): Code RGB d'un sommet voisin vi.

    Returns:
        Float: La distance RGB entre v0 et vi.
    """
    return np.linalg.norm(c0 - ci)

def dist_max(mesh, v0):
    """Calcule la distance RGB max entre v0 et ses voisins.

    Args:
        mesh(Mesh): Maillage dans lequel se situe le sommet.
        v0 (Vertex): Sommet considéré.

    Returns:
        Float: La distance RGB max.
    """
    d_max = 0
    c0 = get_rgb(mesh, v0)
    neighbors_v0 = meshman.get_neighbors(mesh, v0)
    
    for index in neighbors_v0:
        vi = mesh.vertex_handle(index)
        ci = get_rgb(mesh, vi)
        d = rgb_dist(c0, ci)
        if (d > d_max):
            d_max = d
    return d_max

def Q(mesh, v0, v1):
    """
    Calcule l'erreur quadric d'un half-edge.

    Args:
        v0 (Vertex): Premier sommet
        v1 (Vertex): Second sommet

    Returns:
        float: L'erreur quadrique de la contraction de l'arête orientée
    """
    # Points associés aux sommets
    point_first_vertex = mesh.point(v0)
    point_second_vertex = mesh.point(v1)

    # Sommet considéré pour la contraction
    v_considered = point_second_vertex

    # Récupération des faces adjacentes aux deux sommets
    adjacent_faces = meshman.get_faces(mesh, v0) + meshman.get_faces(mesh, v1)

    # Initialisation de l'erreur totale
    res_tot = 0

    # Prétraitement pour éviter les recalculs
    identity_matrix = np.identity(3)

    for fh in adjacent_faces:
        # Récupération des sommets de la face
        vertices_list = meshman.get_3_vertices_of_a_face(mesh, fh)

        # Calcul des vecteurs e1 et e2 (et normalisation si nécessaire)
        e1_transpose = vertices_list[1] - vertices_list[0]
        e1_norm = np.linalg.norm(e1_transpose)
        if e1_norm > 0:
            e1_transpose /= e1_norm

        e2_transpose = vertices_list[2] - vertices_list[0]
        e2_transpose -= np.dot(e1_transpose, e2_transpose) * e1_transpose
        e2_norm = np.linalg.norm(e2_transpose)
        if e2_norm > 0:
            e2_transpose /= e2_norm

        # Conversion en matrices/vecteurs pour les calculs matriciels
        e1 = e1_transpose[:, np.newaxis]
        e2 = e2_transpose[:, np.newaxis]

        # Calcul des termes quadrics
        A = identity_matrix - e1 @ e1.T - e2 @ e2.T
        b = (
            np.dot(vertices_list[0], e1_transpose) * e1_transpose
            + np.dot(vertices_list[0], e2_transpose) * e2_transpose
            - vertices_list[0]
        )
        c = (
            np.dot(vertices_list[0], vertices_list[0])
            - np.dot(vertices_list[0], e1_transpose) ** 2
            - np.dot(vertices_list[0], e2_transpose) ** 2
        )

        # Calcul de l'erreur pour la face courante
        res = (
            np.dot(v_considered.T @ A, v_considered)
            + 2 * np.dot(b, v_considered)
            + c
        )
        res_tot += res

    return res_tot

def I(mesh, v0):
    """Calcule l'importance visuelle d'un sommet.

    Args:
        v0 (Vec3): Sommet considéré.
    
    Returns:
        float: L'importance visuelle de v0.
    """
    d_max = dist_max(mesh, v0)
    c0 = get_rgb(mesh,v0)
    
    if (d_max == 0):
        return 0
    
    s = 0
    neighbors_v0 = meshman.get_neighbors(mesh, v0)
    # Calcul du max des distances
    for index in neighbors_v0:
        vi = mesh.vertex_handle(index)
        ci = get_rgb(mesh,vi)
        s += rgb_dist(c0, ci)
    return s/d_max

# Collapse Color Error
def C(mesh, v0, v1):
    """Calcule la variation de couleur avant et après un Half-Edge collapse 

    Args:
        mesh (Mesh): Maillage auquel appartient le sommet.
        v0 (Vertex): Sommet initial.
        v1 (Vertex): Sommet v0 après application du Half-Edge collapse.
    
    Returns:
        Float: La valeur de la variation.
    """
    c0, c1 = get_rgb(mesh, v0), get_rgb(mesh, v1)
    

    s = 0
    neighbors_v0 = meshman.get_neighbors(mesh, v0)
    v0_coordonne=mesh.point(v0)

    v1_coordonne=mesh.point(v1)

    
    for index in neighbors_v0:
        
        vi = mesh.vertex_handle(index)
        ci = get_rgb(mesh, vi)
        vi_coordonne=mesh.point(vi)

        first_term = np.linalg.norm(c0 - ci) * np.linalg.norm(v0_coordonne - vi_coordonne)

        second_term = np.linalg.norm(c1 - ci) * np.linalg.norm(v1_coordonne - vi_coordonne)

        s += abs(first_term - second_term)
    

    return s

def error(mesh, v0, v1):
    """Détermine le coût d'un half edge collapse entre deux sommets

    Args:
        mesh (Mesh): Maillage auquel appartiennent v0 et v1.
        v0 (Vertex): Premier sommet
        v1 (Vertex): Second sommet

    Returns:
        Float: Le coût de l'half edge collapse entre v0 et v1.
    """
    q = Q(mesh,v0,v1)
    visual_importance = I(mesh, v0)
    color_error = C(mesh, v0, v1)
    e = (1+q) * (1+visual_importance) * (1+color_error)
    return e
