/******************************************************************************
 *  COPYRIGHT   :       Copyright 2000, EUMETSAT, All Rights Reserved
 *  PRODUCED BY :       This SW (document) was developed by GMV S.A. ,under
 *                      contract of INM, within he context of the EUMETSAT
 *                      Satellite Application facility on Nowcasting
 *                      and Short Range Forecasting, under the Cooperation
 *                      Agreement dated on 05 December 1996, between EUMETSAT
 *                      and INM.
 *  PROJECT     :       SAFNWC
 *  UNIT NAME   :       MSG
 *  FILE        :       msg_l15.h
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       L15 definitions
 *
 ****************************************************************************
 * HISTORY
 *
 *  DATE      VERSION  AUTHOR  REASONS
 *
 *  11/02/03  v0.1     GMV     SAFNWC/MSG v0.1
 *				 SPR-SAF-NWC-IOP-0089 : SMR-SAF-NWC-IOP-0082
 *  26/03/04  v1.0     GMV     SAFNWC/MSG v1.0
 *
 ****************************************************************************/

#include "msg_basictypes.h"

/* ----------------------------------- */
/* Definition of basic data structures */
/* ----------------------------------- */

/* List of data structures and sizes */
/*


SatelliteDefinition_Record                  7  bytes
SatelliteOperations_Record                  28 bytes    
Orbit_Record                             39612 bytes    
Attitude_Record                          20420 bytes
UTCCorrelation_Record                       59 bytes    
SatelliteStatus_Record                  60134  bytes    

PlannedAcquisitionTime_Record               30 bytes    
RadiometerStatus_Record                     54 bytes    
RadiometerSettings_Record                  586 bytes    
RadiometerOperations_Record                 30 bytes    
ImageAcquisition_Record                    700 bytes    

Ephemerids_Record                       326042 bytes    
RelationToImage_Record                      16 bytes    
CelestialEvents_Record                  326058 bytes    

ProjectionDescription_Record                 5 bytes    
ReferenceGrid_Record                        17 bytes    
PlannedCoverageVIS_IR_Record                16 bytes    
PlannedCoverageHRV_Record                   32 bytes    
Level1_5ImageProduction_Record              14 bytes    
ImageDescription_Record                    101 bytes    

RPSummary_Record                            72 bytes    
Level1_5ImageCalibration_Record             16 bytes    
BlackBodyDataUsed_Record                   967 bytes
MPEFCalFeedBack                            384 bytes    
RadProcMTFAdaptation_Record               5376 bytes    
RadiometricProcessing_Record             20815 bytes    

OptAxisDistances_Record                    336 bytes    
EarthModel_Record                           25 bytes
GeometricProcessing_Record               17653 bytes    

IMPFConfiguration_Record                 19786 bytes    

L15Header_Record                        445248 bytes

LineSideInfo_Record                         26 bytes
L15VISIRLine_Record                       4667 bytes    
L15HRVLine_Record                         6987 bytes    

ImageProductionStats_Record                340 bytes    
NavigationExtrationResults_Record         5680 bytes ??
RadiometricQuality_Record               371256 bytes    
GeometricQuality_Record                   2916 bytes    
Timeliness_Record                           12 bytes    
Completeness_Record                         10 bytes
TimelinessAndCompleteness_Record           132 bytes    

*/


typedef struct SatelliteDefinition_Record {         /*     7  bytes */
  GP_SC_ID                   SatelliteId;              /*     2 */
  float                      NominalLongitude;         /*     4 */
  unsigned char              SatelliteStatus;          /*     1 */
} SatelliteDefinition_Record;

typedef struct SatelliteOperations_Record {   /* 28 bytes */
  char ch[28];
} SatelliteOperations_Record;

typedef struct Orbit_Record {            /*  39612 bytes */
  char ch[39612];
} Orbit_Record;

typedef struct Attitude_Record {            /* 20420 bytes */
  char ch[20420];
} Attitude_Record;

typedef struct UTCCorrelation_Record {    /* 59 bytes */
  char ch[59];
} UTCCorrelation_Record;

