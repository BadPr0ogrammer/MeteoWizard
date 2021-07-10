#if 0
/*****************************************************************************
* HISTORY
*
*  DATE      VERSION  AUTHOR  REASONS
*
*  24/01/00  1        GMV     Creation.
*  02/03/01  1.3      GMV     SPR-0003-MFL  : SMR-0007-GMV/2
*		   	      SPR-0016-MFL  : SMR-0020-GMV/2
*			      SPR-0012-GMV  : SMR-0054-GMV
*			      SPR-0021-GMV  : SMR-0064-GMV
*			      SPR-0037-MFL  : SMR-0125-GMV
*  16/09/02  v0.1     GMV     SAFNWC/MSG v0.1
*                              SPR-SAF-NWC-IOP-0023 : SMR-SAF-NWC-IOP-0013
*                              SPR-SAF-NWC-IOP-0057 : SMR-SAF-NWC-IOP-0050
* 			       SPR-SAF-NWC-IOP-0090 : SMR-SAF-NWC-IOP-0083
*  06/11/03  v1.0     GMV     SAFNWC/MSG v1.0
*                              SPR-SAF-NWC-IOP-0127 : SMR-SAF-NWC-IOP-0104
*  Oct 2006  v2.0     GMV     SAFNWC/MSG v2.0
*                              SPR-SAF-NWC-IOP-0217 : SMR-SAF-NWC-IOP-0200
*                              SPR-SAF-NWC-IOP-0244 : SMR-SAF-NWC-IOP-0227
*
*  AUG 2007  v2008    GMV     SAFNWC/MSG v2008
*                              SPR-SAF-NWC-CDOP-0302 : SMR-SAF-NWC-CDOP-0288
*  OCT 2010  v2011    GMV     SAFNWC/MSG v2011
*                              SPR-SAF-NWC-CDOP-0446 : SMR-SAF-NWC-CDOP-0xxx
*
 *****************************************************************************/
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
extern "C" {
	//#include "sevext.h"
#include "sevext_basictypes.h"
#include "msg_hrit.h"
#include "msg_l15.h"
}

#include "inc.h"

#include "ReadPrologue.h"

int ReadPrologue(FILE * fd, Seviri_struct * seviri);

int ReadMSGInfo(char* fname, CvRect_ * ret, double** p_calib)
{
	Seviri_struct seviri;
	char* p, bn[300];
	FILE* file;
	int len = (int)strlen(fname);
	bn[sizeof(bn) - 1] = 0;
	strncpy(bn, fname, sizeof(bn) - 1);

	memset(&seviri, 0, sizeof(Seviri_struct));

	if (!(seviri.file = (File_information*)calloc(1, sizeof(File_information)))
		|| !(seviri.file->name = (char*)calloc(1, 300))
		|| !(seviri.sat_params = (Processing_sat_params*)calloc(1, sizeof(Processing_sat_params)))
		|| !(seviri.other_sat_params = (Sat_params*)calloc(1, sizeof(Sat_params)))
		|| !(seviri.planned_acq_time = (Planned_acquisition_time*)calloc(1, sizeof(Planned_acquisition_time)))
		|| !(seviri.sun_position = (Ephemeris*)calloc(1, sizeof(Ephemeris)))
		|| !(seviri.image_descriptor = (Image_description*)calloc(1, sizeof(Image_description)))) {
		//ATLTRACE(L"[%s]", fname);
		return FALSE;
	}
	p = bn + len - 2;
	*p = '_';
	p = bn + len - 25;
	memcpy(p, "PRO___", 6);
	p = bn + len - 35;
	memcpy(p, "______", 6);

	file = fopen(bn, "rb");
	if (!file) {
		//ATLTRACE(L"[%s]", fname);
		return FALSE;
	}

	if (!ReadPrologue(file, &seviri)) {
		fclose(file);
		//ATLTRACE(L"[%s]", fname);
		return FALSE;
	}

	ret->height = seviri.image_descriptor->planned_cov_HRV.up_south_line;
	ret->y = seviri.image_descriptor->planned_cov_HRV.up_north_line;
	ret->width = seviri.image_descriptor->planned_cov_HRV.up_east_line;
	ret->x = seviri.image_descriptor->planned_cov_HRV.up_west_line;

	if (p_calib) {
		*p_calib = (double*)malloc(12 * 2 * sizeof(double));
		memcpy(*p_calib, seviri.calibration, 12 * 2 * sizeof(double));
	}
	if (seviri.file->name)
		free(seviri.file->name);
	if (seviri.file)
		free(seviri.file);
	if (seviri.sat_params)
		free(seviri.sat_params);
	if (seviri.other_sat_params)
		free(seviri.other_sat_params);
	if (seviri.planned_acq_time)
		free(seviri.planned_acq_time);
	if (seviri.sun_position)
		free(seviri.sun_position);
	if (seviri.image_descriptor)
		free(seviri.image_descriptor);

	fclose(file);

	return TRUE;
}

