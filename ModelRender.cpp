#include <vector>

#include <QGuiApplication>
#include <QDoubleSpinBox>
#include <QAbstractButton>

#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkPiecewiseFunction.h>
#include <vtkDiscretizableColorTransferFunction.h>
#include <vtkLookupTable.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkCutter.h>
#include <vtkGeometryFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkImageData.h>
#include <vtkPlane.h>
#include <vtkPlaneCollection.h>
#include <vtkCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkFloatArray.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkProperty.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVoxel.h>
#include <vtkImplicitModeller.h>
#include <vtkContourFilter.h>
#include <vtkClipDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkNamedColors.h>
#include <vtkTriangleFilter.h>
#include <vtkExtractSurface.h>
#include <vtkCleanPolyData.h>
#include <vtkBoxWidget2.h>
#include <vtkWidgetRepresentation.h>
#include <vtkCubeAxesActor.h>
#include <vtkTextProperty.h>
#include <vtkPlaneWidget.h>
#include <vtkCommand.h>
#include <vtkRenderingVolumeOpenGL2Module.h>

//.;MSG\include;2.06\DISE;2.06\COMP\Inc;2.06\COMP\JPEG\Inc;2.06\COMP\WT\Inc;2.06\COMP\T4\Inc;shapelib;..\opencv-3.4.14\build;..\opencv-3.4.14\modules\core\include;..\opencv-3.4.14\modules\imgproc\include;..\opencv-3.4.14\modules\imgcodecs\include;..\opencv-3.4.14\modules\highgui\include;..\opencv-3.4.14\modules\videoio\include;debug;/include;..\opencv-3.4.14\3rdparty\libjasper;..\opencv-3.4.14\3rdparty\libpng;..\opencv-3.4.14\3rdparty\libjpeg;win32;met-5.2_bugfix\src\basic\vx_cal;met-5.2_bugfix\src\basic\vx_config;met-5.2_bugfix\src\basic\vx_log;met-5.2_bugfix\src\basic\vx_math;met-5.2_bugfix\src\basic\vx_util;met-5.2_bugfix\src\libcode\vx_data2d;met-5.2_bugfix\src\libcode\vx_data2d_factory;met-5.2_bugfix\src\libcode\vx_data2d_grib2;met-5.2_bugfix\src\libcode\vx_data2d_grib;met-5.2_bugfix\src\libcode\vx_grid;g2clib-1.6.0;met-5.2_bugfix;..\VTK-master\build\Utilities\KWIML;..\VTK-master\Utilities\KWIML;..\VTK-master\build\Common\Core;..\VTK-master\Common\Core;..\VTK-master\build\Rendering\Core;..\VTK-master\Rendering\Core;..\	\build\Common\DataModel;..\VTK-master\Common\DataModel;..\VTK-master\build\Rendering\VolumeOpenGL2;..\VTK-master\Rendering\VolumeOpenGL2;..\VTK-master\build\Filters\Core;..\VTK-master\Filters\Core;..\VTK-master\build\Filters\Geometry;..\VTK-master\Filters\Geometry;..\VTK-master\build\Rendering\OpenGL2;..\VTK-master\Rendering\OpenGL2;..\VTK-master\build\Filters\Hybrid;..\VTK-master\Filters\Hybrid;..\VTK-master\build\Filters\General;..\VTK-master\Filters\General;..\VTK-master\build\Common\Color;..\VTK-master\Common\Color;..\VTK-master\build\Filters\Points;..\VTK-master\Filters\Points;..\VTK-master\build\Interaction\Widgets;..\VTK-master\Interaction\Widgets;..\VTK-master\build\Rendering\Annotation;..\VTK-master\Rendering\Annotation;..\VTK-master\build\Common\Math;..\VTK-master\Common\Math;..\VTK-master\build\Common\ExecutionModel;..\VTK-master\Common\ExecutionModel;..\VTK-master\build\Rendering\Volume;..\VTK-master\Rendering\Volume;..\VTK-master\build\Imaging\Core;..\VTK-master\Imaging\Core;..\VTK-master\build\Common\Misc;..\VTK-master\Common\Misc;
#include "PlaneWidgetCallback.h"
#include "meteowizard.h"

