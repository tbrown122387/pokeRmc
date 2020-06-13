#include "simulator.h"

#include <cassert> // assert
#include <chrono>
#include <iostream>

Simulator::Simulator(unsigned num_sims, unsigned num_opponents)
    : m_num_sims(num_sims), m_num_folders(0), m_num_opponents(num_opponents)
    , m_num_wins(0.0), m_num_ties(0.0), m_num_losses(0.0)
{
}


void Simulator::addYouCard(const Card& c)
{
    assert(0 <= m_your_cards.size() && m_your_cards.size() < 2);
    m_your_cards.push_back(c);
}


void Simulator::addCommunityCard(const Card& c)
{
    assert(0 <= m_community_cards.size() && m_community_cards.size() < 5);
    m_community_cards.push_back(c);
}


void Simulator::addFolder()
{
    m_num_folders++;
}


void Simulator::doSim(double& perc_won, double& perc_tie)
{

    // reset counts
    m_num_wins = 0.0;
    m_num_ties = 0.0;
    m_num_losses = 0.0;

    // perform the correct simulation
    if( m_community_cards.size() == 0){
        
        for(size_t i = 0; i < m_num_sims; ++i){

            // reset the seed
            std::mt19937_64 prng(i);           
            RandomDeck rd(m_num_opponents, m_num_folders, prng, m_your_cards[0], m_your_cards[1]); 
           
            if( rd.getOutcome() == RoundOutcome::win){
                m_num_wins += 1.0;
            }else if( rd.getOutcome() == RoundOutcome::lose){
                m_num_losses += 1.0;
            }else{
                m_num_ties += 1.0;
            }
        }

    }else if(m_community_cards.size() == 3 ){
        
        for(size_t i = 0; i < m_num_sims; ++i){
            
            std::mt19937_64 prng(i);           
                      
            RandomDeck rd(
                   m_num_opponents, m_num_folders, prng, 
                   m_your_cards[0], m_your_cards[1],
                   m_community_cards[0], m_community_cards[1], m_community_cards[2]); 

            if( rd.getOutcome() == RoundOutcome::win){
                m_num_wins += 1.0;
            }else if( rd.getOutcome() == RoundOutcome::lose){
                m_num_losses += 1.0;
            }else{
                m_num_ties += 1.0;
            }
       }

    }else if( m_community_cards.size() == 4){
        
        for(size_t i = 0; i < m_num_sims; ++i){

            std::mt19937_64 prng(i);
           
            RandomDeck rd(
                   m_num_opponents, m_num_folders, prng, 
                   m_your_cards[0], m_your_cards[1],
                   m_community_cards[0], m_community_cards[1], m_community_cards[2], 
                   m_community_cards[3]); 
           
            if( rd.getOutcome() == RoundOutcome::win){
                m_num_wins += 1.0;
            }else if( rd.getOutcome() == RoundOutcome::lose){
                m_num_losses += 1.0;
            }else{
                m_num_ties += 1.0;
            }

        
        }


    }else if( m_community_cards.size() == 5){
 
        for(size_t i = 0; i < m_num_sims; ++i){
           
            std::mt19937_64 prng(i);
            RandomDeck rd(
                   m_num_opponents, m_num_folders, prng, 
                   m_your_cards[0], m_your_cards[1],
                   m_community_cards[0], m_community_cards[1], m_community_cards[2], 
                   m_community_cards[3],
                   m_community_cards[4]); 
       
            if( rd.getOutcome() == RoundOutcome::win){
                m_num_wins ++;
            }else if( rd.getOutcome() == RoundOutcome::lose){
                m_num_losses += 1.0;
            }else{
                m_num_ties += 1.0;
            }
        }

    }else{
        throw std::runtime_error("weird number of community cards\n");
    }

    // assign final answer to args passed in by reference
    perc_won = m_num_wins/m_num_sims;
    perc_tie = m_num_ties/m_num_sims;


    m_pretty_results = "probability of having dominant hand:\n" 
                     + std::to_string(perc_won) + " +- " 
                     + std::to_string(1.96 * std::sqrt(perc_won*(1-perc_won)/m_num_sims))
                     + "\n\n"
                     + "probability of splitting the pot: \n" 
                     + std::to_string(perc_tie) + "+- " 
                     + std::to_string(1.96 * std::sqrt(perc_tie*(1-perc_tie)/m_num_sims))
                     + "\n ";
}


std::string Simulator::prettyResults() const
{
    return m_pretty_results;
}
