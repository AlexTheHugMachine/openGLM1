#include "mesh.h"

/*!
\class Mesh mesh.h

\brief Core triangle mesh class.
*/


/*!
\brief Initialize the mesh to empty.
*/
Mesh::Mesh()
{
}

/*!
\brief Initialize the mesh from a list of vertices and a list of triangles.

Indices must have a size multiple of three (three for triangle vertices and three for triangle normals).

\param vertices List of geometry vertices.
\param indices List of indices wich represent the geometry triangles.
*/
Mesh::Mesh(const std::vector<Vector>& vertices, const std::vector<int>& indices) :vertices(vertices), varray(indices)
{
  normals.resize(vertices.size(), Vector::Z);
}

/*!
\brief Create the mesh.

\param vertices Array of vertices.
\param normals Array of normals.
\param va, na Array of vertex and normal indexes.
*/
Mesh::Mesh(const std::vector<Vector>& vertices, const std::vector<Vector>& normals, const std::vector<int>& va, const std::vector<int>& na) :vertices(vertices), normals(normals), varray(va), narray(na)
{
}

/*!
\brief Reserve memory for arrays.
\param nv,nn,nvi,nvn Number of vertices, normals, vertex indexes and vertex normals.
*/
void Mesh::Reserve(int nv, int nn, int nvi, int nvn)
{
  vertices.reserve(nv);
  normals.reserve(nn);
  varray.reserve(nvi);
  narray.reserve(nvn);
}

/*!
\brief Empty
*/
Mesh::~Mesh()
{
}

/*!
\brief Smooth the normals of the mesh.

This function weights the normals of the faces by their corresponding area.
\sa Triangle::AreaNormal()
*/
void Mesh::SmoothNormals()
{
  // Initialize 
  normals.resize(vertices.size(), Vector::Null);

  narray = varray;

  // Accumulate normals
  for (int i = 0; i < varray.size(); i += 3)
  {
    Vector tn = Triangle(vertices[varray.at(i)], vertices[varray.at(i + 1)], vertices[varray.at(i + 2)]).AreaNormal();
    normals[narray[i + 0]] += tn;
    normals[narray[i + 1]] += tn;
    normals[narray[i + 2]] += tn;
  }

  // Normalize 
  for (int i = 0; i < normals.size(); i++)
  {
    Normalize(normals[i]);
  }
}

/*!
\brief Add a smooth triangle to the geometry.
\param a, b, c Index of the vertices.
\param na, nb, nc Index of the normals.
*/
void Mesh::AddSmoothTriangle(int a, int na, int b, int nb, int c, int nc)
{
  varray.push_back(a);
  narray.push_back(na);
  varray.push_back(b);
  narray.push_back(nb);
  varray.push_back(c);
  narray.push_back(nc);
}

/*!
\brief Add a triangle to the geometry.
\param a, b, c Index of the vertices.
\param n Index of the normal.
*/
void Mesh::AddTriangle(int a, int b, int c, int n)
{
  varray.push_back(a);
  narray.push_back(n);
  varray.push_back(b);
  narray.push_back(n);
  varray.push_back(c);
  narray.push_back(n);
}

/*!
\brief Add a smmoth quadrangle to the geometry.

Creates two smooth triangles abc and acd.

\param a, b, c, d  Index of the vertices.
\param na, nb, nc, nd Index of the normal for all vertices.
*/
void Mesh::AddSmoothQuadrangle(int a, int na, int b, int nb, int c, int nc, int d, int nd)
{
  // First triangle
  AddSmoothTriangle(a, na, b, nb, c, nc);

  // Second triangle
  AddSmoothTriangle(a, na, c, nc, d, nd);
}

/*!
\brief Add a quadrangle to the geometry.

\param a, b, c, d  Index of the vertices and normals.
*/
void Mesh::AddQuadrangle(int a, int b, int c, int d)
{
  AddSmoothQuadrangle(a, a, b, b, c, c, d, d);
}

/*!
\brief Compute the bounding box of the object.
*/
Box Mesh::GetBox() const
{
  if (vertices.size() == 0)
  {
    return Box::Null;
  }
  return Box(vertices);
}

