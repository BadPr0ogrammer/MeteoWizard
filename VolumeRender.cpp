#include <vector>

#include <vtkTypeInt64Array.h>
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
#include <vtkGenericOpenGLRenderWindow.h>
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

#include "ModelRender.h"
#include "VolumeRender.h"

#include "Palettes.h"

using namespace std;

#include "data_class.h"
#include "data2d_grib.h"
#include "data2d_grib2.h"
#include "data2d_factory.h"
#include "grib_strings.h"
#include "vx_data2d.h"
#include "table_lookup.h"
#include "data2d_grib_utils.h"
#include "data_plane.h"

#include "datec.h"
#include "griblatlon.h"
#include "readgrib.h"

#include "meteowizard.h"

VolumeRender::VolumeRender(MeteoWizard* win) : m_win(win) {}

VolumeRender::~VolumeRender()
{
	removeAddClippingPlanes(false);
	removeAddActor(false);
}

void  VolumeRender::createVolume()
{
	grib2_c* grib;
	////////////////////////////////////////////////////////grib2_c* grib = m_win->m_grib;
	int nx = grib->m_nx;
	int ny = grib->m_ny;
	int nz = grib->m_U.size();// grib->m_grib2DataFile->RecList.size();

	m_ext[0] = grib->m_reg.m_lon_ll;
	m_ext[1] = grib->m_reg.east(nx);
	m_ext[2] = grib->m_reg.m_lat_ll;
	m_ext[3] = grib->m_reg.north(ny);
	m_ext[4] = 0;//0;
	m_ext[5] = nz;//1000;

	_image->SetDimensions(nx, ny, nz);
	_image->SetOrigin(grib->m_reg.m_lon_ll, grib->m_reg.m_lat_ll, 0);
	_image->SetSpacing(grib->m_reg.width(nx) / nx, grib->m_reg.height(ny) / ny, 1);
	_image->AllocateScalars(VTK_FLOAT, 1);
	
	int k = nz - 1;
	//for (auto it = grib->m_grib2DataPlanes.begin(); it != grib->m_grib2DataPlanes.end(); it++, k--) {
	for (auto itu = grib->m_U.begin(), itv = grib->m_V.begin(); itu != grib->m_U.end() && itv != grib->m_V.end(); itu++, itv++, k--) {
		pair<std::string, grib2_rec_c* > u = *itu;
		pair<std::string, grib2_rec_c* > v = *itv;
		/*
		// проверить упорядоченность
		// проверить тег
		// проверить 
		string s = pair_rec.first;
		istringstream iss(s);
		string tag;
		std::getline(iss, tag, ':');
		string level;
		std::getline(iss, level, ':');
		//int k = atoi(level.c_str());
		
		double* dbl = pair_rec.second->m_plane->data_ptr();
		*/
		double* up = u.second->m_plane->data_ptr();
		double* vp = v.second->m_plane->data_ptr();
		for (int j = 0; j < ny; j++) {
			for (int i = 0; i < nx; i++) {
				if (up[i + j * nx] == BAD_VALUE_m9999 || vp[i + j * nx] == BAD_VALUE_m9999)
					continue;

				float* ptr = (float*)_image->GetScalarPointer(i, j, k);
				double val = _hypot(up[i + j * nx], vp[i + j * nx]);
				val = (val - m_win->m_modelRender->m_minRho) / (m_win->m_modelRender->m_maxRho - m_win->m_modelRender->m_minRho);
				*ptr = val;
			}
		}
	}
	_image->Modified();
}

void VolumeRender::setPalette(const std::vector<double>& xv, const std::vector<double>& yv)
{
	_imageColorTF->RemoveAllPoints();
	_imageOpacityTF->RemoveAllPoints();

	pal_ptr_t pal = m_win->m_palettes->m_pal_ptrs[m_win->m_modelRender->m_curPalIdx];
	int sz = m_win->m_palettes->m_size[m_win->m_modelRender->m_curPalIdx];

	for (int i = 0; i < color_num; i++) {
		double x0 = xv[2 * i];
		double x1 = xv[2 * i + 1];
		double y0 = yv[2 * i];
		double y1 = yv[2 * i + 1];

		int id0 = y0 * (sz - 1);
		int id1 = y1 * (sz - 1);

		_imageColorTF->AddRGBSegment(x0, pal[id0][0], pal[id0][1], pal[id0][2], x1, pal[id1][0], pal[id1][1], pal[id1][2]);
		
		_imageOpacityTF->AddPoint(x0, y1 - y0 < 0.001 ? 0 : 0.9999, 0.5, 0);
		_imageOpacityTF->AddPoint(x1, y1 - y0 < 0.001 ? 0 : 0.9999, 0.5, 0);
	}
	_imageColorTF->Build();
	_imageOpacityTF->Modified();
}

