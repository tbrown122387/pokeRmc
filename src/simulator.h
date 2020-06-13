#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "deck.h"


/**
 * @brief simulates many random decks
 * and calculates which player has the best hand at the end of the river
 *
 */
class Simulator {
private:
    unsigned m_num_sims;
    unsigned m_num_folders;
    unsigned m_num_opponents;
    std::vector<Card> m_your_cards;
    std::vector<Card> m_community_cards;
    double m_num_wins;
    double m_num_ties;
    double m_num_losses;
    std::string m_pretty_results;

public:

    Simulator() = delete;
    Simulator(unsigned num_sims, unsigned num_opponents);

    void addYouCard(const Card& c);
    void addCommunityCard(const Card& c);
    void addFolder();
    void doSim(double& perc_won, double& perc_tie);
    std::string prettyResults() const;

};


#endif // SIMULATOR_HPP