typedef struct SatelliteStatus_Record {         /* 60134  bytes */
  SatelliteDefinition_Record SatelliteDefinition;      /*     7 */
  SatelliteOperations_Record SatelliteOperations;      /*    28 */
  Orbit_Record               Orbit;                    /* 39612 */
  Attitude_Record            Attitude;                 /* 20420 */
  double                     SpinRateatRCStart;        /*     8 */
  UTCCorrelation_Record      UTCCorrelation;           /*    59 */
} SatelliteStatus_Record;

typedef struct PlannedAcquisitionTime_Record {  /* 30 bytes */
  TimeCDSExpanded   TrueRepeatCycleStart;          /*    10 */
  TimeCDSExpanded   PlannedForwardScanEnd;         /*    10 */
  TimeCDSExpanded   PlannedRepeatCycleEnd;         /*    10 */
} PlannedAcquisitionTime_Record;

typedef struct RadiometerStatus_Record {     /* 54 bytes */
  unsigned char    ChannelStatus[12];           /*    12 */
  unsigned char    DetectorStatus[42];          /*    42 */
} RadiometerStatus_Record;


typedef struct RadiometerSettings_Record {    /* 586 bytes */
  char  ch[586];               /*  586 */
} RadiometerSettings_Record;


typedef struct RadiometerOperations_Record {  /* 30 bytes */
  char  ch[30];              /*  30 */
} RadiometerOperations_Record;

typedef struct ImageAcquisition_Record {              /* 700 bytes */
  PlannedAcquisitionTime_Record PlannedAcquisitionTime;  /*     30 */
  RadiometerStatus_Record       RadiometerStatus;        /*     54 */
  RadiometerSettings_Record     RadiometerSettings;      /*    586 */
  RadiometerOperations_Record   RadiometerOperations;    /*     30 */
} ImageAcquisition_Record;

typedef struct Ephemerids_Record { 
  char ch[326042];
} Ephemerids_Record;

typedef struct RelationToImage_Record {     /* 16 bytes */
  char ch[16];
} RelationToImage_Record;


typedef struct CelestialEvents_Record {         /* 326058 bytes */
  Ephemerids_Record      CelestialBodiesPosition;    /*  326042 */
  RelationToImage_Record RelationToImage;            /*      16 */
} CelestialEvents_Record;

typedef struct ProjectionDescription_Record {    /* 5 bytes */
  unsigned char    TypeOfProjection;                /*    1 */
  float            LongitudeOfSSP;                  /*    4 */
} ProjectionDescription_Record;

typedef struct ReferenceGrid_Record {            /* 17 bytes */
  unsigned int     NumberOfLines;                  /*      4 */
  unsigned int     NumberOfColumns;                /*      4 */
  float            LineDirGridStep;                /*      4 */
  float            ColumnDirGridStep;              /*      4 */
  unsigned char    GridOrigin;                     /*      1 */
} ReferenceGrid_Record;

typedef struct PlannedCoverageVIS_IR_Record {    /* 16 bytes */
  unsigned int    SouthernLinePlanned;              /*     4 */
  unsigned int    NorthernLinePlanned;              /*     4 */
  unsigned int    EasternColumnPlanned;             /*     4 */
  unsigned int    WesternColumnPlanned;             /*     4 */
} PlannedCoverageVIS_IR_Record;

typedef struct PlannedCoverageHRV_Record {      /* 32 bytes */
  unsigned int  LowerSouthLinePlanned;              /*    4 */
  unsigned int  LowerNorthLinePlanned;              /*    4 */
  unsigned int  LowerEastColumnPlanned;             /*    4 */
  unsigned int  LowerWestColumnPlanned;             /*    4 */
  unsigned int  UpperSouthLinePlanned;              /*    4 */
  unsigned int  UpperNorthLinePlanned;              /*    4 */
  unsigned int  UpperEastColumnPlanned;             /*    4 */
  unsigned int  UpperWestColumnPlanned;             /*    4 */
} PlannedCoverageHRV_Record;

typedef struct Level1_5ImageProduction_Record {  /* 14 bytes */
  unsigned char  ImageProcDirection;                /*     1 */
  unsigned char  PixelGenDirection;                 /*     1 */
  unsigned char  PlannedChanProcessing[12];         /*    12 */
} Level1_5ImageProduction_Record;