/*!
\brief Creates an axis aligned box.

The object has 8 vertices, 6 normals and 12 triangles.
\param box The box.
*/
Mesh::Mesh(const Box& box)
{
  // Vertices
  vertices.resize(8);

  for (int i = 0; i < 8; i++)
  {
    vertices[i] = box.Vertex(i);
  }

  // Normals
  normals.push_back(Vector(-1, 0, 0));
  normals.push_back(Vector(1, 0, 0));
  normals.push_back(Vector(0, -1, 0));
  normals.push_back(Vector(0, 1, 0));
  normals.push_back(Vector(0, 0, -1));
  normals.push_back(Vector(0, 0, 1));

  // Reserve space for the triangle array
  varray.reserve(12 * 3);
  narray.reserve(12 * 3);

  AddTriangle(0, 2, 1, 4);
  AddTriangle(1, 2, 3, 4);

  AddTriangle(4, 5, 6, 5);
  AddTriangle(5, 7, 6, 5);

  AddTriangle(0, 4, 2, 0);
  AddTriangle(4, 6, 2, 0);

  AddTriangle(1, 3, 5, 1);
  AddTriangle(3, 7, 5, 1);

  AddTriangle(0, 1, 5, 2);
  AddTriangle(0, 5, 4, 2);

  AddTriangle(3, 2, 7, 3);
  AddTriangle(6, 7, 2, 3);
}

/*!
 * \brief Create the mesh for a disk with a degree of detail
 * \param disk Mathematic disk which we want to generate the mesh
 * \param nbpoints Level of detail
 */
Mesh::Mesh(const class Disk& disk, int nbpoints)
{
    vertices.resize(nbpoints + 1);
    vertices[0] = disk.Center;

    float step = (2 * M_PI) / nbpoints;
    normals.push_back(disk.Up);

    for (int i = 0; i<nbpoints; i++)
    {
        double alpha = step * i;
        double x = disk.Center[0] + (disk.radius * cos(alpha));
        double y = disk.Center[1] + (disk.radius * sin(alpha));

        vertices[i+1] = Vector(x, y, (double)(0.0 + disk.Center[2]));
    }

    varray.reserve((nbpoints ) * 3);
    narray.reserve((nbpoints ) * 3);

    for (int k = 0; k < nbpoints; k++)
    {
        AddTriangle(0,1+k, 1+((k+1) % nbpoints) , 0); // 1+ pour gerer le decal du cengtre
    }
}

/*!
 * \brief Create the mesh for a cone with a degree of detail
 * \param cone Mathematic cone which we want to generate the mesh
 * \param nbpoints Level of detail
 */
Mesh::Mesh(const Cone& cone, int nbpoints)
{
    // Vertices
    vertices.resize(nbpoints + 2);
    vertices[0] = cone.Center;
    normals.push_back(Vector(0, 0, 1));

    float step = (2 * M_PI) / nbpoints;
    for (int i = 1; i <= nbpoints; i++)
    {
        double alpha = step * i;
        double x = cone.Center[0] + cone.radius * cos(alpha);
        double y = cone.Center[1] + cone.radius * sin(alpha);
        vertices[i] = Vector(x, y, (double)(0.0 + cone.Center[2]));
    }

    // Reserve space for the triangle array
    varray.reserve((nbpoints) * 3);
    narray.reserve((nbpoints) * 3);

    for (int k = 0; k < nbpoints; k++)
    {
        AddTriangle(0, 1+k, 1+((k+1) % nbpoints), 0);
    }

    // Scale to return Disk so its normal face downward.
    this->Scale(-1);

    // Add tip of Cone and triangles
    vertices[nbpoints+1] = Vector(cone.Center[0], cone.Center[1], cone.Center[2] + cone.height);

    for (int j = 0; j< nbpoints; j++)
    {
        //Create Triangle with the cone tip and the base (disk)
        //Triangle t(vertices[j], vertices[nbpoints+1], vertices[(j % nbpoints) + 1]);
        double alpha = step * j;
        double x = cone.Center[0] + cone.radius * cos(alpha);
        double y = cone.Center[1] + cone.radius * sin(alpha);

        Vector u = Vector(x, y, 0);
        Vector z = Vector(0, 0, 1);
        Vector n = u*cone.height + z*cone.radius;

        normals.push_back(n);
        AddSmoothTriangle(nbpoints+1,nbpoints+1/*astuce*/,1+j,1+j, 1+((j+1) % nbpoints) , 1+((j+1) % nbpoints));
    }
    normals.push_back(Vector(0, 0, 1)); //Sert pour approximer la normale du point du haut
}

