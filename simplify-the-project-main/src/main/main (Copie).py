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
    key_min=np.nan
    list_a_suprime=[]
    k_current=err_h.ErrorHeap()
    for l,k in my_dict.items():
        if not k.is_empty():
            mini=k.top()
            error_mini=np.nanmin([error,mini[0]])
            if error_mini!=error:
                error=error_mini
                composant_min=mini
                key_min=l
                k_current=k.heap
                
        else:
            list_a_suprime.append(l)

    for k in list_a_suprime:
        del my_dict[k]
    
    
    #print("la clé du min renvoyé est ",key_min)
    #print("la heap associe est ", k_current)
    
    return composant_min
            



def main():
    if (len(sys.argv) != 2):
        raise Exception(f"1 argument attendu, {len(sys.argv)-1} ont été donné(s).")
    else:
        my_file = sys.argv[1]
        mesh = acq.acquire(my_file)
        meshman.generate_colors(mesh)
        print("voici à quoi ressemble le mesh avant la simplification")
        am.affiche_mesh(mesh)
        
        mon_dic_d_indice=defaultdict(err_h.ErrorHeap)

        #On a un problème on parcours toutes la head pour retrouver l'indice des points
        # qui sont adjacents aux points qui vont subir le edge collapse.
        # Pas de différence avec un parcours de toute la liste du Heap, on peut sans doute 
        # profiter de la structure pour avoir une recherche plus facile.
        # par exemple créer un dictionnaire stockant l'état courant d'un point dans la Heap.
        
        #print("on commence à mettre tous les halfedges")
        
        #nombre_edge=0
        
        for fv in mesh.halfedges():
            first_point=mesh.from_vertex_handle(fv)
            second_point=mesh.to_vertex_handle(fv)
            erreur=err.error(mesh,first_point,second_point)
            l=[erreur,fv,first_point,second_point]
            hash1=str(mesh.point(first_point))
            hash2=str(mesh.point(second_point))
            mon_dic_d_indice[hash1].push(l)
            mon_dic_d_indice[hash2].push(l)
            
            #nombre_edge+=1

        #print("On a fini de mettre tous les halfedge dans le dict")
        
        iterator=0
        
        #print("nombre de vertex",len(mon_dic_d_indice))
        #print("nombre d'arête", nombre_edge)

        composant_min=minimun_dict(mon_dic_d_indice)
         
        
        while composant_min is not np.nan:
            #print("composant_mini1",composant_min)
            current_halfedge=composant_min[1]
            v1=composant_min[2]
            v2=composant_min[3]
            
            mesh.collapse(current_halfedge)
            
            point_mis_a_jour=[]
            hash1=str(mesh.point(v1))
            hash2=str(mesh.point(v2))
            #mon_dic_d_indice[hash1].pop()
            
            #print("le dic du sommet à détruire",mon_dic_d_indice[hash1].heap)
            
            #print("taille avant le parcours du sommet à détruire",len(mon_dic_d_indice))
            
            
            
            
            while not mon_dic_d_indice[hash1].is_empty():

                list_ =mon_dic_d_indice[hash1].pop()
                
                error_,k =  list_[0],list_[1]
                
                point_debut=list_[3]
                
                if point_debut!=v1:
                    point_etudie=point_debut
                
                else:
                    point_etudie=list_[2]   
                
                if point_etudie not in point_mis_a_jour:
                    
                    point_mis_a_jour.append(point_etudie)
                    
                    hashetudiee=str(mesh.point(point_etudie))
                    heap_etudie=mon_dic_d_indice[hashetudiee]
                    
                    
                    
                    Heap_de_rechange=err_h.ErrorHeap()
                    
                    while not heap_etudie.is_empty():
                        
                        list_renvoye=heap_etudie.pop()
                        
                        error_,j=list_renvoye[0],list_renvoye[1]
                        
                        point1=list_renvoye[2]
                        
                        if point1!=point_etudie:
                            point_adjacent=point1
                            
                            if point_adjacent!=v1:
                                erreur=err.error(mesh,point_adjacent,point_etudie)
                                list_renvoye[0]=erreur
                                Heap_de_rechange.push(list_renvoye)
                        
                        else:
                            point_adjacent=list_renvoye[3]
                            
                            if point_adjacent!=v1:
                                erreur=err.error(mesh,point_etudie,point_adjacent)
                                list_renvoye[0]=erreur
                                Heap_de_rechange.push(list_renvoye)
                        
                    mon_dic_d_indice[hashetudiee]=Heap_de_rechange
            
            
            del mon_dic_d_indice[hash1]            
            
            hash2=str(mesh.point(v2))
            
            #print("taille après parcours du vertice à detruire",len(mon_dic_d_indice)) 
            
            ma_liste_=err_h.ErrorHeap()

            while not mon_dic_d_indice[hash2].is_empty():
                list_ =mon_dic_d_indice[hash2].pop()

                point_debut=list_[2]
                point_fin=list_[3]
                
                if point_debut!=v1 and point_fin !=v1:
                    
                    if point_debut!=v2:
                        point_etudie=point_debut
                    
                    else:
                        point_etudie=point_fin
                    
                    if point_etudie not in point_mis_a_jour:
                    
                        point_mis_a_jour.append(point_etudie)
                    
                        hashetudiee=str(mesh.point(point_etudie))
                        
                        heap_etudie=mon_dic_d_indice[hashetudiee]
                    
                    
                        Heap_de_rechange=err_h.ErrorHeap()
                        
                        while not heap_etudie.is_empty():
                        
                            list_renvoye=heap_etudie.pop()
                            error_,j =list_renvoye[0],list_renvoye[1]
                        
                            point1=list_renvoye[2]
                        
                            if point1!=point_etudie:
                                point_adjacent=point1
                            
                                if point_adjacent!=v1:
                                    erreur=err.error(mesh,point_adjacent,point_etudie)
                                    list_renvoye[0]=erreur
                                    Heap_de_rechange.push(list_renvoye)
                            
                            else:
                                point_adjacent=list_renvoye[3]
                        
                                if point_adjacent!=v1:
                                    erreur=err.error(mesh,point_etudie,point_adjacent)
                                    list_renvoye[0]=erreur
                                    Heap_de_rechange.push(list_renvoye)
                            
                        mon_dic_d_indice[hashetudiee]=Heap_de_rechange                    
                
                    ma_liste_.push(list_)
            
            mon_dic_d_indice[hash2]=ma_liste_

            if ma_liste_.is_empty():
                del mon_dic_d_indice[hash2]
            
            
            
            
            #print("taille après le parcours de sommet contracté",len(mon_dic_d_indice))
            
            #print("\n")
            
            

            #print("on supprime les éléments du dictionnaire")
            #print("\n")
            
            
         
 



            #print(f"iterator :  {iterator}")
            #for l,v in mon_dic_d_indice.items():
                #print(f"key {l}: {len(v.heap)}")
            
            #print("\n")
            
            #print("le hashage etudié", mon_dic_d_indice[hash1].heap)
            

                                  
            composant_min=minimun_dict(mon_dic_d_indice)
            
            #print(len(mon_dic_d_indice))
            
            
            
            
            
            
            
                        
            iterator+=1
            
    return mesh            
            
if __name__ == "__main__":
    my_mesh=main()
    #nombre_vertex_fin=0
    #nombre_edge_fin=0

    #for v in my_mesh.vertices():
        #nombre_vertex_fin+=1
    #for fv in my_mesh.halfedges():
        #nombre_edge_fin+=1
    
    am.affiche_mesh(my_mesh)    
    #print("nombre de vertex après simplification",nombre_vertex_fin)
    #print("nombre de edge après simplification",nombre_edge_fin)