typedef struct ImageDescription_Record {               /* 101 bytes */
  ProjectionDescription_Record   ProjectionDescription;     /*    5 */
  ReferenceGrid_Record           ReferenceGridVIS_IR;       /*   17 */
  ReferenceGrid_Record           ReferenceGridHRV;          /*   17 */
  PlannedCoverageVIS_IR_Record   PlannedCoverageVIS_IR;     /*   16 */
  PlannedCoverageHRV_Record      PlannedCoverageHRV;        /*   32 */
  Level1_5ImageProduction_Record  Level1_5ImageProduction;  /*   14 */
} ImageDescription_Record;

/* -------------------------------------------------------------------*/

typedef struct RPSummary_Record {                              /* 72 bytes */
  char ch[72];
} RPSummary_Record;

typedef struct Level1_5ImageCalibration_Record {               /* 16 bytes */
  double   Cal_Slope;                                              /*    8 */
  double   Cal_Offset;                                             /*    8 */
} Level1_5ImageCalibration_Record;

typedef struct BlackBodyDataUsed_Record {                     /* 967 bytes */
  char ch[967];
} BlackBodyDataUsed_Record;

typedef struct MPEFCalFeedBack {                              /* 384 bytes */
  char ch[384];
} MPEFCalFeedBack;

typedef struct RadProcMTFAdaptation_Record {                 /* 5376 bytes */
  char ch[5376];
} RadProcMTFAdaptation_Record;

typedef struct RadiometricProcessing_Record {                /* 20815 bytes */
  RPSummary_Record                 RPSummary;                      /*    72 */
  Level1_5ImageCalibration_Record  Level1_5ImageCalibration[12];   /*   192 */
  BlackBodyDataUsed_Record         BlackBodyDataUsed;              /*   967 */
  MPEFCalFeedBack                  IMPF_CAL_Data;                  /*   384 */
  float                            RadTransform[42][64];           /* 10752 */
  RadProcMTFAdaptation_Record      RadProcMTFAdaptation;           /*  5376 */
  float                            StraylightCorrection[12][8][8]; /*  3072 */
} RadiometricProcessing_Record;

/* --------------------------------------------------------------------*/

typedef struct OptAxisDistances_Record {                /* 336 bytes */
  float   E_WFocalPlane[42];                               /* 42 * 4 */
  float   N_SFocalPlane[42];                               /* 42 * 4 */
} OptAxisDistances_Record;

typedef struct EarthModel_Record {                      /* 25 bytes */
  unsigned char     TypeOfEarthModel;                       /*    1 */
  double            EquatorialRadius;                       /*    8 */
  double            NorthPolarRadius;                       /*    8 */
  double            SouthPolarRadius;                       /*    8 */
}EarthModel_Record;

typedef struct GeometricProcessing_Record {           /* 17653 bytes */
  OptAxisDistances_Record  OptAxisDistances;               /*    336 */
  EarthModel_Record        EarthModel;                     /*     25 */
  float                    AtmosphericModel[12][360];      /*  17280 */
  unsigned char            ResamplingFunctions[12];        /*     12 */
} GeometricProcessing_Record;

/* --------------------------------------------------------------------*/

typedef struct IMPFConfiguration_Record {                 /* 19786 bytes */
  char   ch[19786];
} IMPFConfiguration_Record;

/* --------------------------------------------------------------------*/

typedef struct L15Header_Record{                 /*  445248 bytes */
  unsigned char                L15HEADERVersion;        /*      1 */
  SatelliteStatus_Record       SatelliteStatus;         /*  60134 */
  ImageAcquisition_Record      ImageAcquisition;        /*    700 */
  CelestialEvents_Record       CelestialEvents;         /* 326058 */
  ImageDescription_Record      ImageDescription;        /*    101 */
  RadiometricProcessing_Record RadiometricProcessing;   /*  20815 */
  GeometricProcessing_Record   GeometricProcessing;     /*  17653 */
  IMPFConfiguration_Record     IMPFConfiguration;       /*  19786 */
} L15Header_Record;

/* --------------------------------------------------------------------*/
/* --------------------------------------------------------------------*/