int ReadPrologue(FILE* fd, Seviri_struct* seviri)
{
	hrit_header0* h0 = (hrit_header0*)malloc(sizeof(hrit_header0));
	hrit_header4* h4 = (hrit_header4*)malloc(sizeof(hrit_header4));
	L15Header_Record* l15h = (L15Header_Record*)malloc(sizeof(L15Header_Record));
	memset(h0, 0, sizeof(hrit_header0));
	memset(h4, 0, sizeof(hrit_header4));
	memset(l15h, 0, sizeof(L15Header_Record));
	/* Read HRIT Header 0 */
	freadHRITHeader0(h0, fd);

	if (h0->Header_Type != 0) {
		//ATLTRACE;
		return FALSE;
	}
	if (h0->Header_Record_Length != HEADER0_LENGTH) {
		//ATLTRACE;
		return FALSE;
	}
	if ((unsigned char)h0->File_Type_Code != 128)  /* PROLOGUE */ {
		//ATLTRACE;
		return FALSE;
	}
	/* Read HRIT Header 4 */
	freadHRITHeader4(h4, fd);

	if (h4->Header_Type != 4) {
		//ATLTRACE;
		return FALSE;
	}
	if (h4->Header_Record_Length != HEADER4_LENGTH) {
		//ATLTRACE;
		return FALSE;
	}

	/* Skip HRIT headers */
	if (fseek(fd, h0->Total_Header_Length, SEEK_SET) == -1) {
		//ATLTRACE;
		return FALSE;
	}
	/* Read SEVIRI1.5 headers information and store useful data in the SEVIRI struct */

	// Read Satellite Status Record 
	freadSatelliteStatusRecord(&l15h->SatelliteStatus, fd);
	seviri->sat_params->satellite_identifier = l15h->SatelliteStatus.SatelliteDefinition.SatelliteId;
	seviri->sat_params->ref_long = l15h->SatelliteStatus.SatelliteDefinition.NominalLongitude;
	seviri->sat_params->ref_alt = 0.0;
	seviri->sat_params->nb_tcols = 0;
	seviri->sat_params->nb_tlines = 0;
	seviri->sat_params->acq_dur = 0;
	seviri->sat_params->nb_day_slots = 0;
	seviri->sat_params->time_slot1 = 0;

	// Copy orbit, attitude and spin rate information 
	memcpy(&seviri->other_sat_params->orbit,
		&l15h->SatelliteStatus.Orbit.ch, sizeof(Orbit_Record));
	memcpy(&seviri->other_sat_params->attitude,
		&l15h->SatelliteStatus.Attitude.ch, sizeof(Attitude_Record));
	memcpy(&seviri->other_sat_params->spin_rate,
		&l15h->SatelliteStatus.SpinRateatRCStart, sizeof(double));
	// Read Image Acquisition Record 
	freadImageAcquisitionRecord(&l15h->ImageAcquisition, fd);

	// Copy Planned Acquisition Time information 
	memcpy(&seviri->planned_acq_time->repeat_cycle_start,
		&l15h->ImageAcquisition.PlannedAcquisitionTime.TrueRepeatCycleStart,
		sizeof(TimeCDSExpanded));
	memcpy(&seviri->planned_acq_time->planned_fwd_scan_end,
		&l15h->ImageAcquisition.PlannedAcquisitionTime.PlannedForwardScanEnd,
		sizeof(TimeCDSExpanded));
	memcpy(&seviri->planned_acq_time->planned_cycle_end,
		&l15h->ImageAcquisition.PlannedAcquisitionTime.PlannedRepeatCycleEnd,
		sizeof(TimeCDSExpanded));
	// Read Celestial Events Record (only sun information) 
	freadCelestialEventsRecord(&l15h->CelestialEvents, fd);

	// Copy Ephemeris Record information 
	memcpy(&seviri->sun_position->start_time,
		&l15h->CelestialEvents.CelestialBodiesPosition.ch,
		sizeof(TimeCDSShort));
	memcpy(&seviri->sun_position->end_time,
		&l15h->CelestialEvents.CelestialBodiesPosition.ch[6],
		sizeof(TimeCDSShort));
	memcpy(&seviri->sun_position->orbit_file_time,
		&l15h->CelestialEvents.CelestialBodiesPosition.ch[12], 16);
	memcpy(&seviri->sun_position->attitude_file_time,
		&l15h->CelestialEvents.CelestialBodiesPosition.ch[28], 16);
	memcpy(&seviri->sun_position->sun_ephemeris,
		&l15h->CelestialEvents.CelestialBodiesPosition.ch[28044], 14000);

	// Read Image Description Record 
	freadImageDescriptionRecord(&l15h->ImageDescription, fd);

	// Copy Image Description Information 
	seviri->image_descriptor->projection.type_of_projection = (Projection_type)l15h->ImageDescription.ProjectionDescription.TypeOfProjection;
	seviri->image_descriptor->projection.SSP_longitude = l15h->ImageDescription.ProjectionDescription.LongitudeOfSSP;

	seviri->image_descriptor->grid_VIS_IR.nb_lines = l15h->ImageDescription.ReferenceGridVIS_IR.NumberOfLines;
	seviri->image_descriptor->grid_VIS_IR.nb_columns = l15h->ImageDescription.ReferenceGridVIS_IR.NumberOfColumns;
	seviri->image_descriptor->grid_VIS_IR.line_grid_step = l15h->ImageDescription.ReferenceGridVIS_IR.LineDirGridStep;
	seviri->image_descriptor->grid_VIS_IR.column_grid_step = l15h->ImageDescription.ReferenceGridVIS_IR.ColumnDirGridStep;
	seviri->image_descriptor->grid_VIS_IR.origin = (Grid_origin)l15h->ImageDescription.ReferenceGridVIS_IR.GridOrigin;

	seviri->image_descriptor->grid_HRV.nb_lines = l15h->ImageDescription.ReferenceGridHRV.NumberOfLines;
	seviri->image_descriptor->grid_HRV.nb_columns = l15h->ImageDescription.ReferenceGridHRV.NumberOfColumns;
	seviri->image_descriptor->grid_HRV.line_grid_step = l15h->ImageDescription.ReferenceGridHRV.LineDirGridStep;
	seviri->image_descriptor->grid_HRV.column_grid_step = l15h->ImageDescription.ReferenceGridHRV.ColumnDirGridStep;
	seviri->image_descriptor->grid_HRV.origin = (Grid_origin)l15h->ImageDescription.ReferenceGridHRV.GridOrigin;

	seviri->image_descriptor->planned_cov_HRV.low_south_line = l15h->ImageDescription.PlannedCoverageHRV.LowerSouthLinePlanned;
	seviri->image_descriptor->planned_cov_HRV.low_north_line = l15h->ImageDescription.PlannedCoverageHRV.LowerNorthLinePlanned;
	seviri->image_descriptor->planned_cov_HRV.low_east_line = l15h->ImageDescription.PlannedCoverageHRV.LowerEastColumnPlanned;
	seviri->image_descriptor->planned_cov_HRV.low_west_line = l15h->ImageDescription.PlannedCoverageHRV.LowerWestColumnPlanned;

	seviri->image_descriptor->planned_cov_HRV.up_south_line = l15h->ImageDescription.PlannedCoverageHRV.UpperSouthLinePlanned;
	seviri->image_descriptor->planned_cov_HRV.up_north_line = l15h->ImageDescription.PlannedCoverageHRV.UpperNorthLinePlanned;
	seviri->image_descriptor->planned_cov_HRV.up_east_line = l15h->ImageDescription.PlannedCoverageHRV.UpperEastColumnPlanned;
	seviri->image_descriptor->planned_cov_HRV.up_west_line = l15h->ImageDescription.PlannedCoverageHRV.UpperWestColumnPlanned;

	memcpy(&seviri->image_descriptor->planned_cov_VIS_IR, &l15h->ImageDescription.PlannedCoverageVIS_IR,
		sizeof(PlannedCoverageVIS_IR_Record));
	memcpy(&seviri->image_descriptor->planned_cov_HRV, &l15h->ImageDescription.PlannedCoverageHRV,
		sizeof(PlannedCoverageHRV_Record));
	seviri->image_descriptor->image_production.image_prod_dir = (Prod_direction)l15h->ImageDescription.Level1_5ImageProduction.ImageProcDirection;
	seviri->image_descriptor->image_production.pixel_gen_dir = (Pixel_direction)l15h->ImageDescription.Level1_5ImageProduction.PixelGenDirection;

	memset(&seviri->image_descriptor->image_production.planned_chan_proc, 0, 12);
	memcpy(&seviri->image_descriptor->image_production.planned_chan_proc,
		&l15h->ImageDescription.Level1_5ImageProduction.PlannedChanProcessing,
		12);
	// Read Radiometric Processing Record (just calibration information)   
	freadRadiometricProcessingRecord(&l15h->RadiometricProcessing, fd);

	// Copy Image Calibration information 
	memcpy(&seviri->calibration, &l15h->RadiometricProcessing.Level1_5ImageCalibration, 12 * sizeof(Level1_5ImageCalibration_Record));

	free(h0);
	free(h4);
	free(l15h);

	return TRUE;

}
#endif
