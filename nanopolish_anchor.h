//---------------------------------------------------------
// Copyright 2015 Ontario Institute for Cancer Research
// Written by Jared Simpson (jared.simpson@oicr.on.ca)
//---------------------------------------------------------
//
// nanopolish_anchor - a collection of data types
// for representing a set of event-to-sequence
// mappings.
#ifndef NANOPOLISH_ANCHOR_H
#define NANOPOLISH_ANCHOR_H

#include "htslib/htslib/hts.h"
#include "htslib/htslib/sam.h"

// An event index and orientation that gives us a handle
// into the event sequence for some SquiggleRead
struct HMMStrandAnchor
{
    //
    HMMStrandAnchor(int32_t ei, bool f) : event_idx(ei), rc(f) {}

    //
    int32_t event_idx;
    bool rc; // with respect to consensus
};

// A pair of vectors containing all of the anchors
// for both strands of a SquiggleRead
struct HMMReadAnchorSet
{
    std::vector<HMMStrandAnchor> strand_anchors[NUM_STRANDS];
};

// This data structure represents a column of a 
// multiple alignment where the base sequence
// is a subsequence of a contig that we
// we have mapped events to. It also holds alternative
// sequences sampled from the reads at starting at this column.
struct HMMAnchoredColumn
{
    std::string base_sequence;
    std::vector<HMMStrandAnchor> anchors;
    std::vector<std::string> alt_sequences;
};

// functions
void build_input_for_region(const std::string& filename, int ref_id, int start, int end, int stride);
HMMReadAnchorSet build_anchors_for_read(bam1_t* record, int start, int end, int stride);

#endif