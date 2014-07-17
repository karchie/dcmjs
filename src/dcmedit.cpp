/**
 * Copyright (c) 2014 Washington University School of Medicine
 * Author: Kevin A. Archie <karchie@wustl.edu>
 */
#include <iostream>

#include "dcmedit.h"

#include "dcdatset.h"
#include "dcfilefo.h"
#include "dcobject.h"
#include "dcstack.h"
#include "dctagkey.h"

#include "ofcond.h"

int remove_matching(DcmDataset &dataset,
		    const Uint16 group_pattern,
		    const Uint16 group_mask = 0xffff,
		    const Uint16 elem_pattern = 0,
		    const Uint16 elem_mask = 0) {
  int count = 0;
  DcmStack stack;
  
  while (dataset.nextObject(stack, OFTrue).good()) {
    DcmObject * const o = stack.top();
    const Uint16 group = o->getGTag();
    const Uint16 elem = o->getETag();
    if (group_pattern == (group & group_mask) &&
	elem_pattern == (elem & elem_mask)) {
      stack.pop();
      delete static_cast<DcmItem *>(stack.top())->remove(o);
      count++;
    }
  }
  return count;
}
  
int remove_private(DcmDataset &dataset) {
  return remove_matching(dataset, 0x0001, 0x0001);
}

