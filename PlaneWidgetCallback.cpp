#if defined(WITH_VTK)

#include <QDoubleSpinBox>

#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkPlaneWidget.h>

#include "PlaneWidgetCallback.h"
#include "ModelRender.h"
#include "meteowizard.h"

void PlaneWidgetCallback::Execute(vtkObject* caller, unsigned long, void*)
{
	model->setCutFunction();
	
	double n[3]{ 0,0,0 };
	model->_planeWidget->GetNormal(n);
	
	mainWindow->m_normSp[0]->setValue(n[0]);
	mainWindow->m_normSp[1]->setValue(n[1]);
	mainWindow->m_normSp[2]->setValue(n[2]);
	
	double c[3]{ 0,0,0 };
	model->_planeWidget->GetCenter(c);

	mainWindow->m_cutSp[0]->setValue(c[0]);
	mainWindow->m_cutSp[1]->setValue(c[1]);
	mainWindow->m_cutSp[2]->setValue(c[2]);
}

#endif
