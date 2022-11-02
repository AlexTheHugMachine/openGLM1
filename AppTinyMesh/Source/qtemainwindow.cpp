#include "qte.h"
#include "implicits.h"
#include "ui_interface.h"

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
    Vector center1(0, 0, 0);

    Mesh AmongUs;
    Mesh cylinderMesh1 = Mesh(Cylinder(5.0, 5.0, center1), 14);
    Mesh cylinderMesh2 = Mesh(Cylinder(5.0, 5.0, center1), 14);
    Mesh cylinderMesh3 = Mesh(Cylinder(5.0, 5.0, center1), 14);
    Mesh sphereMesh1 = Mesh(Sphere(5.0, center1), 15);
    Mesh sphereMesh2 = Mesh(Sphere(5.0, center1), 15);
    Mesh sphereMesh3 = Mesh(Sphere(5.0, center1), 15);
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
    sphereMesh1.RotateZ(180);

    sphereMesh2.Translation(Vector(0, 7, 15));
    sphereMesh2.ScaleWithVector(Vector(0.8, 0.5, 0.5));
    sphereMesh2.RotateZ(180);

    sphereMesh3.Translation(Vector(0, -8, 7));
    sphereMesh3.ScaleWithVector(Vector(0.6, 0.6, 0.9));
    sphereMesh3.RotateZ(180);

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

    std::vector<Color> cols;
    cols.resize(m.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(200,200,200); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::DiskMesh()
{
    Vector up1(0, 1, 0);
    Vector center1(0, 0, 0);

    //Mesh diskMesh = Mesh(Disk(10.0, up1, center1), 15);
    m = Mesh(Disk(10.0, up1, center1), 15);

    std::vector<Color> cols;
    cols.resize(m.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(1,1,1);//Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();

}

void MainWindow::ConeMesh()
{
    Vector center1(0, 0, 0);

    //Mesh coneMesh = Mesh(Cone(5.0, 5.0, center1), 15);
    //coneMesh.RotateX(90);
    //coneMesh.Translation(Vector(0, 0, 5));
    m = Mesh(Cone(5.0, 5.0, center1), 15);

    std::vector<Color> cols;
    cols.resize(m.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(200,200,200); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::CylinderMesh()
{
    Vector center1(0, 0, 0);

    //Mesh cylinderMesh = Mesh(Cylinder(5.0, 5.0, center1), 15);
    m = Mesh(Cylinder(5.0, 5.0, center1), 15);


    Triangle test;
    Vector Normalised;
    Vector t1center;
    Vector t1center2;
    Vector t1normal;
    float rx;
    float ry;
    float rz;
    Vector rayon;
    double t;
    double u;
    double v;

    std::vector<Color> cols;
    cols.resize(m.Vertexes());

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;
        std::cout<<1111111111111111111<<c<<std::endl;
        std::cout<<m.Vertex(i)<<std::endl;
        //AB = AxBx + AyBy + AzBz
        bool collision = false;
        t1center = m.Vertex(i);
        t1normal = m.Normal(i);
        Normalised = Normalized(t1normal);
        t1center2 = t1center+Normalised;
        for(int j=0; j<5; j++)
        {
            do
            {
                rx = (rand()%100);
                ry = (rand()%100);
                rz = (rand()%100);
                rayon = Normalized(Vector(rx, ry, rz));
            }
            while((Normalised[0]*rayon[0]+Normalised[1]*rayon[1]+Normalised[2]*rayon[2]) > 0);
            Ray ray1(t1center2, rayon);
            if(c <= 5)
            {
                for(int k=0; k<m.Triangles() && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v))
                    {
                        std::cout<<c++<<std::endl;
                        collision = true;
                    }
                }
                collision = false;
            }
            std::cout<<"sussy : "<<c<<std::endl;
        }
        cols[i] = Color(255*(6-c)/5, 255*(6-c)/5, 255*(6-c)/5);
    }

    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    //std::cout<<"sussy";
    UpdateGeometry();
}

void MainWindow::SphereMesh()
{
    Vector center1(0, 0, 0);

    //Mesh sphereMesh = Mesh(Sphere(5.0, center1), 15);
    m = Mesh(Sphere(5.0, center1), 15);


    Triangle test;
    Vector Normalised;
    Vector t1center;
    Vector t1center2;
    Vector t1normal;
    float rx;
    float ry;
    float rz;
    Vector rayon;
    double t;
    double u;
    double v;

    std::vector<Color> cols;
    cols.resize(m.Vertexes());

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;
        std::cout<<1111111111111111111<<c<<std::endl;
        std::cout<<m.Vertex(i)<<std::endl;
        bool collision = false;
        t1center = m.Vertex(i);
        t1normal = m.Normal(i);
        Normalised = Normalized(t1normal);
        t1center2 = t1center+Normalised;
        for(int j=0; j<5; j++)
        {
            do
            {
                rx = (rand()%100);
                ry = (rand()%100);
                rz = (rand()%100);
                rayon = Normalized(Vector(rx, ry, rz));
            }
            while((Normalised[0]*rayon[0]+Normalised[1]*rayon[1]+Normalised[2]*rayon[2]) > 0);      //AB = AxBx + AyBy + AzBz
            Ray ray1(t1center2, rayon);
            if(c <= 5)
            {
                for(int k=0; k<m.Triangles() && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v))
                    {
                        std::cout<<c++<<std::endl;
                        collision = true;
                    }
                }
                collision = false;
            }
            std::cout<<"sussy : "<<c<<std::endl;
        }
        cols[i] = Color(255*(6-c)/5, 255*(6-c)/5, 255*(6-c)/5);
    }

    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    //std::cout<<"sussy";
    UpdateGeometry();

    /*std::vector<Color> cols;
    cols.resize(m.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(200,200,200); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    UpdateGeometry();*/
}

