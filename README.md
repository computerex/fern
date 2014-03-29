Fern
====

The program renders the barnsley fern in OpenGL using glut. 
The color for each point is calculated in the computePoints 
method:
// rgb 
scheme.push_back(abs(cos(point.x)+rand()%255/255.));
scheme.push_back(0);
scheme.push_back(abs(sin(point.y*point.x)+rand()%255/255.));

