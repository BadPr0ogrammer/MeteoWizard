#if defined(WITH_VTK)
#pragma once

#include <vector>

class vtkRenderer;
class vtkPiecewiseFunction;
class vtkColorTransferFunction;
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
class QVTKOpenGLNativeWidget;
class vtkUnstructuredGrid;
class vtkImplicitModeller;
class vtkContourFilter;
class vtkCubeAxesActor;
class vtkPlaneWidget;
class vtkGenericOpenGLRenderWindow;
class vtkClipDataSet;
class PlaneWidgetCallback;

class MeteoWizard;

class VolumeRender
{
public:
	vtkNew<vtkImageData> _image;
	vtkNew<vtkSmartVolumeMapper> _volumeMapper;
	vtkNew<vtkVolume> _volume;
	vtkNew<vtkVolumeProperty> _volumeProperty;
	vtkNew<vtkPiecewiseFunction> _imageOpacityTF;
	vtkNew<vtkColorTransferFunction> _imageColorTF;	

	double m_ext[6];
	MeteoWizard* m_win;
	VolumeRender(MeteoWizard* win);
	~VolumeRender();

	void createVolume();
	void renderVolume();

	void removeAddActor(bool add);
	void removeAddClippingPlanes(bool add);
	void setPalette(const std::vector<double>& xv, const std::vector<double>& yv);
};
#endif
