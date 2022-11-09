#include "qte.h"
#include "implicits.h"
#include "ui_interface.h"
#include <chrono>
using namespace std::chrono;

int RX;
int RY;
int RZ;
Mesh m;

MainWindow::MainWindow() : QMainWindow(), uiw(new Ui::Assets)
{
	// Chargement de l'interface
    uiw->setupUi(this);

	// Chargement du GLWidget
	meshWidget = new MeshWidget;
	QGridLayout* GLlayout = new QGridLayout;
	GLlayout->addWidget(meshWidget, 0, 0);
	GLlayout->setContentsMargins(0, 0, 0, 0);
    uiw->widget_GL->setLayout(GLlayout);

	// Creation des connect
	CreateActions();

	meshWidget->SetCamera(Camera(Vector(10, 0, 0), Vector(0.0, 0.0, 0.0)));
}

MainWindow::~MainWindow()
{
	delete meshWidget;
}

void MainWindow::CreateActions()
{
	// Buttons
    connect(uiw->amongusButton, SIGNAL(clicked()), this, SLOT(AmongusMesh()));
    connect(uiw->boxMesh, SIGNAL(clicked()), this, SLOT(BoxMeshExample()));
    connect(uiw->DiskButton, SIGNAL(clicked()), this, SLOT(DiskMesh()));
    connect(uiw->ConeButton, SIGNAL(clicked()), this, SLOT(ConeMesh()));
    connect(uiw->CylinderButton, SIGNAL(clicked()), this, SLOT(CylinderMesh()));
    connect(uiw->SphereButton, SIGNAL(clicked()), this, SLOT(SphereMesh()));
    connect(uiw->ToreButton, SIGNAL(clicked()), this, SLOT(ToreMesh()));
    connect(uiw->sphereImplicit, SIGNAL(clicked()), this, SLOT(SphereImplicitExample()));
    connect(uiw->resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));
    connect(uiw->wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_1, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_2, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->RotateXslider, SIGNAL(valueChanged(int)), this, SLOT(meshRotationX()));
    connect(uiw->RotateYslider, SIGNAL(valueChanged(int)), this, SLOT(meshRotationY()));
    connect(uiw->RotateZslider, SIGNAL(valueChanged(int)), this, SLOT(meshRotationZ()));

	// Widget edition
	connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
	connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}

void MainWindow::editingSceneLeft(const Ray&)
{
}

void MainWindow::editingSceneRight(const Ray&)
{
}

void MainWindow::on_RotateXslider_valueChanged(int value)
{
    RX = value;
}

void MainWindow::on_RotateYslider_valueChanged(int value)
{
    RY = value;
}

void MainWindow::on_RotateZslider_valueChanged(int value)
{
    RZ = value;
}