#include "VolumeRender.h"
//#include "GridRender.h"
//#include "UnionRender.h"

#include "ModelRender.h"

#include "Palettes.h"

ModelRender::ModelRender(MeteoWizard* mainWindow) :
	m_mainWindow(mainWindow),
	m_minRho(0), m_maxRho(0),
	m_volume(nullptr), //m_union(nullptr),
	m_curPalIdx(0)
{
	_camera->SetViewUp(0, 0, 1);
	_camera->SetPosition(1200, 1200, -100);

	_renderer->SetBackground(0.8, 0.8, 0.8);
	_renderer->SetActiveCamera(_camera);

	_cubeAxesActor->SetCamera(_camera);
	_cubeAxesActor->GetTitleTextProperty(0)->SetColor(1.0, 0.0, 0.0);
	_cubeAxesActor->GetLabelTextProperty(0)->SetColor(1.0, 0.0, 0.0);
	_cubeAxesActor->GetTitleTextProperty(1)->SetColor(0.0, 1.0, 0.0);
	_cubeAxesActor->GetLabelTextProperty(1)->SetColor(0.0, 1.0, 0.0);
	_cubeAxesActor->GetTitleTextProperty(2)->SetColor(0.0, 0.0, 1.0);
	_cubeAxesActor->GetLabelTextProperty(2)->SetColor(0.0, 0.0, 1.0);
	_cubeAxesActor->DrawXGridlinesOn();
	_cubeAxesActor->DrawYGridlinesOn();
	_cubeAxesActor->DrawZGridlinesOn();
	_cubeAxesActor->SetGridLineLocation(_cubeAxesActor->VTK_GRID_LINES_FURTHEST);
	_cubeAxesActor->XAxisMinorTickVisibilityOff();
	_cubeAxesActor->YAxisMinorTickVisibilityOff();
	_cubeAxesActor->ZAxisMinorTickVisibilityOff();

	_cubeAxesActor->SetFlyModeToClosestTriad();

	_renderer->AddActor(_cubeAxesActor);

	_renderer->AddActor(_cubeAxesActor);

	_renderWindow->AddRenderer(_renderer);
	
	_renderWindowInteractor->SetRenderWindow(_renderWindow);

	_planeWidget->SetCenter(500, 500, -100);
	_planeWidget->SetNormal(1, 0, 1);
	_planeWidget->SetRepresentationToWireframe();

	_planeWidgetCallback = new PlaneWidgetCallback();
	_planeWidgetCallback->model = this;
	_planeWidgetCallback->mainWindow = mainWindow;

	_planeWidget->AddObserver(vtkCommand::EndInteractionEvent, _planeWidgetCallback);
	_planeWidget->SetInteractor(_renderWindow->GetInteractor());

	_planeWidget->SetResolution(0.1);
	_planeWidget->SetHandleSize(0.002);
	_planeWidget->SetPlaceFactor(1);
	_planeWidget->GetPlaneProperty()->SetColor(0.2, 0.6, 0.2);
	_planeWidget->GetPlaneProperty()->SetOpacity(1);
	_planeWidget->GetHandleProperty()->SetColor(0, 0.4, 0.7);
	_planeWidget->GetHandleProperty()->SetLineWidth(2);

	_renderWindow->Render();
	_renderWindowInteractor->Start();
}

ModelRender::~ModelRender()
{
	delete m_volume;
	//delete m_grid;
	//delete m_union;
	
	delete _planeWidgetCallback;
}

void ModelRender::setCutFunction()
{
	if (m_volume)
		m_volume->removeAddClippingPlanes(true);
	//if (m_grid)
		//m_grid->setCutFunction();
}

