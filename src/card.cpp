#include "card.h"
#include <locale>



Card::Card(Value value, Suit suit)
    : m_value(value), m_suit(suit)
{    
}


Value Card::value() const
{    
    return m_value;
}


Suit Card::suit() const
{    
    return m_suit;
}


bool Card::operator< (const Card& other) const
{
    return m_value < other.value();
}


bool Card::operator== (const Card& other) const
{
    if (m_value != other.value() || m_suit != other.suit())
        return false;
    else
        return true;
}


bool Card::sameSuit (const Card& other) const
{
    if (m_suit == other.suit())
        return true;
    else
        return false;
}


bool Card::sameValue (const Card& other) const
{
    if (m_value == other.value())
        return true;
    else
        return false;
}


std::string Card::toString(Value val)
{
    switch(val){
        case Value::two:
            return std::string("2");
        case Value::three:
            return std::string("3");
        case Value::four:
            return std::string("4");
        case Value::five:
            return std::string("5");
        case Value::six:
            return std::string("6");
        case Value::seven:
            return std::string("7");
        case Value::eight:
            return std::string("8");
        case Value::nine:
            return std::string("9");
        case Value::ten:
            return std::string("10");
        case Value::jack:
            return std::string("jack");
        case Value::queen:
            return std::string("queen");
        case Value::king:
            return std::string("king");
        case Value::ace:
            return std::string("ace");
    }
}


std::string Card::toString(Suit suit)
{

    switch(suit){
        case Suit::hearts :
            return std::string("hearts");
        case Suit::diamonds :
            return std::string("diamonds");
        case Suit::clubs :
            return std::string("clubs");
        case Suit::spades :
            return std::string("spades");
    }
}


std::string Card::prettyPrint(const Card& c)
{
    return Card::toString(c.value()) + " of " + Card::toString(c.suit());
}


std::array<Card, 52> Card::all_cards()
{
    return std::array<Card,52> {
        Card(Value::two, Suit::clubs), 
        Card(Value::three, Suit::clubs), 
        Card(Value::four,  Suit::clubs), 
        Card(Value::five, Suit::clubs), 
        Card(Value::six, Suit::clubs), 
        Card(Value::seven, Suit::clubs), 
        Card(Value::eight, Suit::clubs), 
        Card(Value::nine, Suit::clubs), 
        Card(Value::ten, Suit::clubs), 
        Card(Value::jack, Suit::clubs), 
        Card(Value::queen, Suit::clubs), 
        Card(Value::king, Suit::clubs), 
        Card(Value::ace, Suit::clubs), 
        Card(Value::two, Suit::hearts), 
        Card(Value::three, Suit::hearts), 
        Card(Value::four,  Suit::hearts), 
        Card(Value::five, Suit::hearts), 
        Card(Value::six, Suit::hearts), 
        Card(Value::seven, Suit::hearts), 
        Card(Value::eight, Suit::hearts), 
        Card(Value::nine, Suit::hearts), 
        Card(Value::ten, Suit::hearts), 
        Card(Value::jack, Suit::hearts), 
        Card(Value::queen, Suit::hearts), 
        Card(Value::king, Suit::hearts), 
        Card(Value::ace, Suit::hearts), 
        Card(Value::two, Suit::diamonds), 
        Card(Value::three, Suit::diamonds), 
        Card(Value::four,  Suit::diamonds), 
        Card(Value::five, Suit::diamonds), 
        Card(Value::six, Suit::diamonds), 
        Card(Value::seven, Suit::diamonds), 
        Card(Value::eight, Suit::diamonds), 
        Card(Value::nine, Suit::diamonds), 
        Card(Value::ten, Suit::diamonds), 
        Card(Value::jack, Suit::diamonds), 
        Card(Value::queen, Suit::diamonds), 
        Card(Value::king, Suit::diamonds), 
        Card(Value::ace, Suit::diamonds), 
        Card(Value::two, Suit::spades), 
        Card(Value::three, Suit::spades), 
        Card(Value::four,  Suit::spades), 
        Card(Value::five, Suit::spades), 
        Card(Value::six, Suit::spades), 
        Card(Value::seven, Suit::spades), 
        Card(Value::eight, Suit::spades), 
        Card(Value::nine, Suit::spades), 
        Card(Value::ten, Suit::spades), 
        Card(Value::jack, Suit::spades), 
        Card(Value::queen, Suit::spades), 
        Card(Value::king, Suit::spades), 
        Card(Value::ace, Suit::spades) 
    };
}


Card Card::fromString(const std::string& value, const std::string& suit)
{
    std::locale loc;
    Value v;
    Suit s;
    if( suit.compare("d") == 0){

        s = Suit::diamonds;

    }else if(suit.compare("c") == 0){

        s = Suit::clubs;

    }else if(suit.compare("s") == 0){
    
        s = Suit::spades;

    }else if(suit.compare("h") == 0){

        s = Suit::hearts;

    }else{
        throw std::runtime_error("could not identify suit of card\n");
    }

    if(value.compare("2") == 0 ){
        v = Value::two;
    }else if( value.compare("3") == 0){
        v = Value::three;
    }else if( value.compare("4") == 0){
        v = Value::four;
    }else if( value.compare("5") == 0){
        v = Value::five;
    }else if( value.compare("6") == 0){
        v = Value::six;
    }else if( value.compare("7") == 0){
        v = Value::seven;
    }else if( value.compare("8") == 0){
        v = Value::eight;
    }else if( value.compare("9") == 0){
        v = Value::nine;
    }else if( value.compare("10") == 0){
        v = Value::ten;
    }else if( value.compare("j") == 0){
        v = Value::jack;
    }else if( value.compare("q") == 0){
        v = Value::queen;
    }else if( value.compare("k") == 0){
        v = Value::king;
    }else if( value.compare("a") == 0){
        v = Value::ace;
    }else{
        throw std::runtime_error("could not identify suit of card\n");
    }

    return Card(v,s);
}
