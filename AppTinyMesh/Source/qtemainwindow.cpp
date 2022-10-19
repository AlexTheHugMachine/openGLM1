#include "qte.h"
#include "implicits.h"
#include "ui_interface.h"

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

void MainWindow::DiskMesh()
{
    Vector up1(0, 1, 0);
    Vector center1(0, 0, 0);

    Mesh diskMesh = Mesh(Disk(10.0, up1, center1), 15);

    std::vector<Color> cols;
    cols.resize(diskMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(1,1,1);//Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(diskMesh, cols, diskMesh.VertexIndexes());
    UpdateGeometry();

}

void MainWindow::ConeMesh()
{
    Vector center1(0, 0, 0);

    Mesh coneMesh = Mesh(Cone(5.0, 5.0, center1), 15);

    std::vector<Color> cols;
    cols.resize(coneMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(200,200,200); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(coneMesh, cols, coneMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::CylinderMesh()
{
    Vector center1(0, 0, 0);

    Mesh cylinderMesh = Mesh(Cylinder(5.0, 5.0, center1), 15);

    std::vector<Color> cols;
    cols.resize(cylinderMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(200,200,200); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(cylinderMesh, cols, cylinderMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::SphereMesh()
{
    Vector center1(0, 0, 0);

    Mesh sphereMesh = Mesh(Sphere(5.0, center1), 15);

    std::vector<Color> cols;
    cols.resize(sphereMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(200,200,200); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(sphereMesh, cols, sphereMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::ToreMesh()
{
    Mesh ToreMesh = Mesh(Tore(5.0, 5.0), 15, 15);

    std::vector<Color> cols;
    cols.resize(ToreMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(200,200,200); //Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);
    meshColor = MeshColor(ToreMesh, cols, ToreMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::BoxMeshExample()
{
	Mesh boxMesh = Mesh(Box(1.0));

	std::vector<Color> cols;
	cols.resize(boxMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
		cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

	meshColor = MeshColor(boxMesh, cols, boxMesh.VertexIndexes());
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
