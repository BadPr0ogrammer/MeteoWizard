#if defined(WITH_VTK)
#pragma once

class vtkRenderer;
class vtkPiecewiseFunction;
class vtkDiscretizableColorTransferFunction;
class vtkLookupTable;
class vtkSmartVolumeMapper;
class vtkVolume;
class vtkVolumeProperty;
class vtkCutter;
class vtkGeometryFilter;
class vtkPolyDataMapper;
class vtkActor;
class vtkImageData;
class vtkPlane;
class vtkCamera;
class vtkUnstructuredGrid;
class vtkImplicitModeller;
class vtkContourFilter;
class vtkCubeAxesActor;
class vtkPlaneWidget;
class vtkClipDataSet;
class PlaneWidgetCallback;
class vtkRenderWindowInteractor;

class MeteoWizard;
class VolumeRender;
class GridRender;
//class UnionRender;

template<class T> class vtkNew;

class palettes_c;

class ModelRender
{
public:
	vtkNew<vtkRenderer> _renderer;
	vtkNew<vtkRenderWindow> _renderWindow;
	vtkNew<vtkCubeAxesActor> _cubeAxesActor;
	vtkNew<vtkPlaneWidget> _planeWidget;
	PlaneWidgetCallback* _planeWidgetCallback;
	vtkNew<vtkCamera> _camera;
	vtkNew<vtkRenderWindowInteractor> _renderWindowInteractor;

	double m_minRho, m_maxRho;	
	int m_curPalIdx;

	MeteoWizard* m_mainWindow;

	VolumeRender* m_volume;
	//GridRender* m_grid;
	//UnionRender* m_union;

	ModelRender(MeteoWizard* mainWindow);
	~ModelRender();

	void removeAllActors();
	void setCutFunction();
};
#endif