void  VolumeRender::renderVolume()
{
	std::vector<double> xv, yv;
	m_win->checkColorTF(xv, yv);
	setPalette(xv, yv);

	_volumeProperty->ShadeOn();
	_volumeProperty->SetInterpolationTypeToLinear();
	_volumeProperty->SetColor(_imageColorTF);
	_volumeProperty->SetScalarOpacity(_imageOpacityTF);
	double w = m_ext[1] - m_ext[0];
	_volumeProperty->SetScalarOpacityUnitDistance(w);//??

	_volumeProperty->SetAmbient(1);
	_volumeProperty->SetDiffuse(1);

	_volume->SetProperty(_volumeProperty);
	_volume->Update();

	_volumeMapper->SetInputData(_image);

	_volumeMapper->SetBlendModeToComposite();

	_volume->SetMapper(_volumeMapper);
	
	m_win->m_modelRender->_renderer->AddViewProp(_volume);
	m_win->m_modelRender->_renderer->Render();

	m_win->m_modelRender->_planeWidget->SetInputData(_image);

	m_win->m_modelRender->_planeWidget->PlaceWidget();
	m_win->m_modelRender->_planeWidget->On();
	vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
	m_win->m_modelRender->_planeWidget->GetPlane(plane);
	vtkSmartPointer<vtkPlaneCollection> planes = vtkSmartPointer<vtkPlaneCollection>::New();
	planes->AddItem(plane);
	
	_volumeMapper->SetClippingPlanes(planes);
	_volumeMapper->Update();

	double* bbox = _image->GetBounds();
	m_win->m_modelRender->_cubeAxesActor->SetBounds(bbox);
}

void VolumeRender::removeAddActor(bool add)
{
	if (add)
		m_win->m_modelRender->_renderer->AddViewProp(_volume);
	else
		m_win->m_modelRender->_renderer->RemoveViewProp(_volume);
}

void VolumeRender::removeAddClippingPlanes(bool add)
{
	if (add) {
		if (_volumeMapper->GetClippingPlanes() != nullptr)
			_volumeMapper->RemoveAllClippingPlanes();

		vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
		m_win->m_modelRender->_planeWidget->GetPlane(plane);
		vtkSmartPointer<vtkPlaneCollection> planes = vtkSmartPointer<vtkPlaneCollection>::New();
		planes->AddItem(plane);

		_volumeMapper->SetClippingPlanes(planes);
	}
	else
		_volumeMapper->RemoveAllClippingPlanes();
}

/*
void VolumeRender::initPalette()
{
	_imageColorTF->RemoveAllPoints();

	for (int i = m_win->m_boxes->size() - 1; i >= 0; i--) {
		box_model_c& pbox = (*m_win->m_boxes)[i];
		double val = (pbox.m_rho - m_win->m_modelRender->m_minRho) / (m_win->m_modelRender->m_maxRho - m_win->m_modelRender->m_minRho);
		int n = val * (m_win->m_palettes->m_size[m_win->m_modelRender->m_curPalIdx] - 1);
		pal_ptr_t pal = m_win->m_palettes->m_pal_ptrs[m_win->m_modelRender->m_curPalIdx];

		_imageColorTF->AddRGBPoint(val, pal[n][0], pal[n][1], pal[n][2]);
	}
	_imageColorTF->Build();
}
*/
/*
void VolumeRender::setPalette()
{
	if (m_win->m_palettes && m_win->m_palettes->m_pal_ptrs.size() > m_win->m_modelRender->m_curPalIdx && m_win->m_modelRender->m_curPalIdx >= 0)
	{		
		std::vector<double> xv, yv;
		for (int i = 0; i < 2 * color_num; i++) {
			xv.push_back(color_tf[i].x());
			yv.push_back(color_tf[i].y());
		}
		initPalette(xv, yv);

		_volumeProperty->SetColor(_imageColorTF);
		_volumeMapper->Update();
		m_win->m_modelRender->_renderer->Render();
	}
}
*/