#if defined(WITH_VTK)
#pragma once

#include <vtkCommand.h>

class ModelRender;
class MeteoWizard;

class PlaneWidgetCallback : public vtkCommand
{
public:
	static PlaneWidgetCallback* New()
	{
		return new PlaneWidgetCallback;
	}
	virtual void Execute(vtkObject* caller, unsigned long, void*);

	ModelRender* model;
	MeteoWizard* mainWindow;
	PlaneWidgetCallback() : model(nullptr), mainWindow(nullptr) {}
};
#endif

