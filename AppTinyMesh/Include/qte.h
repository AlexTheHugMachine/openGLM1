#ifndef __Qte__
#define __Qte__

#include <QtWidgets/qmainwindow.h>
#include "realtime.h"
#include "meshcolor.h"

QT_BEGIN_NAMESPACE
	namespace Ui { class Assets; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  Ui::Assets* uiw;           //!< Interface

  MeshWidget* meshWidget;   //!< Viewer
  MeshColor meshColor;		//!< Mesh.

public:
  MainWindow();
  ~MainWindow();
  void CreateActions();
  void UpdateGeometry();

public slots:
  void editingSceneLeft(const Ray&);
  void editingSceneRight(const Ray&);
  void meshRotationX();
  void meshRotationY();
  void meshRotationZ();
  void AmongusMesh();
  void BoxMeshExample();
  void DiskMesh();
  void ConeMesh();
  void CylinderMesh();
  void SphereMesh();
  void ToreMesh();
  void SphereImplicitExample();
  void ResetCamera();
  void UpdateMaterial();
private slots:
  void on_RotateXslider_valueChanged(int value);
  void on_RotateYslider_valueChanged(int value);
  void on_RotateZslider_valueChanged(int value);
};

#endif
