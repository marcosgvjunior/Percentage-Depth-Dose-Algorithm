# Percentage-Depth-Dose-Algorithm

**Algorithm to obtain the percentage dose depth from phase space values obtained from a simulation with GEANT4.**

To see the math formulas, one could add the Chrome extension MathJax Plugin for Github: https://chrome.google.com/webstore/detail/github-with-mathjax/ioemnmodlmafdkllaclgeombjnmnbima

A ROOT file was used as the output of the simulation [1]. In this file, information such as position and deposited energy of each particle were saved. The algorithm was implemented after the use of the MakeClass method [2], with the steps described here present in the Analysis.C file, mainly after the condition in line 88 and also in the use of the spherecenter function, at line 171.

Below I briefly explain the logic used in the implementation of the code to obtain the values for the percentage dose depth curve. The algorithm was used for 3 different values of radius of spheres along the transverse axis. Then, a small variation was made to obtain the curve on the longitudinal axis, setting the depth at 1.5 cm.

The algorithm can be divided into 3 fundamental parts:

- Use of the equation of a sphere to associate the deposit positions within the respective volumes;

- Determination of each sphere center position from depth continuous values;

- Indexing the centers values in vectors (index, dose).

First, some conditions were established in a way to only consider energy deposits inside a parallelepiped with a square cross section and side equal to the diameter of the largest sphere. In this way, it was not necessary to evaluate the dose values outside the volumes of the spheres of interest. Then, two ways of obtaining the position $ p $ of the spheres center from the depth values $ y $ were verified empirically. The first one was by:

$$ p = r \left( \left\lceil \frac{y}{2 r} \right\rceil + \left\lfloor \frac{y}{2 r} \right\rfloor \right)\text{ ,} \tag{1} $$ where $ r $ is the sphere radius, $ \lceil \rceil $ is the ceiling of the value and $ \lfloor \rfloor $ is the floor of the value. The other one was by:

$$ p = \left\lfloor \frac{y}{r} \right\rfloor r\text{ .} \tag{2} $$ 

I've tried to obtain equation (2) from equation (1), but I was unsuccessful. Either way, the two methods are equivalent, with (1) being used in the code.

Once the coordinate of the sphere's center was obtained, it was possible to restrict deposits to those within the sphere's volume, no longer in a square cross section. This was done with:

$$ x^2 + (y-p)^2 + z^2 = r^2 \tag{3} $$ where the $ x $ and $ z $ values corresponds to the dimensions in the radiation field plane.

For the last item I could have used map [3] to store the elements, with the values already being saved as a relation (center, dose), but at the time I still didn't know about this possibility. Thus, it was done through the equation of the general term of a arithmetic progression, isolating the term $ n $ in the form:

$$ n = \frac{p_n + r}{2 r} \tag{4} $$ where $ p_n $ is the n-th depht of the sequence, $ 2 r $ is both the diameter of the spheres and the progression ratio, since the spheres in the sequence are tangent.

I hope that the algorithm logic can be useful to others too. For me, it was a curious way of obtaining the centers's positions and a think it could be applied in others cases where discrete positions are needed from continuous values.

[1] - https://root.cern.ch/root/html534/guides/users-guide/InputOutput.html  
[2] - https://root.cern.ch/root/htmldoc/guides/users-guide/Trees.html#using-ttreemakeclass  
[3] - http://www.cplusplus.com/reference/map/map/  