/*!
 * \brief Create the mesh for a cylinder with a degree of detail
 * \param cylinder Mathematic cylinder which we want to generate the mesh
 * \param nbpoints Level of detail
 */
Mesh::Mesh(const Cylinder& cylinder, int nbpoints)
{
    vertices.resize((nbpoints+1)*2);
    vertices[0] = cylinder.Center;
    Vector Center2Z(0, 0, cylinder.height);
    Vector Center2 = Center2Z + cylinder.Center;

    vertices[nbpoints+1] = Center2;

    varray.reserve((nbpoints) * 6);
    narray.reserve((nbpoints) * 6);

    float step = (2 * M_PI) / nbpoints;
    normals.push_back(Vector(0, 0, 1));

    for (int i = 0; i<nbpoints; i++)
    {
        double alpha = step * i;
        double x1 = cylinder.Center[0] + (cylinder.radius * cos(alpha));
        double y1 = cylinder.Center[1] + (cylinder.radius * sin(alpha));

        vertices[i+1] = Vector(x1, y1, (double)(0.0 + cylinder.Center[2]));

        AddTriangle(0,1+i, 1+((i+1) % nbpoints) , 0); // 1+ pour gerer le decal du cengtre
    }

    //normals.push_back(Vector(0, 0, 1));
    for (int j = 0; j<nbpoints+1; j++)
    {
        double alpha = step * (j+nbpoints);
        double x2 = Center2[0] + (cylinder.radius * cos(alpha));
        double y2 = Center2[1] + (cylinder.radius * sin(alpha));

        vertices[j+2+nbpoints] = Vector(x2, y2, (double)(0.0 + Center2[2]));

        AddTriangle(nbpoints+1, 1+j+nbpoints, 2+((j+nbpoints) % nbpoints+nbpoints) , 0); // 1+ pour gerer le decal du cengtre
    }

    for (int k = 0; k<nbpoints+1; k++)
    {
        AddTriangle(k+nbpoints, 1+k+nbpoints, ((k +nbpoints)%nbpoints), 0);
        AddTriangle(k+1, (k%nbpoints)+(nbpoints+1), (k%nbpoints), 0);
    }
}

/*Mesh::Mesh(const Sphere& sphere, int nbpoints)
{

}*/
/*!
 * \brief Create the mesh for a sphere with a degree of detail
 * \param sphere Mathematic sphere which we want to generate the mesh
 * \param nbpoints Level of detail
 */
