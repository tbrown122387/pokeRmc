#include <Rcpp.h>
using namespace Rcpp;

#include "simulator.h"


//' Calculate pre-flop probability estimates
//' 
//' @param your_cards your cards as a length-4 character vector.
//' @param num_sims number of simulations.
//' @param num_folders number of folders.
//' @param num_oppo number of opponents.
//' @return a character vector
//' @export
// [[Rcpp::export]]
CharacterVector preFlopComp(CharacterVector your_cards, IntegerVector num_sims, IntegerVector num_folders,
                            IntegerVector num_oppo) {
  
  unsigned int _num_folders = num_folders[0];
  unsigned int _num_sims = num_sims[0];
  unsigned int _num_oppo = num_oppo[0];
  std::string val1 = Rcpp::as<std::string>(your_cards[0]);
  std::string suit1 = Rcpp::as<std::string>(your_cards[1]);
  std::string val2 = Rcpp::as<std::string>(your_cards[2]);
  std::string suit2 = Rcpp::as<std::string>(your_cards[3]);
  
  double percWon, percTie;
  
  // construct simulator object and add folders  
  Simulator s(_num_sims, _num_oppo); 
  for(size_t i = 0; i < _num_folders; ++i)
    s.addFolder();
  
  // add your cards
  s.addYouCard(Card::fromString(val1, suit1));
  s.addYouCard(Card::fromString(val2, suit2));
  
  // get final numbers
  s.doSim(percWon, percTie);
  
  return CharacterVector::create(s.prettyResults());
}


//' Calculate pre-turn probability estimates
//' 
//' @param your_cards your cards as a length-4 character vector.
//' @param num_sims number of simulations.
//' @param num_folders number of folders.
//' @param num_oppo number of opponents.
//' @param comm_cards community cards.
//' @export
// [[Rcpp::export]]
CharacterVector preTurnComp(CharacterVector your_cards, IntegerVector num_sims, IntegerVector num_folders,
                            IntegerVector num_oppo, CharacterVector comm_cards) {
  
  unsigned int _num_folders = num_folders[0];
  unsigned int _num_sims = num_sims[0];
  unsigned int _num_oppo = num_oppo[0];
  double d_num_sims = static_cast<double>(num_sims[0]);
  std::string val1 = Rcpp::as<std::string>(your_cards[0]);
  std::string suit1 = Rcpp::as<std::string>(your_cards[1]);
  std::string val2 = Rcpp::as<std::string>(your_cards[2]);
  std::string suit2 = Rcpp::as<std::string>(your_cards[3]);
  std::string cc1_val = Rcpp::as<std::string>(comm_cards[0]);
  std::string cc1_suit = Rcpp::as<std::string>(comm_cards[1]);
  std::string cc2_val = Rcpp::as<std::string>(comm_cards[2]);
  std::string cc2_suit = Rcpp::as<std::string>(comm_cards[3]);
  std::string cc3_val = Rcpp::as<std::string>(comm_cards[4]);
  std::string cc3_suit = Rcpp::as<std::string>(comm_cards[5]);
  
  
  // return items
  double percWon, percTie;
  
  // construct simulator object and add folders  
  Simulator s(_num_sims, _num_oppo); 
  for(size_t i = 0; i < _num_folders; ++i)
    s.addFolder();
  
  // add your cards
  s.addYouCard(Card::fromString(val1, suit1));
  s.addYouCard(Card::fromString(val2, suit2));
  
  // add community cards
  s.addCommunityCard(Card::fromString(cc1_val, cc1_suit));
  s.addCommunityCard(Card::fromString(cc2_val, cc2_suit));
  s.addCommunityCard(Card::fromString(cc3_val, cc3_suit));
  
  // get final numbers
  s.doSim(percWon, percTie);
  
  return CharacterVector::create(s.prettyResults());
}


