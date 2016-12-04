//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat Aug  8 12:24:49 PDT 2015
// Last Modified: Fri Aug 14 22:45:49 PDT 2015
// Filename:      HumdrumFileBase.h
// URL:           https://github.com/craigsapp/humlib/blob/master/include/HumdrumFileBase.h
// Syntax:        C++11
// vim:           ts=3 noexpandtab
//
// Description:   Used to store Humdrum text lines from input stream
//                for further parsing.  This class analyzes the basic
//                spine structure after reading a Humdrum file.  The
//                HumdrumFileStructure class continues structural analysis,
//                primarily of rhythm (generated by **kern, **recip and
//                **koto data).
//

#ifndef _HUMDRUMFILEBASE_H_INCLUDED
#define _HUMDRUMFILEBASE_H_INCLUDED

#include <iostream>
#include <vector>

// USING_URI is defined if you want to be able to download Humdrum data
// from the internet in command-line tools.  JavaScript Humdrum toolkit
// cannot access data from the internet due to the same-origin policy
// in JavaScript unless it is from the computer serving the webpage
// (except under certain circumstances).
#define USING_URI 1
#ifdef USING_URI
	#include <sys/types.h>   /* socket, connect */
	#include <sys/socket.h>  /* socket, connect */
	#include <netinet/in.h>  /* htons           */
	#include <netdb.h>       /* gethostbyname   */
	#include <unistd.h>      /* read, write     */
	#include <string.h>      /* memcpy          */
   #include <sstream>
#endif

#include "HumdrumLine.h"

using namespace std;

namespace hum {

// START_MERGE

// The following options are used for get[Primary]TrackTokens:
// * OPT_PRIMARY    => only extract primary subspine/subtrack.
// * OPT_NOEMPTY    => don't include null tokens in extracted list if all
//                        extracted subspines contains null tokens.
//                        Includes null interpretations and comments as well.
// * OPT_NONULL     => don't include any null tokens in extracted list.
// * OPT_NOINTERP   => don't include interprtation tokens.
// * OPT_NOMANIP    => don't include spine manipulators (*^, *v, *x, *+,
//                        but still keep ** and *0).
// * OPT_NOCOMMENT  => don't include comment tokens.
// * OPT_NOGLOBALS  => don't include global records (global comments, reference
//                        records, and empty lines). In other words, only return
//                        a list of tokens from lines which hasSpines() it true.
// * OPT_NOREST     => don't include **kern rests.
// * OPT_NOTIE      => don't include **kern secondary tied notes.
//
// Compound options:
// * OPT_DATA      (OPT_NOMANIP | OPT_NOCOMMENT | OPT_NOGLOBAL)
//     Only data tokens (including barlines)
// * OPT_ATTACKS   (OPT_DATA | OPT_NOREST | OPT_NOTIE | OPT_NONULL)
//     Only note-attack tokens (when etracting **kern data)
//
#define OPT_PRIMARY   0x001
#define OPT_NOEMPTY   0x002
#define OPT_NONULL    0x004
#define OPT_NOINTERP  0x008
#define OPT_NOMANIP   0x010
#define OPT_NOCOMMENT 0x020
#define OPT_NOGLOBAL  0x040
#define OPT_NOREST    0x080
#define OPT_NOTIE     0x100
#define OPT_DATA      (OPT_NOMANIP | OPT_NOCOMMENT | OPT_NOGLOBAL)
#define OPT_ATTACKS   (OPT_DATA | OPT_NOREST | OPT_NOTIE | OPT_NONULL)


class TokenPair {
	public:
		TokenPair(void) { clear(); }
		~TokenPair() { clear(); }
		void clear(void) {
			first = NULL;
			last  = NULL;
		}
		HTp first;
		HTp last;
};


bool sortTokenPairsByLineIndex(const TokenPair& a, const TokenPair& b);


class HumdrumFileBase : public HumHash {
	public:
		              HumdrumFileBase          (void);
                    HumdrumFileBase          (const string& contents);
                    HumdrumFileBase          (istream& contents);
		             ~HumdrumFileBase          ();

		bool          read                     (istream& contents);
		bool          read                     (const char* filename);
		bool          read                     (const string& filename);
		bool          readCsv                  (istream& contents,
		                                        const string& separator=",");
		bool          readCsv                  (const char* contents,
		                                        const string& separator=",");
		bool          readCsv                  (const string& contents,
		                                        const string& separator=",");

		bool          readString               (const char* contents);
		bool          readString               (const string& contents);
		bool          readStringCsv            (const char* contents,
		                                        const string& separator=",");
		bool          readStringCsv            (const string& contents,
		                                        const string& separator=",");
		bool          isValid                  (void);
		string        getParseError            (void) const;
		bool          isQuiet                  (void) const;
		void          setQuietParsing          (void);
		void          setNoisyParsing          (void);
		void          clear                    (void);