extern "C" int
dcmedit_main(const int argc, char * const argv[]) {
  if (argc < 3) {
    std::cout << argv[0] << std::endl;
    std::cout << "Usage: " << argv[0] << " infile outfile" << std::endl;
    return 1;
  }

  DcmFileFormat dcmf;

  dcmf.loadFile(argv[1]);

  // TODO: can we unlink the original file now?

  DcmDataset* dataset = dcmf.getDataset();

  std::cout << "input cardinality " << dataset->card() << std::endl;

  DcmTag tagStudyDesc(0x0008,0x1030);
  const char *studyDesc;
  dataset->findAndGetString(tagStudyDesc, studyDesc);
  std::cout << "Study Description = " << studyDesc << std::endl;

  DcmTagKey tAccessionNumber(0x0008,0x0050);

  dataset->remove(DcmTagKey(0x0018,0x4000)); // Acquisition Comments
  dataset->remove(DcmTagKey(0x0040,0x0555)); // Acquisition Context Sequence
  dataset->remove(DcmTagKey(0x0008,0x0022)); // Acquisition Date
  dataset->remove(DcmTagKey(0x0008,0x002A)); // Acquisition DateTime
  dataset->remove(DcmTagKey(0x0018,0x1400)); // Acquisition Device Processing Description
  dataset->remove(DcmTagKey(0x0018,0x9424)); // Acquisition Protocol Description
  dataset->remove(DcmTagKey(0x0008,0x0032)); // Acquisition Time
  dataset->remove(DcmTagKey(0x0040,0x4035)); // Actual Human Performers Sequence
  dataset->remove(DcmTagKey(0x0010,0x21B0)); // Additional Patient's History
  dataset->remove(DcmTagKey(0x0038,0x0010)); // Admission ID
  dataset->remove(DcmTagKey(0x0038,0x0020)); // Admitting Date
  dataset->remove(DcmTagKey(0x0008,0x1084)); // Admitting Diagnoses Code Sequence
  dataset->remove(DcmTagKey(0x0008,0x1080)); // Admitting Diagnoses Description
  dataset->remove(DcmTagKey(0x0038,0x0021)); // Admitting Time
  dataset->remove(DcmTagKey(0x0000,0x1000)); // Affected SOP Instance UID
  dataset->remove(DcmTagKey(0x0010,0x2110)); // Allergies
  dataset->remove(DcmTagKey(0x4000,0x0010)); // Arbitrary
  dataset->remove(DcmTagKey(0x0040,0xA078)); // Author Observer Sequence
  dataset->remove(DcmTagKey(0x0010,0x1081)); // Branch of Service
  dataset->remove(DcmTagKey(0x0018,0x1007)); // Cassette ID
  dataset->remove(DcmTagKey(0x0040,0x0280)); // Comments on Performed Procedure Step
  dataset->remove(DcmTagKey(0x0020,9161)); // Concatenation UID
  dataset->remove(DcmTagKey(0x0040,0x3001)); // Confidentiality Constraint on Patient Data Description
  dataset->remove(DcmTagKey(0x0070,0x0086)); // Content Creator's Identification Code Sequence
  dataset->remove(DcmTagKey(0x0040,0xA730)); // Content Sequence
  dataset->remove(DcmTagKey(0x0008,0x010D)); // Context Group Extension Creator UID
  dataset->remove(DcmTagKey(0x0018,0xA003)); // Contribution Description
  dataset->remove(DcmTagKey(0x0010,0x2150)); // Country of Residence
  dataset->remove(DcmTagKey(0x0008,0x9123)); // Creator Version UID
  dataset->remove(DcmTagKey(0x0038,0x0300)); // Current Patient Location
  dataset->remove(DcmTagKey(0x0008,0x0025)); // Curve Date
  dataset->remove(DcmTagKey(0x0008,0x0035)); // Curve Time
  dataset->remove(DcmTagKey(0x0040,0xA07C)); // Custodial Organization Sequence
  dataset->remove(DcmTagKey(0xFFFC,0xFFFC)); // Data Set Trailing Padding
  dataset->remove(DcmTagKey(0x0008,0x2111)); // Derivation Description
  dataset->remove(DcmTagKey(0x0018,0x700A)); // Detector ID
  dataset->remove(DcmTagKey(0x0018,0x1000)); // Device Serial Number
  dataset->remove(DcmTagKey(0x0018,0x1002)); // Device UID
  dataset->remove(DcmTagKey(0x0400,0x0100)); // Digital Signature UID
  dataset->remove(DcmTagKey(0xFFFA,0xFFFA)); // Digital Signatures Sequence
  dataset->remove(DcmTagKey(0x0020,0x9164)); // Dimension Organization UID
  dataset->remove(DcmTagKey(0x0038,0x0040)); // Discharge Diagnosis Description
  dataset->remove(DcmTagKey(0x4008,0x011A)); // Distribution Address
  dataset->remove(DcmTagKey(0x4008,0x0119)); // Distribution Name
  dataset->remove(DcmTagKey(0x300A,0x0013)); // Dose Reference UID
  dataset->remove(DcmTagKey(0x0010,0x2160)); // Ethnic Group
  dataset->remove(DcmTagKey(0x0008,0x0058)); // Failed SOP Instance UID List
  dataset->remove(DcmTagKey(0x0070,0x031A)); // Fiducial UID
  dataset->remove(DcmTagKey(0x0020,0x9158)); // Frame Comments
  dataset->remove(DcmTagKey(0x0020,0x0052)); // Frame of Reference UID
  dataset->remove(DcmTagKey(0x0018,0x1008)); // Gantry ID
  dataset->remove(DcmTagKey(0x0018,0x1005)); // Generator ID
  dataset->remove(DcmTagKey(0x0070,0x0001)); // Graphic Annotation Sequence (NOTE: should be dummy value)
  dataset->remove(DcmTagKey(0x0040,0x4037)); // Human Performers Name
  dataset->remove(DcmTagKey(0x0040,0x4036)); // Human Performers Organization
  dataset->remove(DcmTagKey(0x0088,0x0200)); // Icon Image Sequence
  dataset->remove(DcmTagKey(0x0008,0x4000)); // Identifying Comments
  dataset->remove(DcmTagKey(0x0020,0x4000)); // Image Comments
  dataset->remove(DcmTagKey(0x0028,0x4000)); // Image Presentation Comments
  dataset->remove(DcmTagKey(0x0040,0x2400)); // Image Service Request Comments
  dataset->remove(DcmTagKey(0x4008,0x0300)); // Impressions
  dataset->remove(DcmTagKey(0x0008,0x0012)); // Instance Creation Date (NOTE: not in deident standard)
  dataset->remove(DcmTagKey(0x0008,0x0013)); // Instance Creation Time (NOTE: not in deident standard)
  dataset->remove(DcmTagKey(0x0008,0x0014)); // Instance Creator UID
  dataset->remove(DcmTagKey(0x0008,0x0081)); // Institution Address
  dataset->remove(DcmTagKey(0x0008,0x0082)); // Institution Code Sequence
  dataset->remove(DcmTagKey(0x0008,0x0080)); // Institution Name
  dataset->remove(DcmTagKey(0x0008,0x1040)); // Institutional Department Name
  dataset->remove(DcmTagKey(0x0010,0x1050)); // Insurance Plan Identification
  dataset->remove(DcmTagKey(0x0040,0x1011)); // Intended Recipients of Results Identification Sequence
  dataset->remove(DcmTagKey(0x4008,0x0111)); // Interpretation Approver Sequence
  dataset->remove(DcmTagKey(0x4008,0x010C)); // Interpretation Author
  dataset->remove(DcmTagKey(0x4008,0x0115)); // Interpretation Diagnosis Description
  dataset->remove(DcmTagKey(0x4008,0x0202)); // Interpretation ID Issuer
  dataset->remove(DcmTagKey(0x4008,0x0102)); // Interpretation Recorder
  dataset->remove(DcmTagKey(0x4008,0x010B)); // Interpretation Text
  dataset->remove(DcmTagKey(0x4008,0x010A)); // Interpretation Transcriber
  dataset->remove(DcmTagKey(0x0008,0x3010)); // Irradiation Event UID
  dataset->remove(DcmTagKey(0x0038,0x0011)); // Issuer of Admission ID
  dataset->remove(DcmTagKey(0x0010,0x0021)); // Issuer of Patient ID
  dataset->remove(DcmTagKey(0x0038,0x0061)); // Issuer of Service Episode ID
  dataset->remove(DcmTagKey(0x0028,0x1214)); // Large Palette Color Lookup Table UID
  dataset->remove(DcmTagKey(0x0010,0x21D0)); // Last Menstrual Date
  dataset->remove(DcmTagKey(0x0040,0x0404)); // MAC
  dataset->remove(DcmTagKey(0x0002,0x0003)); // Media Storage SOP Instance UID
  dataset->remove(DcmTagKey(0x0010,0x2000)); // Medical Alerts
  dataset->remove(DcmTagKey(0x0010,0x1090)); // Medical Record Locator
  dataset->remove(DcmTagKey(0x0010,0x1080)); // Military Rank
  dataset->remove(DcmTagKey(0x0400,0x0550)); // Modified Attributes Sequence
  dataset->remove(DcmTagKey(0x0020,0x3406)); // Modified Image Description
  dataset->remove(DcmTagKey(0x0020,0x3401)); // Modifying Device ID
  dataset->remove(DcmTagKey(0x0020,0x3404)); // Modifying Device Manufacturer
  dataset->remove(DcmTagKey(0x0008,0x1060)); // Name of Physician(s) Reading Study
  dataset->remove(DcmTagKey(0x0040,0x1010)); // Names of Intended Recipient of Results
  dataset->remove(DcmTagKey(0x0010,0x2180)); // Occupation
  dataset->remove(DcmTagKey(0x0008,0x1072)); // Operators' Identification Sequence
  dataset->remove(DcmTagKey(0x0008,0x1070)); // Operators' Name
  dataset->remove(DcmTagKey(0x0400,0x0561)); // Original Attributes Sequence
  dataset->remove(DcmTagKey(0x0040,0x2010)); // Order Callback Phone Number
  dataset->remove(DcmTagKey(0x0040,0x2008)); // Order Entered By
  dataset->remove(DcmTagKey(0x0040,0x2009)); // Order Enterer Location
  dataset->remove(DcmTagKey(0x0010,0x1000)); // Other Patient IDs
  dataset->remove(DcmTagKey(0x0010,0x1002)); // Other Patient IDs Sequence
  dataset->remove(DcmTagKey(0x0010,0x1001)); // Other Patient Names
  dataset->remove(DcmTagKey(0x0008,0x0024)); // Overlay Date
  dataset->remove(DcmTagKey(0x0008,0x0034)); // Overlay Time
  dataset->remove(DcmTagKey(0x0028,0x1199)); // Palette Color Lookup Table UID
  dataset->remove(DcmTagKey(0x0040,0xA07A)); // Participant Sequence
  dataset->remove(DcmTagKey(0x0010,0x1040)); // Patient Address
  dataset->remove(DcmTagKey(0x0010,0x4000)); // Patient Comments
  dataset->remove(DcmTagKey(0x0010,0x2203)); // Patient Sex Neutered
  dataset->remove(DcmTagKey(0x0038,0x0500)); // Patient State
  dataset->remove(DcmTagKey(0x0040,0x1004)); // Patient Transport Arrangements
  dataset->remove(DcmTagKey(0x0010,0x1010)); // Patient's Age
  dataset->remove(DcmTagKey(0x0010,0x1005)); // Patient's Birth Name
  dataset->remove(DcmTagKey(0x0010,0x0032)); // Patient's Birth Time
  dataset->remove(DcmTagKey(0x0038,0x0400)); // Patient's Institution Residence
  dataset->remove(DcmTagKey(0x0010,0x0050)); // Patient's Insurance Plan Code Sequence
  dataset->remove(DcmTagKey(0x0010,0x1060)); // Patient's Mother's Birth Name
  dataset->remove(DcmTagKey(0x0010,0x0101)); // Patient's Primary Language Code Sequence
  dataset->remove(DcmTagKey(0x0010,0x0102)); // Patient's Primary Language Modifier Code Sequence
  dataset->remove(DcmTagKey(0x0010,0x21F0)); // Patient's Religious Preference
  dataset->remove(DcmTagKey(0x0010,0x1020)); // Patient's Size
  dataset->remove(DcmTagKey(0x0010,0x2154)); // Patient's Telephone Number
  dataset->remove(DcmTagKey(0x0010,0x1030)); // Patient's Weight
  dataset->remove(DcmTagKey(0x0040,0x0243)); // Performed Location
  dataset->remove(DcmTagKey(0x0040,0x0254)); // Performed Procedure Step Description
  dataset->remove(DcmTagKey(0x0040,0x0253)); // Performed Procedure Step ID
  dataset->remove(DcmTagKey(0x0040,0x0244)); // Performed Procedure Step Start Date
  dataset->remove(DcmTagKey(0x0040,0x0245)); // Performed Procedure Step Start Time
  dataset->remove(DcmTagKey(0x0040,0x0241)); // Performed Station AE Title
  dataset->remove(DcmTagKey(0x0040,0x4030)); // Performed Station Geographic Location Code Sequence
  dataset->remove(DcmTagKey(0x0040,0x0242)); // Performed Station Name
  dataset->remove(DcmTagKey(0x0040,0x0248)); // Performed Station Name Code Sequence
  dataset->remove(DcmTagKey(0x0008,0x1052)); // Performing Physicians' Identification Sequence
  dataset->remove(DcmTagKey(0x0008,0x1050)); // Performing Physicians' Name
  dataset->remove(DcmTagKey(0x0040,0x1102)); // Person Address
  dataset->remove(DcmTagKey(0x0040,0x1101)); // Person Identification Code Sequence (NOTE: should be dummy value)
  dataset->remove(DcmTagKey(0x0040,0xA123)); // Person Name (NOTE: should be dummy value)
  dataset->remove(DcmTagKey(0x0040,0x1103)); // Person Telephone Numbers
  dataset->remove(DcmTagKey(0x4008,0x0114)); // Physician Approving Interpretation
  dataset->remove(DcmTagKey(0x0008,0x1062)); // Physican Reading Study Identification Sequence
  dataset->remove(DcmTagKey(0x0008,0x1048)); // Physician(s) of Record
  dataset->remove(DcmTagKey(0x0008,0x1049)); // Physician(s) of Record Identification Sequence
  dataset->remove(DcmTagKey(0x0018,0x1004)); // Plate ID
  dataset->remove(DcmTagKey(0x0040,0x0012)); // Pre-Medication
  dataset->remove(DcmTagKey(0x0010,0x21C0)); // Pregnancy Status
  dataset->remove(DcmTagKey(0x0018,0x1030)); // Protocol Name
  dataset->remove(DcmTagKey(0x0040,0x2001)); // Reason for Imaging Service Request
  dataset->remove(DcmTagKey(0x0032,0x1030)); // Reason for Study
  dataset->remove(DcmTagKey(0x0400,0x0402)); // Referenced Digital Signature Sequence
  dataset->remove(DcmTagKey(0x3006,0x0024)); // Referenced Frame of Reference UID
  dataset->remove(DcmTagKey(0x0040,0x4023)); // Referenced General Purpose Scheduled Procedure Step Transaction UID
  dataset->remove(DcmTagKey(0x0008,0x1140)); // Referenced Image Sequence
  dataset->remove(DcmTagKey(0x0038,0x1234)); // Referenced Patient Atlas Sequence
  dataset->remove(DcmTagKey(0x0008,0x1120)); // Referenced Patient Sequence
  dataset->remove(DcmTagKey(0x0008,0x1111)); // Referenced Performed Procedure Step Sequence
  dataset->remove(DcmTagKey(0x0400,0x0403)); // Referenced SOP Instance MAC Sequence
  dataset->remove(DcmTagKey(0x0008,0x1155)); // Referenced SOP Instance UID
  dataset->remove(DcmTagKey(0x0004,0x1511)); // Referenced SOP Instance UID in File
  dataset->remove(DcmTagKey(0x0008,0x1110)); // Referenced Study Sequence
  dataset->remove(DcmTagKey(0x0008,0x0092)); // Referring Physician's Address
  dataset->remove(DcmTagKey(0x0008,0x0096)); // Referring Physician's Identification Sequence
  dataset->remove(DcmTagKey(0x0008,0x0094)); // Referring Physician's Telephone Numbers
  dataset->remove(DcmTagKey(0x0010,0x2152)); // Region of Residence
  dataset->remove(DcmTagKey(0x3006,0x00C2)); // Related Frame of Reference UID
  dataset->remove(DcmTagKey(0x0040,0x0275)); // Request Attributes Sequence
  dataset->remove(DcmTagKey(0x0032,0x1070)); // Requested Contrast Agent
  dataset->remove(DcmTagKey(0x0040,0x1400)); // Requested Procedure Comments
  dataset->remove(DcmTagKey(0x0032,0x1060)); // Requested Procedure Description
  dataset->remove(DcmTagKey(0x0040,0x1001)); // Requested Procedure ID
  dataset->remove(DcmTagKey(0x0040,0x1005)); // Requested Procedure Location
  dataset->remove(DcmTagKey(0x0000,0x1001)); // Requested SOP Instance UID
  dataset->remove(DcmTagKey(0x0032,0x1032)); // Requesting Physican
  dataset->remove(DcmTagKey(0x0032,0x1033)); // Requesting Service
  dataset->remove(DcmTagKey(0x0010,0x2299)); // Responsible Organization
  dataset->remove(DcmTagKey(0x0010,0x2297)); // Responsible Person
  dataset->remove(DcmTagKey(0x4008,0x4000)); // Results Comments
  dataset->remove(DcmTagKey(0x4008,0x0118)); // Results Distribution List Sequence
  dataset->remove(DcmTagKey(0x4008,0x0042)); // Results ID Issuer
  dataset->remove(DcmTagKey(0x300E,0x0008)); // Reviewer Name
  dataset->remove(DcmTagKey(0x0040,0x4034)); // Scheduled Human Performers Sequence
  dataset->remove(DcmTagKey(0x0038,0x001E)); // Scheduled Patient Institution Reference
  dataset->remove(DcmTagKey(0x0040,0x000B)); // Scheduled Performing Physician Identification Sequence
  dataset->remove(DcmTagKey(0x0040,0x0006)); // Scheduled Performing Physician Name
  dataset->remove(DcmTagKey(0x0040,0x0004)); // Scheduled Procedure Step End Date
  dataset->remove(DcmTagKey(0x0040,0x0005)); // Scheduled Procedure Step End Time
  dataset->remove(DcmTagKey(0x0040,0x0007)); // Scheduled Procedure Step Description
  dataset->remove(DcmTagKey(0x0040,0x0011)); // Scheduled Procedure Step Location
  dataset->remove(DcmTagKey(0x0040,0x0002)); // Scheduled Procedure Step Start Date
  dataset->remove(DcmTagKey(0x0040,0x0003)); // Scheduled Procedure Step Start Time
  dataset->remove(DcmTagKey(0x0040,0x0001)); // Scheduled Station AE Title
  dataset->remove(DcmTagKey(0x0040,0x4027)); // Scheduled Station Geographic Location Code Sequence
  dataset->remove(DcmTagKey(0x0040,0x0010)); // Scheduled Station Name
  dataset->remove(DcmTagKey(0x0040,0x4025)); // Scheduled Station Name Code Sequence
  dataset->remove(DcmTagKey(0x0032,0x1020)); // Scheduled Study Location
  dataset->remove(DcmTagKey(0x0032,0x1021)); // Scheduled Study Location AE Title
  dataset->remove(DcmTagKey(0x0008,0x0021)); // Series Date
  dataset->remove(DcmTagKey(0x0008,0x103E)); // Series Description
  dataset->remove(DcmTagKey(0x0020,0x000E)); // Series Instance UID
  dataset->remove(DcmTagKey(0x0008,0x0031)); // Series Time
  dataset->remove(DcmTagKey(0x0038,0x0062)); // Service Episode Description
  dataset->remove(DcmTagKey(0x0038,0x0060)); // Service Episode ID
  dataset->remove(DcmTagKey(0x0010,0x21A0)); // Smoking Status
  dataset->remove(DcmTagKey(0x0008,0x2112)); // Source Image Sequence
  dataset->remove(DcmTagKey(0x0038,0x0050)); // Special Needs
  dataset->remove(DcmTagKey(0x0008,0x1010)); // Station Name
  dataset->remove(DcmTagKey(0x0088,0x0140)); // Storage Media Fileset UID
  dataset->remove(DcmTagKey(0x0032,0x4000)); // Study Comments
  dataset->remove(DcmTagKey(0x0032,0x0012)); // Study ID Issuer
  dataset->remove(DcmTagKey(0x0020,0x0200)); // Synchronization Frame of Reference UID
  dataset->remove(DcmTagKey(0x0040,0xDB0D)); // Template Extension Creator UID
  dataset->remove(DcmTagKey(0x0040,0xDB0D)); // Template Extension Creator UID
  dataset->remove(DcmTagKey(0x0008,0x1195)); // Transaction UID
  dataset->remove(DcmTagKey(0x0040,0xA124)); // UID
  dataset->remove(DcmTagKey(0x0040,0xA088)); // Verifying Observer Identification Code Sequence
  dataset->remove(DcmTagKey(0x0040,0xA075)); // Verifying Observer Name (NOTE: should be dummy value)
  dataset->remove(DcmTagKey(0x0040,0xA073)); // Verifying Observer Sequence (NOTE: should be dummy value)
  dataset->remove(DcmTagKey(0x0040,0xA027)); // Verifying Organization
  dataset->remove(DcmTagKey(0x0038,0x4000)); // Visit Comments

  remove_private(*dataset);
  remove_matching(*dataset, 0x5000, 0xff00); // curve data
  remove_matching(*dataset, 0x6000, 0xff00, 0x4000, 0xffff); // overlay comments
  remove_matching(*dataset, 0x6000, 0xff00, 0x3000, 0xffff); // overlay data

  std::cout << "output cardinality " << dataset->card() << std::endl;

  dcmf.saveFile(argv[2]);

  return 0;
}
