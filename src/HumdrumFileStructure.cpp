//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Mon Aug 17 02:39:28 PDT 2015
// Last Modified: Mon Aug 17 02:39:32 PDT 2015
// Filename:      HumdrumFileStructure.h
// URL:           https://github.com/craigsapp/minHumdrum/blob/master/src/HumdrumFileStructure.cpp
// Syntax:        C++11
// vim:           ts=3 noexpandtab
//
// Description:   Used to further process HumdrumFileBase content, primarily
//                rhythmic analyses, but also parses global and local
//                token parameters.  The HumdrumFileContent class does
//                further analysis of the Humdrum data, primary of specific
//                data content rather than general structural analysis.
//

#include "HumdrumFileStructure.h"
#include "Convert.h"

using namespace std;

namespace minHumdrum {

// START_MERGE

//////////////////////////////
//
// HumdrumFileStructure::HumdrumFileStructure -- HumdrumFileStructure
//     constructor.
//

HumdrumFileStructure::HumdrumFileStructure(void) {
	// do nothing
}



//////////////////////////////
//
// HumdrumFileStructure::~HumdrumFileStructure -- HumdrumFileStructure 
//     deconstructor.
//

HumdrumFileStructure::~HumdrumFileStructure() {
	// do nothing
}



//////////////////////////////
//
// HumdrumFileStructure::read --  Read the contents of a file from a file or
//   istream.  The file's structure is analyzed, and then the rhythmic structure
//   is calculated.
//


bool HumdrumFileStructure::read(istream& contents) {
	if (!readNoRhythm(contents)) {
		return false;
	}
	return analyzeStructure();
}

bool HumdrumFileStructure::read(const char* filename) {
	if (!readNoRhythm(filename)) {
		return false;
	}
	return analyzeStructure();
}

bool HumdrumFileStructure::read(const string& filename) {
	if (!readNoRhythm(filename)) {
		return false;
	}
	return analyzeStructure();
}



//////////////////////////////
//
// HumdrumFileStructure::readCsv --  Read the contents of a file from a file or
//   istream in CSV format.  The file's structure is analyzed, and then the
//   rhythmic structure is calculated.
// default value: separator = ","
//


bool HumdrumFileStructure::readCsv(istream& contents,
		const string& separator) {
	if (!readNoRhythmCsv(contents, separator)) {
		return false;
	}
	return analyzeStructure();
}

bool HumdrumFileStructure::readCsv(const char* filename,
		const string& separator) {
	if (!readNoRhythmCsv(filename, separator)) {
		return false;
	}
	return analyzeStructure();
}

bool HumdrumFileStructure::readCsv(const string& filename,
		const string& separator) {
	if (!readNoRhythmCsv(filename, separator)) {
		return false;
	}
	return analyzeStructure();
}



//////////////////////////////
//
// HumdrumFileStructure::readString -- Read the contents from a string.
//    Similar to HumdrumFileStructure::read, but for string data.
//

bool HumdrumFileStructure::readString(const char* contents) {
	if (!HumdrumFileBase::readString(contents)) {
		return false;
	}
	return analyzeStructure();
}


bool HumdrumFileStructure::readString(const string& contents) {
	if (!HumdrumFileBase::readString(contents)) {
		return false;
	}
	return analyzeStructure();
}



//////////////////////////////
//
// HumdrumFileStructure::readStringCsv -- Read the contents from a string.
//    Similar to HumdrumFileStructure::read, but for string data.
// default value: separator = ","
//

bool HumdrumFileStructure::readStringCsv(const char* contents,
		const string& separator) {
	if (!HumdrumFileBase::readStringCsv(contents, separator)) {
		return false;
	}
	return analyzeStructure();
}


bool HumdrumFileStructure::readStringCsv(const string& contents,
		const string& separator) {
	if (!HumdrumFileBase::readStringCsv(contents, separator)) {
		return false;
	}
	return analyzeStructure();
}



//////////////////////////////
//
// HumdrumFileStructure::analyzeStructure -- Analyze global/local
//    parameters and rhythmic structure.
//


bool HumdrumFileStructure::analyzeStructure(void) {
   if (!analyzeGlobalParameters() ) { return false; }
   if (!analyzeLocalParameters()  ) { return false; }
   if (!analyzeTokenDurations()   ) { return false; }
   if (!analyzeRhythm()           ) { return false; }
   if (!analyzeDurationsOfNonRhythmicSpines()) { return false; }
   return true;
}



//////////////////////////////
//
// HumdrumFileStructure::readNoRhythm -- Similar to the read() functions, but
//    does not parse rhythm (or parameters).
//

bool HumdrumFileStructure::readNoRhythm(istream& infile) {
	return HumdrumFileBase::read(infile);
}


bool HumdrumFileStructure::readNoRhythm(const char* filename) {
	return HumdrumFileBase::read(filename);
}


bool HumdrumFileStructure::readNoRhythm(const string& filename) {
	return HumdrumFileBase::read(filename);
}



//////////////////////////////
//
// HumdrumFileStructure::readNoRhythmCsv -- Similar to the readCsv()
//    functions, but does not parse rhythm (or parameters).
// default value: separator = ","
//

bool HumdrumFileStructure::readNoRhythmCsv(istream& infile,
		const string& seperator) {
	return HumdrumFileBase::readCsv(infile);
}


bool HumdrumFileStructure::readNoRhythmCsv(const char* filename,
		const string& seperator) {
	return HumdrumFileBase::readCsv(filename);
}


bool HumdrumFileStructure::readNoRhythmCsv(const string& filename,
		const string& seperator) {
	return HumdrumFileBase::readCsv(filename);
}



//////////////////////////////
//
// HumdrumFileStructure::readStringNoRhythm -- Read a string, but
//   do not analyze the rhythm (or parameters) in the read data.
//


bool HumdrumFileStructure::readStringNoRhythm(const char* contents) {
	return HumdrumFileBase::readString(contents);
}


bool HumdrumFileStructure::readStringNoRhythm(const string& contents) {
	return HumdrumFileBase::readString(contents);
}



//////////////////////////////
//
// HumdrumFileStructure::readStringNoRhythmCsv -- Read a string, but
//   do not analyze the rhythm (or parameters) in the read data.
// default value: separator = ","
//


bool HumdrumFileStructure::readStringNoRhythmCsv(const char* contents,
		const string& separator) {
	return HumdrumFileBase::readStringCsv(contents);
}


bool HumdrumFileStructure::readStringNoRhythmCsv(const string& contents,
		const string& separator) {
	return HumdrumFileBase::readStringCsv(contents);
}



//////////////////////////////
//
// HumdrumFileStructure::getScoreDuration -- Return the total duration
//    of the score in quarter note units.  Returns zero if no lines in the
//    file, or -1 if there are lines, but no rhythmic analysis has been done.
// 

HumNum HumdrumFileStructure::getScoreDuration(void) const {
	if (lines.size() == 0) {
		return 0;
	}
	return lines.back()->getDurationFromStart();
}



//////////////////////////////
//
// HumdrumFileStructure::tpq -- "Ticks per Quarter-note".  Returns the minimal
//    number of integral time units that divide a quarter note into equal
//    subdivisions.  This value is needed to convert Humdrum data into
//    MIDI file data, MuseData, and MusicXML data.  Also useful for timebase
//    type of operations on the data and describing the durations in terms
//    of integers rather than with fractions.  This function will also 
//    consider the implicit durations of non-rhythmic spine data.
//

int HumdrumFileStructure::tpq(void) {
	if (ticksperquarternote > 0) {
		return ticksperquarternote;
	}
	set<HumNum> durlist = getPositiveLineDurations();
	vector<int> dems;
	for (auto& it : durlist) {
		if (it.getDenominator() > 1) {
			dems.push_back(it.getDenominator());
		}
	}
	int lcm = 1;
	if (dems.size() > 0) {
		lcm = Convert::getLcm(dems);
	}
	ticksperquarternote = lcm;
	return ticksperquarternote;
}



//////////////////////////////
//
// HumdrumFileStructure::getPositiveLineDurations -- Return a list of all
//    unique token durations in the file.  This function could be expanded
//    to limit the search to a range of lines or to a specific track.
//

set<HumNum> HumdrumFileStructure::getPositiveLineDurations(void) {
	set<HumNum> output;
	for (auto& line : lines) {
		if (line->getDuration().isPositive()) {
			output.insert(line->getDuration());
		}
	}
	return output;
}



//////////////////////////////
//
// HumdrumFileStructure::printDurationInfo -- Print the assigned duration
//    of each line in a file.  Useful for debugging.
//

ostream& HumdrumFileStructure::printDurationInfo(ostream& out) {
	for (int i=0; i<getLineCount(); i++) {
		lines[i]->printDurationInfo(out) << '\n';
	}
	return out;
}



//////////////////////////////
//
// HumdrumFileStructure::getBarline -- Return the given barline from the file
//   based on the index number.  Negative index accesses from the end of the
//   list.  If the first barline is a pickup measure, then the returned 
//   HumdrumLine* will not be an actual barline line.
//

HumdrumLine* HumdrumFileStructure::getBarline(int index) const {
	if (index < 0) {
		index += barlines.size();
	}
	if (index < 0) {
		return NULL;
	}
	if (index >= barlines.size()) {
		return NULL;
	}
	return barlines[index];
}



//////////////////////////////
//
// HumdrumFileStructure::getBarlineCount -- Return the number of barlines in
//   the file.  If there is a pickup beat, then the count includes an imaginary
//   barline before the first pickup (and the start of the file will be returned
//   for barline(0).
//

int HumdrumFileStructure::getBarlineCount(void) const {
	return barlines.size();
}



///////////////////////////////
//
// HumdrumFileStructure::getBarlineDuration --  Return the duration from the
//    current barline to the next barline in the data.  For the last barline,
//    the duration will be calculated from the end of the data;  The final
//    will have a duration of 0 if there are not notes after the barline
//    in the data.
//

HumNum HumdrumFileStructure::getBarlineDuration(int index) const {
	if (index < 0) {
		index += barlines.size();
	}
	if (index < 0) {
		return 0;
	}
	if (index >= barlines.size()) {
		return 0;
	}
	HumNum startdur = barlines[index]->getDurationFromStart();
	HumNum enddur;
	if (index + 1 < barlines.size() - 1) {
		enddur = barlines[index+1]->getDurationFromStart();
	} else {
		enddur = getScoreDuration();
	}
	return enddur - startdur;
}



///////////////////////////////
//
// HumdrumFileStructure::getBarlineDurationFromStart -- Return the duration
//    between the start of the Humdrum file and the given barline.
//

HumNum HumdrumFileStructure::getBarlineDurationFromStart(int index) const {
	if (index < 0) {
		index += barlines.size();
	}
	if (index < 0) {
		return 0;
	}
	if (index >= barlines.size()) {
		return getScoreDuration();
	}
	return barlines[index]->getDurationFromStart();
}



///////////////////////////////
//
// HumdrumFileStructure::getBarlineDurationToEnd -- Return the duration
//    between barline and the end of the HumdrumFileStructure.
//

HumNum HumdrumFileStructure::getBarlineDurationToEnd(int index) const {
	if (index < 0) {
		index += barlines.size();
	}
	if (index < 0) {
		return 0;
	}
	if (index >= barlines.size()) {
		return getScoreDuration();
	}
	return barlines[index]->getDurationToEnd();
}



//////////////////////////////
//
// HumdrumFileStructure::analyzeRhythm -- Analyze the rhythmic structure of the
//     data.  Returns false if there was a parse error.
//

bool HumdrumFileStructure::analyzeRhythm(void) {
	if (getMaxTrack() == 0) {
		return true;
	}
	int startline = getTrackStart(1)->getLineIndex();
	int testline;
	HumNum zero(0);

	int i;
	for (int i=1; i<=getMaxTrack(); i++) {
		if (!getTrackStart(i)->hasRhythm()) {
			// Can't analyze rhythm of spines that do not have rhythm.
			continue;
		}
		testline = getTrackStart(i)->getLineIndex();
		if (testline == startline) {
			if (!assignDurationsToTrack(getTrackStart(i), zero)) {
				return false;
			}
		} else {
			// Spine does not start at beginning of data, so
			// the starting position of the spine has to be
			// determined before continuing.  Search for a token
			// which is on a line with assigned duration, then work
			// outwards from that position.
			continue;
		}
	}

	// Go back and analyze spines which do not start at the beginning
	// of the data stream.
	for (i=1; i<=getMaxTrack(); i++) {
		if (!getTrackStart(i)->hasRhythm()) {
			// Can't analyze rhythm of spines that do not have rhythm.
			continue;
		}
		testline = getTrackStart(i)->getLineIndex();
		if (testline > startline) {
			if (!analyzeRhythmOfFloatingSpine(getTrackStart(i))) { return false; }
		}
	}

	if (!analyzeNullLineRhythms()) { return false; }
	fillInNegativeStartTimes();
	assignLineDurations();
	if (!analyzeMeter()) { return false; }
	if (!analyzeNonNullDataTokens()) { return false; }

	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::analyzeMeter -- Store the times from the last barline
//     to the current line, as well as the time to the next barline.
//     the sum of these two will be the duration of the barline, except
//     for barlines, where the getDurationToBarline() will store the
//     duration of the measure staring at that barline.  To get the
//     beat, you will have to figure out the current time signature.
//

bool HumdrumFileStructure::analyzeMeter(void) {

	barlines.resize(0);

	int i;
	HumNum sum = 0;
	bool foundbarline = false;
	for (i=0; i<getLineCount(); i++) {
		lines[i]->setDurationFromBarline(sum);
		sum += lines[i]->getDuration();
		if (lines[i]->isBarline()) {
			foundbarline = true;
			barlines.push_back(lines[i]);
			sum = 0;
		}
		if (lines[i]->isData() && !foundbarline) {
			// pickup measure, so set the first measure to the start of the file.
			barlines.push_back(lines[0]);
			foundbarline = 1;
		}
	}

	sum = 0;
	for (i=getLineCount()-1; i>=0; i--) {
		sum += lines[i]->getDuration();
		lines[i]->setDurationToBarline(sum);
		if (lines[i]->isBarline()) {
			sum = 0;
		}
	}

	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::analyzeTokenDurations -- Calculate the duration of
//   all tokens in spines which posses duration in a file.
//

bool HumdrumFileStructure::analyzeTokenDurations (void) {
	for (int i=0; i<getLineCount(); i++) {
		if (!lines[i]->analyzeTokenDurations()) {
			return false;
		}
	}
	return true;
}



///////////////////////////////
//
// HumdrumFileStructure::analyzeGlobalParameters -- only allowing layout
//    parameters at the moment.  Global parameters affect the next
//    line which is either a barline, dataline or an interpretation
//    other than a spine manipulator.  Null lines are also not
//    considered.
//

bool HumdrumFileStructure::analyzeGlobalParameters(void) {
	HumdrumLine* spineline = NULL;
	for (int i=lines.size()-1; i>=0; i--) {
		if (lines[i]->hasSpines()) {
			if (lines[i]->isAllNull())  {
				continue;
			}
			if (lines[i]->isManipulator()) {
				continue;
			}
			if (lines[i]->isCommentLocal()) {
				continue;
			}
			// should be a non-null data, barlines, or interpretation
			spineline = lines[i];
			continue;
		}
		if (spineline == NULL) {
			continue;
		}
		if (!lines[i]->isCommentGlobal()) {
			continue;
		}
		if (lines[i]->find("!!LO:") != 0) {
			continue;
		}
		spineline->setParameters(lines[i]);
	}

	return true;
}



///////////////////////////////
//
// HumdrumFileStructure::analyzeLocalParameters -- only allowing layout
//    parameters at the moment.
//

bool HumdrumFileStructure::analyzeLocalParameters(void) {
	// analyze backward tokens:
	for (int i=1; i<=getMaxTrack(); i++) {
		for (int j=0; j<getTrackEndCount(i); j++) {
			if (!processLocalParametersForTrack(getTrackEnd(i, j),
					getTrackEnd(i, j))) {
				return false;
			}
		}
	}

	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::analyzeDurationsOfNonRhythmicSpines -- Calculate the
//    duration of non-null data token in non-rhythmic spines.
//

bool HumdrumFileStructure::analyzeDurationsOfNonRhythmicSpines(void) {
	// analyze tokens backwards:
	for (int i=1; i<=getMaxTrack(); i++) {
		for (int j=0; j<getTrackEndCount(i); j++) {
			if (getTrackEnd(i, j)->hasRhythm()) {
				continue;
			}
			if (!assignDurationsToNonRhythmicTrack(getTrackEnd(i, j),
					getTrackEnd(i, j))) {
				return false;
			}
		}
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::getMinDur -- Return the smallest duration on the
//   line.  If all durations are zero, then return zero; otherwise,
//   return the smallest positive duration.
//

HumNum HumdrumFileStructure::getMinDur(vector<HumNum>& durs,
		vector<HumNum>& durstate) {
	HumNum mindur = 0;
	bool allzero = true;

	for (int i=0; i<(int)durs.size(); i++) {
		if (durs[i].isPositive()) {
			allzero = false;
			if (mindur.isZero()) {
				mindur = durs[i];
			} else if (mindur > durs[i]) {
				mindur = durs[i];
			}
		}
	}
	if (allzero) {
		return mindur;
	}

	for (int i=0; i<(int)durs.size(); i++) {
		if (durstate[i].isPositive() && mindur.isZero()) {
			if (durstate[i].isZero()) {
				// mindur = durstate[i];
			} else if (mindur > durstate[i]) {
				mindur = durstate[i];
			}
		}
	}
	return mindur;
}



//////////////////////////////
//
// HumdrumFileStructure::getTokenDurations -- Extract the duration of rhythmic
//    tokens on the line.
//

bool HumdrumFileStructure::getTokenDurations(vector<HumNum>& durs, int line) {
	durs.resize(0);
	for (int i=0; i<lines[line]->getTokenCount(); i++) {
		HumNum dur = lines[line]->token(i).getDuration();
		durs.push_back(dur);
	}
	if (!cleanDurs(durs, line)) {
		return false;
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::cleanDurs -- Check if there are grace note and regular
//    notes on a line (not allowed).  Leaves negative durations which
//    indicate undefined durations (needed for keeping track of null
//    tokens in rhythmic spines.
//

bool HumdrumFileStructure::cleanDurs(vector<HumNum>& durs, int line) {
	bool zero 		= false;
	bool positive = false;
	for (int i=0; i<(int)durs.size(); i++) {
		if      (durs[i].isPositive()) { positive = true; }
		else if (durs[i].isZero())     { zero     = true; }
	}
	if (zero && positive) {
		cerr << "Error on line " << (line+1) << " grace note and "
		     << " regular note cannot occur on same line." << endl;
		cerr << "Line: " << *lines[line] << endl;
		return false;
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::decrementDurStates -- Subtract the line duration from
//   the current line of running durations.  If any duration is less
//   than zero, then a rhythm error exists in the data.
//

bool HumdrumFileStructure::decrementDurStates(vector<HumNum>& durs,
		HumNum linedur, int line) {
	if (linedur.isZero()) {
		return true;
	}
	for (int i=0; i<(int)durs.size(); i++) {
		if (!lines[line]->token(i).hasRhythm()) {
			continue;
		}
		durs[i] -= linedur;
		if (durs[i].isNegative()) {
			cerr << "Error: rhythmic error on line " << (line+1)
			     << " field index " << i << endl;
			cerr << "Duration state is: " << durs[i] << endl;
			return false;
		}
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::assignDurationsToTrack -- Assign duration from starts
//    for each rhythmic spine in the file.  Analysis is done recursively, one
//    sub-spine at a time.  Duplicate analyses are prevented by the state
//    variable in the HumdrumToken (currently called rhycheck because it is only
//    used in this function).  After the durationFromStarts have been assigned
//    for the rhythmic analysis of non-data tokens and non-rhythmic spines is
//    done elsewhere.
//

bool HumdrumFileStructure::assignDurationsToTrack(HumdrumToken* starttoken,
		HumNum startdur) {
	if (!starttoken->hasRhythm()) {
		return true;
	}
	int state = starttoken->getState();
	if (!prepareDurations(starttoken, state, startdur)) { return false; }
	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::prepareDurations -- Helper function for
//     HumdrumFileStructure::assignDurationsToTrack() which does all of the
//     work for assigning durationFromStart values.
//

bool HumdrumFileStructure::prepareDurations(HumdrumToken* token, int state,
		HumNum startdur) {
	if (state != token->getState()) {
		return true;
	}

	HumdrumToken* initial = token;
	HumNum dursum = startdur;
	token->incrementState();

	if (!setLineDurationFromStart(token, dursum)) { return false; }
	if (token->getDuration().isPositive()) {
		dursum += token->getDuration();
	}
	int tcount = token->getNextTokenCount();

	// Assign line durationFromStarts for primary track first.
	while (tcount > 0) {
		token = token->getNextToken(0);
		if (state != token->getState()) {
			return true;
		}
		token->incrementState();
		if (!setLineDurationFromStart(token, dursum)) { return false; }
		if (token->getDuration().isPositive()) {
			dursum += token->getDuration();
		}
		tcount = token->getNextTokenCount();
	}

	if ((tcount == 0) && (token->isTerminateInterpretation())) {
		if (!setLineDurationFromStart(token, dursum)) { return false; }
	}

	// Process secondary tracks next:
	int newstate = state + 1;

	token = initial;
	dursum = startdur;
	if (token->getDuration().isPositive()) {
		dursum += token->getDuration();
	}
	tcount = token->getNextTokenCount();
	while (tcount > 0) {
		if (tcount > 1) {
			for (int i=1; i<tcount; i++) {
				if (!prepareDurations(token->getNextToken(i), state, dursum)) {
					return false;
				}
			}
		}
		token = token->getNextToken(0);
		if (newstate != token->getState()) {
			return true;
		}
		if (token->getDuration().isPositive()) {
			dursum += token->getDuration();
		}
		tcount = token->getNextTokenCount();
	}

	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::setLineDurationFromStart -- Set the duration of
//      a line based on the analysis of tokens in the spine.
//

bool HumdrumFileStructure::setLineDurationFromStart(HumdrumToken* token,
		HumNum dursum) {
	if ((!token->isTerminateInterpretation()) &&
			token->getDuration().isNegative()) {
		// undefined rhythm, so don't assign line duration information:
		return true;
	}
	HumdrumLine* line = token->getOwner();
	if (line->getDurationFromStart().isNegative()) {
		line->setDurationFromStart(dursum);
	} else if (line->getDurationFromStart() != dursum) {
		cerr << "Error: Inconsistent rhythm analysis occurring near line "
		     << token->getLineNumber() << endl;
		cerr << "Expected durationFromStart to be: " << dursum
		     << " but found it to be " << line->getDurationFromStart() << endl;
		cerr << "Line: " << *line << endl;
		return false;
	}

	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::analyzeRhythmOfFloatingSpine --  This analysis
//    function is used to analyze the rhythm of spines which do not start at
//    the beginning of the data.  The function searches for the first line
//    which has an assigned durationFromStart value, and then uses that
//    as the basis for assigning the initial durationFromStart position
//    for the spine.
//

bool HumdrumFileStructure::analyzeRhythmOfFloatingSpine(
		HumdrumToken* spinestart) {
	HumNum dursum = 0;
	HumNum founddur = 0;
	HumdrumToken* token = spinestart;
	int tcount = token->getNextTokenCount();

	// Find a known durationFromStart for a line in the Humdrum file, then
	// use that to calculate the starting duration of the floating spine.
	if (token->getDurationFromStart().isNonNegative()) {
		founddur = token->getLine()->getDurationFromStart();
	} else {
		tcount = token->getNextTokenCount();
		while (tcount > 0) {
			if (token->getDurationFromStart().isNonNegative()) {
				founddur = token->getLine()->getDurationFromStart();
				break;
			}
			if (token->getDuration().isPositive()) {
				dursum += token->getDuration();
			}
			token = token->getNextToken(0);
		}
	}

	if (founddur.isZero()) {
		cerr << "Error cannot link floating spine to score." << endl;
		return false;
	}

	if (!assignDurationsToTrack(spinestart, founddur - dursum)) {
		return false;
	}

	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::analyzeNullLineRhythms -- When a series of null-token
//    data line occur between two data lines possessing a start duration,
//    then split the duration between those two lines amongst the null-token
//    lines.  For example if a data line starts at time 15, and there is one
//    null-token line before another data line at time 16, then the null-token
//    line will be assigned to the position 15.5 in the score.
//

bool HumdrumFileStructure::analyzeNullLineRhythms(void) {
	vector<HumdrumLine*> nulllines;
	HumdrumLine* previous = NULL;
	HumdrumLine* next = NULL;
	HumNum dur;
	HumNum startdur;
	HumNum enddur;
	int i, j;
	for (i=0; i<(int)lines.size(); i++) {
		if (!lines[i]->hasSpines()) {
			continue;
		}
		if (lines[i]->isAllRhythmicNull()) {
			if (lines[i]->isData()) {
				nulllines.push_back(lines[i]);
			}
			continue;
		}
		dur = lines[i]->getDurationFromStart();
		if (dur.isNegative()) {
			if (lines[i]->isData()) {
				cerr << "Error: found an unexpected negative duration on line "
			     	<< lines[i]->getDurationFromStart()<< endl;
				cerr << "Line: " << *lines[i] << endl;
				return false;
			} else {
				continue;
			}
		}
		next = lines[i];
		if (previous == NULL) {
			previous = next;
			nulllines.resize(0);
			continue;
		}
		startdur = previous->getDurationFromStart();
		enddur   = next ->getDurationFromStart();
		HumNum gapdur = enddur - startdur;
		HumNum nulldur = gapdur / (nulllines.size() + 1);
		for (j=0; j<(int)nulllines.size(); j++) {
			nulllines[j]->setDurationFromStart(startdur + (nulldur * (j+1)));
		}
		previous = next;
		nulllines.resize(0);
	}
	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::fillInNegativeStartTimes -- Negative line durations
//    after the initial rhythmAnalysis mean that the lines are not data line.
//    Duplicate the duration of the next non-negative duration for all negative
//    durations.
//

void HumdrumFileStructure::fillInNegativeStartTimes(void) {
	int i;
	HumNum lastdur = -1;
	HumNum dur;
	for (i=lines.size()-1; i>=0; i--) {
		dur = lines[i]->getDurationFromStart();
		if (dur.isNegative() && lastdur.isNonNegative()) {
			lines[i]->setDurationFromStart(lastdur);
		}
		if (dur.isNonNegative()) {
			lastdur = dur;
			continue;
		}
	}

	// fill in start times for ending comments
	for (i=0; i<lines.size(); i++) {
		dur = lines[i]->getDurationFromStart();
		if (dur.isNonNegative()) {
			lastdur = dur;
		} else {
			lines[i]->setDurationFromStart(lastdur);
		}
	}
}



//////////////////////////////
//
// HumdrumFileStructure::assignLineDurations --  Calculate the duration of lines
//   based on the durationFromStart of the current line and the next line.
//

void HumdrumFileStructure::assignLineDurations(void) {
	HumNum startdur;
	HumNum enddur;
	HumNum dur;
	for (int i=0; i<lines.size()-1; i++) {
		startdur = lines[i]->getDurationFromStart();
		enddur = lines[i+1]->getDurationFromStart();
		dur = enddur - startdur;
		lines[i]->setDuration(dur);
	}
	if (lines.size() > 0) {
		lines.back()->setDuration(0);
	}
}



//////////////////////////////
//
// HumdrumFileStructure::assignDurationsToNonRhythmicTrack --  After the basic
//   rhythmAnalysis has been done, go back and assign durations to non-rhythmic
//   spine tokens based on the lineFromStart values of the lines that they 
//   occur on as well as the distance in the file to the next non-null token for
//   that spine.
//

bool HumdrumFileStructure::assignDurationsToNonRhythmicTrack(
		HumdrumToken* endtoken, HumdrumToken* current) {
	HumdrumToken* token = endtoken;
	int tcount = token->getPreviousTokenCount();
	while (tcount > 0) {
		for (int i=1; i<tcount; i++) {
			if (!assignDurationsToNonRhythmicTrack(token->getPreviousToken(i),
					current)) {
				return false;
			}
		}
		if (token->isData()) {
			if (!token->isNull()) {
				token->setDuration(current->getDurationFromStart() -
						token->getDurationFromStart());
				current = token;
			}
		}
		// Data tokens can only be followed by up to one previous token,
		// so no need to check for more than one next token.
		token = token->getPreviousToken(0);
		tcount = token->getPreviousTokenCount();
	}

	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::processLocalParametersForTrack --  Search for local 
//   parameters in each spine and fill in the HumHash for the token to which the
//   parameter is to be applied.
//

bool HumdrumFileStructure::processLocalParametersForTrack(
		HumdrumToken* starttok, HumdrumToken* current) {

	HumdrumToken* token = starttok;
	int tcount = token->getPreviousTokenCount();
	while (tcount > 0) {
		for (int i=1; i<tcount; i++) {
			if (!processLocalParametersForTrack(
					token->getPreviousToken(i), current)) {
				return false;
			}
		}
		if (!(token->isNull() && token->isManipulator())) {
			if (token->isCommentLocal()) {
				checkForLocalParameters(token, current);
			} else {
				current = token;
			}
		}

		// Data tokens can only be followed by up to one previous token,
		// so no need to check for more than one next token.
		token = token->getPreviousToken(0);
		tcount = token->getPreviousTokenCount();
	}

	return true;
}



//////////////////////////////
//
// HumdrumFileStructure::checkForLocalParameters -- Helper function for
//     HumdrumFileStructure::processLocalParametersForTrack.  Only allowing
//     layout parameters currently.
//

void HumdrumFileStructure::checkForLocalParameters(HumdrumToken *token,
		HumdrumToken *current) {
	if (token->size() < 1) {
		return;
	}
	if (token->find("!LO:") != 0) {
		return;
	}
	current->setParameters(token);
}



// END_MERGE

} // end namespace std;