void MainWindow::meshRotationX()
{
    m.RotateX(RX/10);

    std::vector<Color> cols;
    cols.resize(m.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(200,200,200); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::meshRotationY()
{
    m.RotateY(RY/10);

    std::vector<Color> cols;
    cols.resize(m.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(200,200,200); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::meshRotationZ()
{
    m.RotateZ(RZ/10);

    std::vector<Color> cols;
    cols.resize(m.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(200,200,200); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::AmongusMesh()
{
    auto start = high_resolution_clock::now();
    Vector center1(0, 0, 0);

    Mesh AmongUs;
    Mesh cylinderMesh1 = Mesh(Cylinder(5.0, 5.0, center1), 14);
    Mesh cylinderMesh2 = Mesh(Cylinder(5.0, 5.0, center1), 14);
    Mesh cylinderMesh3 = Mesh(Cylinder(5.0, 5.0, center1), 14);
    Mesh sphereMesh1 = Mesh(Sphere(5.0, center1), 14);
    Mesh sphereMesh2 = Mesh(Sphere(5.0, center1), 14);
    Mesh sphereMesh3 = Mesh(Sphere(5.0, center1), 14);
    Mesh coneMesh = Mesh(Cone(5.0, 5.0, center1), 15);
    Mesh ToreMesh1 = Mesh(Tore(5.0, 2.0), 8, 8);
    Mesh ToreMesh2 = Mesh(Tore(5.0, 2.0), 8, 8);

    ToreMesh1.ScaleWithVector(Vector(0.37, 0.37, 0.37));
    ToreMesh1.Translation(Vector(3, 0, -4));

    ToreMesh2.ScaleWithVector(Vector(0.37, 0.37, 0.37));
    ToreMesh2.Translation(Vector(-3, 0, -4));

    coneMesh.Translation(Vector(0, 0, 16));
    coneMesh.ScaleWithVector(Vector(1.5, 1.5, 0.7));

    cylinderMesh1.ScaleWithVector(Vector(1, 1, 2));

    cylinderMesh2.Translation(Vector(7.5, 0, -5));
    cylinderMesh2.ScaleWithVector(Vector(0.4, 0.4, 0.8));

    cylinderMesh3.Translation(Vector(-7.5, 0, -5));
    cylinderMesh3.ScaleWithVector(Vector(0.4, 0.4, 0.8));

    sphereMesh1.Translation(Vector(0, 0, 14));
    sphereMesh1.ScaleWithVector(Vector(1, 1, 0.7));

    sphereMesh2.Translation(Vector(0, 7, 16));
    sphereMesh2.ScaleWithVector(Vector(0.8, 0.5, 0.5));

    sphereMesh3.Translation(Vector(0, -8, 7));
    sphereMesh3.ScaleWithVector(Vector(0.6, 0.6, 0.9));

    AmongUs.Merge(cylinderMesh1);
    AmongUs.Merge(cylinderMesh2);
    AmongUs.Merge(cylinderMesh3);
    AmongUs.Merge(sphereMesh1);
    AmongUs.Merge(sphereMesh2);
    AmongUs.Merge(sphereMesh3);
    AmongUs.Merge(coneMesh);
    AmongUs.Merge(ToreMesh1);
    AmongUs.Merge(ToreMesh2);

    m = AmongUs;

    Triangle test;
    Vector ve;
    Vector ro;
    Vector n;
    double rx;
    double ry;
    double rz;
    Vector rayon;
    double t;
    double u;
    double v;
    int secure = 1;     // variable qui permet de bloquer l'affichage d'un seul rayon (car =1) qui intersecte

    std::vector<Color> cols;
    cols.resize(m.Vertexes());

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;      // Correspond au compteur de collision
        bool collision = false;
        ve = m.Vertex(i);
        n = m.Normal(i);
        ro = ve+n;
        for(int j=0; j<20; j++)     // 20 correspond au nombre de rayons envoyés
        {
            rx = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            ry = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rz = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rayon = Normalized(Vector(rx, ry, rz));
            if ((n*rayon) < 0)
                rayon*=-1;
            Ray ray1(ro, rayon);
            if(c <= 20)     // 20 correspond au nombre de rayons envoyés
            {
                for(int k=0; k<m.Triangles() && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v) && t > 0)
                    {
                        c++;
                        if(secure > 0)
                        {
                            std::cout << "normal : " << n << std::endl;
                            std::cout << "rayon : " << rayon << std::endl;
                            secure--;
                        }
                        collision = true;
                    }
                }
                collision = false;
            }
        }
        cols[i] = Color(255*(21-c)/20, 255*(21-c)/20, 255*(21-c)/20);
    }

    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/
    //cols[42] = Color(0, 0, 255);      // Sert a colorier le 42ème point en bleu afin de visualiser où se trouvent les points qui ne fonctionnent pas
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken to generate amongus: "<< duration.count() << " microseconds" << std::endl;
}

void MainWindow::DiskMesh()
{
    auto start = high_resolution_clock::now();
    Vector up1(0, 1, 0);
    Vector center1(0, 0, 0);

    m = Mesh(Disk(10.0, up1, center1), 15);

    Triangle test;
    Vector ve;
    Vector ro;
    Vector n;
    double rx;
    double ry;
    double rz;
    Vector rayon;
    double t;
    double u;
    double v;

    std::vector<Color> cols;
    cols.resize(m.Vertexes());

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;      // Correspond au compteur de collision
        bool collision = false;
        ve = m.Vertex(i);
        n = m.Normal(i);
        ro = ve+n;
        for(int j=0; j<20; j++)     // 20 correspond au nombre de rayons envoyés
        {
            rx = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            ry = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rz = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rayon = Normalized(Vector(rx, ry, rz));
            if ((n*rayon) < 0)
                rayon*=-1;
            Ray ray1(ro, rayon);
            if(c <= 20)     // 20 correspond au nombre de rayons envoyés
            {
                for(int k=0; k<m.Triangles() && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v) && t > 0)
                    {
                        c++;
                        collision = true;
                    }
                }
                collision = false;
            }
        }
        cols[i] = Color(255*(21-c)/20, 255*(21-c)/20, 255*(21-c)/20);
    }

    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken to generate disk: "<< duration.count() << " microseconds" << std::endl;
}