Mesh::Mesh(const Sphere& sphere, int nbpoints)
{
    //float deltaTheta = (2 * M_PI) * (nbpoints + 2); // + 2 To count the level of both poles.
    //float deltaPhi = M_PI * nbpoints;
    double deltaTheta = (2 * M_PI) / nbpoints;
    double deltaPhi = M_PI / nbpoints;
    float theta, phi;

    // Vertices
    vertices.resize((nbpoints * nbpoints) + 2); // div * div vertices + 2 poles.
    vertices[0] = Vector(sphere.center[0], sphere.center[1], sphere.center[2] + sphere.radius); // north pole
    //vertices[0] = Vector(center[0], center[1] + ray, center[2]); // north pole

    for (int j = 0; j < nbpoints; j++)
    {
        theta = deltaTheta * (j + 1);

        for(int i = 0; i < nbpoints; i++)
        {
            phi = deltaPhi * (i + 1);
            double x = sphere.center[0] + sphere.radius * (float)(sin(theta) * cos(phi));
            double y = sphere.center[1] + sphere.radius * (float)(sin(theta) * sin(phi));
            double z = sphere.center[2] + sphere.radius * (float)(cos(theta));
            vertices[(j * nbpoints) + (i + 1)] = Vector(x, y, z);

        }
    }
    //vertices[(div * div) + 1] = Vector(center[0], center[1] - ray, center[2]); // south pole
    vertices[(nbpoints * nbpoints) + 1] = Vector(sphere.center[0], sphere.center[1], sphere.center[2] - sphere.radius); // south pole


    // Reserve space for the triangle array ; base + cone triangle = 2*div
    varray.reserve((nbpoints * 2) * (nbpoints - 1) + (2 * nbpoints)); // div rings -> (div - 1) slices of (2 * div) Triangles + (2 * div) Triangles linking with poles
    narray.reserve((nbpoints * 2) * (nbpoints - 1) + (2 * nbpoints));

    // North Pole Triangles
    for (int k = 1; k <= nbpoints; k++)
    {
        Triangle t(vertices[k], vertices[0], vertices[(k % nbpoints) + 1]);
        normals.push_back(t.Normal());
        AddTriangle(k, 0, (k % nbpoints) + 1, k - 1);
    }
    // Sphere Triangles
    for (int m = 1; m < nbpoints; m++)
    {
        for (int n = 1; n < nbpoints; n++)
        {
            int ia = (m * nbpoints) + n;
            int ib = ((m - 1) * nbpoints) + n;
            int ic = ((m - 1) * nbpoints) + (n % nbpoints) + 1;
            int id = (m * nbpoints) + (n % nbpoints) + 1;

            Triangle abc(vertices[ia], vertices[ib], vertices[ic]);
            normals.push_back(abc.Normal());
            AddTriangle(ia, ib, ic, nbpoints + ((m - 1) * 2 * nbpoints) + (2 * (n - 1)));

            Triangle acd(vertices[ia], vertices[ic], vertices[id]);
            normals.push_back(acd.Normal());
            AddTriangle(ia, ic, id, nbpoints + ((m - 1) * 2 * nbpoints) + (2 * (n - 1)) + 1);
        }
    }
    // South Pole Triangle
    for (int o = 1; o <= nbpoints; o++)
    {
        int ia = ((nbpoints - 1) * nbpoints) + o;
        int ib = (nbpoints * nbpoints) + 1;
        int ic = ((nbpoints - 1) * nbpoints) + (o % nbpoints) + 1;
        Triangle t(vertices[ia], vertices[ib], vertices[ic]);
        normals.push_back(t.Normal());
        AddTriangle(ia, ib, ic, (nbpoints * 2) * (nbpoints - 1) + nbpoints - 1 + o);
    }
}

/*!
 * \brief Create the mesh for a tore with a degree of detail
 * \param tore Mathematic tore which we want to generate the mesh
 * \param nbpoints_radial Level of detail for the radial dimension
 * \param nbpoints_tubular Level of detail for the tubular dimension
 */
Mesh::Mesh(const Tore& tore, int nbpoints_radial, int nbpoints_tubular)
{
    /*vertices.resize(nbpoints_radial * nbpoints_tubular);
    varray.reserve(nbpoints_radial * nbpoints_tubular);
    narray.reserve(nbpoints_radial * nbpoints_tubular);
    for(int i=0; i<nbpoints_radial; i++)
    {
        for(int j=0; j<nbpoints_tubular; i++)
        {
            float u = (float)j / nbpoints_tubular * M_PI * 2.0;
            float v = (float)i / nbpoints_radial * M_PI * 2.0;
            float x = (tore.radius + tore.thickness * cos(v)) * cos(u);
            float y = (tore.radius + tore.thickness * cos(v)) * sin(u);
            float z = tore.thickness * sin(v);
            vertices[j] = Vector(x, y, z);
        }
    }

    for(int i=0; i<nbpoints_radial; i++)
    {
        int i_next = (i+1) % nbpoints_radial;
        for(int j = 0; j<nbpoints_tubular; j++)
        {
            int j_next = (j+1) % nbpoints_tubular;
            int i0 = i*nbpoints_tubular + j;
            int i1 = i*nbpoints_tubular + j_next;
            int i2 = i_next * nbpoints_tubular + j_next;
            int i3 = i_next * nbpoints_tubular + j;

        }
    }

    for(int k=0; k<nbpoints_radial; k++)
    {
        //AddTriangle(k, 0, (k%nbpoints_radial)+1, 0);
    }*/
}

