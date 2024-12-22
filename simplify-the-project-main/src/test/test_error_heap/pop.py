import os
import sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../')))

import main.error_heap as err_h
import main.acquisition as acq
import main.affiche_mesh as am
import openmesh as om
import random as rd

mesh = acq.acquire("../../main/torus.off")
heap = err_h.ErrorHeap()
list_err = []
for fv in mesh.halfedges():
    erreur = rd.random()
    list_err.append(erreur)
    # edge = [erreur, fv]
    heap.push(erreur)

root = heap.pop()
assert (min(list_err) == root)