		bool          parse                    (istream& contents)
		                                    { return read(contents); }
		bool          parse                    (const char* contents)
		                                    { return readString(contents); }
		bool          parse                    (const string& contents)
		                                    { return readString(contents); }
		bool          parseCsv                 (istream& contents,
		                                        const string& separator = ",")
		                                    { return readCsv(contents); }
		bool          parseCsv                 (const char* contents,
		                                        const string& separator = ",")
		                                    { return readStringCsv(contents); }
		bool          parseCsv                 (const string& contents,
		                                        const string& separator = ",")
		                                    { return readStringCsv(contents); }

		void          setXmlIdPrefix           (const string& value);
		string        getXmlIdPrefix           (void);
		void          setFilename              (const string& filename);
		string        getFilename              (void);

      void          setSegmentLevel          (int level = 0);
      int           getSegmentLevel          (void);
      ostream&      printSegmentLabel        (ostream& out);
      ostream&      printNonemptySegmentLabel(ostream& out);

		HumdrumLine&  operator[]               (int index);
		HumdrumLine*  getLine                  (int index);
		int           getLineCount             (void) const;
		HTp           token                    (int lineindex, int fieldindex);
		int           getMaxTrack              (void) const;
		int           getTrackCount (void) const { return getMaxTrack(); }
		int           getSpineCount (void) const { return getMaxTrack(); }
		ostream&      printSpineInfo           (ostream& out = cout);
		ostream&      printDataTypeInfo        (ostream& out = cout);
		ostream&      printTrackInfo           (ostream& out = cout);
		ostream&      printCsv                 (ostream& out = cout,
		                                        const string& separator = ",");
		ostream&      printFieldNumber         (int fieldnum, ostream& out);
		ostream&      printFieldIndex          (int fieldind, ostream& out);

		HTp           getTrackStart            (int track) const;
		HTp           getSpineStart            (int spine) const {
		                                         return getTrackStart(spine+1); }

		void          getSpineStartList        (vector<HTp>& spinestarts);
		void          getSpineStartList        (vector<HTp>& spinestarts,
		                                        const string& exinterp);
      void          getKernSpineStartList    (vector<HTp>& spinestarts);
      vector<HTp>   getKernSpineStartList    ();
		void          getSpineStartList        (vector<HTp>& spinestarts,
		                                        const vector<string>& exinterps);
		void          getTrackStartList        (vector<HTp>& spinestarts) {
								return getSpineStartList(spinestarts); }
		void          getTrackStartList        (vector<HTp>& spinestarts,
		                                        const string& exinterp) {
								return getSpineStartList(spinestarts, exinterp); }
		void          getTrackStartList        (vector<HTp>& spinestarts,
		                                        const vector<string>& exinterps) {
								return getSpineStartList(spinestarts, exinterps); }

		int           getTrackEndCount         (int track) const;
		HTp           getTrackEnd              (int track, int subtrack) const;
		void          createLinesFromTokens    (void);

		void          appendLine               (const char* line);
		void          appendLine               (const string& line);
		void          appendLine               (HumdrumLine* line);
      void          push_back(const char* line)   { appendLine(line); }
      void          push_back(const string& line) { appendLine(line); }
      void          push_back(HumdrumLine* line)  { appendLine(line); }

		void          insertLine               (int index, const char* line);
		void          insertLine               (int index, const string& line);
		void          insertLine               (int index, HumdrumLine* line);

		HumdrumLine*  back                     (void);


		vector<HumdrumLine*> getReferenceRecords(void);

		// spine analysis functionality:
      void          getTrackSequence         (vector<vector<HTp> >& sequence,
		                                        HTp starttoken, int options);
      void          getTrackSequence         (vector<vector<HTp> >& sequence,
		                                        int track, int options);
		void          getPrimaryTrackSequence  (vector<HTp>& sequence,
		                                        int track, int options);

      void          getSpineSequence         (vector<vector<HTp> >& sequence,
		                                        HTp starttoken, int options);
      void          getSpineSequence         (vector<vector<HTp> >& sequence,
		                                        int spine, int options);
		void          getPrimarySpineSequence  (vector<HTp>& sequence,
		                                        int spine, int options);

      void          getTrackSeq              (vector<vector<HTp> >& sequence,
		                                        HTp starttoken, int options)
		                      { getTrackSequence(sequence, starttoken, options); }
      void          getTrackSeq              (vector<vector<HTp> >& sequence,
		                                        int track, int options)
		                           { getTrackSequence(sequence, track, options); }
		void          getPrimaryTrackSeq       (vector<HTp>& sequence,
		                                        int track, int options)
		                     {getPrimaryTrackSequence(sequence, track, options); }

		// functions defined in HumdrumFileBase-net.cpp:
		static string getUriToUrlMapping        (const string& uri);
		void          readFromHumdrumUri        (const string& humaddress);
		void          readFromJrpUri            (const string& jrpaddress);
		void          readFromHttpUri           (const string& webaddress);
		static void   readStringFromHttpUri     (stringstream& inputdata,
		                                         const string& webaddress);

