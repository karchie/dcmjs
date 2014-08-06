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

void edit_dataset(DcmDataset& ds) {
  ds.remove(DcmTagKey(0x0018,0x4000)); // Acquisition Comments
  ds.remove(DcmTagKey(0x0040,0x0555)); // Acquisition Context Sequence
  ds.remove(DcmTagKey(0x0008,0x0022)); // Acquisition Date
  ds.remove(DcmTagKey(0x0008,0x002A)); // Acquisition DateTime
  ds.remove(DcmTagKey(0x0018,0x1400)); // Acquisition Device Processing Description
  ds.remove(DcmTagKey(0x0018,0x9424)); // Acquisition Protocol Description
  ds.remove(DcmTagKey(0x0008,0x0032)); // Acquisition Time
  ds.remove(DcmTagKey(0x0040,0x4035)); // Actual Human Performers Sequence
  ds.remove(DcmTagKey(0x0010,0x21B0)); // Additional Patient's History
  ds.remove(DcmTagKey(0x0038,0x0010)); // Admission ID
  ds.remove(DcmTagKey(0x0038,0x0020)); // Admitting Date
  ds.remove(DcmTagKey(0x0008,0x1084)); // Admitting Diagnoses Code Sequence
  ds.remove(DcmTagKey(0x0008,0x1080)); // Admitting Diagnoses Description
  ds.remove(DcmTagKey(0x0038,0x0021)); // Admitting Time
  ds.remove(DcmTagKey(0x0000,0x1000)); // Affected SOP Instance UID
  ds.remove(DcmTagKey(0x0010,0x2110)); // Allergies
  ds.remove(DcmTagKey(0x4000,0x0010)); // Arbitrary
  ds.remove(DcmTagKey(0x0040,0xA078)); // Author Observer Sequence
  ds.remove(DcmTagKey(0x0010,0x1081)); // Branch of Service
  ds.remove(DcmTagKey(0x0018,0x1007)); // Cassette ID
  ds.remove(DcmTagKey(0x0040,0x0280)); // Comments on Performed Procedure Step
  ds.remove(DcmTagKey(0x0020,9161)); // Concatenation UID
  ds.remove(DcmTagKey(0x0040,0x3001)); // Confidentiality Constraint on Patient Data Description
  ds.remove(DcmTagKey(0x0070,0x0086)); // Content Creator's Identification Code Sequence
  ds.remove(DcmTagKey(0x0040,0xA730)); // Content Sequence
  ds.remove(DcmTagKey(0x0008,0x010D)); // Context Group Extension Creator UID
  ds.remove(DcmTagKey(0x0018,0xA003)); // Contribution Description
  ds.remove(DcmTagKey(0x0010,0x2150)); // Country of Residence
  ds.remove(DcmTagKey(0x0008,0x9123)); // Creator Version UID
  ds.remove(DcmTagKey(0x0038,0x0300)); // Current Patient Location
  ds.remove(DcmTagKey(0x0008,0x0025)); // Curve Date
  ds.remove(DcmTagKey(0x0008,0x0035)); // Curve Time
  ds.remove(DcmTagKey(0x0040,0xA07C)); // Custodial Organization Sequence
  ds.remove(DcmTagKey(0xFFFC,0xFFFC)); // Data Set Trailing Padding
  ds.remove(DcmTagKey(0x0008,0x2111)); // Derivation Description
  ds.remove(DcmTagKey(0x0018,0x700A)); // Detector ID
  ds.remove(DcmTagKey(0x0018,0x1000)); // Device Serial Number
  ds.remove(DcmTagKey(0x0018,0x1002)); // Device UID
  ds.remove(DcmTagKey(0x0400,0x0100)); // Digital Signature UID
  ds.remove(DcmTagKey(0xFFFA,0xFFFA)); // Digital Signatures Sequence
  ds.remove(DcmTagKey(0x0020,0x9164)); // Dimension Organization UID
  ds.remove(DcmTagKey(0x0038,0x0040)); // Discharge Diagnosis Description
  ds.remove(DcmTagKey(0x4008,0x011A)); // Distribution Address
  ds.remove(DcmTagKey(0x4008,0x0119)); // Distribution Name
  ds.remove(DcmTagKey(0x300A,0x0013)); // Dose Reference UID
  ds.remove(DcmTagKey(0x0010,0x2160)); // Ethnic Group
  ds.remove(DcmTagKey(0x0008,0x0058)); // Failed SOP Instance UID List
  ds.remove(DcmTagKey(0x0070,0x031A)); // Fiducial UID
  ds.remove(DcmTagKey(0x0020,0x9158)); // Frame Comments
  ds.remove(DcmTagKey(0x0020,0x0052)); // Frame of Reference UID
  ds.remove(DcmTagKey(0x0018,0x1008)); // Gantry ID
  ds.remove(DcmTagKey(0x0018,0x1005)); // Generator ID
  ds.remove(DcmTagKey(0x0070,0x0001)); // Graphic Annotation Sequence (NOTE: should be dummy value)
  ds.remove(DcmTagKey(0x0040,0x4037)); // Human Performers Name
  ds.remove(DcmTagKey(0x0040,0x4036)); // Human Performers Organization
  ds.remove(DcmTagKey(0x0088,0x0200)); // Icon Image Sequence
  ds.remove(DcmTagKey(0x0008,0x4000)); // Identifying Comments
  ds.remove(DcmTagKey(0x0020,0x4000)); // Image Comments
  ds.remove(DcmTagKey(0x0028,0x4000)); // Image Presentation Comments
  ds.remove(DcmTagKey(0x0040,0x2400)); // Image Service Request Comments
  ds.remove(DcmTagKey(0x4008,0x0300)); // Impressions
  ds.remove(DcmTagKey(0x0008,0x0012)); // Instance Creation Date (NOTE: not in deident standard)
  ds.remove(DcmTagKey(0x0008,0x0013)); // Instance Creation Time (NOTE: not in deident standard)
  ds.remove(DcmTagKey(0x0008,0x0014)); // Instance Creator UID
  ds.remove(DcmTagKey(0x0008,0x0081)); // Institution Address
  ds.remove(DcmTagKey(0x0008,0x0082)); // Institution Code Sequence
  ds.remove(DcmTagKey(0x0008,0x0080)); // Institution Name
  ds.remove(DcmTagKey(0x0008,0x1040)); // Institutional Department Name
  ds.remove(DcmTagKey(0x0010,0x1050)); // Insurance Plan Identification
  ds.remove(DcmTagKey(0x0040,0x1011)); // Intended Recipients of Results Identification Sequence
  ds.remove(DcmTagKey(0x4008,0x0111)); // Interpretation Approver Sequence
  ds.remove(DcmTagKey(0x4008,0x010C)); // Interpretation Author
  ds.remove(DcmTagKey(0x4008,0x0115)); // Interpretation Diagnosis Description
  ds.remove(DcmTagKey(0x4008,0x0202)); // Interpretation ID Issuer
  ds.remove(DcmTagKey(0x4008,0x0102)); // Interpretation Recorder
  ds.remove(DcmTagKey(0x4008,0x010B)); // Interpretation Text
  ds.remove(DcmTagKey(0x4008,0x010A)); // Interpretation Transcriber
  ds.remove(DcmTagKey(0x0008,0x3010)); // Irradiation Event UID
  ds.remove(DcmTagKey(0x0038,0x0011)); // Issuer of Admission ID
  ds.remove(DcmTagKey(0x0010,0x0021)); // Issuer of Patient ID
  ds.remove(DcmTagKey(0x0038,0x0061)); // Issuer of Service Episode ID
  ds.remove(DcmTagKey(0x0028,0x1214)); // Large Palette Color Lookup Table UID
  ds.remove(DcmTagKey(0x0010,0x21D0)); // Last Menstrual Date
  ds.remove(DcmTagKey(0x0040,0x0404)); // MAC
  ds.remove(DcmTagKey(0x0002,0x0003)); // Media Storage SOP Instance UID
  ds.remove(DcmTagKey(0x0010,0x2000)); // Medical Alerts
  ds.remove(DcmTagKey(0x0010,0x1090)); // Medical Record Locator
  ds.remove(DcmTagKey(0x0010,0x1080)); // Military Rank
  ds.remove(DcmTagKey(0x0400,0x0550)); // Modified Attributes Sequence
  ds.remove(DcmTagKey(0x0020,0x3406)); // Modified Image Description
  ds.remove(DcmTagKey(0x0020,0x3401)); // Modifying Device ID
  ds.remove(DcmTagKey(0x0020,0x3404)); // Modifying Device Manufacturer
  ds.remove(DcmTagKey(0x0008,0x1060)); // Name of Physician(s) Reading Study
  ds.remove(DcmTagKey(0x0040,0x1010)); // Names of Intended Recipient of Results
  ds.remove(DcmTagKey(0x0010,0x2180)); // Occupation
  ds.remove(DcmTagKey(0x0008,0x1072)); // Operators' Identification Sequence
  ds.remove(DcmTagKey(0x0008,0x1070)); // Operators' Name
  ds.remove(DcmTagKey(0x0400,0x0561)); // Original Attributes Sequence
  ds.remove(DcmTagKey(0x0040,0x2010)); // Order Callback Phone Number
  ds.remove(DcmTagKey(0x0040,0x2008)); // Order Entered By
  ds.remove(DcmTagKey(0x0040,0x2009)); // Order Enterer Location
  ds.remove(DcmTagKey(0x0010,0x1000)); // Other Patient IDs
  ds.remove(DcmTagKey(0x0010,0x1002)); // Other Patient IDs Sequence
  ds.remove(DcmTagKey(0x0010,0x1001)); // Other Patient Names
  ds.remove(DcmTagKey(0x0008,0x0024)); // Overlay Date
  ds.remove(DcmTagKey(0x0008,0x0034)); // Overlay Time
  ds.remove(DcmTagKey(0x0028,0x1199)); // Palette Color Lookup Table UID
  ds.remove(DcmTagKey(0x0040,0xA07A)); // Participant Sequence
  ds.remove(DcmTagKey(0x0010,0x1040)); // Patient Address
  ds.remove(DcmTagKey(0x0010,0x4000)); // Patient Comments
  ds.remove(DcmTagKey(0x0010,0x2203)); // Patient Sex Neutered
  ds.remove(DcmTagKey(0x0038,0x0500)); // Patient State
  ds.remove(DcmTagKey(0x0040,0x1004)); // Patient Transport Arrangements
  ds.remove(DcmTagKey(0x0010,0x1010)); // Patient's Age
  ds.remove(DcmTagKey(0x0010,0x1005)); // Patient's Birth Name
  ds.remove(DcmTagKey(0x0010,0x0032)); // Patient's Birth Time
  ds.remove(DcmTagKey(0x0038,0x0400)); // Patient's Institution Residence
  ds.remove(DcmTagKey(0x0010,0x0050)); // Patient's Insurance Plan Code Sequence
  ds.remove(DcmTagKey(0x0010,0x1060)); // Patient's Mother's Birth Name
  ds.remove(DcmTagKey(0x0010,0x0101)); // Patient's Primary Language Code Sequence
  ds.remove(DcmTagKey(0x0010,0x0102)); // Patient's Primary Language Modifier Code Sequence
  ds.remove(DcmTagKey(0x0010,0x21F0)); // Patient's Religious Preference
  ds.remove(DcmTagKey(0x0010,0x1020)); // Patient's Size
  ds.remove(DcmTagKey(0x0010,0x2154)); // Patient's Telephone Number
  ds.remove(DcmTagKey(0x0010,0x1030)); // Patient's Weight
  ds.remove(DcmTagKey(0x0040,0x0243)); // Performed Location
  ds.remove(DcmTagKey(0x0040,0x0254)); // Performed Procedure Step Description
  ds.remove(DcmTagKey(0x0040,0x0253)); // Performed Procedure Step ID
  ds.remove(DcmTagKey(0x0040,0x0244)); // Performed Procedure Step Start Date
  ds.remove(DcmTagKey(0x0040,0x0245)); // Performed Procedure Step Start Time
  ds.remove(DcmTagKey(0x0040,0x0241)); // Performed Station AE Title
  ds.remove(DcmTagKey(0x0040,0x4030)); // Performed Station Geographic Location Code Sequence
  ds.remove(DcmTagKey(0x0040,0x0242)); // Performed Station Name
  ds.remove(DcmTagKey(0x0040,0x0248)); // Performed Station Name Code Sequence
  ds.remove(DcmTagKey(0x0008,0x1052)); // Performing Physicians' Identification Sequence
  ds.remove(DcmTagKey(0x0008,0x1050)); // Performing Physicians' Name
  ds.remove(DcmTagKey(0x0040,0x1102)); // Person Address
  ds.remove(DcmTagKey(0x0040,0x1101)); // Person Identification Code Sequence (NOTE: should be dummy value)
  ds.remove(DcmTagKey(0x0040,0xA123)); // Person Name (NOTE: should be dummy value)
  ds.remove(DcmTagKey(0x0040,0x1103)); // Person Telephone Numbers
  ds.remove(DcmTagKey(0x4008,0x0114)); // Physician Approving Interpretation
  ds.remove(DcmTagKey(0x0008,0x1062)); // Physican Reading Study Identification Sequence
  ds.remove(DcmTagKey(0x0008,0x1048)); // Physician(s) of Record
  ds.remove(DcmTagKey(0x0008,0x1049)); // Physician(s) of Record Identification Sequence
  ds.remove(DcmTagKey(0x0018,0x1004)); // Plate ID
  ds.remove(DcmTagKey(0x0040,0x0012)); // Pre-Medication
  ds.remove(DcmTagKey(0x0010,0x21C0)); // Pregnancy Status
  ds.remove(DcmTagKey(0x0018,0x1030)); // Protocol Name
  ds.remove(DcmTagKey(0x0040,0x2001)); // Reason for Imaging Service Request
  ds.remove(DcmTagKey(0x0032,0x1030)); // Reason for Study
  ds.remove(DcmTagKey(0x0008,0x1250)); // Related Series Sequence
  ds.remove(DcmTagKey(0x0400,0x0402)); // Referenced Digital Signature Sequence
  ds.remove(DcmTagKey(0x3006,0x0024)); // Referenced Frame of Reference UID
  ds.remove(DcmTagKey(0x0040,0x4023)); // Referenced General Purpose Scheduled Procedure Step Transaction UID
  ds.remove(DcmTagKey(0x0008,0x1140)); // Referenced Image Sequence
  ds.remove(DcmTagKey(0x0038,0x1234)); // Referenced Patient Atlas Sequence
  ds.remove(DcmTagKey(0x0008,0x1120)); // Referenced Patient Sequence
  ds.remove(DcmTagKey(0x0008,0x1111)); // Referenced Performed Procedure Step Sequence
  ds.remove(DcmTagKey(0x0400,0x0403)); // Referenced SOP Instance MAC Sequence
  ds.remove(DcmTagKey(0x0008,0x1155)); // Referenced SOP Instance UID
  ds.remove(DcmTagKey(0x0004,0x1511)); // Referenced SOP Instance UID in File
  ds.remove(DcmTagKey(0x0008,0x1110)); // Referenced Study Sequence
  ds.remove(DcmTagKey(0x0008,0x0092)); // Referring Physician's Address
  ds.remove(DcmTagKey(0x0008,0x0096)); // Referring Physician's Identification Sequence
  ds.remove(DcmTagKey(0x0008,0x0094)); // Referring Physician's Telephone Numbers
  ds.remove(DcmTagKey(0x0010,0x2152)); // Region of Residence
  ds.remove(DcmTagKey(0x3006,0x00C2)); // Related Frame of Reference UID
  ds.remove(DcmTagKey(0x0040,0x0275)); // Request Attributes Sequence
  ds.remove(DcmTagKey(0x0032,0x1070)); // Requested Contrast Agent
  ds.remove(DcmTagKey(0x0040,0x1400)); // Requested Procedure Comments
  ds.remove(DcmTagKey(0x0032,0x1060)); // Requested Procedure Description
  ds.remove(DcmTagKey(0x0040,0x1001)); // Requested Procedure ID
  ds.remove(DcmTagKey(0x0040,0x1005)); // Requested Procedure Location
  ds.remove(DcmTagKey(0x0000,0x1001)); // Requested SOP Instance UID
  ds.remove(DcmTagKey(0x0032,0x1032)); // Requesting Physican
  ds.remove(DcmTagKey(0x0032,0x1033)); // Requesting Service
  ds.remove(DcmTagKey(0x0010,0x2299)); // Responsible Organization
  ds.remove(DcmTagKey(0x0010,0x2297)); // Responsible Person
  ds.remove(DcmTagKey(0x4008,0x4000)); // Results Comments
  ds.remove(DcmTagKey(0x4008,0x0118)); // Results Distribution List Sequence
  ds.remove(DcmTagKey(0x4008,0x0042)); // Results ID Issuer
  ds.remove(DcmTagKey(0x300E,0x0008)); // Reviewer Name
  ds.remove(DcmTagKey(0x0040,0x4034)); // Scheduled Human Performers Sequence
  ds.remove(DcmTagKey(0x0038,0x001E)); // Scheduled Patient Institution Reference
  ds.remove(DcmTagKey(0x0040,0x000B)); // Scheduled Performing Physician Identification Sequence
  ds.remove(DcmTagKey(0x0040,0x0006)); // Scheduled Performing Physician Name
  ds.remove(DcmTagKey(0x0040,0x0004)); // Scheduled Procedure Step End Date
  ds.remove(DcmTagKey(0x0040,0x0005)); // Scheduled Procedure Step End Time
  ds.remove(DcmTagKey(0x0040,0x0007)); // Scheduled Procedure Step Description
  ds.remove(DcmTagKey(0x0040,0x0011)); // Scheduled Procedure Step Location
  ds.remove(DcmTagKey(0x0040,0x0002)); // Scheduled Procedure Step Start Date
  ds.remove(DcmTagKey(0x0040,0x0003)); // Scheduled Procedure Step Start Time
  ds.remove(DcmTagKey(0x0040,0x0001)); // Scheduled Station AE Title
  ds.remove(DcmTagKey(0x0040,0x4027)); // Scheduled Station Geographic Location Code Sequence
  ds.remove(DcmTagKey(0x0040,0x0010)); // Scheduled Station Name
  ds.remove(DcmTagKey(0x0040,0x4025)); // Scheduled Station Name Code Sequence
  ds.remove(DcmTagKey(0x0032,0x1020)); // Scheduled Study Location
  ds.remove(DcmTagKey(0x0032,0x1021)); // Scheduled Study Location AE Title
  ds.remove(DcmTagKey(0x0008,0x0021)); // Series Date
  ds.remove(DcmTagKey(0x0008,0x103E)); // Series Description
  ds.remove(DcmTagKey(0x0008,0x0031)); // Series Time
  ds.remove(DcmTagKey(0x0038,0x0062)); // Service Episode Description
  ds.remove(DcmTagKey(0x0038,0x0060)); // Service Episode ID
  ds.remove(DcmTagKey(0x0010,0x21A0)); // Smoking Status
  ds.remove(DcmTagKey(0x0008,0x2112)); // Source Image Sequence
  ds.remove(DcmTagKey(0x0038,0x0050)); // Special Needs
  ds.remove(DcmTagKey(0x0008,0x1010)); // Station Name
  ds.remove(DcmTagKey(0x0088,0x0140)); // Storage Media Fileset UID
  ds.remove(DcmTagKey(0x0032,0x4000)); // Study Comments
  ds.remove(DcmTagKey(0x0032,0x0012)); // Study ID Issuer
  ds.remove(DcmTagKey(0x0020,0x0200)); // Synchronization Frame of Reference UID
  ds.remove(DcmTagKey(0x0040,0xDB0D)); // Template Extension Creator UID
  ds.remove(DcmTagKey(0x0040,0xDB0D)); // Template Extension Creator UID
  ds.remove(DcmTagKey(0x0008,0x1195)); // Transaction UID
  ds.remove(DcmTagKey(0x0040,0xA124)); // UID
  ds.remove(DcmTagKey(0x0040,0xA088)); // Verifying Observer Identification Code Sequence
  ds.remove(DcmTagKey(0x0040,0xA075)); // Verifying Observer Name (NOTE: should be dummy value)
  ds.remove(DcmTagKey(0x0040,0xA073)); // Verifying Observer Sequence (NOTE: should be dummy value)
  ds.remove(DcmTagKey(0x0040,0xA027)); // Verifying Organization
  ds.remove(DcmTagKey(0x0038,0x4000)); // Visit Comments

  remove_private(ds);
  remove_matching(ds, 0x5000, 0xff00); // curve data
  remove_matching(ds, 0x6000, 0xff00, 0x4000, 0xffff); // overlay comments
  remove_matching(ds, 0x6000, 0xff00, 0x3000, 0xffff); // overlay data
}

