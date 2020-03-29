#include "Q3DView.h"

#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QPhongMaterial>

Q3DView::Q3DView()
	: Qt3DWindow()
{
	Qt3DCore::QEntity *scene = new Qt3DCore::QEntity();
	Qt3DCore::QEntity *subEntity = new Qt3DCore::QEntity(scene);

	Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(scene);

	QUrl yodaData = QUrl::fromLocalFile("C:/Users/alexa/Documents/Arduino/RoboticArm/assets/Mini-Sub.stl");
	Qt3DRender::QMesh *subMesh = new Qt3DRender::QMesh;
	subMesh->setMeshName("subMesh");
	subMesh->setSource(yodaData);
	subEntity->addComponent(subMesh);
	subEntity->addComponent(material);

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
