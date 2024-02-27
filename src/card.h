#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <unordered_map>
#include <array>


/* enum for the value of a single card */
enum Value { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };


/* enum for the suit of a single card */
enum Suit { hearts, diamonds, clubs, spades };


/**
 * @brief 
 *
 */
class Card {
private:
    /* value of the card */
    Value m_value;

    /* suit of the card */
    Suit  m_suit;

    /* true if aces count as low card */
    //bool m_aces_high_and_low;

public:


    /* disallow ambiguous cards */
    Card() = delete;


    /**
     * @brief constructor
     * @param value the card value (e.g. Value::jack)
     * @param suit the card suit (e.g.  Suit::clubs)
     */
    Card(Value value, Suit suit);


    /**
     * @brief the value getter
     * @return a Value
     */
    Value value() const;


    /**
     * @brief the suit getter
     * @return a Suit 
     */
    Suit suit() const;



    /**
     * @brief returns true if left hand side is smaller 
     */
    bool operator< (const Card& other) const;


    /**
     * @brief returns true if two cards are exactly the same.
     * This should never happen in a single deck.
     */
    bool operator==(const Card& other) const;


    /**
     * @brief returns true if two cards are the same suit
     */
    bool sameSuit(const Card& other) const;

    
    /**
     * @brief returns true if two cards are the same value
     */
    bool sameValue(const Card& other) const;


    static std::string toString(Value val);


    static std::string toString(Suit suit);


    static std::string prettyPrint(const Card& c);

    /**
     * @brief return an array of all 52 cards
     */
    static std::array<Card,52> all_cards();


    static Card fromString(const std::string& value, const std::string& suit);

};



#endif // CARD_HPP
