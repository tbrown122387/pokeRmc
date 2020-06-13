#include "hand.h"

#include <algorithm>
#include <iostream>

Hand::Hand(const std::array<Card,5>& cards)
    : m_sorted_cards(cards)
{
    // sort cards
    std::sort(m_sorted_cards.begin(), m_sorted_cards.end());
    
    // sort and count suits and values 
    sortValuesAndSuits();

    // set the hand type
    setHandName();
}


Hand::Hand(const Card& c1, const Card& c2, const Card& c3, const Card& c4, const Card& c5)
    : m_sorted_cards(std::array<Card,5>{c1, c2, c3, c4, c5})
{
    // sort cards
    std::sort(m_sorted_cards.begin(), m_sorted_cards.end());
 
    // sort and count suits and values 
    sortValuesAndSuits();

    // set the hand type
    setHandName();
}


void Hand::sortValuesAndSuits() 
{

    // the first card is necessarily unique, so process its suit and value
    unsigned uvc = 0;
    m_unique_values.emplace_back(std::make_pair(m_sorted_cards[uvc].value(), 1));
    unsigned usc = 0;
    m_unique_suits.emplace_back(std::make_pair(m_sorted_cards[usc].suit(), 1));

    // iterate over the other four cards
    // either increment the counter, 
    // or add a fresh value pair with count 1
    for(size_t i = 1; i < 5; ++i){

        // process value
        Value v_add_candidate = m_sorted_cards[i].value();
        if( v_add_candidate != m_unique_values[uvc].first ){
            m_unique_values.emplace_back(std::make_pair(v_add_candidate, 1));
            uvc++;
        }else{
            m_unique_values[uvc].second ++;
        }

        // process suit
        Suit s_add_candidate = m_sorted_cards[i].suit();
        if( s_add_candidate != m_unique_suits[usc].first ){
            m_unique_suits.emplace_back(std::make_pair(s_add_candidate, 1));
            usc++;
        }else{
            m_unique_suits[usc].second ++;
        }
    }
}


bool Hand::isRoyalFlush() const
{
    if(!isFlush() || !isStraight() || m_sorted_cards[4].value() != Value::ace)
        return false;
    else
        return true;    
}


bool Hand::isStraightFlush() const
{
    if(!isFlush() || !isStraight())
        return false;
    else
        return true;
}


bool Hand::isFourOfKind() const
{
    for(const auto& vpair : m_unique_values){
        if( vpair.second == 4 )
            return true;
    }
    return false;
}


bool Hand::isFullHouse() const
{
    bool hasTriple = false;
    bool hasDouble = false;
    for(const auto& vpair : m_unique_values){
        if( vpair.second == 2 )
            hasDouble = true;
        else if( vpair.second == 3)
            hasTriple = true;
    }
    return hasTriple && hasDouble;
}


bool Hand::isFlush() const
{
    return m_unique_suits.size() == 1;
}


bool Hand::isStraight() const
{
    for(size_t i = 1; i < 5; ++i){
        if( m_sorted_cards[i].value() - m_sorted_cards[i-1].value() != 1 )
            return false;
    }
    return true;
}


bool Hand::isThreeOfKind() const
{
    for(const auto& val_count_pair : m_unique_values){
        if( val_count_pair.second == 3)
            return true;
    }
    return false;
}

bool Hand::isTwoPair() const
{
    unsigned numPairs (0);
    for(const auto& val_count_pair : m_unique_values){
        if( val_count_pair.second == 2)
            numPairs++;
    }
    return numPairs == 2;
}


bool Hand::isPair() const
{
     for(const auto& val_count_pair : m_unique_values){
        if( val_count_pair.second == 2)
            return true;
    }
    return false;
}


void Hand::setHandName() 
{
    if( isRoyalFlush() ){

        m_hand_name = HandName::royal_flush;
        
    }else if(isStraightFlush() ){
    
        m_hand_name = HandName::straight_flush;
    
    }else if( isFourOfKind() ){
    
        m_hand_name = HandName::four_kind;

    }else if( isFullHouse() ){

        m_hand_name = HandName::full_house;

    }else if( isFlush() ){

        m_hand_name = HandName::flush;

    }else if( isStraight() ) {

        m_hand_name = HandName::straight;

    }else if( isThreeOfKind() ){

        m_hand_name = HandName::three_kind;

    }else if( isTwoPair() ) {

        m_hand_name = HandName::two_pair;

    }else if( isPair() ) {
        
        m_hand_name = HandName::pair;

    }else {

        m_hand_name = HandName::high_card;

    }

}


HandName Hand::getHandName() const 
{
    return m_hand_name;
}


