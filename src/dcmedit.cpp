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

bool remove_if_present(DcmItem& item, const DcmTagKey& tag) {
  const DcmElement* e = item.remove(tag);
  if (e) {
	delete e;
	return true;
  } else {
	return false;
  }
}

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
  remove_if_present(ds, DcmTagKey(0x0018,0x4000)); // Acquisition Comments
  remove_if_present(ds, DcmTagKey(0x0040,0x0555)); // Acquisition Context Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x0022)); // Acquisition Date
  remove_if_present(ds, DcmTagKey(0x0008,0x002A)); // Acquisition DateTime
  remove_if_present(ds, DcmTagKey(0x0018,0x1400)); // Acquisition Device Processing Description
  remove_if_present(ds, DcmTagKey(0x0018,0x9424)); // Acquisition Protocol Description
  remove_if_present(ds, DcmTagKey(0x0008,0x0032)); // Acquisition Time
  remove_if_present(ds, DcmTagKey(0x0040,0x4035)); // Actual Human Performers Sequence
  remove_if_present(ds, DcmTagKey(0x0010,0x21B0)); // Additional Patient's History
  remove_if_present(ds, DcmTagKey(0x0038,0x0010)); // Admission ID
  remove_if_present(ds, DcmTagKey(0x0038,0x0020)); // Admitting Date
  remove_if_present(ds, DcmTagKey(0x0008,0x1084)); // Admitting Diagnoses Code Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x1080)); // Admitting Diagnoses Description
  remove_if_present(ds, DcmTagKey(0x0038,0x0021)); // Admitting Time
  remove_if_present(ds, DcmTagKey(0x0000,0x1000)); // Affected SOP Instance UID
  remove_if_present(ds, DcmTagKey(0x0010,0x2110)); // Allergies
  remove_if_present(ds, DcmTagKey(0x4000,0x0010)); // Arbitrary
  remove_if_present(ds, DcmTagKey(0x0040,0xA078)); // Author Observer Sequence
  remove_if_present(ds, DcmTagKey(0x0010,0x1081)); // Branch of Service
  remove_if_present(ds, DcmTagKey(0x0018,0x1007)); // Cassette ID
  remove_if_present(ds, DcmTagKey(0x0040,0x0280)); // Comments on Performed Procedure Step
  remove_if_present(ds, DcmTagKey(0x0020,9161)); // Concatenation UID
  remove_if_present(ds, DcmTagKey(0x0040,0x3001)); // Confidentiality Constraint on Patient Data Description
  remove_if_present(ds, DcmTagKey(0x0070,0x0086)); // Content Creator's Identification Code Sequence
  remove_if_present(ds, DcmTagKey(0x0040,0xA730)); // Content Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x010D)); // Context Group Extension Creator UID
  remove_if_present(ds, DcmTagKey(0x0018,0xA003)); // Contribution Description
  remove_if_present(ds, DcmTagKey(0x0010,0x2150)); // Country of Residence
  remove_if_present(ds, DcmTagKey(0x0008,0x9123)); // Creator Version UID
  remove_if_present(ds, DcmTagKey(0x0038,0x0300)); // Current Patient Location
  remove_if_present(ds, DcmTagKey(0x0008,0x0025)); // Curve Date
  remove_if_present(ds, DcmTagKey(0x0008,0x0035)); // Curve Time
  remove_if_present(ds, DcmTagKey(0x0040,0xA07C)); // Custodial Organization Sequence
  remove_if_present(ds, DcmTagKey(0xFFFC,0xFFFC)); // Data Set Trailing Padding
  remove_if_present(ds, DcmTagKey(0x0008,0x2111)); // Derivation Description
  remove_if_present(ds, DcmTagKey(0x0018,0x700A)); // Detector ID
  remove_if_present(ds, DcmTagKey(0x0018,0x1000)); // Device Serial Number
  remove_if_present(ds, DcmTagKey(0x0018,0x1002)); // Device UID
  remove_if_present(ds, DcmTagKey(0x0400,0x0100)); // Digital Signature UID
  remove_if_present(ds, DcmTagKey(0xFFFA,0xFFFA)); // Digital Signatures Sequence
  remove_if_present(ds, DcmTagKey(0x0020,0x9164)); // Dimension Organization UID
  remove_if_present(ds, DcmTagKey(0x0038,0x0040)); // Discharge Diagnosis Description
  remove_if_present(ds, DcmTagKey(0x4008,0x011A)); // Distribution Address
  remove_if_present(ds, DcmTagKey(0x4008,0x0119)); // Distribution Name
  remove_if_present(ds, DcmTagKey(0x300A,0x0013)); // Dose Reference UID
  remove_if_present(ds, DcmTagKey(0x0010,0x2160)); // Ethnic Group
  remove_if_present(ds, DcmTagKey(0x0008,0x0058)); // Failed SOP Instance UID List
  remove_if_present(ds, DcmTagKey(0x0070,0x031A)); // Fiducial UID
  remove_if_present(ds, DcmTagKey(0x0020,0x9158)); // Frame Comments
  remove_if_present(ds, DcmTagKey(0x0020,0x0052)); // Frame of Reference UID
  remove_if_present(ds, DcmTagKey(0x0018,0x1008)); // Gantry ID
  remove_if_present(ds, DcmTagKey(0x0018,0x1005)); // Generator ID
  remove_if_present(ds, DcmTagKey(0x0070,0x0001)); // Graphic Annotation Sequence (NOTE: should be dummy value)
  remove_if_present(ds, DcmTagKey(0x0040,0x4037)); // Human Performers Name
  remove_if_present(ds, DcmTagKey(0x0040,0x4036)); // Human Performers Organization
  remove_if_present(ds, DcmTagKey(0x0088,0x0200)); // Icon Image Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x4000)); // Identifying Comments
  remove_if_present(ds, DcmTagKey(0x0020,0x4000)); // Image Comments
  remove_if_present(ds, DcmTagKey(0x0028,0x4000)); // Image Presentation Comments
  remove_if_present(ds, DcmTagKey(0x0040,0x2400)); // Image Service Request Comments
  remove_if_present(ds, DcmTagKey(0x4008,0x0300)); // Impressions
  remove_if_present(ds, DcmTagKey(0x0008,0x0012)); // Instance Creation Date (NOTE: not in deident standard)
  remove_if_present(ds, DcmTagKey(0x0008,0x0013)); // Instance Creation Time (NOTE: not in deident standard)
  remove_if_present(ds, DcmTagKey(0x0008,0x0014)); // Instance Creator UID
  remove_if_present(ds, DcmTagKey(0x0008,0x0081)); // Institution Address
  remove_if_present(ds, DcmTagKey(0x0008,0x0082)); // Institution Code Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x0080)); // Institution Name
  remove_if_present(ds, DcmTagKey(0x0008,0x1040)); // Institutional Department Name
  remove_if_present(ds, DcmTagKey(0x0010,0x1050)); // Insurance Plan Identification
  remove_if_present(ds, DcmTagKey(0x0040,0x1011)); // Intended Recipients of Results Identification Sequence
  remove_if_present(ds, DcmTagKey(0x4008,0x0111)); // Interpretation Approver Sequence
  remove_if_present(ds, DcmTagKey(0x4008,0x010C)); // Interpretation Author
  remove_if_present(ds, DcmTagKey(0x4008,0x0115)); // Interpretation Diagnosis Description
  remove_if_present(ds, DcmTagKey(0x4008,0x0202)); // Interpretation ID Issuer
  remove_if_present(ds, DcmTagKey(0x4008,0x0102)); // Interpretation Recorder
  remove_if_present(ds, DcmTagKey(0x4008,0x010B)); // Interpretation Text
  remove_if_present(ds, DcmTagKey(0x4008,0x010A)); // Interpretation Transcriber
  remove_if_present(ds, DcmTagKey(0x0008,0x3010)); // Irradiation Event UID
  remove_if_present(ds, DcmTagKey(0x0038,0x0011)); // Issuer of Admission ID
  remove_if_present(ds, DcmTagKey(0x0010,0x0021)); // Issuer of Patient ID
  remove_if_present(ds, DcmTagKey(0x0038,0x0061)); // Issuer of Service Episode ID
  remove_if_present(ds, DcmTagKey(0x0028,0x1214)); // Large Palette Color Lookup Table UID
  remove_if_present(ds, DcmTagKey(0x0010,0x21D0)); // Last Menstrual Date
  remove_if_present(ds, DcmTagKey(0x0040,0x0404)); // MAC
  remove_if_present(ds, DcmTagKey(0x0002,0x0003)); // Media Storage SOP Instance UID
  remove_if_present(ds, DcmTagKey(0x0010,0x2000)); // Medical Alerts
  remove_if_present(ds, DcmTagKey(0x0010,0x1090)); // Medical Record Locator
  remove_if_present(ds, DcmTagKey(0x0010,0x1080)); // Military Rank
  remove_if_present(ds, DcmTagKey(0x0400,0x0550)); // Modified Attributes Sequence
  remove_if_present(ds, DcmTagKey(0x0020,0x3406)); // Modified Image Description
  remove_if_present(ds, DcmTagKey(0x0020,0x3401)); // Modifying Device ID
  remove_if_present(ds, DcmTagKey(0x0020,0x3404)); // Modifying Device Manufacturer
  remove_if_present(ds, DcmTagKey(0x0008,0x1060)); // Name of Physician(s) Reading Study
  remove_if_present(ds, DcmTagKey(0x0040,0x1010)); // Names of Intended Recipient of Results
  remove_if_present(ds, DcmTagKey(0x0010,0x2180)); // Occupation
  remove_if_present(ds, DcmTagKey(0x0008,0x1072)); // Operators' Identification Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x1070)); // Operators' Name
  remove_if_present(ds, DcmTagKey(0x0400,0x0561)); // Original Attributes Sequence
  remove_if_present(ds, DcmTagKey(0x0040,0x2010)); // Order Callback Phone Number
  remove_if_present(ds, DcmTagKey(0x0040,0x2008)); // Order Entered By
  remove_if_present(ds, DcmTagKey(0x0040,0x2009)); // Order Enterer Location
  remove_if_present(ds, DcmTagKey(0x0010,0x1000)); // Other Patient IDs
  remove_if_present(ds, DcmTagKey(0x0010,0x1002)); // Other Patient IDs Sequence
  remove_if_present(ds, DcmTagKey(0x0010,0x1001)); // Other Patient Names
  remove_if_present(ds, DcmTagKey(0x0008,0x0024)); // Overlay Date
  remove_if_present(ds, DcmTagKey(0x0008,0x0034)); // Overlay Time
  remove_if_present(ds, DcmTagKey(0x0028,0x1199)); // Palette Color Lookup Table UID
  remove_if_present(ds, DcmTagKey(0x0040,0xA07A)); // Participant Sequence
  remove_if_present(ds, DcmTagKey(0x0010,0x1040)); // Patient Address
  remove_if_present(ds, DcmTagKey(0x0010,0x4000)); // Patient Comments
  remove_if_present(ds, DcmTagKey(0x0010,0x2203)); // Patient Sex Neutered
  remove_if_present(ds, DcmTagKey(0x0038,0x0500)); // Patient State
  remove_if_present(ds, DcmTagKey(0x0040,0x1004)); // Patient Transport Arrangements
  remove_if_present(ds, DcmTagKey(0x0010,0x1010)); // Patient's Age
  remove_if_present(ds, DcmTagKey(0x0010,0x1005)); // Patient's Birth Name
  remove_if_present(ds, DcmTagKey(0x0010,0x0032)); // Patient's Birth Time
  remove_if_present(ds, DcmTagKey(0x0038,0x0400)); // Patient's Institution Residence
  remove_if_present(ds, DcmTagKey(0x0010,0x0050)); // Patient's Insurance Plan Code Sequence
  remove_if_present(ds, DcmTagKey(0x0010,0x1060)); // Patient's Mother's Birth Name
  remove_if_present(ds, DcmTagKey(0x0010,0x0101)); // Patient's Primary Language Code Sequence
  remove_if_present(ds, DcmTagKey(0x0010,0x0102)); // Patient's Primary Language Modifier Code Sequence
  remove_if_present(ds, DcmTagKey(0x0010,0x21F0)); // Patient's Religious Preference
  remove_if_present(ds, DcmTagKey(0x0010,0x1020)); // Patient's Size
  remove_if_present(ds, DcmTagKey(0x0010,0x2154)); // Patient's Telephone Number
  remove_if_present(ds, DcmTagKey(0x0010,0x1030)); // Patient's Weight
  remove_if_present(ds, DcmTagKey(0x0040,0x0243)); // Performed Location
  remove_if_present(ds, DcmTagKey(0x0040,0x0254)); // Performed Procedure Step Description
  remove_if_present(ds, DcmTagKey(0x0040,0x0253)); // Performed Procedure Step ID
  remove_if_present(ds, DcmTagKey(0x0040,0x0244)); // Performed Procedure Step Start Date
  remove_if_present(ds, DcmTagKey(0x0040,0x0245)); // Performed Procedure Step Start Time
  remove_if_present(ds, DcmTagKey(0x0040,0x0241)); // Performed Station AE Title
  remove_if_present(ds, DcmTagKey(0x0040,0x4030)); // Performed Station Geographic Location Code Sequence
  remove_if_present(ds, DcmTagKey(0x0040,0x0242)); // Performed Station Name
  remove_if_present(ds, DcmTagKey(0x0040,0x0248)); // Performed Station Name Code Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x1052)); // Performing Physicians' Identification Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x1050)); // Performing Physicians' Name
  remove_if_present(ds, DcmTagKey(0x0040,0x1102)); // Person Address
  remove_if_present(ds, DcmTagKey(0x0040,0x1101)); // Person Identification Code Sequence (NOTE: should be dummy value)
  remove_if_present(ds, DcmTagKey(0x0040,0xA123)); // Person Name (NOTE: should be dummy value)
  remove_if_present(ds, DcmTagKey(0x0040,0x1103)); // Person Telephone Numbers
  remove_if_present(ds, DcmTagKey(0x4008,0x0114)); // Physician Approving Interpretation
  remove_if_present(ds, DcmTagKey(0x0008,0x1062)); // Physican Reading Study Identification Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x1048)); // Physician(s) of Record
  remove_if_present(ds, DcmTagKey(0x0008,0x1049)); // Physician(s) of Record Identification Sequence
  remove_if_present(ds, DcmTagKey(0x0018,0x1004)); // Plate ID
  remove_if_present(ds, DcmTagKey(0x0040,0x0012)); // Pre-Medication
  remove_if_present(ds, DcmTagKey(0x0010,0x21C0)); // Pregnancy Status
  remove_if_present(ds, DcmTagKey(0x0018,0x1030)); // Protocol Name
  remove_if_present(ds, DcmTagKey(0x0040,0x2001)); // Reason for Imaging Service Request
  remove_if_present(ds, DcmTagKey(0x0032,0x1030)); // Reason for Study
  remove_if_present(ds, DcmTagKey(0x0008,0x1250)); // Related Series Sequence
  remove_if_present(ds, DcmTagKey(0x0400,0x0402)); // Referenced Digital Signature Sequence
  remove_if_present(ds, DcmTagKey(0x3006,0x0024)); // Referenced Frame of Reference UID
  remove_if_present(ds, DcmTagKey(0x0040,0x4023)); // Referenced General Purpose Scheduled Procedure Step Transaction UID
  remove_if_present(ds, DcmTagKey(0x0008,0x1140)); // Referenced Image Sequence
  remove_if_present(ds, DcmTagKey(0x0038,0x1234)); // Referenced Patient Atlas Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x1120)); // Referenced Patient Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x1111)); // Referenced Performed Procedure Step Sequence
  remove_if_present(ds, DcmTagKey(0x0400,0x0403)); // Referenced SOP Instance MAC Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x1155)); // Referenced SOP Instance UID
  remove_if_present(ds, DcmTagKey(0x0004,0x1511)); // Referenced SOP Instance UID in File
  remove_if_present(ds, DcmTagKey(0x0008,0x1110)); // Referenced Study Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x0092)); // Referring Physician's Address
  remove_if_present(ds, DcmTagKey(0x0008,0x0096)); // Referring Physician's Identification Sequence
  remove_if_present(ds, DcmTagKey(0x0008,0x0094)); // Referring Physician's Telephone Numbers
  remove_if_present(ds, DcmTagKey(0x0010,0x2152)); // Region of Residence
  remove_if_present(ds, DcmTagKey(0x3006,0x00C2)); // Related Frame of Reference UID
  remove_if_present(ds, DcmTagKey(0x0040,0x0275)); // Request Attributes Sequence
  remove_if_present(ds, DcmTagKey(0x0032,0x1070)); // Requested Contrast Agent
  remove_if_present(ds, DcmTagKey(0x0040,0x1400)); // Requested Procedure Comments
  remove_if_present(ds, DcmTagKey(0x0032,0x1060)); // Requested Procedure Description
  remove_if_present(ds, DcmTagKey(0x0040,0x1001)); // Requested Procedure ID
  remove_if_present(ds, DcmTagKey(0x0040,0x1005)); // Requested Procedure Location
  remove_if_present(ds, DcmTagKey(0x0000,0x1001)); // Requested SOP Instance UID
  remove_if_present(ds, DcmTagKey(0x0032,0x1032)); // Requesting Physican
  remove_if_present(ds, DcmTagKey(0x0032,0x1033)); // Requesting Service
  remove_if_present(ds, DcmTagKey(0x0010,0x2299)); // Responsible Organization
  remove_if_present(ds, DcmTagKey(0x0010,0x2297)); // Responsible Person
  remove_if_present(ds, DcmTagKey(0x4008,0x4000)); // Results Comments
  remove_if_present(ds, DcmTagKey(0x4008,0x0118)); // Results Distribution List Sequence
  remove_if_present(ds, DcmTagKey(0x4008,0x0042)); // Results ID Issuer
  remove_if_present(ds, DcmTagKey(0x300E,0x0008)); // Reviewer Name
  remove_if_present(ds, DcmTagKey(0x0040,0x4034)); // Scheduled Human Performers Sequence
  remove_if_present(ds, DcmTagKey(0x0038,0x001E)); // Scheduled Patient Institution Reference
  remove_if_present(ds, DcmTagKey(0x0040,0x000B)); // Scheduled Performing Physician Identification Sequence
  remove_if_present(ds, DcmTagKey(0x0040,0x0006)); // Scheduled Performing Physician Name
  remove_if_present(ds, DcmTagKey(0x0040,0x0004)); // Scheduled Procedure Step End Date
  remove_if_present(ds, DcmTagKey(0x0040,0x0005)); // Scheduled Procedure Step End Time
  remove_if_present(ds, DcmTagKey(0x0040,0x0007)); // Scheduled Procedure Step Description
  remove_if_present(ds, DcmTagKey(0x0040,0x0011)); // Scheduled Procedure Step Location
  remove_if_present(ds, DcmTagKey(0x0040,0x0002)); // Scheduled Procedure Step Start Date
  remove_if_present(ds, DcmTagKey(0x0040,0x0003)); // Scheduled Procedure Step Start Time
  remove_if_present(ds, DcmTagKey(0x0040,0x0001)); // Scheduled Station AE Title
  remove_if_present(ds, DcmTagKey(0x0040,0x4027)); // Scheduled Station Geographic Location Code Sequence
  remove_if_present(ds, DcmTagKey(0x0040,0x0010)); // Scheduled Station Name
  remove_if_present(ds, DcmTagKey(0x0040,0x4025)); // Scheduled Station Name Code Sequence
  remove_if_present(ds, DcmTagKey(0x0032,0x1020)); // Scheduled Study Location
  remove_if_present(ds, DcmTagKey(0x0032,0x1021)); // Scheduled Study Location AE Title
  remove_if_present(ds, DcmTagKey(0x0008,0x0021)); // Series Date
  remove_if_present(ds, DcmTagKey(0x0008,0x103E)); // Series Description
  remove_if_present(ds, DcmTagKey(0x0008,0x0031)); // Series Time
  remove_if_present(ds, DcmTagKey(0x0038,0x0062)); // Service Episode Description
  remove_if_present(ds, DcmTagKey(0x0038,0x0060)); // Service Episode ID
  remove_if_present(ds, DcmTagKey(0x0010,0x21A0)); // Smoking Status
  remove_if_present(ds, DcmTagKey(0x0008,0x2112)); // Source Image Sequence
  remove_if_present(ds, DcmTagKey(0x0038,0x0050)); // Special Needs
  remove_if_present(ds, DcmTagKey(0x0008,0x1010)); // Station Name
  remove_if_present(ds, DcmTagKey(0x0088,0x0140)); // Storage Media Fileset UID
  remove_if_present(ds, DcmTagKey(0x0032,0x4000)); // Study Comments
  remove_if_present(ds, DcmTagKey(0x0032,0x0012)); // Study ID Issuer
  remove_if_present(ds, DcmTagKey(0x0020,0x0200)); // Synchronization Frame of Reference UID
  remove_if_present(ds, DcmTagKey(0x0040,0xDB0D)); // Template Extension Creator UID
  remove_if_present(ds, DcmTagKey(0x0040,0xDB0D)); // Template Extension Creator UID
  remove_if_present(ds, DcmTagKey(0x0008,0x1195)); // Transaction UID
  remove_if_present(ds, DcmTagKey(0x0040,0xA124)); // UID
  remove_if_present(ds, DcmTagKey(0x0040,0xA088)); // Verifying Observer Identification Code Sequence
  remove_if_present(ds, DcmTagKey(0x0040,0xA075)); // Verifying Observer Name (NOTE: should be dummy value)
  remove_if_present(ds, DcmTagKey(0x0040,0xA073)); // Verifying Observer Sequence (NOTE: should be dummy value)
  remove_if_present(ds, DcmTagKey(0x0040,0xA027)); // Verifying Organization
  remove_if_present(ds, DcmTagKey(0x0038,0x4000)); // Visit Comments

  remove_private(ds);
  remove_matching(ds, 0x5000, 0xff00); // curve data
  remove_matching(ds, 0x6000, 0xff00, 0x4000, 0xffff); // overlay comments
  remove_matching(ds, 0x6000, 0xff00, 0x3000, 0xffff); // overlay data
}

