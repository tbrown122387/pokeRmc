#include "deck.h"

#include <algorithm>
#include <numeric>
#include <cassert>
#include <iostream>



Deck::Deck()
{
    for(auto& card : Card::all_cards()){
        m_unclaimed_cards.push_back(card);
    }
}


void Deck::turnUnclaimedIntoCommunity(const Card& c)
{
    for(auto p = m_unclaimed_cards.begin(); p != m_unclaimed_cards.end(); ++p)
    {
        if(*p == c){
            m_community_cards.push_back(*p);
            m_unclaimed_cards.erase(p);
            return;
        }
    }
    throw std::runtime_error("could not find unclaimed card to turn into community card\n");
}


void Deck::turnUnclaimedIntoCommunity(unsigned unclmd_idx)
{
    std::vector<Card>::iterator p = m_unclaimed_cards.begin();
    p += unclmd_idx;
    m_community_cards.push_back(*p);
    m_unclaimed_cards.erase(p);
}


void Deck::turnUnclaimedIntoOpponent(unsigned unclmd_idx)
{
    std::vector<Card>::iterator p = m_unclaimed_cards.begin();
    p += unclmd_idx;
    m_oppo_cards.push_back(*p);
    m_unclaimed_cards.erase(p);
}


void Deck::turnUnclaimedIntoYourCard(const Card& c)
{
    for(auto p = m_unclaimed_cards.begin(); p != m_unclaimed_cards.end(); ++p)
    {
        if(*p == c){
            m_your_cards.push_back(*p);
            m_unclaimed_cards.erase(p);
            return;
        }
    }
    throw std::runtime_error("could not find unclaimed card to turn into your card\n");
}


void Deck::turnUnclaimedIntoBurn(unsigned unclmd_idx)
{
    std::vector<Card>::iterator p = m_unclaimed_cards.begin();
    p += unclmd_idx;
    m_burned_cards.push_back(*p);
    m_unclaimed_cards.erase(p);
}


void Deck::turnOpponentIntoBurn(unsigned oppo_idx)
{
    std::vector<Card>::iterator p = m_oppo_cards.begin();
    p += oppo_idx;
    m_burned_cards.push_back(*p);
    m_oppo_cards.erase(p);
}




RandomDeck::RandomDeck(unsigned num_opponents, unsigned num_folders, std::mt19937_64 prng,
                   const Card& your_card1, const Card& your_card2)
    : Deck(), m_num_oppo(num_opponents), m_num_folders(num_folders), m_prng(prng)
{
    // set known stuff
    turnUnclaimedIntoYourCard(your_card1);
    turnUnclaimedIntoYourCard(your_card2);

    // simulate the rest
    // do it sequentially so it will be easier to modify later
    // opponent cards + burn cards + community cards
    unsigned num_available = 52 - 2;
    assert( num_available == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 0);
    assert( m_burned_cards.size() == 0 );
    assert( m_community_cards.size() == 0 );

    // 1. distribute opponent card
    for(size_t i = 0; i < 2*m_num_oppo; ++i){
        turnUnclaimedIntoOpponent( getRandomUnclaimedIndex() ); 
    }
    assert( num_available - 2*num_opponents == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*num_opponents );
    assert( m_burned_cards.size() == 0 );
    assert( m_community_cards.size() == 0 );

    // 2. distribute three community cards (burn one first)
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex()); 
    for(size_t i = 0; i < 3; ++i){
        turnUnclaimedIntoCommunity(getRandomUnclaimedIndex() );
    }
    assert( num_available - 2*num_opponents - 3 - 1 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*num_opponents );
    assert( m_burned_cards.size() == 1 );
    assert( m_community_cards.size() == 3 );

    // 3. distribute turn
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() );
    turnUnclaimedIntoCommunity( getRandomUnclaimedIndex()  ); 
    assert( num_available - 2*num_opponents - 3 - 3 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*num_opponents );
    assert( m_burned_cards.size() == 2 );
    assert( m_community_cards.size() == 4 );
 
    // 4. distribute river
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() ); 
    turnUnclaimedIntoCommunity( getRandomUnclaimedIndex() ); 
    assert( num_available - 2*num_opponents - 3 - 5 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*num_opponents );
    assert( m_burned_cards.size() == 3 );
    assert( m_community_cards.size() == 5 );

    // 5. fold everyone that folded
    // ignores information about how or when they folded
    // TODO ake this mre realistic because now I'm just folding randomly
    // more likely people fold when they have a bad hand 
    for(size_t i = 0; i < 2*num_folders; ++i){
        turnOpponentIntoBurn( getRandomOppoIndex() );
    } 
    assert( num_available - 2*num_opponents - 3 - 5 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*(num_opponents - num_folders) );
    assert( m_burned_cards.size() == 3 + 2*num_folders );
    assert( m_community_cards.size() == 5 );

}


