#ifndef HAND_HPP
#define HAND_HPP

#include <array>
#include <vector>

#include "card.h"


// todo static?
enum HandName {
    royal_flush =10 , 
    straight_flush = 9, 
    four_kind = 8, 
    full_house = 7, 
    flush = 6, 
    straight = 5, 
    three_kind = 4, 
    two_pair = 3, 
    pair = 2, 
    high_card = 1 
};


/**
 * @brief 
 * the getter mthods have to be caled in a certain order
 */
class Hand {
//private:
public:    
    /* five card hand */
    std::array<Card,5> m_sorted_cards;

    /* sorted (ascending order) unique values (and their counts) of the hand */
    std::vector<std::pair<Value,unsigned>> m_unique_values;

    /* sorted (ascending) unique suits (and their counts) of the hand */
    std::vector<std::pair<Suit,unsigned>> m_unique_suits;

    /* a summary of what kind of hand it is (e.g. straight ) without kicker information */
    HandName m_hand_name;

    /* fine comparison values to compare hands when they're the same HandName */
    std::vector<Value> m_fine_comp_values;

    /* arrange sorted_cards into m_sorted_values and m_sorted_suits */
    void sortValuesAndSuits();

    /* returns true if royal flush*/
    bool isRoyalFlush() const;

    bool isStraightFlush() const;

    bool isFourOfKind() const;

    bool isFullHouse() const;

    bool isFlush() const;

    bool isStraight() const;

    bool isThreeOfKind() const;

    bool isTwoPair() const;

    bool isPair() const;

    void setHandName();

public:

    Hand() = delete;

    Hand(const std::array<Card,5>& cards);

    Hand(const Card& c1, const Card& c2, const Card& c3, const Card& c4, const Card& c5);


    /**
     * @brief
     * 1. when two players both have a straight, flush, straight flush,
     * or royal flush, then the one with the higher largest value wins. If both have the
     * same highest value, then the player with the higher second largest
     * value wins, and so on and so forth.
     * 
     * 2. If both players have a 2/3/f-of a kind, then the one with the higher
     * value wins. If they both have the same 2/3/4 of the same kind, then the
     * player with the highest kicker(s) wins.
     * 
     * 3. if both players have a full house, then the higher triple wins. If
     * they have the same triple, then the higher double wins. If they have
     * the same of both, then they split the pot.
     * 
     * 4. if both players have a two pair, the highest pair is used to break tie.
     * If they have the same highest pair, then whoever has the higher second pair
     * wins. Otherwise, fifth card is used to break the tie.
     */
    std::vector<Value> getFineComparisonValues() const;


    /* gets the hand name */
    HandName getHandName() const;


    /**
     *
     */
    bool operator> (const Hand& rhs) const;
    bool operator== (const Hand& rhs) const;
    bool operator< (const Hand& rhs) const;
    bool operator>= (const Hand& rhs) const;
    bool operator<= (const Hand& rhs) const;
    bool operator!= (const Hand& rhs) const;

};

#endif // CARD_HPP