/*!
\brief Scale the mesh.
\param s Scaling factor.
*/
void Mesh::Scale(double s)
{
    // Vertexes
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i] *= s;
    }

    if (s < 0.0)
    {
        // Normals
        for (int i = 0; i < normals.size(); i++)
        {
            normals[i] = -normals[i];
        }
    }
}



#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QRegularExpression>
#include <QtCore/qstring.h>

/*!
\brief Import a mesh from an .obj file.
\param filename File name.
*/
void Mesh::Load(const QString& filename)
{
  vertices.clear();
  normals.clear();
  varray.clear();
  narray.clear();

  QFile data(filename);

  if (!data.open(QFile::ReadOnly))
    return;
  QTextStream in(&data);

  // Set of regular expressions : Vertex, Normal, Triangle
  QRegularExpression rexv("v\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)");
  QRegularExpression rexn("vn\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)");
  QRegularExpression rext("f\\s*(\\d*)/\\d*/(\\d*)\\s*(\\d*)/\\d*/(\\d*)\\s*(\\d*)/\\d*/(\\d*)");
  while (!in.atEnd())
  {
    QString line = in.readLine();
    QRegularExpressionMatch match = rexv.match(line);
    QRegularExpressionMatch matchN = rexn.match(line);
    QRegularExpressionMatch matchT = rext.match(line);
    if (match.hasMatch())//rexv.indexIn(line, 0) > -1)
    {
      Vector q = Vector(match.captured(1).toDouble(), match.captured(2).toDouble(), match.captured(3).toDouble()); vertices.push_back(q);
    }
    else if (matchN.hasMatch())//rexn.indexIn(line, 0) > -1)
    {
      Vector q = Vector(matchN.captured(1).toDouble(), matchN.captured(2).toDouble(), matchN.captured(3).toDouble());  normals.push_back(q);
    }
    else if (matchT.hasMatch())//rext.indexIn(line, 0) > -1)
    {
      varray.push_back(matchT.captured(1).toInt() - 1);
      varray.push_back(matchT.captured(3).toInt() - 1);
      varray.push_back(matchT.captured(5).toInt() - 1);
      narray.push_back(matchT.captured(2).toInt() - 1);
      narray.push_back(matchT.captured(4).toInt() - 1);
      narray.push_back(matchT.captured(6).toInt() - 1);
    }
  }
  data.close();
}

/*!
\brief Save the mesh in .obj format, with vertices and normals.
\param url Filename.
\param meshName %Mesh name in .obj file.
*/
void Mesh::SaveObj(const QString& url, const QString& meshName) const
{
  QFile data(url);
  if (!data.open(QFile::WriteOnly))
    return;
  QTextStream out(&data);
  out << "g " << meshName << Qt::endl;
  for (int i = 0; i < vertices.size(); i++)
    out << "v " << vertices.at(i)[0] << " " << vertices.at(i)[1] << " " << vertices.at(i)[2] << QString('\n');
  for (int i = 0; i < normals.size(); i++)
    out << "vn " << normals.at(i)[0] << " " << normals.at(i)[1] << " " << normals.at(i)[2] << QString('\n');
  for (int i = 0; i < varray.size(); i += 3)
  {
    out << "f " << varray.at(i) + 1 << "//" << narray.at(i) + 1 << " "
      << varray.at(i + 1) + 1 << "//" << narray.at(i + 1) + 1 << " "
      << varray.at(i + 2) + 1 << "//" << narray.at(i + 2) + 1 << " "
      << "\n";
  }
  out.flush();
  data.close();
}

