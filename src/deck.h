#ifndef DECK_HPP
#define DECK_HPP

#include "card.h"
#include "hand.h"

#include <vector>
#include <random>



/* outcome of a round of betting */
enum class RoundOutcome {win, lose, draw};



/**
 * @brief  
 */
class Deck {
//private:
public:
    
    /* 52 card deck */
    std::vector<Card> m_community_cards;
    std::vector<Card> m_your_cards;
    std::vector<Card> m_oppo_cards; // todo vector of these instead of randomly assembling them
    std::vector<Card> m_unclaimed_cards;
    std::vector<Card> m_burned_cards;

public:


    /**
     * @brief sets all cards to unclaimed
     */
    Deck();

    /**
     * @brief this should only be used by RandomDeck because it assumes randomization comes after
     */
    void turnUnclaimedIntoCommunity(const Card& c);

    void turnUnclaimedIntoCommunity(unsigned unclmd_idx);

    void turnUnclaimedIntoOpponent(unsigned unclmd_idx);


    /**
     * @brief this should only be used by RandomDeck because it assumes randomization comes after
     */
    void turnUnclaimedIntoYourCard(const Card& c);

    void turnUnclaimedIntoBurn(unsigned unclmd_idx);

    void turnOpponentIntoBurn(unsigned oppo_idx);

};



/**
 * @brief utility class that generates all combinations
 */
class GenCombos{
private:

	std::vector<unsigned> m_start_vec;
	std::vector<unsigned> m_current_combo;
	std::vector<std::vector<unsigned>> m_all_combos;

	void go(unsigned offset, unsigned k){
		
		if( k == 0){
			m_all_combos.push_back(m_current_combo);
			return;
		}
		
		for(unsigned i = offset; i <= m_start_vec.size() - k; ++i){
			m_current_combo.push_back(m_start_vec[i]);
			go(i+1, k-1);
			m_current_combo.pop_back();
		}
	}
	
public:

    /**
     * @brief ctor constructs all index vectors choosing num_choose from num_from
     */
	GenCombos(unsigned num_from, unsigned num_choose) {
		for(size_t i = 0; i < num_from; ++i) 
			m_start_vec.push_back(i); 
			
        // call go recursively
		go(0, num_choose);
	}
	
	std::vector<std::vector<unsigned>>& getAllCombos()
	{
		return m_all_combos;	
	}
};




/**
 * @brief performs two steps: instantiation, and then simulation.
 * Step 1: instantiate in one of several ways, depending on 
 * how much information you have available.
 * Step 2: shuffle the unknown cards randomly.
 *
 * Cards you know:
 * 1. community
 * 2. your cards
 *
 * Cards you cannot know
 * 1. burn cards
 * 2. opponent cards
 * 3. unclaimed cards
 *
 * Other things you know:
 * 1. num opponents to start
 * 2. num of opponents that have folded
 */
class RandomDeck : public Deck {
private:

    unsigned m_num_oppo;
    unsigned m_num_folders;

    std::mt19937_64 m_prng;


    unsigned getRandomUnclaimedIndex();

    unsigned getRandomOppoIndex();

public:


    RandomDeck() = delete;


    /**
     * @brief Pre-flop constructor: you only know your cards, and the number of opponents
     */
    RandomDeck(unsigned num_opponents, unsigned num_folders, std::mt19937_64 prng,
                   const Card& your_card1, const Card& your_card2);


    /**
     * @brief pre-turn ctor: additional information = three community cards and one card is burnt
     */
    RandomDeck(unsigned num_opponents, unsigned num_folders, std::mt19937_64 prng,
                   const Card& your_card1, const Card& your_card2,
                   const Card& comm_card1, const Card& comm_card2, const Card& comm_card3);

    /**
     * @brief pre-river ctor: additional information = one community cards and one card is burnt
     */
    RandomDeck(unsigned num_opponents, unsigned num_folders, std::mt19937_64 prng,
                   const Card& your_card1, const Card& your_card2,
                   const Card& comm_card1, const Card& comm_card2, const Card& comm_card3,
                   const Card& comm_card4);
   
    
     /**
     * @brief post-river ctor: additional information = one community cards and one card is burnt
     */
    RandomDeck(unsigned num_opponents, unsigned num_folders, std::mt19937_64 prng,
                   const Card& your_card1, const Card& your_card2,
                   const Card& comm_card1, const Card& comm_card2, const Card& comm_card3,
                   const Card& comm_card4,
                   const Card& comm_card5);


    /**
     * @brief looks at community cards and gets best five card hand
     */
    Hand getBestHand(const Card& c1, const Card& c2) const;


    RoundOutcome getOutcome() const;
    

};



#endif // DECK_HPP
