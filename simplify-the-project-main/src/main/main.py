import acquisition as acq
import affiche_mesh as am
import error_heap as err_h
import errors as err
import mesh_manipulation as meshman
from collections import defaultdict
import numpy as np
import sys


def minimun_dict(my_dict):
    error=np.nan
    composant_min=np.nan
    for k in my_dict.values():
        if k.heap!=[]:
            mini=k.top()
            error_mini=np.nanmin([error,mini[0]])
            if error_mini!=error:
                error=error_mini
                composant_min=mini
    return composant_min
            



def main():
    if (len(sys.argv) != 2):
        raise Exception(f"1 argument attendu, {len(sys.argv)-1} ont été donné(s).")
    else:
        my_file = sys.argv[1]
        mesh = acq.acquire(my_file)
        meshman.generate_colors(mesh)
        #am.affiche_mesh(mesh)
        
        mon_dic_d_indice=defaultdict(err_h.ErrorHeap)

        #On a un problème on parcours toutes la head pour retrouver l'indice des points
        # qui sont adjacents aux points qui vont subir le edge collapse.
        # Pas de différence avec un parcours de toute la liste du Heap, on peut sans doute 
        # profiter de la structure pour avoir une recherche plus facile.
        # par exemple créer un dictionnaire stockant l'état courant d'un point dans la Heap.
        
        print("on commence à mettre tous les halfedges")
        
        for fv in mesh.halfedges():
            first_point=mesh.from_vertex_handle(fv)
            second_point=mesh.to_vertex_handle(fv)
            erreur=err.error(mesh,first_point,second_point)
            l=[erreur,fv]
            hash1=str(mesh.point(first_point))
            hash2=str(mesh.point(second_point))
            mon_dic_d_indice[hash1].push(l)
            mon_dic_d_indice[hash2].push(l)

        print("On a fini de mettre tous les halfedge dans le dict")
        
        composant_min=minimun_dict(mon_dic_d_indice)
        
        while composant_min!=np.nan:
            
            current_halfedge=composant_min[1]
            v1=mesh.to_vertex_handle(current_halfedge)
            v2=mesh.from_vertex_handle(current_halfedge)
            mesh.collapse(current_halfedge)
            
            point_mis_a_jour=[]
            hash1=str(mesh.point(v1))
            
            for k in mon_dic_d_indice[hash1].heap:
                point_debut=mesh.from_vertex_handle(k[1])
                
                if point_debut!=v1:
                    point_etudie=point_debut
                else:
                    point_etudie=mesh.to_vertex_handle(k[1])   
                
                if point_etudie not in point_mis_a_jour:
                    point_mis_a_jour.append(point_etudie)
                    
                    hashetudiee=str(mesh.point(point_etudie))
                    heap_etudie=mon_dic_d_indice[hashetudiee]
                    
                    for i,j in enumerate(heap_etudie.heap):
                        point1=mesh.from_vertex_handle(j[1])
                        
                        if point1!=point_etudie:
                            point_adjacent=point1
                            if point_adjacent==v1:
                                del heap_etudie.heap[i]
                                heap_etudie.reorganise_heap_down(i)
                            else:
                                erreur=err.error(mesh,point_adjacent,point_etudie)
                                heap_etudie.heap[i][0]=erreur
                                heap_etudie.reorganise_heap_up(i)
                        
                        else:
                            point_adjacent=mesh.to_vertex_handle(j[1])
                            if point_adjacent==v1:
                                del heap_etudie.heap[i]
                                heap_etudie.reorganise_heap_down(i)
                            else:
                                erreur=err.error(mesh,point_etudie,point_adjacent)
                                heap_etudie.heap[i][0]=erreur
                                heap_etudie.reorganise_heap_up(i)
            
            
            hash2=str(mesh.point(v2))
            
            for k in mon_dic_d_indice[hash2].heap:
                point_debut=mesh.from_vertex_handle(k[1])
                
                if point_debut!=v2:
                    point_etudie=point_debut
                else:
                    point_etudie=mesh.to_vertex_handle(k[1])
                    
                if point_etudie not in point_mis_a_jour:
                    point_mis_a_jour.append(point_etudie)
                    
                    hashetudiee=str(mesh.point(point_etudie))
                    heap_etudie=mon_dic_d_indice[point_etudie]
                    
                    for i,j in enumerate(heap_etudie.heap):
                        point1=mesh.from_vertex_handle(j[1])
                        
                        if point1!=point_etudie:
                            point_adjacent=point1
                            
                            if point_adjacent==v1:
                                del heap_etudie.heap[i]
                                heap_etudie.reorganise_heap_down(i)
                            else:
                                erreur=err.error(mesh,point_adjacent,point_etudie)
                                heap_etudie.heap[i][0]=erreur
                                heap_etudie.reorganise_heap_up(i)
                            
                        else:
                            point_adjacent=mesh.to_vertex_handle(j[1])
                        
                            if point_adjacent==v1:
                                del heap_etudie.heap[i]
                                heap_etudie.reorganise_heap_down(i)
                            else:
                                erreur=err.error(mesh,point_etudie,point_adjacent)
                                heap_etudie.heap[i][0]=erreur
                                heap_etudie.reorganise_heap_up(i)                    
            
            
            print("on supprime les éléments du dictionnaire")
            del mon_dic_d_indice[hash1]
            composant_min=minimun_dict(mon_dic_d_indice)
            
            
if __name__ == "__main__":
    main()