typedef struct LineSideInfo_Record {               /*   26 bytes */
  GP_SC_ID           SatelliteId;                          /*  2 */
  TimeCDSExpanded    TrueRepeatCycleStart;                 /* 10 */
  int                LineNumberInVIS_IRGrid;               /*  4 */
  unsigned char      ChannelId;                            /*  1 */
  TimeCDSShort       L10LineMeanAcquisitionTime;           /*  6 */
  unsigned char      LineValidity;                         /*  1 */
  unsigned char      LineRadiometricQuality;               /*  1 */
  unsigned char      LineGeometricQuality;                 /*  1 */
} LineSideInfo_Record;

typedef struct L15VISIRLine_Record {               /* 4667 bytes */
  unsigned char        L15VISIRLineVersion;              /*    1 */
  LineSideInfo_Record  LineSideInfo;                     /*   26 */
  unsigned char        LineData[4640];                   /* 4640 */
} L15VISIRLine_Record;

typedef struct L15HRVLine_Record {                /*  6987 bytes */
  unsigned char        L15HRVLineVersion;                /*    1 */
  LineSideInfo_Record  LineSideInfo;                     /*   26 */
  unsigned char        LineData[6960];                   /* 6960 */
} L15HRVLine_Record;

/* --------------------------------------------------------------------*/
/* --------------------------------------------------------------------*/

typedef struct ImageProductionStats_Record {            /* 340 bytes */
  GP_SC_ID   SatelliteId;
  char       ch[338];
} ImageProductionStats_Record;

typedef struct NavigationExtrationResults_Record {   /*   5680 bytes */
  char ch[5680];
} NavigationExtrationResults_Record;

typedef struct RadiometricQuality_Record {          /*  371256 bytes */
  char ch[371256];
} RadiometricQuality_Record;

typedef struct GeometricQuality_Record {              /*  2916 bytes */
  char ch[2916];
} GeometricQuality_Record;

typedef struct Timeliness_Record {                      /*  12 bytes */
  float MaxDelay;                                           /*     4 */
  float MinDelay;                                           /*     4 */
  float MeanDelay;                                          /*     4 */
} Timeliness_Record;

typedef struct Completeness_Record {                     /* 10 bytes */
  unsigned short  PlannedL15ImageLines;                       /*   2 */
  unsigned short  GeneratedL15ImageLines;                     /*   2 */
  unsigned short  ValidL15ImageLines;                         /*   2 */
  unsigned short  DummyL15ImageLines;                         /*   2 */
  unsigned short  CorruptedL15ImageLines;                     /*   2 */
} Completeness_Record;

typedef struct TimelinessAndCompleteness_Record {      /*  132 bytes */
  Timeliness_Record   Timeliness;                        /*       12 */
  Completeness_Record Completeness[12];                  /*  12 * 10 */
} TimelinessAndCompleteness_Record;

typedef struct L15Trailer_Record {                      /*   380325 bytes */
  unsigned char                     L15TRAILERVersion;          /*      1 */
  ImageProductionStats_Record       ImageProductionStats;        /*    340 */
  NavigationExtrationResults_Record NavigationExtrationResults;  /*   5680 */
  RadiometricQuality_Record         RadiometricQuality;          /* 371256 */
  GeometricQuality_Record           GeometricQuality;            /*   2916 */
  TimelinessAndCompleteness_Record  TimelinessAndCompleteness;   /*    132 */
} L15Trailer_Record;


/* -----------------------------------------------------------------*/


/* ---------------- */
/* Public Functions */
/* ---------------- */

void freadL15HeaderRecord(L15Header_Record *r, FILE *fp);
void freadL15VISIRLineRecord(L15VISIRLine_Record *r, FILE *fp);
void freadL15HRVLineRecord(L15HRVLine_Record *r, FILE *fp);
void UnpackL15VISIRLineData(unsigned char LineData[4640], 
			    unsigned short a[3712]);
void UnpackL15VISIRLineData_12(unsigned char LineData[5568], 
			    unsigned short a[3712]);
void UnpackL15HRVLineData(unsigned char LineData[6960], 
			  unsigned short a[5568]);
void UnpackL15HRVLineData_12(unsigned char LineData[8352], 
			  unsigned short a[5568]);
void freadL15TrailerRecord(L15Trailer_Record *r, FILE *fp);

void fwriteL15HeaderRecord(L15Header_Record *r, FILE *fp);
void fwriteL15VISIRLineRecord(L15VISIRLine_Record *r, FILE *fp);
void fwriteL15HRVLineRecord(L15HRVLine_Record *r, FILE *fp);
void PackL15VISIRLineData(unsigned short a[3712],
			      unsigned char LineData[4640]);
