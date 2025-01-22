import openmesh as om
import sys
import time

import acquisition as acq
import affiche_mesh as am
import error_heap as err_h
import errors as errs
import mesh_manipulation as mm

# Credits for bunny.off and teapot.off : gaschler (github)


def simplify(mesh, heap, threshold):
    """Fonction effectuant la simplification du mesh.

    Args:
        mesh (Mesh): Mesh à simplifier.
        heap (ErrorHeap): Tas des coûts des half-edge collapses.
    
    Returns:
        Mesh: Le mesh simplifié.
    """
    
    while not heap.is_empty():
        # Extraire le half-edge avec le coût minimum
        error, he = heap.pop()

        if error > threshold:
            break

        # Vérifier si le collapse est possible
        if mm.is_collapse_possible(mesh, he):
            # Collapse du half-edge
            mesh.collapse(he)

            # Mettre à jour les coûts des half-edges affectés
            affected_halfedges = []
            for vh in [mesh.from_vertex_handle(he), mesh.to_vertex_handle(he)]:
                for outgoing_he in mesh.voh(vh):  # Voisins par half-edge
                    if outgoing_he not in affected_halfedges:
                        affected_halfedges.append(outgoing_he)

            for affected_he in affected_halfedges:
                if mm.is_collapse_possible(mesh, affected_he):
                    v0 = mesh.from_vertex_handle(affected_he)
                    v1 = mesh.to_vertex_handle(affected_he)
                    new_error = errs.error(mesh, v0, v1)
                    heap.push([new_error, affected_he])

    # Nettoyer les données obsolètes
    mesh.garbage_collection()

    return mesh

def main():
    mesh = acq.acquire(sys.argv[1])

    print("Mesh avant simplification")
    am.affiche_mesh(mesh)
    
    nv1, ne1 = am.comparison_simplification(mesh, True)


    # TODO : simplification
    # 1st step : attribuer les couleurs.
    mm.generate_colors(mesh)
    # 2nd step : créer le tas.
    heap = err_h.ErrorHeap()
    errors_list = []
    for he in mesh.halfedges():
        if mm.is_collapse_possible(mesh, he):
            v0 = mesh.from_vertex_handle(he)
            v1 = mesh.to_vertex_handle(he)
            error = errs.error(mesh, v0, v1)
            errors_list.append(error)
            elt_heap = [error, he]
            heap.push(elt_heap)
    
    errors_list.sort()
    threshold = errors_list[len(errors_list)//2] # Médiane des erreurs
    print(threshold)
    
    # 3rd step : effectuer la simplification.
    start_simplification_time = time.time()
    
    simplified_mesh = simplify(mesh, heap, threshold)

    end_simplification_time = time.time()        

    # Sauvegarder ou visualiser le résultat
    om.write_mesh(f"results/simplified_{sys.argv[1]}", simplified_mesh)

    print("Mesh après simplification")
    am.affiche_mesh(simplified_mesh)
    nv2, ne2 = am.comparison_simplification(simplified_mesh, True)
    am.ratio_simplification(nv1, nv2, ne1, ne2)
    
    time_exec = round(end_simplification_time - start_simplification_time, 3)
    print("Temps d'exécution de la simplification :", time_exec, "s")


if __name__ == '__main__':
    main()