void MainWindow::ConeMesh()
{
    auto start = high_resolution_clock::now();
    Vector center1(0, 0, 0);

    //coneMesh.RotateX(90);
    //coneMesh.Translation(Vector(0, 0, 5));
    m = Mesh(Cone(5.0, 5.0, center1), 16);
    //--------------------------------------------------------------------------------
    // Permet de tester la fonction SphereWarp en mettant un cone dans une sphere
    /*Sphere s = Sphere(5.0, center1);
    Mesh sw = m.SphereWarp(s);*/

    Triangle test;
    Vector ve;
    Vector ro;
    Vector n;
    double rx;
    double ry;
    double rz;
    Vector rayon;
    double t;
    double u;
    double v;

    std::vector<Color> cols;
    cols.resize(m.Vertexes());      // Remplacer "m.Vertexes()" par "sw.Vertexes()" pour visualiser le sphere warp

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;      // Correspond au compteur de collision
        bool collision = false;
        ve = m.Vertex(i);
        n = m.Normal(i);
        ro = ve+n;
        for(int j=0; j<20; j++)     // 20 correspond au nombre de rayons envoyés
        {
            rx = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            ry = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rz = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rayon = Normalized(Vector(rx, ry, rz));
            if ((n*rayon) < 0)
                rayon*=-1;
            Ray ray1(ro, rayon);
            if(c <= 20)     // 20 correspond au nombre de rayons envoyés
            {
                for(int k=0; k<m.Triangles() && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v) && t > 0)
                    {
                        c++;
                        collision = true;
                    }
                }
                collision = false;
            }
        }
        cols[i] = Color(255*(3-c)/2, 255*(3-c)/2, 255*(3-c)/2);
    }
    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/
    meshColor = MeshColor(m, cols, m.VertexIndexes());      // Remplacer m par sw pour visualiser le sphere warp
    UpdateGeometry();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken to generate cone: "<< duration.count() << " microseconds" << std::endl;
}