RandomDeck::RandomDeck(unsigned num_opponents, unsigned num_folders, std::mt19937_64 prng,
                   const Card& your_card1, const Card& your_card2,
                   const Card& comm_card1, const Card& comm_card2, const Card& comm_card3)
    : Deck(), m_num_oppo(num_opponents), m_num_folders(num_folders), m_prng(prng)

{
    // set known stuff
    // don't forget to burn one for the flop
    turnUnclaimedIntoYourCard(your_card1);
    turnUnclaimedIntoYourCard(your_card2);
    turnUnclaimedIntoCommunity(comm_card1);
    turnUnclaimedIntoCommunity(comm_card2);
    turnUnclaimedIntoCommunity(comm_card3);
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() );

    assert( 52 - 6 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 0);
    assert( m_burned_cards.size() == 1 );
    assert( m_community_cards.size() == 3 );

    // simulate the rest
    // do it sequentially so it will be easier to modify later
    // 1. distribute opponent card
    for(size_t i = 0; i < 2*m_num_oppo; ++i){
        turnUnclaimedIntoOpponent( getRandomUnclaimedIndex() ); 
    }

    assert( 52 - 6 - 2*m_num_oppo == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*num_opponents);
    assert( m_burned_cards.size() == 1 );
    assert( m_community_cards.size() == 3 );


    // 2. distribute turn
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() );
    turnUnclaimedIntoCommunity( getRandomUnclaimedIndex()  ); 
 
    assert( 52 - 6 - 2*m_num_oppo - 2 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*num_opponents);
    assert( m_burned_cards.size() == 2 );
    assert( m_community_cards.size() == 4 );
  
    // 3. distribute river
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() ); 
    turnUnclaimedIntoCommunity( getRandomUnclaimedIndex() ); 

    assert( 52 - 6 - 2*m_num_oppo - 4 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*num_opponents);
    assert( m_burned_cards.size() == 3 );
    assert( m_community_cards.size() == 5 );

    // 4. fold everyone that folded
    // TODO ake this mre realistic because now I'm just folding randomly
    // more likely people fold when they have a bad hand 
    for(size_t i = 0; i < 2*num_folders; ++i){
        turnOpponentIntoBurn( getRandomOppoIndex() );
    } 

    assert( 52 - 6 - 2*m_num_oppo - 4 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*(num_opponents - num_folders));
    assert( m_burned_cards.size() == 3 + 2*num_folders );
    assert( m_community_cards.size() == 5 );
}


RandomDeck::RandomDeck(unsigned num_opponents, unsigned num_folders, std::mt19937_64 prng,
                   const Card& your_card1, const Card& your_card2,
                   const Card& comm_card1, const Card& comm_card2, const Card& comm_card3,
                   const Card& comm_card4)
    : Deck(), m_num_oppo(num_opponents), m_num_folders(num_folders), m_prng(prng)

{

    // set known stuff
    // don't forget to burn two for the flop and turn
    turnUnclaimedIntoYourCard(your_card1);
    turnUnclaimedIntoYourCard(your_card2);
    turnUnclaimedIntoCommunity(comm_card1);
    turnUnclaimedIntoCommunity(comm_card2);
    turnUnclaimedIntoCommunity(comm_card3);
    turnUnclaimedIntoCommunity(comm_card4);
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() );
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() );

    assert( 52 -8 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 0 );
    assert( m_burned_cards.size() == 2 );
    assert( m_community_cards.size() == 4 );

    // simulate the rest
    // do it sequentially so it will be easier to modify later
   
    // 1. distribute opponent card
    for(size_t i = 0; i < 2*m_num_oppo; ++i){
        turnUnclaimedIntoOpponent( getRandomUnclaimedIndex() ); 
    }

    assert( 52 -8-2*m_num_oppo == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*m_num_oppo );
    assert( m_burned_cards.size() == 2 );
    assert( m_community_cards.size() == 4 );

    // 2. distribute river
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() ); 
    turnUnclaimedIntoCommunity( getRandomUnclaimedIndex() ); 

    assert( 52 -8-2*m_num_oppo -2 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*m_num_oppo );
    assert( m_burned_cards.size() == 3 );
    assert( m_community_cards.size() == 5 );

    // 3. fold everyone that sucks
    // TODO ake this mre realistic because now I'm just folding randomly
    // more likely people fold when they have a bad hand 
    for(size_t i = 0; i < 2*num_folders; ++i){
        turnOpponentIntoBurn( getRandomOppoIndex() );
    } 
     
    assert( 52 -8-2*m_num_oppo -2 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*(m_num_oppo-num_folders) );
    assert( m_burned_cards.size() == 3 + 2*num_folders );
    assert( m_community_cards.size() == 5 );

}   
 
   
RandomDeck::RandomDeck(unsigned num_opponents, unsigned num_folders, std::mt19937_64 prng,
                   const Card& your_card1, const Card& your_card2,
                   const Card& comm_card1, const Card& comm_card2, const Card& comm_card3,
                   const Card& comm_card4,
                   const Card& comm_card5)
    : Deck(), m_num_oppo(num_opponents), m_num_folders(num_folders), m_prng(prng)