//' Calculate pre-river probability estimates
//' 
//' @param your_cards your cards as a length-4 character vector.
//' @param num_sims number of simulations.
//' @param num_folders number of folders.
//' @param num_oppo number of opponents.
//' @param comm_cards community cards.
//' @export
// [[Rcpp::export]]
CharacterVector preRiverComp(CharacterVector your_cards, IntegerVector num_sims, IntegerVector num_folders,
                             IntegerVector num_oppo, CharacterVector comm_cards) {
  
  unsigned int _num_folders = num_folders[0];
  unsigned int _num_sims = num_sims[0];
  unsigned int _num_oppo = num_oppo[0];
  std::string val1 = Rcpp::as<std::string>(your_cards[0]);
  std::string suit1 = Rcpp::as<std::string>(your_cards[1]);
  std::string val2 = Rcpp::as<std::string>(your_cards[2]);
  std::string suit2 = Rcpp::as<std::string>(your_cards[3]);
  std::string cc1_val = Rcpp::as<std::string>(comm_cards[0]);
  std::string cc1_suit = Rcpp::as<std::string>(comm_cards[1]);
  std::string cc2_val = Rcpp::as<std::string>(comm_cards[2]);
  std::string cc2_suit = Rcpp::as<std::string>(comm_cards[3]);
  std::string cc3_val = Rcpp::as<std::string>(comm_cards[4]);
  std::string cc3_suit = Rcpp::as<std::string>(comm_cards[5]);
  std::string cc4_val = Rcpp::as<std::string>(comm_cards[6]);
  std::string cc4_suit = Rcpp::as<std::string>(comm_cards[7]);
  
  
  // return items
  double percWon, percTie;
  
  // construct simulator object and add folders  
  Simulator s(_num_sims, _num_oppo); 
  for(size_t i = 0; i < _num_folders; ++i)
    s.addFolder();
  
  // add your cards
  s.addYouCard(Card::fromString(val1, suit1));
  s.addYouCard(Card::fromString(val2, suit2));
  
  // add community cards
  s.addCommunityCard(Card::fromString(cc1_val, cc1_suit));
  s.addCommunityCard(Card::fromString(cc2_val, cc2_suit));
  s.addCommunityCard(Card::fromString(cc3_val, cc3_suit));
  s.addCommunityCard(Card::fromString(cc4_val, cc4_suit));
  
  // get final numbers
  s.doSim(percWon, percTie);
  
  return CharacterVector::create(s.prettyResults());
}



//' Calculate post-river probability estimates
//' 
//' @param your_cards your cards as a length-4 character vector.
//' @param num_sims number of simulations.
//' @param num_folders number of folders.
//' @param num_oppo number of opponents.
//' @param comm_cards community cards.
//' @export
// [[Rcpp::export]]
CharacterVector postRiverComp(CharacterVector your_cards, IntegerVector num_sims, IntegerVector num_folders,
                              IntegerVector num_oppo, CharacterVector comm_cards) {
  
  unsigned int _num_folders = num_folders[0];
  unsigned int _num_sims = num_sims[0];
  unsigned int _num_oppo = num_oppo[0];
  std::string val1 = Rcpp::as<std::string>(your_cards[0]);
  std::string suit1 = Rcpp::as<std::string>(your_cards[1]);
  std::string val2 = Rcpp::as<std::string>(your_cards[2]);
  std::string suit2 = Rcpp::as<std::string>(your_cards[3]);
  std::string cc1_val = Rcpp::as<std::string>(comm_cards[0]);
  std::string cc1_suit = Rcpp::as<std::string>(comm_cards[1]);
  std::string cc2_val = Rcpp::as<std::string>(comm_cards[2]);
  std::string cc2_suit = Rcpp::as<std::string>(comm_cards[3]);
  std::string cc3_val = Rcpp::as<std::string>(comm_cards[4]);
  std::string cc3_suit = Rcpp::as<std::string>(comm_cards[5]);
  std::string cc4_val = Rcpp::as<std::string>(comm_cards[6]);
  std::string cc4_suit = Rcpp::as<std::string>(comm_cards[7]);
  std::string cc5_val = Rcpp::as<std::string>(comm_cards[8]);
  std::string cc5_suit = Rcpp::as<std::string>(comm_cards[9]);
  
  // return items
  double percWon, percTie;
  
  // construct simulator object and add folders  
  Simulator s(_num_sims, _num_oppo); 
  for(size_t i = 0; i < _num_folders; ++i)
    s.addFolder();
  
  // add your cards
  s.addYouCard(Card::fromString(val1, suit1));
  s.addYouCard(Card::fromString(val2, suit2));
  
  // add community cards
  s.addCommunityCard(Card::fromString(cc1_val, cc1_suit));
  s.addCommunityCard(Card::fromString(cc2_val, cc2_suit));
  s.addCommunityCard(Card::fromString(cc3_val, cc3_suit));
  s.addCommunityCard(Card::fromString(cc4_val, cc4_suit));
  s.addCommunityCard(Card::fromString(cc5_val, cc5_suit));
  
  // get final numbers
  s.doSim(percWon, percTie);
  
  return CharacterVector::create(s.prettyResults());
}
