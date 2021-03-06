#pragma once

#include <boost/dynamic_bitset.hpp>
#include "../utils/Config.hh"

typedef boost::dynamic_bitset<> Strand;
/**
 * Problem Interface. It is the computational representation of a Problem
 * Just implement it to be able to load a new problem into the framework.
 */
class Problem {
public:
    /**
     * print a chromosome strand
     * @param strand, strand to print
     */
    virtual void print(const Strand &strand) const = 0;
    
    /**
     * user interaction function. Used to ask parameter to the user. 
     * Can be graphic, not mandatory;
     */
    virtual void askParameters() = 0;
    
    /**
     * give the possibility to load some data into the framework
     * not mandatory
     */
    virtual bool loadData() = 0;
    
    /**
     * Compute the fitness of a chromosome through its strand.
     * @param strand, strand used to compute a chromosome fitness
     * @return 
     */
    virtual double computeFitnessOf(const Strand &strand) const = 0;
    
    /**
     * test whether a solution resolves the problem
     * @param strand, strand to test
     * @return whether a solution resolves the problem
     */
    virtual bool test(const Strand &strand) const = 0;
    
    /**
     * Transmit the best candidate solution to the problem
     * @param strand, the best candidate solution
     */
    virtual void giveBestSolution(const Strand &strand) const = 0;
    
    virtual ~Problem() {}
};