{

    // set known stuff
    // don't forget to burn three for the flop, turn and river
    turnUnclaimedIntoYourCard(your_card1);
    turnUnclaimedIntoYourCard(your_card2);
    turnUnclaimedIntoCommunity(comm_card1);
    turnUnclaimedIntoCommunity(comm_card2);
    turnUnclaimedIntoCommunity(comm_card3);
    turnUnclaimedIntoCommunity(comm_card4);
    turnUnclaimedIntoCommunity(comm_card5);
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() );
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() );
    turnUnclaimedIntoBurn( getRandomUnclaimedIndex() );

    assert( 52 - 10 == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 0 );
    assert( m_burned_cards.size() == 3 );
    assert( m_community_cards.size() == 5 );

    // simulate the rest
    // do it sequentially so it will be easier to modify later
   
    // 1. distribute opponent card
    for(size_t i = 0; i < 2*m_num_oppo; ++i){
        turnUnclaimedIntoOpponent( getRandomUnclaimedIndex() ); 
    }

    assert( 52 - 10 - 2*m_num_oppo == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*m_num_oppo );
    assert( m_burned_cards.size() == 3 );
    assert( m_community_cards.size() == 5 );

    // 2. fold everyone that sucks
    // TODO ake this mre realistic because now I'm just folding randomly
    // more likely people fold when they have a bad hand 
    for(size_t i = 0; i < 2*num_folders; ++i){
        turnOpponentIntoBurn( getRandomOppoIndex() );
    } 

    assert( 52 - 10 - 2*m_num_oppo == m_unclaimed_cards.size()); 
    assert( m_your_cards.size() == 2 );
    assert( m_oppo_cards.size() == 2*(m_num_oppo-num_folders) );
    assert( m_burned_cards.size() == 3 + 2*num_folders );
    assert( m_community_cards.size() == 5 );
}


unsigned RandomDeck::getRandomUnclaimedIndex()
{
    unsigned num_available = m_unclaimed_cards.size();
    std::uniform_int_distribution<unsigned> dstn(0,num_available-1);
    return dstn(m_prng);
}


unsigned RandomDeck::getRandomOppoIndex()
{
    unsigned num_available = m_oppo_cards.size();
    std::uniform_int_distribution<unsigned> dstn(0,num_available-1);
    return dstn(m_prng);
}


Hand RandomDeck::getBestHand(const Card& c1, const Card& c2) const
{
    // only designed for use at the end of the river
    assert(m_community_cards.size() == 5);

    // construct all available cards
    std::array<Card,7> all_available_cards 
                    {c1, c2, m_community_cards[0], m_community_cards[1], m_community_cards[2],
                    m_community_cards[3], m_community_cards[4]};
    // construct all combination vectors
    GenCombos myCombos(5+2, 5); 

    // iterate over all hands, saving the best one
    Hand current_best_hand(c1, c2, m_community_cards[0], m_community_cards[1], m_community_cards[2]);
    for(auto& combo_vec : myCombos.getAllCombos()){
        Hand candidate(all_available_cards[combo_vec[0]],
                       all_available_cards[combo_vec[1]],
                       all_available_cards[combo_vec[2]],
                       all_available_cards[combo_vec[3]],
                       all_available_cards[combo_vec[4]]);

       if( candidate > current_best_hand)
           current_best_hand = candidate;

    }

    return current_best_hand;
}


RoundOutcome RandomDeck::getOutcome() const
{
    assert(m_your_cards.size() == 2);
    Hand my_best = getBestHand(m_your_cards[0], m_your_cards[1]);

    bool had_tie = false;
    for(size_t i = 0; i < m_num_oppo - m_num_folders; ++i){
 
        Hand best_oppo_hand = getBestHand(m_oppo_cards[2*i], m_oppo_cards[2*i+1]); 
        if(best_oppo_hand > my_best){
            return RoundOutcome::lose;
        }else if( best_oppo_hand == my_best){
             had_tie = true;
        }   
    }

    if(had_tie)
        return RoundOutcome::draw;
    else
        return RoundOutcome::win;
}