void ModelRender::removeAllActors()
{
	if (m_volume) {
		m_volume->removeAddClippingPlanes(false);
		m_volume->removeAddActor(false);
	}
	//if (m_grid) {
		//m_grid->removeAddClipDataSet(false);
		//m_grid->removeAddActors(false);
	//}
	//m_union->removeAdd(false);
	//??? smooth bool removeAdd(false);
}


void MeteoWizard::colorBoxValueChanged(double val)
{
	std::vector<double> xv, yv;
	checkColorTF(xv, yv);

	if (m_modelRender->m_volume != nullptr) {
		VolumeRender* vr = m_modelRender->m_volume;

		vr->setPalette(xv, yv);
		/*
		for (int i = 0; i < color_num; i++) {
			/*
			ctbl->SetValue(2 * i, 0, x0);
			ctbl->SetValue(2 * i, 1, y0);
			ctbl->SetValue(2 * i + 1, 0, x1);
			ctbl->SetValue(2 * i + 1, 1, y1);
		}*/
		//ctbl->Modified();

		//m_tfPlotModel->m_ptrPlot->Update();
		//m_tfPlotModel->m_chart->Update();

		//vr->_volumeProperty->SetScalarOpacity(vr->_imageOpacityTF);
		vr->_volume->Update();
		vr->_volumeMapper->Update();
	}
	//else if (m_modelRender->m_grid != nullptr)
		//m_modelRender->m_grid->setPalette(m_hollowContourOn->valueText() == "True", xv, yv, m_hollowLightingOn->valueText() == "True");

	m_modelRender->_renderer->Render();
	m_modelRender->_renderWindow->Render();
}

void MeteoWizard::checkColorTF(std::vector<double>& xv, std::vector<double>& yv)
{
	double x_0 = 0, y_0 = 0;

	for (int i = 0; i < color_num; i++) {
		double x0 = m_colorTfSp_X[2 * i]->value();
		double x1 = m_colorTfSp_X[2 * i + 1]->value();
		if (x0 > x1) { double b = x0; x0 = x1; x1 = b; }

		if (x0 < x_0)
			x0 = x_0;
		xv.push_back(x0);
		x_0 = x0;

		if (x1 < x_0)
			x1 = x_0;
		xv.push_back(x1);
		x_0 = x1;

		m_colorTfSp_X[2 * i]->disconnect(m_colorConnect_X[2 * i]);
		m_colorTfSp_X[2 * i]->setValue(x0);
		m_colorConnect_X[2 * i] = connect(m_colorTfSp_X[2 * i], QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MeteoWizard::colorBoxValueChanged);

		m_colorTfSp_X[2 * i + 1]->disconnect(m_colorConnect_X[2 * i + 1]);
		m_colorTfSp_X[2 * i + 1]->setValue(x1);
		m_colorConnect_X[2 * i + 1] = connect(m_colorTfSp_X[2 * i + 1], QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MeteoWizard::colorBoxValueChanged);

		double y0 = m_colorTfSp_Y[2 * i]->value();
		double y1 = m_colorTfSp_Y[2 * i + 1]->value();
		if (y0 > y1) { double b = y0; y0 = y1; y1 = b; }

		if (y0 < y_0)
			y0 = y_0;
		yv.push_back(y0);
		y_0 = y0;

		if (y1 < y_0)
			y1 = y_0;
		yv.push_back(y1);
		y_0 = y1;

		m_colorTfSp_Y[2 * i]->disconnect(m_colorConnect_Y[2 * i]);
		m_colorTfSp_Y[2 * i]->setValue(y0);
		m_colorConnect_Y[2 * i] = connect(m_colorTfSp_Y[2 * i], QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MeteoWizard::colorBoxValueChanged);

		m_colorTfSp_Y[2 * i + 1]->disconnect(m_colorConnect_Y[2 * i + 1]);
		m_colorTfSp_Y[2 * i + 1]->setValue(y1);
		m_colorConnect_Y[2 * i + 1] = connect(m_colorTfSp_Y[2 * i + 1], QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MeteoWizard::colorBoxValueChanged);
	}
}