std::vector<Value> Hand::getFineComparisonValues() const
{

    // see documentation for how kickers are calculated
    // return this (it's in descending order so you traverse it left to right)
    std::vector<Value> fine_comp_values;

    if( isRoyalFlush() ){


        // fine comparison for comparing two hands of the same type 
        // we are not assuming it's a 52 card deck here, so
        // there could be two of these
        for(size_t i = 0; i < 5; ++i){
            fine_comp_values.push_back(
                    m_sorted_cards[4-i].value()
                    );
        }

    }else if( isStraightFlush() ){

        for(size_t i = 0; i < 5; ++i){
            fine_comp_values.push_back(
                    m_sorted_cards[4-i].value()
                    );
        }
    
    }else if( isFourOfKind() ){
   
        // matched value, next highest card (kicker)
        Value matched, kicker;
        for(auto& uv : m_unique_values){
            if( uv.second == 4 ){
                matched = uv.first;
            }else if( uv.second == 1 ){
                kicker = uv.first;
            }else{
                throw std::runtime_error("unexpectd unique values for a 4-of-a-kind\n");
            }
        }

        // add them in the right order
        fine_comp_values.push_back(matched);
        fine_comp_values.push_back(kicker);

    }else if( isFullHouse() ){

        // matched value, next highest card (kicker)
        Value triple_val, double_val;
        for(auto& uv : m_unique_values){
            if( uv.second == 3 ){
                triple_val = uv.first;
            }else if( uv.second == 2 ){
                double_val = uv.first;
            }else{
                throw std::runtime_error("unexpectd unique values for a 4-of-a-kind\n");
            }
        }

        // add them in the right order
        fine_comp_values.push_back(triple_val);
        fine_comp_values.push_back(double_val);

    }else if( isFlush() ){

        for(size_t i = 0; i < 5; ++i){
            fine_comp_values.push_back(
                    m_sorted_cards[4-i].value()
                    );
        }

    }else if( isStraight() ) {

        for(size_t i = 0; i < 5; ++i){
            fine_comp_values.push_back(
                    m_sorted_cards[4-i].value()
                    );
        }

    }else if( isThreeOfKind() ){


        // triple value, next hgihest next highest
        Value triple_val, next_highest, second_highest;
        unsigned num_high_received (0);
        for(auto& uv : m_unique_values){
            if( uv.second == 3 ){
                triple_val = uv.first;
            }else if( num_high_received == 0){
                next_highest = uv.first;
                num_high_received++;
            }else if( num_high_received == 1){
                second_highest = uv.first;
            }
        }

        // add them in the right order
        fine_comp_values.push_back(triple_val);
        if(next_highest > second_highest){
            fine_comp_values.push_back(next_highest);
            fine_comp_values.push_back(second_highest);
        }else{
            fine_comp_values.push_back(second_highest);
            fine_comp_values.push_back(next_highest);
        }

    }else if( isTwoPair() ) {

        // highest double, lowest double, next highest
        Value highest_double_a, highest_double_b, next_highest;
        unsigned num_double_received (0);
        for(auto& uv : m_unique_values){
            if( uv.second == 2 && num_double_received == 0){

                highest_double_a = uv.first;
                num_double_received ++;
            
            }else if( uv.second == 2 && num_double_received == 1){
                 
                highest_double_b = uv.first;
                num_double_received ++;
            
            }else if( uv.second == 1){
                
                next_highest = uv.first;
            }else{
                throw std::runtime_error("unexpeted sorted values in three of a kind\n");
            }
        }

        // add them in the right order
        if(highest_double_a > highest_double_b){
            fine_comp_values.push_back(highest_double_a);
            fine_comp_values.push_back(highest_double_b);
        }else{
            fine_comp_values.push_back(highest_double_b);
            fine_comp_values.push_back(highest_double_a);
        }
        fine_comp_values.push_back(next_highest);


    }else if( isPair() ) {
       
        // highest two times val, next highest, next next highest, next next highest
        Value highest_double;
        std::vector<Value> h;

        for(auto& uv : m_unique_values){
            if( uv.second == 2 ){
                highest_double = uv.first;
            }else if( h.size() == 0){
                h.push_back( uv.first);
            }else if( h.size() == 1){
                
                h.push_back(uv.first);
            }else if( h.size() == 2){
                
                h.push_back(uv.first);
            }else{
                throw std::runtime_error("unexpeted sorted values in three of a kind\n");
            }
        }

        // add them in the right order
        fine_comp_values.push_back(highest_double);
        std::sort(h.begin(), h.end(), std::greater<>());
        fine_comp_values.insert(fine_comp_values.end(), h.begin(), h.end());
       
    }else { // high_card

        for(size_t i = 0; i < 5; ++i){
            fine_comp_values.push_back(
                    m_sorted_cards[4-i].value()
                    );
        }
    }

    // return final answer
    return fine_comp_values;

}


bool Hand::operator> (const Hand& rhs) const 
{
    int rough_comparison = this->getHandName() - rhs.getHandName();
    if( rough_comparison  > 0 ){
        return true;
    }else if( rough_comparison < 0) {
        return false;
    }else{ // kickers etc.
        auto left_kickers = this->getFineComparisonValues();
        auto right_kickers = rhs.getFineComparisonValues(); 
        int tmp_fine_comp;

        for(size_t i = 0; i < left_kickers.size(); ++i){

            tmp_fine_comp = left_kickers[i] - right_kickers[i]; 
            if( tmp_fine_comp > 0 )
                return true;
            else if( tmp_fine_comp < 0 )
                return false;
        }

        // if every kicker is the same here, then they're the same hand
        return false;
    }   
}



bool Hand::operator== (const Hand& rhs) const
{
    int rough_comparison = this->getHandName() - rhs.getHandName();
    if( rough_comparison  != 0 ){
        return false;
    }else{ 
        
        // iterate over all kicker comparisons
        auto left_kickers = this->getFineComparisonValues();
        auto right_kickers = rhs.getFineComparisonValues(); 

        for(size_t i = 0; i < left_kickers.size(); ++i){
            if( left_kickers[i] != right_kickers[i] )
                return false;
        }

        // return true if it got through everything
        return true;
    }   
} 


bool Hand::operator< (const Hand& rhs) const
{
    return rhs > *this;
}


bool Hand::operator>= (const Hand& rhs) const
{
    return !(rhs > *this);
}

    
bool Hand::operator<= (const Hand& rhs) const
{
    return !(*this > rhs);
}


bool Hand::operator!= (const Hand& rhs) const
{
    return !(*this == rhs);
} 