void MainWindow::ToreMesh()
{
    //Mesh ToreMesh = Mesh(Tore(5.0, 2.0), 20, 20);
    m = Mesh(Tore(5.0, 2.5), 20, 20);

    Triangle test;
    Vector Normalised;
    Vector t1center;
    Vector t1center2;
    Vector t1normal;
    float rx;
    float ry;
    float rz;
    Vector rayon;
    double t;
    double u;
    double v;

    std::vector<Color> cols;
    cols.resize(m.Vertexes());

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;
        std::cout<<1111111111111111111<<c<<std::endl;
        std::cout<<m.Vertex(i)<<std::endl;
        //AB = AxBx + AyBy + AzBz
        bool collision = false;
        t1center = m.Vertex(i);
        t1normal = m.Normal(i);
        Normalised = Normalized(t1normal);
        t1center2 = t1center+Normalised;
        for(int j=0; j<5; j++)
        {
            do
            {
                rx = (rand()%100);
                ry = (rand()%100);
                rz = (rand()%100);
                rayon = Normalized(Vector(rx, ry, rz));
            }
            while((Normalised[0]*rayon[0]+Normalised[1]*rayon[1]+Normalised[2]*rayon[2]) > 0);
            Ray ray1(t1center2, rayon);
            if(c <= 5)
            {
                for(int k=1; k<m.Triangles() && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v))
                    {
                        std::cout<<c++<<std::endl;
                        collision = true;
                    }
                }
                collision = false;
            }
            std::cout<<"sussy : "<<c<<std::endl;
        }
        cols[i] = Color(255*(6-c)/5, 255*(6-c)/5, 255*(6-c)/5);
    }

    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    //std::cout<<"sussy";
    UpdateGeometry();
}

void MainWindow::BoxMeshExample()
{
    //Mesh boxMesh = Mesh(Box(1.0));
    m = Mesh(Box(1.0));

    Triangle test;
    Vector Normalised;
    Vector t1center;
    Vector t1center2;
    Vector t1normal;
    float rx;
    float ry;
    float rz;
    Vector rayon;
    double t;
    double u;
    double v;

    std::vector<Color> cols;
    cols.resize(m.Vertexes());

    for(int i = 0; i<m.Vertexes(); i++)
    {
        int c = 1;
        std::cout<<1111111111111111111<<c<<std::endl;
        std::cout<<m.Vertex(i)<<std::endl;
        //AB = AxBx + AyBy + AzBz
        bool collision = false;
        t1center = m.Vertex(i);
        t1normal = m.Normal(i);
        Normalised = Normalized(t1normal);
        t1center2 = t1center+Normalised;
        for(int j=0; j<5; j++)
        {
            do
            {
                rx = (rand()%100);
                ry = (rand()%100);
                rz = (rand()%100);
                rayon = Normalized(Vector(rx, ry, rz));
            }
            while((Normalised[0]*rayon[0]+Normalised[1]*rayon[1]+Normalised[2]*rayon[2]) > 0);
            Ray ray1(t1center2, rayon);
            if(c <= 5)
            {
                for(int k=0; k<1 && !collision; k++)
                {
                    test = m.GetTriangle(k);
                    if(test.Intersect(ray1, t, u, v))
                    {
                        std::cout<<c++<<std::endl;
                        collision = true;
                    }
                }
                collision = false;
            }
            std::cout<<"sussy : "<<c<<std::endl;
        }
        cols[i] = Color(255*(6-c)/5, 255*(6-c)/5, 255*(6-c)/5);

    }

    /*for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(255-(255/(5*c)),0,0); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);*/
    meshColor = MeshColor(m, cols, m.VertexIndexes());
    //std::cout<<"sussy";
    UpdateGeometry();
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
