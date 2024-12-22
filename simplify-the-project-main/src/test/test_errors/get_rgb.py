import os
import sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../')))

import main.errors as errs
import main.acquisition as acq
import main.affiche_mesh as am

mesh = acq.acquire("../../main/my_file.off")
errs.meshman.generate_colors(mesh)
am.print_mesh(mesh)

rgb_0 = errs.get_rgb(mesh, mesh.vertices()[0])

assert (len(rgb_0) == 3)
assert (rgb_0 == [0.0, 1.0, 0.5])