inline const char *safestr(const char *s) {
  return s ? s : "(null)";
}

int edit_files(std::istream &filenames) {
  DcmFileFormat dcmf;
  for (std::string line; getline(filenames, line); ) {
	std::istringstream iss(line);
	std::string pre, post;
	if (!(iss >> pre >> post)) {
	  std::cout << "bad input line: " << line << std::endl;
	  return 2;
	}

	dcmf.loadFile(pre.c_str());

	// TODO: can we unlink the original file now?
	DcmDataset* dataset = dcmf.getDataset();
	
	const unsigned long precard = dataset->card();
	const char *studyDesc, *seriesDesc, *instanceNumber;
	dataset->findAndGetString(DcmTagKey(0x0008,0x1030), studyDesc);
	dataset->findAndGetString(DcmTagKey(0x0008,0x103e), seriesDesc);
	dataset->findAndGetString(DcmTagKey(0x0020,0x0013), instanceNumber);

	edit_dataset(*dataset);

	const unsigned long postcard = dataset->card();

	std::cout << safestr(studyDesc) << "/" << safestr(seriesDesc)
			  << "/" << safestr(instanceNumber) << ": "
			  << precard << " -> " << postcard << std::endl;
	
	dcmf.saveFile(post.c_str());
	dcmf.clear();
  }
  return 0;
}

#ifdef EMSCRIPTEN
extern "C" int
dcmedit_main(const int argc, char * const argv[]) {
#else
int main(const int argc, char * const argv[]) {
#endif
  int rval;
  switch (argc) {
  case 1:
	rval = edit_files(std::cin);
	break;
  case 2: {
	std::ifstream in(argv[1]);
	rval = edit_files(in);
	break;
  }
  case 3: {
	std::stringstream filenames;
	filenames << argv[1] << " " << argv[2] << std::endl;
	rval = edit_files(filenames);
	break;
  }
  default:
    std::cout << argv[0] << std::endl;
    std::cout << "Usage: " << argv[0] << " [argsfile]|[in-dcmfile out-dcmfile]" << std::endl;
    rval = 1;
	break;
  }
  return rval;
}
