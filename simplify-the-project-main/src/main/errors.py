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

def Q(mesh,v0,v1):
    """Calcule l'erreur quadric d'un half-edge.
    Args:
        v0 (Vertex): Premier sommet
        v1 (Vertex): Second sommet

    Returns:
        float: l'erreur quadric de la contraction de l'arête orientée

    """

    "On récupère les deux vertices de l'halfedge"
    first_vertex= v0
    second_vertex=v1
    

    "On retranscrit les 2 arêtes en points et on initialise le point considéré à celui du point vers lequel point la demi arête"
    point_first_vertex=mesh.point(first_vertex)
    
    
    point_second_vertex=mesh.point(second_vertex)
    
    v_considéré=point_second_vertex

    "On initialise l'erreur à 0"
    res_tot=0
    
    " On récupère l'ensemble des faces adjacentes des 2 points " 
    first_vertex_adjacent_face=meshman.get_faces(mesh,first_vertex)
    second_vertex_adjacent_face=meshman.get_faces(mesh,second_vertex)
   
    "On calcule d'erreur sur chaque face adjacente de la première arête que l'on applique au v considéré "
    for fh in first_vertex_adjacent_face:

        verticesList=meshman.get_3_vertices_of_a_face(mesh,fh)
        e1_transpose=(verticesList[1]-verticesList[0])
        if (np.linalg.norm(e1_transpose) != 0):
            e1_transpose=e1_transpose/np.linalg.norm(e1_transpose)
        e1=e1_transpose.reshape(3,1)
        e2_transpose=(verticesList[2]-verticesList[0])
        e2_transpose=e2_transpose-np.dot(e1_transpose,e2_transpose)*e1_transpose
        if (np.linalg.norm(e2_transpose) != 0):
            e2_transpose=e2_transpose/np.linalg.norm(e2_transpose)
        e2=e2_transpose.reshape(3,1)
        n=len(e1)

        A=np.identity(n) - np.matmul(e1,np.transpose(e1)) - np.matmul(e2,np.transpose(e2))
        b=np.dot(verticesList[0],e1_transpose)*e1_transpose + np.dot(verticesList[0],e2_transpose)*e2_transpose-verticesList[0]
        c=np.dot(verticesList[0],verticesList[0])-(np.dot(verticesList[0],e1_transpose))**2-(np.dot(verticesList[1],e2_transpose)**2)
        res=np.matmul(np.matmul(np.transpose(v_considéré),A),v_considéré)+2*np.dot(b,v_considéré)+c
        res_tot+=res
         
    "On fait de même pour les faces adjacentes de la seconde arête" 
                                                                                   
    for fh in second_vertex_adjacent_face: 
        
        verticesList=meshman.get_3_vertices_of_a_face(mesh,fh)                                                                            
        e1_transpose=(verticesList[1]-verticesList[0])
        if (np.linalg.norm(e1_transpose) != 0):
            e1_transpose=e1_transpose/np.linalg.norm(e1_transpose)
        e1=e1_transpose.reshape(3,1)
        e2_transpose=(verticesList[2]-verticesList[0])
        e2_transpose=e2_transpose-np.dot(e1_transpose,e2_transpose)*e1_transpose
        if (np.linalg.norm(e2_transpose) != 0):
            e2_transpose=e2_transpose/np.linalg.norm(e2_transpose)
        e2=e2_transpose.reshape(3,1)
        n=len(e1)

        A=np.identity(n) - np.matmul(e1,np.transpose(e1)) - np.matmul(e2,np.transpose(e2))
        b=np.dot(verticesList[0],e1_transpose)*e1_transpose + np.dot(verticesList[0],e2_transpose)*e2_transpose-verticesList[0]
        c=np.dot(verticesList[0],verticesList[0])-(np.dot(verticesList[0],e1_transpose))**2-(np.dot(verticesList[1],e2_transpose)**2)
        res=np.matmul(np.matmul(np.transpose(v_considéré),A),v_considéré)+2*np.dot(b,v_considéré)+c

        res_tot+=res

    "On retourne le résultat total"

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
