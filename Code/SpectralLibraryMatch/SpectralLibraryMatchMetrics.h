/*
 * The information in this file is
 * Copyright(c) 2010 Ball Aerospace & Technologies Corporation
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#ifndef SPECTRALLIBRARYMATCHMETRICS_H
#define SPECTRALLIBRARYMATCHMETRICS_H

/// Qt5 MOC can choke on <tbb/tbb.h>, so we break the SpectralLibraryMatch::MatchMetrics class
/// declaration into this separate file to be included by .cpp files where necessary. 

// The Intel Threading Building Blocks Library (tbb) is not supported on the Solaris Sparc platform
#ifndef SOLARIS
#include <tbb/tbb.h>

class SpectralLibraryMatch::MatchMetrics
   {
   public:
      MatchMetrics(double* pLibData, unsigned int numSignatures,
         MatchResults* pMatchInfo, double* pResultsData);
      ~MatchMetrics();

      void operator() (tbb::blocked_range<unsigned int>& range) const;

      double* mpLibData;
      unsigned int mNumSignatures;
      MatchResults* mpMatchInfo;
      double* mpResultsData;
      unsigned int mNumBands;
   };
#endif

#endif