	protected:
		static int    getChunk                  (int socket_id,
		                                         stringstream& inputdata,
		                                         char* buffer, int bufsize);
		static int    getFixedDataSize          (int socket_id,
		                                         int datalength,
		                                         stringstream& inputdata,
		                                         char* buffer, int bufsize);
		static void   prepare_address           (struct sockaddr_in *address,
		                                         const string& hostname,
		                                         unsigned short int port);
		static int    open_network_socket       (const string& hostname,
		                                         unsigned short int port);

	protected:
		bool          analyzeTokens             (void);
		bool          analyzeSpines             (void);
		bool          analyzeLinks              (void);
		bool          analyzeTracks             (void);
		bool          analyzeLines              (void);
		bool          adjustSpines              (HumdrumLine& line,
		                                         vector<string>& datatype,
		                                         vector<string>& sinfo);
		string        getMergedSpineInfo        (vector<string>& info,
		                                         int starti, int extra);
		bool          stitchLinesTogether       (HumdrumLine& previous,
		                                         HumdrumLine& next);
		void          addToTrackStarts          (HTp token);
		bool          analyzeNonNullDataTokens  (void);
		void          addUniqueTokens           (vector<HTp>& target,
		                                         vector<HTp>& source);
		bool          processNonNullDataTokensForTrackForward(HTp starttoken,
		                                         vector<HTp> ptokens);
		bool          processNonNullDataTokensForTrackBackward(HTp starttoken,
		                                         vector<HTp> ptokens);
		bool          setParseError             (stringstream& err);
		bool          setParseError             (const string& err);
		bool          setParseError             (const char* format, ...);

	protected:

		// m_lines: an array representing lines from the input file.
		// The contents of lines must be deallocated when deconstructing object.
		vector<HumdrumLine*> m_lines;

		// m_filename: name of the file which was loaded.
		string m_filename;

		// m_segementlevel: segment level (e.g., work/movement)
		int m_segmentlevel;

		// m_trackstarts: list of addresses of the exclusive interpreations
		// in the file.  The first element in the list is reserved, so the
		// number of tracks (primary spines) is equal to one less than the
		// size of this list.
		vector<HTp> m_trackstarts;

		// m_trackends: list of the addresses of the spine terminators in the
		// file. It is possible that spines can split and their subspines do not
		// merge before termination; therefore, the ends are stored in
		// a 2d array. The first dimension is the track number, and the second
		// dimension is the list of terminators.
		vector<vector<HTp> > m_trackends;

		// m_barlines: list of barlines in the data.  If the first measures is
		// a pickup measure, then the first entry will not point to the first
		// starting exclusive interpretation line rather than to a barline.
		vector<HumdrumLine*> m_barlines;
		// Maybe also add "measures" which are complete metrical cycles.

		// m_ticksperquarternote: this is the number of tick
		int m_ticksperquarternote;

		// m_idprefix: an XML id prefix used to avoid id collisions when
		// includeing multiple HumdrumFile XML in a single group.
		string m_idprefix;

		// m_strands1d: one-dimensional list of spine strands.
		vector<TokenPair> m_strand1d;

		// m_strands2d: two-dimensional list of spine strands.
		vector<vector<TokenPair> > m_strand2d;

		// m_quietParse: Set to true if error messages should not be
		// printed to the console when reading.
		bool m_quietParse;

		// m_parseError: Set to true if a read is successful.
		string m_parseError;

		// m_displayError: Used to print error message only once.
		bool m_displayError;

	public:
		// Dummy functions to allow the HumdrumFile class's inheritance
		// to be shifted between HumdrumFileContent (the top-level default),
		// HumdrumFileStructure (mid-level interface), or HumdrumFileBase
		// (low-level interface).

		//
		// HumdrumFileStructure public functions:
		//
		bool readNoRhythm      (istream& infile) { return read(infile); };
		bool readNoRhythm      (const char*   filename) {return read(filename);};
		bool readNoRhythm      (const string& filename) {return read(filename);};
		bool readStringNoRhythm(const char*   contents) {return read(contents);};
		bool readStringNoRhythm(const string& contents) {return read(contents);};
		HumNum       getScoreDuration           (void) const { return 0; };
		ostream&     printDurationInfo          (ostream& out=cout) {return out;};
		int          tpq                        (void) { return 0; }
		int          getBarlineCount            (void) const { return 0; }
		HumdrumLine* getBarline                 (int index) const { return NULL;};
		HumNum       getBarlineDuration         (int index) const { return 0; };
		HumNum       getBarlineDurationFromStart(int index) const { return 0; };
		HumNum       getBarlineDurationToEnd    (int index) const { return 0; };

		// HumdrumFileContent public functions:

};

ostream& operator<<(ostream& out, HumdrumFileBase& infile);


// END_MERGE

} // end namespace hum

#endif /* _HUMDRUMFILEBASE_H_INCLUDED */