int edit_files(std::istream &filenames) {
  for (std::string line; getline(filenames, line); ) {
	std::istringstream iss(line);
	std::string pre, post;
	if (!(iss >> pre >> post)) {
	  std::cout << "bad input line: " << line << std::endl;
	  return 2;
	}
	
	DcmFileFormat dcmf;
	dcmf.loadFile(pre.c_str());

	// TODO: can we unlink the original file now?

	DcmDataset* dataset = dcmf.getDataset();
	
	std::cout << "input cardinality " << dataset->card() << std::endl;
	
	DcmTag tagStudyDesc(0x0008,0x1030);
	const char *studyDesc;
	dataset->findAndGetString(tagStudyDesc, studyDesc);
	std::cout << "Study Description = " << studyDesc << std::endl;
	
	edit_dataset(*dataset);
	
	std::cout << "output cardinality " << dataset->card() << std::endl;
	
	dcmf.saveFile(post.c_str());
  }
  return 0;
}

#ifdef EMSCRIPTEN
extern "C" int
dcmedit_main(const int argc, char * const argv[]) {
#else
int main(const int argc, char * const argv[]) {
#endif
  switch (argc) {
  case 1: return edit_files(std::cin);
  case 2: {
	std::ifstream in(argv[1]);
	return edit_files(in);
  }
  case 3: {
	std::stringstream filenames;
	filenames << argv[1] << " " << argv[2] << std::endl;
	return edit_files(filenames);
  }
  default:
    std::cout << argv[0] << std::endl;
    std::cout << "Usage: " << argv[0] << " [argsfile]|[in-dcmfile out-dcmfile]" << std::endl;
    return 1;
  }
}