/*
vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
lut->SetNumberOfTableValues(num);
lut->SetTableRange(0, num);
for (int i = 0; i < num; i++) {
	double c[3] = { 0,0,0 };
	int j = i % 10;
	switch (j) {
	case 0:c[0] = 1; break;
	case 1:c[1] = 1; break;
	case 2:c[2] = 1; break;
	case 3:c[0] = c[1] = 1; break;
	case 4:c[0] = c[2] = 1; break;
	case 5:c[1] = c[2] = 1; break;
	case 6:c[0] = 0.7; c[1] = 0.5; c[2] = 1.0; break;
	case 7:c[0] = 0.5; c[1] = 0.7; c[2] = 0.5; break;
	case 8:c[0] = 0.8; c[1] = 0.6; c[2] = 0.7; break;
	case 9:c[0] = 0.4; c[1] = 0.8; c[2] = 0.5; break;
	}
	lut->SetTableValue(i, c[0], c[1], c[2], 0.5);
}

m_image_map = vtkSmartPointer<vtkImageMapToColors>::New();
m_image_map->SetLookupTable(lut);
m_image_map->SetOutputFormatToRGBA();
m_image_map->SetInputData(m_image);
m_image_map->Update();
*/
/*
vtkSmartPointer<vtkLookupTable> ModelRender::setLookupTable(double opacity, int range)
{
	vtkSmartPointer<vtkLookupTable> lookupTable = vtkLookupTable::New();

	lookupTable->SetTableRange(0, 1);
	lookupTable->SetHueRange(0, 1);
	lookupTable->SetSaturationRange(1, 1);
	lookupTable->SetValueRange(0, range);
	lookupTable->Build();
	double rgba[4] = { 0,0,0,0 };
	lookupTable->SetTableValue(0, rgba);

	for (int i = 0; i < lookupTable->GetNumberOfColors(); i++) {
		lookupTable->GetTableValue(i, rgba);
		rgba[3] = opacity;
		lookupTable->SetTableValue(i, rgba);
	}
	lookupTable->Build();

	return lookupTable;
}
*/

/*
_ñutter->SetInputData(_volume->Get);
_ñutter->GenerateCutScalarsOn();

_ñutImage->SetCutFunction(plane);
_ñutImage->Update();

	_cutterMapper->SetInputData(_volume);//geometryFilter->GetOutputPort()
_cutterMapper->SetLookupTable(lut);
_cutterMapper->ScalarVisibilityOn();
//_cutImageMapper->SetScalarRange(0, m_mainWindow->m_boxes->size());
_cutterMapper->UseLookupTableScalarRangeOn();
_cutterMapper->Update();



	vtkSmartPointer<vtkGeometryFilter> geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();
	geometryFilter->SetInputConnection(_ñutVolume->GetOutputPort());
	geometryFilter->Update();

	vtkSmartPointer<vtkLookupTable> lut =
		vtkSmartPointer<vtkLookupTable>::New();//This seems to be required to render anything at all.
	lut->SetRange(0.3, 1); // image intensity range
	lut->SetValueRange(0.3, 1.0); // from black to white
	lut->SetSaturationRange(0.3, 1.0); // no color saturation
	lut->SetTableRange(0.2, 1.0);
	lut->SetRampToLinear();
	lut->SetBelowRangeColor(1, 1, 1, 1);
	lut->Build();


	_cutImageActor->SetMapper(_cutImageMapper);
	_cutImageActor->GetProperty()->LightingOn();
	_cutImageActor->GetProperty()->SetAmbient(1.0);

	//_renderer->AddActor(_cutImageActor);
*/
//vtkNew<vtkCutter> _ñutter;
//vtkNew<vtkPolyDataMapper> _cutterMapper;
//vtkNew<vtkActor> _cutterActor;


//	vtkNew<vtkLookupTable> _imageColorTable;
//_imageColorTable->SetTableValue(0, 1, 1, 1, 0.5);
//_imageColorTable->SetTableValue(i + 1, r, g, b, o);