void PackL15VISIRLineData_12(unsigned short a[3712],
			      unsigned char LineData[5568]);
void PackL15HRVLineData(unsigned short a[5568],
			   unsigned char LineData[6960]);
void PackL15HRVLineData_12(unsigned short a[5568],
			   unsigned char LineData[8352]);
void fwriteL15TrailerRecord(L15Trailer_Record *r, FILE *fp);


/* ----------------- */
/* Private Functions */
/* ----------------- */

void freadSatelliteStatusRecord(SatelliteStatus_Record *r, FILE *fp);
void freadSatelliteDefinitionRecord(SatelliteDefinition_Record *r, FILE *fp);
void freadSatelliteOperationsRecord(SatelliteOperations_Record *r, FILE *fp);
void freadOrbitRecord(Orbit_Record *r, FILE *fp);
void freadAttitudeRecord(Attitude_Record *r, FILE *fp);
void freadUTCCorrelationRecord(UTCCorrelation_Record *r, FILE *fp);

void freadImageAcquisitionRecord(ImageAcquisition_Record *r, FILE *fp);
void freadPlannedAcquisitionTimeRecord(
         PlannedAcquisitionTime_Record *r, FILE *fp);
void freadRadiometerStatusRecord(RadiometerStatus_Record *r, FILE *fp);
void freadRadiometerSettingsRecord(RadiometerSettings_Record *r, FILE *fp);
void freadRadiometerOperationsRecord(RadiometerOperations_Record *r, FILE *fp);

void freadCelestialEventsRecord(CelestialEvents_Record *r, FILE *fp);
void freadEphemeridsRecord(Ephemerids_Record *r, FILE *fp);
void freadRelationToImageRecord(RelationToImage_Record *r, FILE *fp);

void freadImageDescriptionRecord(ImageDescription_Record *r, FILE *fp);
void freadProjectionDescriptionRecord(ProjectionDescription_Record *r,
                                      FILE *fp);
void freadReferenceGridRecord(ReferenceGrid_Record *r, FILE *fp);
void freadPlannedCoverageVIS_IRRecord(PlannedCoverageVIS_IR_Record *r,
                                      FILE *fp);
void freadPlannedCoverageHRVRecord(PlannedCoverageHRV_Record *r, FILE *fp);
void freadLevel1_5ImageProductionRecord(Level1_5ImageProduction_Record *r,
                                        FILE *fp);

void freadRadiometricProcessingRecord(RadiometricProcessing_Record *r,
                                      FILE *fp);
void freadRPSummaryRecord(RPSummary_Record *r, FILE *fp);
void freadLevel1_5ImageCalibrationRecord(Level1_5ImageCalibration_Record *r,
                                         FILE *fp);
void freadBlackBodyDataUsedRecord(BlackBodyDataUsed_Record *r, FILE *fp);
void freadMPEFCalFeedBack(MPEFCalFeedBack *r, FILE *fp);
void freadRadProcMTFAdaptationRecord(RadProcMTFAdaptation_Record *r, FILE *fp);

void freadGeometricProcessingRecord(GeometricProcessing_Record *r, FILE *fp);
void freadOptAxisDistancesRecord(OptAxisDistances_Record *r, FILE *fp);
void freadEarthModelRecord(EarthModel_Record *r, FILE *fp);

void freadIMPFConfigurationRecord(IMPFConfiguration_Record *r, FILE *fp);

void freadLineSideInfoRecord(LineSideInfo_Record *r, FILE *fp);

void freadImageProductionStatsRecord(ImageProductionStats_Record *r, FILE *fp);
void freadNavigationExtrationResultsRecord(
      NavigationExtrationResults_Record *r, FILE *fp);
void freadRadiometricQualityRecord(RadiometricQuality_Record *r, FILE *fp);
void freadGeometricQualityRecord(GeometricQuality_Record *r, FILE *fp);
void freadTimelinessRecord(Timeliness_Record *r, FILE *fp);
void freadCompletenessRecord(Completeness_Record *r, FILE *fp);
void freadTimelinessAndCompletenessRecord(TimelinessAndCompleteness_Record *r,
                                FILE *fp);


