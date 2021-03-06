// -*- C++ -*-
// AID-GENERATED
// =========================================================================
// This class was generated by AID - Abstract Interface Definition          
// DO NOT MODIFY, but use the org.freehep.aid.Aid utility to regenerate it. 
// =========================================================================
#ifndef AIDA_ICLOUD1D_H
#define AIDA_ICLOUD1D_H 1

//  This file is part of the AIDA library
//  Copyright (C) 2002 by the AIDA team.  All rights reserved.
//  This library is free software and under the terms of the
//  GNU Library General Public License described in the LGPL.txt 

#include <vector>

#include "AIDA/ICloud.h"

namespace AIDA {

class IHistogram1D;

/**
 * User level interface to a 1D Cloud.
 *
 * @author The AIDA team (http://aida.freehep.org/)
 *
 */
 
class ICloud1D : virtual public ICloud {

public: 
    /// Destructor.
    virtual ~ICloud1D() { /* nop */; }

    /**
     * Fill the ICloud1D with a value and a corresponding weight.
     * @param x      The value.
     * @param weight The corresponding weight. By default it is 1.
     * @return false If the ICloud1D is full, if the weight's value is
     *                                  is not between 0 and 1.
     *
     */
    virtual bool fill(double x, double weight = 1.) = 0;

    /**
     * Get the lower edge of the ICloud1D.
     * @return The lower edge.
     *
     */
    virtual double lowerEdge() const = 0;

    /**
     * Get the upper edge of the ICloud1D.
     * @return The upper edge.
     *
     */
    virtual double upperEdge() const = 0;

    /**
     * Get the value corresponding to a given entry.
     * @param index The entry's index.
     * @return      The value of the index-th entry.
     *              If the ICloud1D has already been converted, 0 is returned.
     *
     */
      
           
       
                                                    
                                      
                                                    
                                                                                         
      
       
      
    virtual double value(int index) const = 0;

    /**
     * Get the weight corresponding to a given entry.
     * @param index The entry's index.
     * @return      The weight of the index-th entry.
     *              If the ICloud1D has already been converted, 0 is returned.
     *
     */
      
           
       
                                                     
                                      
                                                     
                                                                                       
      
       
      
    virtual double weight(int index) const = 0;

    /**
     * Get the mean of the ICloud1D.
     * @return The mean.
     *
     */
    virtual double mean() const = 0;

    /**
     * Get the RMS of the ICloud1D.
     * @return The RMS.
     *
     */
    virtual double rms() const = 0;

    /**
     * Convert internally the ICloud1D to an IHistogram1D
     * with given number of bins, upper edge and lower edge.
     * @param nBins     The number of bins.
     * @param lowerEdge The lower edge.
     * @param upperEdge The upper edge.
     * @return false If the ICloud1D has already been converted.
     *
     */
    virtual bool convert(int nBins, double lowerEdge, double upperEdge) = 0;

    /**
     * Convert internally the ICloud1D to an IHistogram1D
     * with given bin edges.
     * @param binEdges The bins edges.
     * @return false If the ICloud1D has already been converted.
     *
     */
    virtual bool convert(const std::vector<double>  & binEdges) = 0;

    /**
     * Get the internal IHistogram1D in which the ICloud1D converted to.
     * @return The histogram.
     *                          or because of a convert() method invocation.
     *
     */
    virtual const IHistogram1D & histogram() const = 0;

    /**
     * Project the ICloud1D on an IHistogram1D.
     * @param hist The IHistogram1D to be filled.
     * @return false If the ICloud1D is already converted.
     *
     */
    virtual bool fillHistogram(IHistogram1D & hist) const = 0;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ICLOUD1D_H */
