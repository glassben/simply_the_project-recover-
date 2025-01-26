import openmesh as om
import sys
import time

import acquisition as acq
import affiche_mesh as am
import error_heap as err_h
import errors as errs
import mesh_manipulation as mm

import statistics
import concurrent.futures

# Credits for bunny.off and teapot.off : gaschler (github)


def simplify(mesh, heap, threshold):
    """Simplifie le maillage en appliquant des collapses de half-edges sous un certain seuil.

    Args:
        mesh (Mesh): Mesh à simplifier.
        heap (ErrorHeap): Tas des coûts des half-edge collapses.
        threshold (float): Seuil d'erreur pour arrêter la simplification.
    
    Returns:
        Mesh: Le mesh simplifié.
    """
    while not heap.is_empty():
        # Extraire le half-edge avec le coût minimum
        error, he = heap.pop()

        # Si l'erreur dépasse le seuil, on arrête
        if error > threshold:
            break

        # Vérifier si le collapse est possible
        if mm.is_collapse_possible(mesh, he):
            # Collapse du half-edge
            mesh.collapse(he)

            # Mise à jour des half-edges affectés
            affected_halfedges = {}
            vertices = [mesh.from_vertex_handle(he), mesh.to_vertex_handle(he)]
            
            for vh in vertices:
                # Récupérer tous les voisins du sommet `vh`
                for outgoing_he in mesh.voh(vh):
                    # Ajout des half-edges affectés
                    affected_halfedges[outgoing_he.idx()] = outgoing_he

            # Calculer les nouveaux coûts pour les half-edges affectés
            for affected_he in affected_halfedges.values():
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

    # 1ère étape : attribuer les couleurs.
    mm.generate_colors(mesh)
    
    # 2ème étape : créer le tas.
    heap = err_h.ErrorHeap()
    errors_list = []

    # Utilisation de concurrent.futures pour paralléliser le calcul des erreurs
    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = {}
        for he in mesh.halfedges():
            if mm.is_collapse_possible(mesh, he):
                v0 = mesh.from_vertex_handle(he)
                v1 = mesh.to_vertex_handle(he)
                future = executor.submit(errs.error, mesh, v0, v1)
                futures[future] = he
        
        for future in concurrent.futures.as_completed(futures):
            error = future.result()
            errors_list.append(error)
            elt_heap = [error, futures[future]]
            heap.push(elt_heap)
    
    threshold = statistics.median(errors_list)
    print(threshold)
    
    # 3ème étape : effectuer la simplification.
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