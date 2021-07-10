#/******************************************************************************
# *  COPYRIGHT   :       Copyright 2000, EUMETSAT, All Rights Reserved
# *  PRODUCED BY :       This SW (document) was developed by GMV S.A. ,under
# *                      contract of INM, within he context of the EUMETSAT
# *                      Satellite Application facility on Nowcasting
# *                      and Short Range Forecasting, under the Cooperation
# *                      Agreement dated on 05 December 1996, between EUMETSAT
# *                      and INM.
# *  PROJECT     :       SAFNWC
# *  UNIT NAME   :       NWCLIB
# *  FILE        :       makefile
# *  TYPE        :       makefile
# *
# *  FUNCTION    :       Install MSG
# *
# ******************************************************************************
# * HISTORY
# *
# *  DATE      VERSION  AUTHOR  REASONS
# *
# *  27/01/03  v0.1     GMV     System integration
# *  26/03/04  v1.0     GMV     SAFNWC/MSG v1.0
# *
# ******************************************************************************

MSG_SOURCE =  msg_basictypes_Double.c  \
 	     msg_basictypes_Float.c  \
             msg_basictypes_GPSCID.c  \
             msg_basictypes_SInt.c  \
             msg_basictypes_SShort.c  \
             msg_basictypes_TimeCDS.c  \
             msg_basictypes_TimeCDSExpanded.c  \
             msg_basictypes_TimeCDSShort.c  \
             msg_basictypes_UInt.c  \
             msg_basictypes_UShort.c  \
             msg_hrit_HRITHeader0.c  \
             msg_hrit_HRITHeader1.c  \
             msg_hrit_HRITHeader128.c  \
             msg_hrit_HRITHeader129.c  \
             msg_hrit_HRITHeader2.c  \
             msg_hrit_HRITHeader4.c  \
             msg_hrit_HRITHeader5.c  \
             msg_hrit_LineQualityRecord.c  \
             msg_l15_4pix10bit.c  \
             msg_l15_2pix12bit.c  \
             msg_l15_AttitudeRecord.c  \
             msg_l15_BlackBodyDataUsedRecord.c  \
             msg_l15_CelestialEventsRecord.c  \
             msg_l15_CompletenessRecord.c  \
             msg_l15_EarthModelRecord.c  \
             msg_l15_EphemeridsRecord.c  \
             msg_l15_GeometricProcessingRecord.c  \
             msg_l15_GeometricQualityRecord.c  \
             msg_l15_IMPFConfigurationRecord.c  \
             msg_l15_ImageAcquisitionRecord.c  \
             msg_l15_ImageDescriptionRecord.c  \
             msg_l15_ImageProductionStatsRecord.c  \
             msg_l15_L15HRVLineData.c  \
             msg_l15_L15HRVLineRecord.c  \
             msg_l15_L15HeaderRecord.c  \
             msg_l15_L15TrailerRecord.c  \
             msg_l15_L15VISIRLineData.c  \
             msg_l15_L15VISIRLineRecord.c  \
             msg_l15_Level1_5ImageCalibrationRecord.c  \
             msg_l15_Level1_5ImageProductionRecord.c  \
             msg_l15_LineSideInfoRecord.c  \
             msg_l15_MPEFCalFeedBack.c  \
             msg_l15_NavigationExtrationResultsRecord.c  \
             msg_l15_OptAxisDistancesRecord.c  \
             msg_l15_OrbitRecord.c  \
             msg_l15_PlannedAcquisitionTimeRecord.c  \
             msg_l15_PlannedCoverageHRVRecord.c  \
             msg_l15_PlannedCoverageVIS_IRRecord.c  \
             msg_l15_ProjectionDescriptionRecord.c  \
             msg_l15_RPSummaryRecord.c  \
             msg_l15_RadProcMTFAdaptationRecord.c  \
             msg_l15_RadiometerOperationsRecord.c  \
             msg_l15_RadiometerSettingsRecord.c  \
             msg_l15_RadiometerStatusRecord.c  \
             msg_l15_RadiometricProcessingRecord.c  \
             msg_l15_RadiometricQualityRecord.c  \
             msg_l15_ReferenceGridRecord.c  \
             msg_l15_RelationToImageRecord.c  \
             msg_l15_SatelliteDefinitionRecord.c  \
             msg_l15_SatelliteOperationsRecord.c  \
             msg_l15_SatelliteStatusRecord.c  \
             msg_l15_TimelinessAndCompletenessRecord.c  \
             msg_l15_TimelinessRecord.c  \
             msg_l15_UTCCorrelationRecord.c \
	     msg_navigation.c \
	     msg_calibration.c


MSG_OBJECTS = $(MSG_SOURCE:.c=.o)

MSGLIB = $(SAFNWC)/bin/libmsg.a
INC_DIR = $(SAFNWC)/include/NWCLIB

compile: $(MSGLIB)

all:
	$(MAKE) clear
	$(MAKE) compile

$(MSGLIB): $(MSG_OBJECTS)
	ar -cr $@ $(MSG_OBJECTS)

.c.o:
	$(CC) -c $< $(CFLAGS) -I$(INC_DIR)

clean:
	rm -f *.o

clear:
	$(MAKE) clean
	rm -f $(MSGLIB)