void MainWindow::CylinderMesh()
{
    auto start = high_resolution_clock::now();
    Vector center1(0, 0, 0);

    //Mesh cylinderMesh = Mesh(Cylinder(5.0, 5.0, center1), 15);
    m = Mesh(Cylinder(5.0, 5.0, center1), 15);
    /*Sphere s = Sphere(5.0, center1);
    Mesh sw = m.SphereWarp(s);*/


    Triangle test;
    Vector ve;
    Vector ro;
    Vector n;
    double rx;
    double ry;
    double rz;
    Vector rayon;
    double t;
    double u;
    double v;

    std::vector<Color> cols;
    cols.resize(m.Vertexes());

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;      // Correspond au compteur de collision
        bool collision = false;
        ve = m.Vertex(i);
        n = m.Normal(i);
        ro = ve+n+Vector(0, 0, -3);     // Nous avons rajouté un vecteur pour décaler les rayons pour voir si cela changeait quelque chose
        for(int j=0; j<2; j++)      // 20 correspond au nombre de rayons envoyés
        {
            rx = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            ry = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rz = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rayon = Normalized(Vector(rx, ry, rz));
            if ((n*rayon) < 0)
                rayon*=-1;
            Ray ray1(ro, rayon);
            if(c <= 2)      // 20 correspond au nombre de rayons envoyés
            {
                for(int k=0; k<m.Triangles() && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v) && t > 0)
                    {
                        c++;
                        if(i == 1 || i == 21)       // =1 ou =21 car on sait que le deuxième point et le 21eme collisionnent alors qu'ils ne devraient pas
                        {
                            // tests servants à visualiser les rayons collisionnent avec quelque chose alors qu'ils ne devraient pas
                            std::cout<<std::endl;
                            std::cout<<"Vector de départ du rayon : "<< ro << std::endl;
                            std::cout<<"Normal test : "<< test.Normal()<<std::endl;
                            std::cout<<"Center test : "<<test.Center()<<std::endl;
                            std::cout << "n : " << n << std::endl;
                            std::cout << "rayon : " << rayon << std::endl;
                            std::cout<<std::endl;
                        }
                        collision = true;
                    }
                }
                collision = false;
            }
        }
        cols[i] = Color(255*(3-c)/2, 255*(3-c)/2, 255*(3-c)/2);
    }

    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken to generate cylinder: "<< duration.count() << " microseconds" << std::endl;
}

void MainWindow::SphereMesh()
{
    auto start = high_resolution_clock::now();
    Vector center1(0, 0, 0);

    m = Mesh(Sphere(5.0, center1), 15);

    Triangle test;
    Vector ve;
    Vector ro;
    Vector n;
    double rx;
    double ry;
    double rz;
    Vector rayon;
    double t;
    double u;
    double v;

    std::vector<Color> cols;
    cols.resize(m.Vertexes());

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;      // Correspond au compteur de collision
        bool collision = false;
        ve = m.Vertex(i);
        n = m.Normal(i);
        ro = ve+n;
        for(int j=0; j<20; j++)     // 20 correspond au nombre de rayons envoyés
        {
            rx = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            ry = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rz = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rayon = Normalized(Vector(rx, ry, rz));
            if ((n*rayon) < 0)
                rayon*=-1;
            Ray ray1(ro, rayon);
            if(c <= 20)     // 20 correspond au nombre de rayons envoyés
            {
                for(int k=0; k<m.Triangles() && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v) && t>0)
                    {
                        c++;
                        // La sphere ne possède pas de tests d'affichage de rayons car nous
                        //voulions comprendre le problème sur les autres formes en premier
                        collision = true;
                    }
                }
                collision = false;
            }
        }
        cols[i] = Color(255*(21-c)/20, 255*(21-c)/20, 255*(21-c)/20);
    }

    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken to generate sphere: "<< duration.count() << " microseconds" << std::endl;
}

