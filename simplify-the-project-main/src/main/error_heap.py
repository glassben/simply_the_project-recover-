# import openmesh as om
# import errors as err
# import acquisition as acq
import heapq as hq

class ErrorHeap:
    def __init__(self):
        """Initialise le tas."""
        self.heap = []
        
    def is_empty(self):
        """Vérifie si un tas est vide ou non.

        Returns:
            Bool: Booléen valant True si et seulement si le tas est vide.
        """
        return self.heap == []
 
    def push(self, edge):
        """Ajoute un élément dans le tas, tout en conservant l'intégrité du tas.

        Args:
            edge (List[Float,autre_extremité, HalfEdge]): Une liste contenant le coût du half-edge collapse, et le half-edge collapse.
        """
        hq.heappush(self.heap, edge)
    
    def pop(self):
        """Supprime et renvoie la racine du tas.

        Raises:
            IndexError: Si le tas est vide.

        Returns:
            Float: Le coût minimal sauvegardé dans le tas.
        """
        if (self.heap == []):
            raise IndexError("Le tas est vide.")
        m = hq.heappop(self.heap)
        return m
    
    def top(self):
        """Renvoie la racine du tas sans la supprimer.

        Raises:
            IndexError: Si le tas est vide.

        Returns:
            Float: Le coût minimal sauvegardé dans le tas.
        """
        if not self.heap:
            raise IndexError("Heap is empty.")
        return self.heap[0]

    
    def __str__(self):
        """Affiche le tas.

        Returns:
            String: La liste sous forme de chaîne de caractère, pour pouvoir la print.
        """
        return str(self.heap)