/* ----------------------------------------------------------------------- */

void fwriteSatelliteStatusRecord(SatelliteStatus_Record *r, FILE *fp);
void fwriteSatelliteDefinitionRecord(SatelliteDefinition_Record *r, FILE *fp);
void fwriteSatelliteOperationsRecord(SatelliteOperations_Record *r, FILE *fp);
void fwriteOrbitRecord(Orbit_Record *r, FILE *fp);
void fwriteAttitudeRecord(Attitude_Record *r, FILE *fp);
void fwriteUTCCorrelationRecord(UTCCorrelation_Record *r, FILE *fp);

void fwriteImageAcquisitionRecord(ImageAcquisition_Record *r, FILE *fp);
void fwritePlannedAcquisitionTimeRecord(
         PlannedAcquisitionTime_Record *r, FILE *fp);
void fwriteRadiometerStatusRecord(RadiometerStatus_Record *r, FILE *fp);
void fwriteRadiometerSettingsRecord(RadiometerSettings_Record *r, FILE *fp);
void fwriteRadiometerOperationsRecord(RadiometerOperations_Record *r, FILE *fp);

void fwriteCelestialEventsRecord(CelestialEvents_Record *r, FILE *fp);
void fwriteEphemeridsRecord(Ephemerids_Record *r, FILE *fp);
void fwriteRelationToImageRecord(RelationToImage_Record *r, FILE *fp);

void fwriteImageDescriptionRecord(ImageDescription_Record *r, FILE *fp);
void fwriteProjectionDescriptionRecord(ProjectionDescription_Record *r,
                                      FILE *fp);
void fwriteReferenceGridRecord(ReferenceGrid_Record *r, FILE *fp);
void fwritePlannedCoverageVIS_IRRecord(PlannedCoverageVIS_IR_Record *r,
                                      FILE *fp);
void fwritePlannedCoverageHRVRecord(PlannedCoverageHRV_Record *r, FILE *fp);
void fwriteLevel1_5ImageProductionRecord(Level1_5ImageProduction_Record *r,
                                        FILE *fp);

void fwriteRadiometricProcessingRecord(RadiometricProcessing_Record *r,
                                      FILE *fp);
void fwriteRPSummaryRecord(RPSummary_Record *r, FILE *fp);
void fwriteLevel1_5ImageCalibrationRecord(Level1_5ImageCalibration_Record *r,
                                         FILE *fp);
void fwriteBlackBodyDataUsedRecord(BlackBodyDataUsed_Record *r, FILE *fp);
void fwriteMPEFCalFeedBack(MPEFCalFeedBack *r, FILE *fp);
void fwriteRadProcMTFAdaptationRecord(RadProcMTFAdaptation_Record *r, FILE *fp);

void fwriteGeometricProcessingRecord(GeometricProcessing_Record *r, FILE *fp);
void fwriteOptAxisDistancesRecord(OptAxisDistances_Record *r, FILE *fp);
void fwriteEarthModelRecord(EarthModel_Record *r, FILE *fp);

void fwriteIMPFConfigurationRecord(IMPFConfiguration_Record *r, FILE *fp);

void fwriteLineSideInfoRecord(LineSideInfo_Record *r, FILE *fp);

void fwriteImageProductionStatsRecord(ImageProductionStats_Record *r, FILE *fp);
void fwriteNavigationExtrationResultsRecord(
      NavigationExtrationResults_Record *r, FILE *fp);
void fwriteRadiometricQualityRecord(RadiometricQuality_Record *r, FILE *fp);
void fwriteGeometricQualityRecord(GeometricQuality_Record *r, FILE *fp);
void fwriteTimelinessRecord(Timeliness_Record *r, FILE *fp);
void fwriteCompletenessRecord(Completeness_Record *r, FILE *fp);
void fwriteTimelinessAndCompletenessRecord(TimelinessAndCompleteness_Record *r,
                                FILE *fp);

void Unpack4pix10bit(unsigned char *data, unsigned short *a);
void Pack4pix10bit(unsigned short *a, unsigned char *data);
void Unpack2pix12bit(unsigned char *data, unsigned short *a);
void Pack2pix12bit(unsigned short *a, unsigned char *data);