void MainWindow::ToreMesh()
{

    auto start = high_resolution_clock::now();

    m = Mesh(Tore(5.0, 2.5), 20, 20);

    Triangle test;
    Vector ve;
    Vector ro;
    Vector n;
    double rx;
    double ry;
    double rz;
    Vector rayon;
    double t;
    double u;
    double v;

    std::vector<Color> cols;
    cols.resize(m.Vertexes());

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;      // Correspond au compteur de collision
        bool collision = false;
        ve = m.Vertex(i);
        n = m.Normal(i);
        ro = ve+n;
        for(int j=0; j<20; j++)     // 20 correspond au nombre de rayons envoyés
        {
            rx = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            ry = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rz = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rayon = Normalized(Vector(rx, ry, rz));
            if ((n*rayon) < 0)
                rayon*=-1;
            Ray ray1(ro, rayon);
            if(c <= 20)     // 20 correspond au nombre de rayons envoyés
            {
                for(int k=0; k<m.Triangles() && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v))
                    {
                        c++;
                        if(i == 98)     // =98 car on sait que le 98eme collisionne alors qu'il ne devrait pas
                        {
                            // tests servants à visualiser les rayons collisionnent avec quelque chose alors qu'ils ne devraient pas
                            std::cout<<std::endl;
                            std::cout<<"Normal test : "<< test.Normal()<<std::endl;
                            std::cout<<"Center test : "<<test.Center()<<std::endl;
                            std::cout << "n : " << n << std::endl;
                            std::cout << "rayon : " << rayon << std::endl;
                            std::cout<<std::endl;
                        }
                        collision = true;
                    }
                }
                collision = false;
            }
        }
        cols[i] = Color(255*(21-c)/20, 255*(21-c)/20, 255*(21-c)/20);
    }

    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/

    // --------------------------------------------------------------
    // Nous a permis de visualiser comment les points étaient répartis
    // afin de trouver quels points posent problème dans l'intersection
    cols[0] = Color(255, 0, 0);
    cols[98] = Color(0, 255, 0);
    cols[2] = Color(0, 0, 255);
    std::cout<<"Vector vertice 98 " << m.Vertex(98) << std::endl;
    std::cout<<"Normal vertice 98 " << m.Normal(98) << std::endl;

    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken to generate tore: "<< duration.count() << " microseconds" << std::endl;
}

void MainWindow::BoxMeshExample()
{
    auto start = high_resolution_clock::now();
    m = Mesh(Box(1.0));

    Triangle test;
    Vector ve;
    Vector ro;
    Vector n;
    double rx;
    double ry;
    double rz;
    Vector rayon;
    double t;
    double u;
    double v;

    std::vector<Color> cols;
    cols.resize(m.Vertexes());

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;      // Correspond au compteur de collision
        bool collision = false;
        ve = m.Vertex(i);
        n = m.Normal(i);
        ro = ve+n;
        for(int j=0; j<20; j++)     // 20 correspond au nombre de rayons envoyés
        {
            rx = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            ry = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rz = (double(rand() % 101) / 100.0) * 2.0 - 1.0;
            rayon = Normalized(Vector(rx, ry, rz));
            if ((n*rayon) < 0)
                rayon*=-1;
            Ray ray1(ro, rayon);
            if(c <= 20)     // 20 correspond au nombre de rayons envoyés
            {
                for(int k=0; k<m.Triangles() && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v) && t>0)
                    {
                        c++;
                        collision = true;
                    }
                }
                collision = false;
            }
        }
        cols[i] = Color(255*(21-c)/20, 255*(21-c)/20, 255*(21-c)/20);
    }

    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken to generate boxExample: "<< duration.count() << " microseconds" << std::endl;
}

void MainWindow::SphereImplicitExample()
{
  AnalyticScalarField implicit;

  Mesh implicitMesh;
  implicit.Polygonize(31, implicitMesh, Box(2.0));

  std::vector<Color> cols;
  cols.resize(implicitMesh.Vertexes());
  for (size_t i = 0; i < cols.size(); i++)
    cols[i] = Color(0.8, 0.8, 0.8);

  meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
  UpdateGeometry();
}

void MainWindow::UpdateGeometry()
{
	meshWidget->ClearAll();
	meshWidget->AddMesh("BoxMesh", meshColor);
    meshWidget->AddMesh("DiskMesh", meshColor);

    uiw->lineEdit->setText(QString::number(meshColor.Vertexes()));
    uiw->lineEdit_2->setText(QString::number(meshColor.Triangles()));

	UpdateMaterial();
}

void MainWindow::UpdateMaterial()
{
    meshWidget->UseWireframeGlobal(uiw->wireframe->isChecked());

    if (uiw->radioShadingButton_1->isChecked())
		meshWidget->SetMaterialGlobal(MeshMaterial::Normal);
	else
		meshWidget->SetMaterialGlobal(MeshMaterial::Color);
}

void MainWindow::ResetCamera()
{
	meshWidget->SetCamera(Camera(Vector(-10.0), Vector(0.0)));
}
