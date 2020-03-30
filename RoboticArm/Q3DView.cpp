#include "Q3DView.h"

#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QPhongMaterial>

Q3DView::Q3DView()
	: Qt3DWindow()
{
	Qt3DCore::QEntity *scene = new Qt3DCore::QEntity();
	Qt3DCore::QEntity *armEntity = new Qt3DCore::QEntity(scene);

	Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(scene);

	QUrl armData = QUrl::fromLocalFile("C:/Users/alexa/Documents/Arduino/RoboticArm/assets/Waist.stl");
	Qt3DRender::QMesh *armMesh = new Qt3DRender::QMesh;
	armMesh->setMeshName("subMesh");
	armMesh->setSource(armData);

	Qt3DCore::QTransform *armTransform = new Qt3DCore::QTransform;
	armTransform->setScale3D(QVector3D(0.10, 0.10, 0.10));

	armEntity->addComponent(armMesh);
	armEntity->addComponent(material);
	armEntity->addComponent(armTransform);

	Qt3DRender::QCamera *camera = this->camera();
	camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	camera->setPosition(QVector3D(0, 0, 40.0f));
	camera->setViewCenter(QVector3D(0, 0, 0));

	Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(scene);
	camController->setLinearSpeed(50.0f);
	camController->setLookSpeed(180.0f);
	camController->setCamera(camera);

	this->setRootEntity(scene);
}

Q3DView::~Q3DView()
{
}
